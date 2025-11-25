/**
* This file is part of the dashboard library
* 
* Copyright 2025 lishiying  lsyeei@163.com
* 
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "bigraphicsscene.h"
#include "filetemplate.h"
#include "graphicsitemgroup.h"
#include "zoneproperty.h"
#include "rectselector.h"
#include <QBuffer>
#include <QXmlStreamWriter>
#include <XmlHelper.h>

#define RECTINFO(rect) "{" << rect.left() << "," << rect.top() << ","\
<< rect.right() << "," << rect.bottom() << "}"

GraphicsItemGroup::GraphicsItemGroup(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsFocusable);
    this->setAcceptHoverEvents(true);
    auto attr = attribute();
    attr->setAspectRatio(true);
    PenProperty pen;
    pen.setStyle(Qt::NoPen);
    attr->setPen(pen);
    connect(this, SIGNAL(itemAddEvent(QGraphicsItem*)), this, SLOT(onItemAdd(QGraphicsItem*)), Qt::QueuedConnection);
    connect(this, &GraphicsItemGroup::editEnableEvent, this,
            &GraphicsItemGroup::receiveEditEnableEvent, Qt::QueuedConnection);
    connect(this, &GraphicsItemGroup::editFinishEvent, this,
            &GraphicsItemGroup::receiveEditFinishEvent, Qt::QueuedConnection);
}

GraphicsItemGroup::GraphicsItemGroup(const QString &xml, QGraphicsItem *parent)
    : GraphicsItemGroup(parent)
{
    parseXML(xml);
}

QString GraphicsItemGroup::classId() const
{
    return "GROUP_2024";
}

QPainterPath GraphicsItemGroup::shapePath() const
{
    QPainterPath path;
    if (mergeType > MergeType::None) {
        QTransform trans;
        float sx = logicRect.width()*1.0/mergedRect.width();
        float sy = logicRect.height()*1.0/mergedRect.height();
        auto center = logicRect.center();
        trans.translate(center.x(), center.y());
        trans.scale(sx, sy);
        path = trans.map(mergedPath);
    } else {
        auto arc  = 0;
        if (attribute()->getRound()) {
            arc = attribute()->getArcSize();
        }
        path.addRoundedRect(logicRect, arc, arc);
    }
    return path;
}

QVariant GraphicsItemGroup::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemChildAddedChange && scene()){
        if (!isParsing){
            // 延迟到下一个消息循环再处理
            emit itemAddEvent(value.value<QGraphicsItem*>());
        }
    } else if (change == QGraphicsItem::ItemChildRemovedChange) {
        // 立即处理，否则图元关联的很多信息会消失
        onItemRemove(value.value<QGraphicsItem*>());
    } else if (change == QGraphicsItem::ItemSelectedHasChanged) {
        if (value.toBool()) {
            setFlag(GraphicsItemFlag::ItemClipsChildrenToShape, false);
        }else{
            setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
        }
    } else if (change == QGraphicsItem::ItemSceneHasChanged && !value.isNull()){
        // 加入 scene
        auto attr = attribute();
        if (attr->getWidth() > 0 || attr->getHeight() > 0) {
            // 重新组合时，宽高及位置无需重新计算
            isParsing = true;
        }
    }
    return AbstractZoneItem::itemChange(change, value);
}

void GraphicsItemGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    auto mousePos = event->pos();
    QGraphicsItem *underMouseItem{nullptr};
    // 打散组合，并记录
    QList<QGraphicsItem*> childs;
    auto items = childItems();
    foreach (auto item, items) {
        if (item == selector) {
            continue;
        }
        // 获取鼠标下的图元
        auto shape = item->shape();
        auto pos = item->pos();
        QTransform trans;
        trans.translate(pos.x(),pos.y());
        shape = trans.map(shape);
        if(underMouseItem == nullptr && shape.contains(mousePos)){
            underMouseItem = item;
        }
        // 记录
        childs << item;
    }
    QPair<QGraphicsItem*, QList<QGraphicsItem*>> redoData{underMouseItem, childs};
    undoTrigger("edit group", {"editGroup", QVariant::fromValue(childs), QVariant::fromValue(redoData)});
}

void GraphicsItemGroup::sizeChanged(QRectF offsetValue)
{
    AbstractZoneItem::sizeChanged(offsetValue);
    adjustChildItemSize(offsetValue);
}

void GraphicsItemGroup::adjustChildItemSize(QRectF rectOffset)
{
    if (rectOffset.left() == 0 && rectOffset.top() == 0 &&
        rectOffset.right() == 0 && rectOffset.bottom() == 0) {
        return;
    }
    auto items = childItems();
    foreach (auto item, items) {
        if (item == selector) {
            continue;
        }
        adjustSubItemSize(item);
    }
}

void GraphicsItemGroup::adjustEnd(AbstractSelector::AdjustType type)
{
    if (type == AbstractSelector::SIZE && (centerOffset.x() != 0 || centerOffset.y() != 0)) {
        adjustChildItemPos(centerOffset);
    }
    AbstractZoneItem::adjustEnd(type);
}

void GraphicsItemGroup::sceneSelectionChanged()
{
    if(!editFlag || endEditSignal){
        // 只有编辑状态才监控子图元选中状态；如果已经收到信号，后续信号自动拒绝
        return;
    }
    if (auto s=dynamic_cast<BIGraphicsScene*>(scene())) {
        if(s->findGroup(this)){
            // 如果存在上级组则等待上级组通知结束编辑状态
            return;
        }
    }
    if (!hasChildSelected()) {
        endEditSignal = true;
        disconnect(scene(), &QGraphicsScene::selectionChanged,
                   this, &GraphicsItemGroup::sceneSelectionChanged);
        // 结束编辑
        auto childs = editingChilds;
        childs.detach();
        auto undoParam = QPair<QGraphicsItem*, QList<QGraphicsItem*>>{nullptr, childs};
        undoTrigger("group edit finished", {"editFinished",QVariant::fromValue(undoParam),QVariant::fromValue(childs)});
    }
}

GraphicsItemGroup::MergeType GraphicsItemGroup::getMergeType() const
{
    return mergeType;
}

void GraphicsItemGroup::setMergeType(MergeType newMergeType)
{
    if (mergeType == newMergeType) {
        return;
    }    // 通知改变
    undoTrigger("set merge type", {"changeMergeType", mergeType, newMergeType});
}

void GraphicsItemGroup::adjustChildItemPos(QPointF offset)
{
    auto childs = childItems();
    foreach (auto item, childs) {
        if (item == selector) {
            continue;
        }
        item->setPos(item->pos() - offset);
    }
}

void GraphicsItemGroup::calcChildItemRatio()
{
    auto childs = childItems();
    foreach (auto item, childs) {
        if (item == selector) {
            continue;
        }

        auto itemRect = item->boundingRect();
        auto mapTopLeft = item->mapToParent(itemRect.topLeft());
        auto mapTopRight = item->mapToParent(itemRect.topRight());
        auto mapBottomLeft = item->mapToParent(itemRect.bottomLeft());
        auto mapBottomRight = item->mapToParent(itemRect.bottomRight());
        // 计算 item 旋转后对应的topLeft和bottomRig
        auto angle = item->rotation();
        angle = fmodf(angle, 360);
        if (angle > 180) {
            angle -= 360;
        }else if(angle < -180){
            angle += 360;
        }

        QPointF leftPt, rightPt, topPt, bottomPt;
        if (angle > 0 && angle <= 90) {
            leftPt = mapBottomLeft;
            rightPt = mapTopRight;
            topPt = mapTopLeft;
            bottomPt = mapBottomRight;
        } else if (angle > 90 && angle <= 180) {
            leftPt = mapBottomRight;
            rightPt = mapTopLeft;
            topPt = mapBottomLeft;
            bottomPt = mapTopRight;
        } else if (angle < -90 && angle > -180) {
            leftPt = mapTopRight;
            rightPt = mapBottomLeft;
            topPt = mapBottomRight;
            bottomPt = mapTopLeft;
        }else if(angle <= 0 && angle > -90){
            leftPt = mapTopLeft;
            rightPt = mapBottomRight;
            topPt = mapTopRight;
            bottomPt = mapBottomLeft;
        }
        // 计算2点的比例
        QVector<qreal> ratios;
        ratios.append((leftPt.x() - logicRect.left())/logicRect.width());
        ratios.append((leftPt.y() - logicRect.top())/logicRect.height());
        ratios.append((rightPt.x() - logicRect.left())/logicRect.width());
        ratios.append((rightPt.y() - logicRect.top())/logicRect.height());

        ratios.append((topPt.x() - logicRect.left())/logicRect.width());
        ratios.append((topPt.y() - logicRect.top())/logicRect.height());
        ratios.append((bottomPt.x() - logicRect.left())/logicRect.width());
        ratios.append((bottomPt.y() - logicRect.top())/logicRect.height());
        // 保存比例
        itemRatios[item] = ratios;
    }
}

void GraphicsItemGroup::adjustSubItemSize(QGraphicsItem * const item)
{
    auto angle = item->rotation();
    angle = fmodf(angle, 360);
    if (angle > 180) {
        angle -= 360;
    }else if(angle < -180){
        angle += 360;
    }

    // 计算2点的比例
    QVector<qreal> ratios = itemRatios[item];
    // 按比例计算2点新位置
    QPointF leftPt{logicRect.left() + logicRect.width()*ratios[0],
                   logicRect.top() + logicRect.height()*ratios[1]};
    QPointF rightPt{logicRect.left() + logicRect.width()*ratios[2],
                    logicRect.top() + logicRect.height()*ratios[3]};
    QPointF topPt{logicRect.left() + logicRect.width()*ratios[4],
                   logicRect.top() + logicRect.height()*ratios[5]};
    QPointF bottomPt{logicRect.left() + logicRect.width()*ratios[6],
                    logicRect.top() + logicRect.height()*ratios[7]};

    leftPt = item->mapFromParent(leftPt);
    rightPt = item->mapFromParent(rightPt);
    topPt = item->mapFromParent(topPt);
    bottomPt = item->mapFromParent(bottomPt);
    // 计算item偏移
    QPointF newTopLeft, newBottomRight;
    if (angle > 0 && angle <= 90) {
        newTopLeft = QPointF{leftPt.x(), topPt.y()};
        newBottomRight = QPointF{rightPt.x(), bottomPt.y()};
    } else if (angle > 90 && angle <= 180) {
        newTopLeft = QPointF{rightPt.x(), bottomPt.y()};
        newBottomRight = QPointF{leftPt.x(), topPt.y()};
    } else if (angle < -90 && angle > -180) {
        newTopLeft = QPointF{bottomPt.x(), leftPt.y()};
        newBottomRight = QPointF{topPt.x(), rightPt.y()};
    } else if (angle <= 0 && angle > -90) {
        newTopLeft = QPointF{leftPt.x(), topPt.y()};
        newBottomRight = QPointF{rightPt.x(), bottomPt.y()};
    }

    auto width = newBottomRight.x() - newTopLeft.x();
    auto height = newBottomRight.y() - newTopLeft.y();
    if (width < 0){
        width = 0;
        newTopLeft.setX(newBottomRight.x());
    }
    if (height < 0) {
        height = 0;
        newTopLeft.setY(newBottomRight.y());
    }
    if (typeid(*item) == typeid(GraphicsItemGroup)) {
        auto obj = dynamic_cast<GraphicsItemGroup*>(item);
        if (obj) {
            auto itemRect = item->boundingRect();
            QRectF itemOffset{0,0,0,0};
            itemOffset.adjust(newTopLeft.x() - itemRect.left(),
                              newTopLeft.y() - itemRect.top(),
                              newBottomRight.x() - itemRect.right(),
                              newBottomRight.y() - itemRect.bottom());
            obj->setSize({width,height});
            obj->setPos(item->mapToParent(QPointF{newTopLeft.x() + width/2,
                                                  newTopLeft.y() + height/2}));
            obj->adjustChildItemSize({1,1,1,1});
        }
    }else{
        auto obj = dynamic_cast<ICustomGraphic*>(item);
        if (obj) {
            obj->setSize({width, height});
            obj->setPos(item->mapToParent(QPointF{newTopLeft.x() + width/2,
                                                   newTopLeft.y() + height/2}));
        }
    }
}

void GraphicsItemGroup::doMerge(MergeType type)
{
    mergeType = type;

    auto childs = childItems();
    auto attr = attribute();
    attr->setAspectRatio(true);
    PenProperty pen;
    BrushProperty brush;
    if (type == None){
        pen.setStyle(Qt::NoPen);
        attr->setPen(pen);
        brush.setStyle(Qt::NoBrush);
        attr->setBrush(brush);

        foreach (auto item, childs) {
            if (dynamic_cast<QObject*>(item)->objectName() == "RectSelector") {
                continue;
            }
            item->show();
        }
        return;
    }else{
        mergedPath.clear();
        QPainterPath path,interShape;
        foreach (auto item, childs) {
            if (dynamic_cast<QObject*>(item)->objectName() == "RectSelector") {
                continue;
            }
            item->hide();
            auto shape = item->mapToParent(item->shape());
            if (path.isEmpty()) {
                path.addPath(shape);
                interShape.addPath(shape);
                continue;
            }
            switch (type) {
            case Unit:
                path = path.united(shape);
                break;
            case Intersect:
                path = path.intersected(shape);
                break;
            case Subtract:
                path = path.subtracted(shape);
                break;
            case Exclude:
                path = path.united(shape);
                interShape = interShape.intersected(shape);
                break;
            default:
                break;
            }
        }
        if (type == Exclude) {
            path = path.subtracted(interShape);
        }
        path.closeSubpath();
        mergedPath = path.simplified();
        mergedRect = logicRect;
        pen.setStyle(Qt::SolidLine);
        attr->setPen(pen);
        brush.setStyle(Qt::SolidPattern);
        attr->setBrush(brush);
        setSelected(true);
    }
}

void GraphicsItemGroup::editEnabled(QGraphicsItem *item, const QList<QGraphicsItem*> &childs)
{
    setFlag(QGraphicsItem::ItemIsMovable,false);
    // setSelected(false);
    editingChilds = childs;
    editFlag = true;
    editRect = boundingRect();
    auto oldPos = pos();
    QGraphicsItem *selectedItem{item};
    // 打散组合
    foreach (auto child, childs) {
        removeFromGroup(child);
        // 如果存在内部组合，逐级打散
        if (typeid(*child) == typeid(GraphicsItemGroup)) {
            if(auto subGroup = dynamic_cast<GraphicsItemGroup*>(child)){
                subGroup->notifyEditEnable();
                if (child == selectedItem) {
                    // 如果内部选中的图元是组合，交给组合去处理
                    selectedItem = nullptr;
                    setSelected(false);
                }
                subGroupList << subGroup;
                connect(subGroup, &GraphicsItemGroup::editReadyEvent,
                        this, &GraphicsItemGroup::onSubGroupEditReady, Qt::QueuedConnection);
            }
        }
    }
    if (selectedItem) {
        setSelected(false);
        selectedItem->setSelected(true);
    }
    // 保持原位置，标记原位置
    auto attr = attribute();
    attr->setWidth(editRect.width());
    attr->setHeight(editRect.height());
    setPos(oldPos);

    // 监控选中图元变化
    if (subGroupList.isEmpty()) {
        // 不存在内部组合，直接监控 scene 选中变换
        onSubGroupEditReady();
    }
    // 等待内部组合准备好后再监控
}

void GraphicsItemGroup::editFinished(const QList<QGraphicsItem*> &childs)
{
    editingChilds = childs;
    // 先将内部组合复原
    foreach (auto item, childs) {
        if (typeid(*item) == typeid(GraphicsItemGroup)){
            auto subGroup = dynamic_cast<GraphicsItemGroup*>(item);
            subGroup->notifyEditFinished();
            subGroupList << subGroup;
            connect(subGroup, &GraphicsItemGroup::regroupEndEvent,
                    this, &GraphicsItemGroup::onSubgroupRegroupEnd);
        }
    }
    if (subGroupList.isEmpty()) {
        // 不存在下级组合
        onSubgroupRegroupEnd();
    }
    // 内部存在组合，等待内部组合完成的消息
}

void GraphicsItemGroup::onItemAdd(QGraphicsItem *item)
{
    if (item == nullptr || item == selector || typeid(*item) == typeid(RectSelector)){
        return;
    }
    if(selector == nullptr && isSelected()){
        // 此时添加的可能是选择框
        return;
    }
    if (!editingChilds.isEmpty()) {
        // 编辑图元归位后从记录中移除
        editingChilds.removeOne(item);
    }

    auto groupRect = mapToScene(boundingRect()).boundingRect();
    auto itemBound = item->mapToScene(item->boundingRect()).boundingRect();
    groupRect = groupRect.united(itemBound);
    // 调整组的大小及位置
    prepareGeometryChange();
    adjustGroup(groupRect);
    updateSelector();
    updateForm();
    // 编辑状态是否结束
    if (editFlag && isEditEnd()){
        editFlag = false;
        endEditSignal = false;
        setFlag(QGraphicsItem::ItemIsMovable);
        update();
        // 触发
        setSelected(true);
        emit regroupEndEvent();
    }
}

void GraphicsItemGroup::onItemRemove(QGraphicsItem *item)
{
    if (item == nullptr || item == selector){
        return;
    }
    if (item->scene() == nullptr){
        // 从 scene 中删除的图元，不处理
        return;
    }
    item->show();
    item->setRotation(item->rotation() + rotation());

    QRectF groupRect{0,0,0,0};
    auto childs = childItems();
    foreach (auto child, childs) {
        if (child == selector || child == item || typeid(*child) == typeid(RectSelector)) {
            continue;
        }
        groupRect = groupRect.united(child->mapToScene(child->boundingRect()).boundingRect());
    }
    // 调整组的大小及位置
    adjustGroup(groupRect);

}

void GraphicsItemGroup::receiveEditEnableEvent()
{
    if (editFlag) {
        return;
    }
    QGraphicsItem* underMouseItem{nullptr};
    // 打散组合，并记录
    QList<QGraphicsItem*> childs;
    auto items = childItems();
    foreach (auto item, items) {
        if (item == selector) {
            continue;
        }
        // 获取鼠标下的图元
        if (underMouseItem == nullptr && isUnderMouse()) {
            underMouseItem = item;
        }
        // 记录
        childs << item;
    }
    editEnabled(underMouseItem, childs);
}

void GraphicsItemGroup::receiveEditFinishEvent(const QList<QGraphicsItem*> &items)
{
    disconnect(scene(), &QGraphicsScene::selectionChanged,
               this, &GraphicsItemGroup::sceneSelectionChanged);
    editFinished(items);
}

void GraphicsItemGroup::onSubGroupEditReady()
{
    if (!subGroupList.isEmpty()) {
        auto subGroup = dynamic_cast<GraphicsItemGroup*>(sender());
        subGroupList.removeOne(subGroup);
        if (!subGroupList.isEmpty()) {
            // 还有内部组未准备好
            return;
        }
    }
    connect(scene(), &QGraphicsScene::selectionChanged,
            this, &GraphicsItemGroup::sceneSelectionChanged, Qt::QueuedConnection);
    emit editReadyEvent();
}

void GraphicsItemGroup::onSubgroupRegroupEnd()
{
    if (!subGroupList.isEmpty()) {
        auto obj = dynamic_cast<GraphicsItemGroup*>(sender());
        subGroupList.removeOne(obj);
        if (!subGroupList.isEmpty()) {
            return;
        }
    }
    disconnect(this, SLOT(onSubgroupRegroupEnd()));
    // 恢复组的初始状态
    auto attr = attribute();
    attr->setWidth(0);
    attr->setHeight(0);
    logicRect = attr->getLogicRect();
    prepareGeometryChange();
    // 执行本级组合
    foreach (auto item, editingChilds) {
        if(item->scene() == nullptr){
            // 已被删除
            continue;
        }
        item->setSelected((false));
        // 自动触发 group 大小改变
        addToGroup(item);
    }
}

void GraphicsItemGroup::adjustGroup(const QRectF &boundRect)
{
    prepareGeometryChange();
    // 更新属性
    auto attr = attribute();
    attr->setWidth(boundRect.width());
    attr->setHeight(boundRect.height());
    attr->setPos(boundRect.center());
    logicRect = attr->getLogicRect();

    // 调整中心位置
    auto offset = boundRect.center() - pos();
    setPos(boundRect.center());
    // 调整内部图元位置
    adjustChildItemPos(offset);
    // 计算并保存初始比例，用于后续缩放
    calcChildItemRatio();
}

void GraphicsItemGroup::customUndoAction(QString action, QVariant data, bool isUndo)
{
    if (action.compare("changeMergeType") == 0) {
        auto type = data.value<MergeType>();
        doMerge(type);
    } else  if (action.compare("size") == 0) {
        copyProperty(data, attributes[attrIndex]);
        // 设定尺寸变化
        QRectF offsetValue{1,1,1,1};
        logicRect = attribute()->getLogicRect();
        // 调整子图元尺寸
        adjustChildItemSize(offsetValue);
        return;
    } else if(action.compare("editGroup") == 0) {
        if (isUndo) {
            emit editFinishEvent(data.value<QList<QGraphicsItem*>>());
        }else{
            auto params = data.value<QPair<QGraphicsItem*, QList<QGraphicsItem*>>>();
            editEnabled(params.first, params.second);
        }
    } else if(action.compare("editFinished") == 0) {
        if (isUndo) {
            auto params = data.value<QPair<QGraphicsItem*, QList<QGraphicsItem*>>>();
            editEnabled(params.first, params.second);
        } else{
            emit editFinishEvent(data.value<QList<QGraphicsItem*>>());
        }
    }
    AbstractZoneItem::customUndoAction(action, data, isUndo);
}

QString GraphicsItemGroup::toXml() const
{
    typedef XmlTemplate::shapesTemplate::groupTemplate groupTemplate;
    QString data;
    QXmlStreamWriter xml(&data);
    xml.writeStartElement(groupTemplate::index);
    xml.writeCharacters(QString::asprintf("%d", attrIndex));
    xml.writeEndElement();
    xml.writeStartElement(groupTemplate::property);
    QByteArray array;
    QDataStream stream(&array, QIODeviceBase::WriteOnly);
    int count = attributes.count();
    stream << count;
    foreach (auto attr, attributes) {
        stream << *attr;
    }
    stream << transform() << mergeType << mergedPath << mergedRect;
    xml.writeCDATA(array.toHex());
    xml.writeEndElement();

    xml.writeStartElement(groupTemplate::childs);
    xml.writeCharacters("");
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    data += biScene->toXml(childItems());
    xml.writeEndElement();

    return data;
}

void GraphicsItemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    AbstractZoneItem::paint(painter, option, widget);
    // if(editFlag){
    //     // 设置编辑模式的样式
    //     painter->save();
    //     auto pen = painter->pen();
    //     pen.setStyle(Qt::DashLine);
    //     pen.setColor(Qt::red);
    //     pen.setWidth(2);
    //     painter->setPen(pen);
    //     // auto brush = painter->brush();
    //     // brush.setStyle(Qt::SolidPattern);
    //     // brush.setColor(Qt::yellow);
    //     // painter->setBrush(brush);
    //     painter->setOpacity(0.2);
    //     painter->drawRect(editRect);
    //     painter->restore();
    // }
}

bool GraphicsItemGroup::isEditing()
{
    return editFlag;
}

void GraphicsItemGroup::notifyEditEnable()
{
    emit editEnableEvent();
}

void GraphicsItemGroup::notifyEditFinished()
{
    emit editFinishEvent(editingChilds);
}

bool GraphicsItemGroup::hasChildSelected()
{
    bool hasSelected{false};
    foreach (auto item, editingChilds) {
        if (typeid(*item) == typeid(GraphicsItemGroup)){
            if(auto subGroup=dynamic_cast<GraphicsItemGroup*>(item)) {
                if(subGroup->hasChildSelected()){
                    hasSelected = true;
                    break;
                }
            }
        }else if (item->isSelected()) {
            hasSelected = true;
            break;
        }
    }
    return hasSelected;
}

bool GraphicsItemGroup::isEditEnd()
{
    if(editingChilds.isEmpty()){
        return true;
    }
    bool result{true};
    foreach (auto item, editingChilds) {
        if(item->scene()){
            // 还有未归位的图元
            result = false;
            break;
        }
    }
    return result;
}

void GraphicsItemGroup::parseXML(const QString &xml)
{
    isParsing = true;
    QTransform trans;
    auto array = xml.toUtf8();
    QBuffer buf(&array);
    buf.open(QIODeviceBase::ReadOnly);
    QXmlStreamReader reader(&buf);
    typedef XmlTemplate::shapesTemplate::groupTemplate groupTemplate;
    while (!reader.atEnd()) {
        reader.readNext();
        auto name = reader.name();
        if (!reader.isStartElement()) {
            continue;
        }
        if (name.compare(groupTemplate::index) == 0) {
            reader.readNext();
            if (reader.isCharacters()){
                attrIndex = reader.text().toInt();
            }
        } else if (name.compare(groupTemplate::property) == 0) {
            reader.readNext();
            if (reader.isCDATA()){
                auto data = reader.text();
                QByteArray array =  QByteArray::fromHex(data.toLocal8Bit());
                QDataStream stream(&array, QIODeviceBase::ReadOnly);
                int count;
                stream >> count;
                for(int i=0; i<count; i++){
                    auto attr = newProperty();
                    stream >> *attr;
                    attributes[i] = attr;
                }
                stream >> trans >> mergeType >> mergedPath >> mergedRect;
            }
        } else if (name.compare(groupTemplate::childs) == 0) {
            auto items = BIGraphicsScene::toItems(XmlHelper::rawText(&reader, false));
            // 不触发group边框计算
            setSelected(true);
            foreach (auto item, items) {
                item->setFlag(GraphicsItemFlag::ItemIsSelectable);
                item->setFlag(GraphicsItemFlag::ItemIsMovable);
                item->setFlag(GraphicsItemFlag::ItemIsFocusable);
                addToGroup(item);
            }
            auto attr = attribute();

            PenProperty pen;
            BrushProperty brush;
            if (mergeType != None){
                pen.setStyle(Qt::SolidLine);
                attr->setPen(pen);
                brush.setStyle(Qt::SolidPattern);
                attr->setBrush(brush);

                foreach (auto item, items) {
                    if (dynamic_cast<QObject*>(item)->objectName() == "RectSelector") {
                        continue;
                    }
                    item->hide();
                }
            }
            setPos(attr->getPos());
            logicRect = attr->getLogicRect();
            setRotation(attr->getRotate());
            setTransform(trans);
            calcChildItemRatio();
            updateSelector();
        }
    }
    buf.close();
    isParsing = false;
}

void GraphicsItemGroup::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    auto old = dynamic_cast<const ZoneProperty*>(&oldAttr);
    auto current = dynamic_cast<const ZoneProperty*>(&newAttr);
    auto offsetX = current->getWidth() - old->getWidth();
    auto offsetY = current->getHeight() - old->getHeight();
    if (offsetX !=0 || offsetY != 0) {
        adjustChildItemSize({0,0,offsetX,offsetY});
    }
    AbstractZoneItem::attributeChanged(oldAttr, newAttr);
}
