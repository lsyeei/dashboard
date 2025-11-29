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
#include "graphicsitemgroup.h"
#include "graphicrootwidget.h"
#include "igraphicplugin.h"
#include <QDebug>
#include <QEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QWidget>
#include <QObject>
#include <QFocusEvent>
#include <QXmlStreamWriter>
#include <QThread>
#include <xmlHelper.h>
#include <QBuffer>
#include <QGuiApplication>
#include <QClipboard>
#include "filetemplate.h"
#include "snowflake.h"

int BIGraphicsScene::itemIdIndex = 0;
int BIGraphicsScene::itemNameIndex = 1;
int BIGraphicsScene::itemHideFlag = 2;
int BIGraphicsScene::itemGroupFlag = 3;

BIGraphicsScene::BIGraphicsScene(QObject *parent)
    : IGraphicsScene{parent}/*, UndoObject{}*/
{
    penProperty.setStyle(Qt::DashLine);
    penProperty.setColor(0x424242);
    penProperty.setWidth(0.5);
    brushProperty.setStyle(Qt::SolidPattern);
    brushProperty.setColor(0x18141d);
    idGenerator = new SnowFlake();
}

BIGraphicsScene::~BIGraphicsScene()
{
    delete idGenerator;
}

void BIGraphicsScene::refreshBackground(QGraphicsView *view, QPainter *painter)
{
    QPolygonF mapRect = view->mapFromScene(sceneRect());
    auto paintRect = mapRect.boundingRect();
    drawSceneGrid(painter, paintRect);
}

QList<QGraphicsItem *> BIGraphicsScene::toItems(const QString &xmlText)
{
    QList<QGraphicsItem *> items;
    auto array = xmlText.toUtf8();
    QBuffer buf(&array);
    buf.open(QIODeviceBase::ReadOnly);
    QXmlStreamReader xml(&buf);
    while (!xml.atEnd()){
        xml.readNext();
        QStringView itemName = xml.name();
        if (!xml.isStartElement()) {
            continue;
        }
        auto attr = xml.attributes();
        typedef XmlTemplate::shapesTemplate temp;
        if (itemName.compare(temp::group) ==0) {
            auto groupText = XmlHelper::rawText(&xml, false);
            GraphicsItemGroup *group = new GraphicsItemGroup(groupText);
            if (attr.hasAttribute(temp::groupTemplate::groupId)){
                group->setData(itemIdIndex, attr.value(temp::groupTemplate::groupId).toString());
            }
            if (attr.hasAttribute(temp::groupTemplate::groupName)){
                group->setData(itemNameIndex, attr.value(temp::groupTemplate::groupName).toUtf8());
            }
            items.append(group);
        } else if(itemName.compare(temp::item) ==0) {
            typedef XmlTemplate::shapesTemplate::itemTemplate itemTemplate;
            if (attr.hasAttribute(itemTemplate::classId)){
                auto classId = attr.value(itemTemplate::classId);
                auto item = GraphicsManager::instance()->createGraphic(classId.toString(),XmlHelper::rawText(&xml, true));
                if (attr.hasAttribute(itemTemplate::itemId)){
                    item->setData(itemIdIndex, attr.value(itemTemplate::itemId).toString());
                }
                if (attr.hasAttribute(itemTemplate::itemName)){
                    item->setData(itemNameIndex, attr.value(itemTemplate::itemName).toUtf8());
                }
                if (item) {
                    items.append(item);
                }
            }
        }
    }
    buf.close();

    return items;
}

QString BIGraphicsScene::toXml()
{
    return toXml(items(Qt::AscendingOrder));
}

QString BIGraphicsScene::toXml(QList<QGraphicsItem *> items)
{
    QString data;
    QXmlStreamWriter xml(&data);

    typedef XmlTemplate::shapesTemplate node;
    for (int i = 0; i< items.count(); i++) {
        auto item = items[i];
        if (items.contains(item->parentItem())) {
            items.removeAt(i);
            i --;
            continue;
        }
        if (isHide(item)){
            continue;
        }
        if (typeid(*item) == typeid(GraphicsItemGroup)) {
            // group
            GraphicsItemGroup *group = dynamic_cast<GraphicsItemGroup *>(item);
            xml.writeStartElement(node::group);
            xml.writeAttribute(node::groupTemplate::groupId,
                               group->data(itemIdIndex).toString());
            xml.writeAttribute(node::groupTemplate::groupName,
                               group->data(itemNameIndex).toByteArray());
            xml.writeCharacters("");
            data += group->toXml();
            xml.writeEndElement();
        }else{
            auto graphic = dynamic_cast<ICustomGraphic *>(item);
            if (graphic != nullptr) {
                auto id = graphic->data(itemIdIndex).toString();
                auto name = graphic->data(itemNameIndex).toByteArray();
                xml.writeStartElement(node::item);
                xml.writeAttribute(node::itemTemplate::classId, graphic->classId());
                xml.writeAttribute(node::itemTemplate::itemId, id);
                xml.writeAttribute(node::itemTemplate::itemName, name);
                xml.writeCharacters("");
                data += graphic->toXml();
                xml.writeEndElement();
            }
        }
    }
    return data;
}

void BIGraphicsScene::addEditableItem(QGraphicsItem *item)
{
    // 不要使用setFlags，否则CustomGraphicItemInterface内部设置的flag会失效
    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
    item->setFlag(QGraphicsItem::ItemIsFocusable, true);
    QString id = getItemId(item);
    if (id.isEmpty()){
        id = idGenerator->nextIdString();
        setItemId(item, id);
    }
    addItem(item);
    emit contentChanged(ItemAction::ADD, {item});
}

void BIGraphicsScene::addItems(QList<QGraphicsItem *> items)
{
    for(auto item: items){
        addEditableItem(item);
    }
}

void BIGraphicsScene::ungroup(QGraphicsItemGroup *group)
{
    blockSignals(true);
    foreach (QGraphicsItem *item, group->childItems()){
        group->removeFromGroup(item);
        item->setData(itemGroupFlag, QVariant());
        item->setFlag(QGraphicsItem::ItemIsFocusable, true);
        item->setSelected(true);
    }    
    blockSignals(false);
    group->setSelected(false);
    removeItem(group);
    emit contentChanged(ItemAction::UNGROUP, {group});
}

void BIGraphicsScene::group(QGraphicsItemGroup *group, const QList<QGraphicsItem *> &items)
{
    auto groupId = getItemId(group);
    if (groupId.isEmpty()) {
        // 对于新建组，需要分配ID
        groupId = idGenerator->nextIdString();
        setItemId(group, groupId);
    }
    addItem(group);
    blockSignals(true);
    clearSelection();
    for (int i = 0; i < items.count(); ++i) {
        auto item = items[i];
        item->setFlag(QGraphicsItem::ItemIsFocusable, false);
        item->setData(itemGroupFlag, groupId);
        group->addToGroup(item);
    }
    blockSignals(false);
    group->update();
    group->setSelected(true);
    group->setFocus(Qt::MouseFocusReason);
    emit contentChanged(ItemAction::GROUP, {group});
}

bool BIGraphicsScene::canGroup()
{
    auto selectList = selectedItems();
    if (selectList.isEmpty()) {
        return false;
    }
    bool flag{true};
    foreach (auto item, selectList) {
        if (!item->data(itemGroupFlag).isNull()) {
            // 组图元正处于编辑状态，不能执行组合操作
            flag = false;
            break;
        }
    }
    return flag;
}

QGraphicsItem *BIGraphicsScene::findGroup(QGraphicsItem *item)
{
    auto groupFlag = item->data(itemGroupFlag);
    if (groupFlag.isNull()) {
        return nullptr;
    }
    auto id = groupFlag.toString();
    return getItemById(id);
}

void BIGraphicsScene::flipItem(Qt::Orientation orientation)
{
    auto items = selectedItems();
    if (items.isEmpty()) {
        return;
    }
    QTransform trans;
    if (orientation == Qt::Horizontal){
        // 水平翻转
        trans.rotate(180, Qt::YAxis);
    } else {
        // 垂直翻转
        trans.rotate(180, Qt::XAxis);
    }
    items.first()->setSelected(false);
    items.first()->setTransform(trans, true);
    items.first()->setSelected(true);
}

void BIGraphicsScene::setSelectedItemZOrder(OrderAction action)
{
    auto items = selectedItems();
    if (items.isEmpty()) {
        return;
    }
    QPainterPath selectArea;
    foreach (auto item, items) {
        if (selectArea.isEmpty()) {
            selectArea = item->mapToScene(item->shape());
            continue;
        }
        selectArea = selectArea.united(item->mapToScene(item->shape()));
    }
    // 获取选择范围内的所有图元，按照stack 顺序升序排列，既序号小的先绘制，会被序号大的遮挡
    QList<QGraphicsItem *> zoneItems = this->items(selectArea, Qt::IntersectsItemShape, Qt::AscendingOrder);

    if (zoneItems.isEmpty()) {
        return;
    }
    // 移除选择框、group中的子图元及选中的图元
    QList<QGraphicsItem *> removedItems;
    for (int i = 0; i < zoneItems.count(); ++i) {
        if (items.contains(zoneItems[i]->parentItem()) ||
            zoneItems.contains(zoneItems[i]->parentItem()) ||
            removedItems.contains(zoneItems[i]->parentItem())) {
            removedItems.append(zoneItems[i]);
            zoneItems.removeAt(i);
            i --;
        }
    }
    if (zoneItems.count() == items.count()){
        // 不需要修改
        return;
    }

    if (action == OrderAction::TOP) {
        int j = -1;
        for (int i = 0; i < zoneItems.count(); ++i) {
            if (items.contains(zoneItems[i])) {
                if (j < 0) {
                    j = i;
                }
                continue;
            }
            if (j < 0) {
                continue;
            }
            zoneItems[i]->stackBefore(zoneItems[j]);
            updateItem(zoneItems[i]);
        }
        return;
    }
    if (action == OrderAction::BOTTOM) {
        int j = 0;
        for(int i=0; i < zoneItems.count(); i++) {
            if (items.contains(zoneItems[i])) {
                zoneItems[i]->stackBefore(zoneItems[j]);
                updateItem(zoneItems[i]);
            }
        }
        return;
    }
    if (action == OrderAction::UP) {
        int j = -1;
        for(int i=0; i < zoneItems.count(); i++) {
            if (items.contains(zoneItems[i])) {
                if (j<0) {
                    j = i;
                }
                continue;
            }
            if (j>=0) {
                zoneItems[i]->stackBefore(zoneItems[j]);
                updateItem(zoneItems[i]);
                j = -1;
            }
        }
        return;
    }
    if (action == OrderAction::DOWN) {
        int j = -1;
        for(int i=1; i < zoneItems.count(); i++) {
            if (items.contains(zoneItems[i])) {
                if (j < 0){
                    j = i-1;
                }
                zoneItems[i]->stackBefore(zoneItems[j]);
                updateItem(zoneItems[i]);
            } else {
                j = -1;
            }
        }
    }
}

void BIGraphicsScene::setItemsAlign(AlignAction action)
{
    auto items = selectedItems();
    if (items.isEmpty()) {
        return;
    }
    QPainterPath boundRegion;
    QHash<QGraphicsItem *, QPainterPath> shapeMap;
    foreach (auto item, items) {
        auto shape = item->mapToScene(item->shape());
        shapeMap[item] = shape;
        if (boundRegion.isEmpty()) {
            boundRegion = shape;
        }  else {
            boundRegion = boundRegion.united(shape);
        }
    }
    if (action == AlignAction::LEFT){
        // 计算最左坐标
       qreal left = boundRegion.boundingRect().left();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
           auto bound = i.value().boundingRect();
            auto offset = left - bound.left();
           if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
               continue;
            }
           auto item = i.key();
           item->setPos(item->pos() + QPointF{offset, 0});
           item->update();
       }
    }
    if (action == AlignAction::RIGHT){
        // 计算最右坐标
        qreal right = boundRegion.boundingRect().right();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
            auto bound = i.value().boundingRect();
            auto offset = right - bound.right();
            if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
                continue;
            }
            auto item = i.key();
            item->setPos(item->pos() + QPointF{offset, 0});
            item->update();
        }
    }
    if (action == AlignAction::TOP){
        // 计算最上坐标
        qreal top = boundRegion.boundingRect().top();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
            auto bound = i.value().boundingRect();
            auto offset = top - bound.top();
            if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
                continue;
            }
            auto item = i.key();
            item->setPos(item->pos() + QPointF{0, offset});
            item->update();
        }
    }
    if (action == AlignAction::BOTTOM){
        // 计算最下坐标
        qreal bottom = boundRegion.boundingRect().bottom();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
            auto bound = i.value().boundingRect();
            auto offset = bottom - bound.bottom();
            if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
                continue;
            }
            auto item = i.key();
            item->setPos(item->pos() + QPointF{0, offset});
            item->update();
        }
    }
    if (action == AlignAction::HORIZON){
        // 计算中心点y坐标
        qreal y = boundRegion.boundingRect().center().y();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
            auto bound = i.value().boundingRect();
            auto offset = y - bound.center().y();
            if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
                continue;
            }
            auto item = i.key();
            item->setPos(item->pos() + QPointF{0, offset});
            item->update();
        }
    }
    if (action == AlignAction::VERTICAL){
        // 计算中心点x坐标
        qreal x = boundRegion.boundingRect().center().x();
        for (auto i = shapeMap.begin(); i != shapeMap.end(); i++){
            auto bound = i.value().boundingRect();
            auto offset = x - bound.center().x();
            if (qFabs(offset) < std::numeric_limits<qreal>::epsilon()) {
                // 坐标相同时不做调整
                continue;
            }
            auto item = i.key();
            item->setPos(item->pos() + QPointF{offset, 0});
            item->update();
        }
    }
}

void BIGraphicsScene::distributeItems(DistributeAction action)
{
    auto items = selectedItems();
    if (items.isEmpty() || items.count() < 3) {
        return;
    }
    QPainterPath boundRegion;
    QVector<QPair<QGraphicsItem *, QPainterPath>> shapeList;
    QGraphicsItem * last;
    QPainterPath lastShape;
    qreal total = 0;
    // 计算整体位置，并将各个图形按照从左(上）到右（下）的顺序排序
    for (int i=0; i<items.count(); i++) {
        auto item = items[i];
        auto shape = item->mapToScene(item->shape());
        auto x = shape.boundingRect().left();
        if (action == DistributeAction::VERTICAL){
            x = shape.boundingRect().top();
        }
        if (boundRegion.isEmpty()) {
            boundRegion = shape;
            last = item;
            lastShape = shape;
            total = shape.boundingRect().width();
            if (action == DistributeAction::VERTICAL){
                total = shape.boundingRect().height();
            }
        }  else {
            boundRegion = boundRegion.united(shape);
            if (action == DistributeAction::HORIZON){
                total += shape.boundingRect().width();
                if (shape.boundingRect().right() > lastShape.boundingRect().right()) {
                    last = item;
                    lastShape = shape;
                }
            }else{
                total += shape.boundingRect().height();
                if (shape.boundingRect().bottom() > lastShape.boundingRect().bottom()) {
                    last = item;
                    lastShape = shape;
                }
            }
        }
        if (shapeList.isEmpty()) {
            shapeList.append({item, shape});
        }else{
            int i = 0;
            for (i = 0; i < shapeList.count(); ++i) {
                auto x1 = shapeList[i].second.boundingRect().left();
                if (action == DistributeAction::VERTICAL){
                    x1 = shapeList[i].second.boundingRect().top();
                }
                if (x1 > x) {
                    shapeList.insert(i, {item, shape});
                    break;
                }
            }
            if (i == shapeList.count()) {
                shapeList.append({item, shape});
            }
        }
    }
    // 计算并调整图形位置
    qreal blankArea = 0;
    if (action == DistributeAction::HORIZON){
        blankArea = boundRegion.boundingRect().width();
    } else {
        blankArea = boundRegion.boundingRect().height();
    }
    blankArea = blankArea - total;
    qreal space = blankArea / (items.count() - 1);
    for (int i = 1; i <= shapeList.count() - 1; ++i) {
        auto curItem = shapeList[i].first;
        if (curItem == last) {
            shapeList.removeAt(i);
            i --;
            continue;
        }
        auto leftItem = shapeList[i - 1].first;
        auto shape = leftItem->mapToScene(leftItem->shape());
        qreal x = 0,  x0 = 0;
        if (action == DistributeAction::HORIZON){
            x = shapeList[i].second.boundingRect().left();
            x0 = shape.boundingRect().right();
        } else{
            x = shapeList[i].second.boundingRect().top();
            x0 = shape.boundingRect().bottom();
        }
        qreal offset = x0 + space - x;
        if (action == DistributeAction::HORIZON){
            curItem->setPos(curItem->pos() + QPointF{offset, 0});
        } else {
            curItem->setPos(curItem->pos() + QPointF{0, offset});
        }
        updateItem(curItem);
    }
}

void BIGraphicsScene::selectAll(bool flag)
{
    foreach (auto item, items()) {
        auto hideFlag = item->data(itemHideFlag);
        if (hideFlag.isValid() && hideFlag.toInt() == 1){
            continue;
        }
        item->setSelected(flag);
    }
}

void BIGraphicsScene::copyItems()
{
    auto items = selectedItems();
    if (items.isEmpty()) {
        return;
    }
    QString data = "<CopyItems>" + toXml(items) + "</CopyItems>";
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(data);
}

void BIGraphicsScene::cutItems()
{
    auto items = selectedItems();
    if (items.isEmpty()) {
        return;
    }
    QString data = "<CutItems>" + toXml(items) + "</CutItems>";
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(data);
    deleteItems(items);
}

QList<QGraphicsItem *> BIGraphicsScene::pastItems(QPointF pos)
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    auto text = clipboard->text();
    if (text.isEmpty()) {
        return QList<QGraphicsItem *>{};
    }
    // auto newItems = addItems(text);
    bool cutFlag = text.startsWith("<CutItems>");
    bool copyFlag = text.startsWith("<CopyItems>");
    if (!cutFlag && !copyFlag) {
        return QList<QGraphicsItem *>{};
    }
    auto newItems = toItems(text);
    // 修改新图元位置到当前鼠标位置
    QRectF bound;
    foreach(auto item, newItems){
        addEditableItem(item);
        if (bound.isEmpty()) {
            bound = item->sceneBoundingRect();
        }else{
            bound = bound.united(item->sceneBoundingRect());
        }
    }
    QPointF center = bound.center();
    auto offset = pos - center;
    foreach(auto item, newItems){
        // 修改新图元属性
        if (copyFlag) {
            setItemId(item, idGenerator->nextIdString());
            setItemName(item, item->data(itemNameIndex).toByteArray() + "_copy");
        }
        item->setPos(item->pos() + offset);
        updateItem(item);
    }
    if (cutFlag) {
        clipboard->setText("");
    }

    return newItems;
}

void BIGraphicsScene::moveItems(QList<QGraphicsItem *> items, const QPointF offset)
{
    if (items.isEmpty()){
        return;
    }
    foreach (auto item, items) {
        item->setPos(item->pos() + offset);
        updateItem(item);
    }
}

void BIGraphicsScene::deleteItems(QList<QGraphicsItem *> items)
{
    if (items.isEmpty()){
        return;
    }
    foreach (auto item, items) {
        item->setSelected(false);
        removeItem(item);
    }
    emit contentChanged(ItemAction::REMOVE, items);
}

void BIGraphicsScene::undo(QVariant undoData)
{
    doCommand(undoData);
}

void BIGraphicsScene::redo(QVariant redoData)
{
    doCommand(redoData);
}

void BIGraphicsScene::setItemName(QGraphicsItem *item, QString name)
{
    item->setData(itemNameIndex, name);
    emit contentChanged(ItemAction::RENAME, {item});
}

QString BIGraphicsScene::itemName(QGraphicsItem *item)
{
    return item->data(itemNameIndex).toString();
}

void BIGraphicsScene::setItemId(QGraphicsItem *item, const QString &id)
{
    if (id.isEmpty()){
        return;
    }
    item->setData(itemIdIndex, id);
}

QString BIGraphicsScene::getItemId(QGraphicsItem *item)
{
    auto data = item->data(itemIdIndex);
    if (!data.isValid()) {
        return "";
    }
    return data.toString();
}

QGraphicsItem *BIGraphicsScene::getItemById(const QString &id)
{
    if (id.isEmpty()) {
        return nullptr;
    }
    auto itemList = items();
    for(int i=0; i< itemList.count(); i++){
        if (id.compare(getItemId(itemList[i])) == 0) {
            return itemList[i];
        }
    }
    return nullptr;
}

QList<QGraphicsItem *> BIGraphicsScene::sortItems(QList<QGraphicsItem *> itemList, Qt::SortOrder order)
{
    if (itemList.isEmpty()) {
        return itemList;
    }
    auto count = itemList.count();
    QList<QGraphicsItem *> result;
    auto sortedItems = items(order);
    int j = 0;
    for (int i = 0; i < sortedItems.count() && j < count; ++i) {
        if (itemList.contains(sortedItems[i])) {
            result.append(sortedItems[i]);
            j++;
        }
    }
    return result;
}

void BIGraphicsScene::setPainter(const BrushProperty &brush, const PenProperty &pen)
{
    brushProperty = brush;
    penProperty = pen;
}

QPainterPath BIGraphicsScene::getUnitBound(QList<QGraphicsItem *> items)
{
    QPainterPath boundRegion;
    foreach (auto item, items) {
        auto shape = item->mapToScene(item->shape());
        if (boundRegion.isEmpty()) {
            boundRegion = shape;
        }  else {
            boundRegion = boundRegion.united(shape);
        }
    }
    return boundRegion;
}

void BIGraphicsScene::hideItem(QGraphicsItem *item)
{
    item->setData(itemHideFlag, 1);
}

bool BIGraphicsScene::isHide(QGraphicsItem *item)
{
    auto flag = item->data(itemHideFlag);
    if (flag.isValid() && flag.toInt() == 1){
        return true;
    }
    return false;
}

void BIGraphicsScene::setSelectionArea(const QPainterPath &path,
                                       Qt::ItemSelectionOperation selectionOperation,
                                       Qt::ItemSelectionMode mode,
                                       const QTransform &deviceTransform)
{
    auto unselectItems = selectedItems();

    // Disable emitting selectionChanged() for individual items.
    blockSignals(true);
    bool changed = false;

    // Set all items in path to selected.
    const auto items = this->items(path, mode, Qt::DescendingOrder, deviceTransform);
    for (QGraphicsItem *item : items) {
        if (item->flags() & QGraphicsItem::ItemIsSelectable) {
            unselectItems.removeOne(item);
            if (!isHide(item)){
                if (!item->isSelected())
                    changed = true;
                item->setSelected(true);
            }else{
                if (item->isSelected()) {
                    changed = true;
                    item->setSelected(false);
                }
            }
        }
    }

    switch (selectionOperation) {
    case Qt::ReplaceSelection:
        // Deselect all items outside path.
        for (QGraphicsItem *item : std::as_const(unselectItems)) {
            item->setSelected(false);
            changed = true;
        }
        break;
    default:
        break;
    }
    blockSignals(false);
    if (changed)
        emit selectionChanged();
}

QList<QGraphicsItem *> BIGraphicsScene::getGroupItems(QGraphicsItem *group)
{
    QList<QGraphicsItem *> items{group};
    if (typeid(*group) != typeid(GraphicsItemGroup)){
        return items;
    }
    auto childs = group->childItems();
    foreach (auto child, childs) {
        if (typeid(*child) == typeid(QGraphicsItemGroup)) {
            items << getGroupItems(dynamic_cast<QGraphicsItemGroup*>(child));
        }else{
            items << child;
        }
    }
    return items;
}

void BIGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
}

void BIGraphicsScene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);
}

void BIGraphicsScene::drawSceneGrid(QPainter *painter, const QRectF &rect)
{
    painter->save();
    // 绘制背景时，不缩放
    QTransform trans;
    trans.scale(1,1);
    painter->setTransform(trans);
    QColor lineColor;
    painter->setBrush(brushProperty.getBrush(rect.toRect()));
    painter->setBrushOrigin(rect.topLeft());
    lineColor = penProperty.getColor();
    QColor guidesColor(lineColor);
    guidesColor.setAlpha(100);
    auto pen = penProperty.getPen();
    pen.setColor(guidesColor);
    painter->setPen(pen);

    painter->drawRect(rect);

    for (int i = rect.left(); i < rect.right(); i += gridStep) {
        painter->drawLine(QPointF(i, rect.top()), QPointF(i, rect.bottom()));
    }
    for (int i = rect.top(); i <rect.bottom(); i += gridStep) {
        painter->drawLine(QPointF(rect.left(), i), QPointF(rect.right(), i));
    }

    pen.setColor(lineColor);
    painter->setPen(pen);
    for (int i = rect.left(); i < rect.right(); i += gridStep * 4) {
        painter->drawLine(QPointF(i, rect.top()), QPointF(i, rect.bottom()));
    }
    for (int i = rect.top(); i <rect.bottom(); i += gridStep * 4) {
        painter->drawLine(QPointF(rect.left(), i), QPointF(rect.right(), i));
    }
    painter->restore();
}

QRectF BIGraphicsScene::getMapRect(const QRectF &rect)
{
    auto sceneViews = views();
    if (sceneViews.isEmpty()) {
        return rect;
    }
    QGraphicsView *view = sceneViews.first();
    for (auto item : sceneViews){
        if (item->hasFocus()){
            view = item;
            break;
        }
    }
    if (view == nullptr){
        return rect;
    }
    QPolygon mapRect = view->mapFromScene(rect);
    return mapRect.boundingRect();
}

void BIGraphicsScene::updateItem(QGraphicsItem *item)
{
    auto childs = item->childItems();
    foreach (auto child, childs) {
        child->update();
    }
    item->update();
}

void BIGraphicsScene::doCommand(QVariant undoData)
{
    auto data = undoData.value<QPair<QString,QVariant>>();
    typedef QList<QGraphicsItem*> list;
    if (data.first.compare("addItems") == 0){
        // 添加图元
        foreach (auto item, data.second.value<list>()) {
            if (item->scene() == nullptr) {
                addItem(item);
            }
        }
    } else if (data.first.compare("delItems") == 0){
        // 删除图元
        deleteItems(data.second.value<list>());
    } else if (data.first.compare("ungroup") == 0){
        // 解散组
        auto item = data.second.value<list>().first();
        auto obj = dynamic_cast<QGraphicsItemGroup *>(item);
        if (obj){
            ungroup(obj);
        }
    } else if (data.first.compare("group") == 0){
        // 组合
        auto items = data.second.value<list>();
        group(dynamic_cast<QGraphicsItemGroup*>(items[0]), items.sliced(1));
    }else if (data.first.compare("setPos") == 0){
        auto itemsPos = data.second.value<QHash<QGraphicsItem *, QPointF>>();
        for(auto item = itemsPos.begin(); item != itemsPos.end(); ++item){
            item.key()->setPos(item.value());
        }
    }
}

