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
        auto item = value.value<QGraphicsItem*>();
        if (item && !isSelected() && !isParsing) {
            auto itemBound = item->mapToScene(item->boundingRect()/*shape()*/).boundingRect();
            if (rect.isEmpty()) {
                rect = itemBound;
            }else{
                rect = rect.united(itemBound);
            }
            auto attr = attribute();
            attr->setWidth(rect.width());
            attr->setHeight(rect.height());
            attr->setPos(rect.center());
            logicRect = attr->getLogicRect();
            updateForm();
        }
    }
    if (change == QGraphicsItem::ItemChildRemovedChange) {
        auto item = value.value<QGraphicsItem*>();
        if (item == nullptr || item == selector){
            return AbstractZoneItem::itemChange(change, value);
        }
        item->show();
        item->setRotation(item->rotation() + rotation());
    }
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        // 首次选中，切换子图元坐标到grop坐标
        if (firstSelected) {
            setPos(rect.center());
            adjustChildItemPos(rect.center());
            firstSelected = false;
            // 计算并保存初始比例，用于后续缩放
            calcChildItemRatio();
        }
        if (value.toBool()) {
            setFlag(GraphicsItemFlag::ItemClipsChildrenToShape, false);
        }else{
            setFlag(GraphicsItemFlag::ItemClipsChildrenToShape);
        }
    }
    return AbstractZoneItem::itemChange(change, value);
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
            obj->sizeChanged(itemOffset);
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


void GraphicsItemGroup::customUndoAction(QString action, QVariant data, bool isUndo)
{
    Q_UNUSED(isUndo)
    if (action.compare("changeMergeType") == 0) {
        auto type = data.value<MergeType>();
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


void GraphicsItemGroup::parseXML(const QString &xml)
{
    isParsing = true;
    QTransform trans;
    // auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
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
            firstSelected = false;
            setPos(attr->getPos());
            logicRect = attr->getLogicRect();
            rect = logicRect;
            rect.moveCenter(attr->getPos());
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
