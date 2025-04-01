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

#include "abstractlinepath.h"
#include "linepathproperty.h"
#include "lineselector.h"
#include <QGraphicsScene>
/**
 * AbstractLinePath 继承自AbstractItem， 但是不使用UndoStack, 与撤销相关的代码失效
 */

AbstractLinePath::AbstractLinePath(QGraphicsItem *parent)
    : IMovePath(parent)
{
    // 不跟随父节点变换
    // setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    attributes[0] = newProperty();
    attributes[0]->setId(0);
    attributes[0]->setName("default");
    attrIndex = 0;
    oldAttr = newProperty();
    auto pen = attribute()->getPen();
    pen.setColor(Qt::lightGray);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);
    attribute()->setPen(pen);
}

AbstractLinePath::~AbstractLinePath()
{}

void AbstractLinePath::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-40,40});
    attr->appendPoint({40, -40});
    setSize({80,80});
}

LinePathProperty *AbstractLinePath::attribute() const
{
    auto attr = attributes[attrIndex];
    return dynamic_cast<LinePathProperty*>(attr);
}

QRectF AbstractLinePath::boundingRect() const
{
    qreal offset = attribute()->getPen().getWidth();
    return logicRect.adjusted(-offset, -offset, offset, offset);
}

QPainterPath AbstractLinePath::shape() const
{
    return shapePath();
}

void AbstractLinePath::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    auto attr = attribute();
    auto pen = attr->getPen().getPen();


    painter->setPen(pen);
    QBrush brush(pen.color(), Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::VerticalSubpixelPositioning);

    drawEndType(painter);

    auto path = linePath(attr->getPoints());
    painter->setBrushOrigin(path.boundingRect().topLeft());
    painter->strokePath(path, pen);

    // pen.setColor(Qt::red);
    // painter->setPen(pen);
    // brush.setStyle(Qt::NoBrush);
    // painter->setBrush(brush);
    // painter->drawRect(boundingRect());

    painter->restore();
}

void AbstractLinePath::setSize(const QSizeF &size)
{
    auto attr = attribute();
    attr->setWidth(size.width());
    attr->setHeight(size.height());
    // 按比例调整所有点的位置
    if (!logicRect.isEmpty()) {
        auto xRatio = size.width() / logicRect.width();
        auto yRatio = size.height() / logicRect.height();
        auto list = attr->getPointList();qDebug() << xRatio << yRatio;
        foreach (auto item, list) {
            attr->updatePoint(item.id, {item.pt.x() * xRatio, item.pt.y()*yRatio});
        }
    }

    updateGraphic();
    updateForm();
    updateSelector();
}

QPainterPath AbstractLinePath::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    path.addPolygon(points);
    return path;
}

QPainterPath AbstractLinePath::startShape() const
{
    return startType;
}

QPainterPath AbstractLinePath::endShape() const
{
    return endType;
}

QPainterPath AbstractLinePath::path()
{
    auto attr = attribute();
    auto path = linePath(attr->getPoints());
    // return path;
    auto pos = attr->getPos();
    QTransform trans;// = sceneTransform();qDebug() << trans;
    trans.translate(pos.x(), pos.y());
    return trans.map(path);
}

void AbstractLinePath::setMaster(QGraphicsItem *master)
{
    pathOwner = master;
}

QGraphicsItem *AbstractLinePath::getMaster()
{
    return pathOwner;
}

QPainterPath AbstractLinePath::previewPath(QList<QPointF> points, QVariant args) const
{
    Q_UNUSED(args)
    // auto attr = attribute();
    QPainterPath path = linePath(points);
    // 合并端点path
    path.addPath(startType);
    path.addPath(endType);

    return path;
}

void AbstractLinePath::enableEdit(bool flag)
{
    editable = flag;
}

void AbstractLinePath::enablePreview(bool flag)
{
    previewMode = flag;
}

void AbstractLinePath::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    Q_UNUSED(oldAttr)
    auto newItem = dynamic_cast<const LinePathProperty&>(newAttr);
    logicRect = newItem.getLogicRect();
    setPos(newItem.getPos());
    updateSelector();
}

void AbstractLinePath::attributeSwitched(int oldIndex, int newIndex)
{
    Q_UNUSED(oldIndex)
    Q_UNUSED(newIndex)
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    setPos(attr->getPos());
}

AbstractSelector *AbstractLinePath::createSelector()
{
    auto pointList = attribute()->getPointList();
    auto s = new LineSelector(pointList, this);
    s->enableEdit(editable);
    s->setPreviewMode(previewMode);
    connect(s, SIGNAL(pointMoved(QString,QPointF)), this, SLOT(onPointMoved(QString,QPointF)));
    connect(s, SIGNAL(addPoint(QString,QPointF)), this, SLOT(onAddPoint(QString,QPointF)));
    connect(s, SIGNAL(delPoint(QString)), this, SLOT(onDelPoint(QString)));
    connect(s, SIGNAL(pointMoveStart(QString)), this, SLOT(onPointMoveStart(QString)));
    connect(s, SIGNAL(pointMoveEnd(QString)), this, SLOT(onPointMoveEnd(QString)));
    afterCreateSelector(s);
    return s;
}

QVariant AbstractLinePath::attr2Variant(const BaseProperty &attr)
{
    auto data = dynamic_cast<const LinePathProperty*>(&attr);
    if (data == nullptr) {
        return QVariant::fromValue(attr);
    }
    return QVariant::fromValue(*data);
}

void AbstractLinePath::copyProperty(QVariant from, BaseProperty *to)
{
    if (!from.canConvert<LinePathProperty>()) {
        return;
    }
    auto f =from.value<LinePathProperty>();
    auto t = dynamic_cast<LinePathProperty*>(to);
    if (t == nullptr) {
        return;
    }
    t->copy(f);
}

void AbstractLinePath::updateSelector()
{
    auto s = dynamic_cast<LineSelector*>(selector);
    if (s == nullptr) {
        return;
    }
    s->updatePoints(attribute()->getPointList());
    if (editable) {
        s->updateEditPoint(createEditPoint());
    }
}

void AbstractLinePath::updateGraphic()
{
    auto attr = attribute();
    if (!pointMoveFlag) {
        updatePos();
    }
    auto points = attr->getPoints();
    QPainterPath path = linePath(points);
    auto rect = path.boundingRect();
    logicRect = rect;
    // 更新起始端和终端断点位置及旋转角度
    createStartType(points[0]);
    auto angle = path.angleAtPercent(1-path.percentAtLength(1));
    createEndType(points.last(), -angle);
    path.addPath(startType);
    path.addPath(endType);

    // 更新logicRect
    rect = path.boundingRect();
    logicRect = rect;
    update();
    if (initStatge == FINISHED) {
        emit pathChanged();
    }
}

QPainterPath AbstractLinePath::shapePath() const
{
    auto attr = attribute();
    QPainterPath path = linePath(attr->getPoints());
    // 合并端点path
    path.addPath(startType);
    path.addPath(endType);

    return path;
}

void AbstractLinePath::customUndoAction(QString action, QVariant data, bool isUndo)
{
    Q_UNUSED(action)
    Q_UNUSED(data)
    Q_UNUSED(isUndo)
}

BaseProperty *AbstractLinePath::newProperty()
{
    auto attr = new LinePathProperty();
    if (attrIndex >=0 && attributes[attrIndex] != nullptr){
        attr->copy(*attribute());
        attr->setId(-1);
        attr->setName("");
    }
    return attr;
}

void AbstractLinePath::parseXML(const QString &xml)
{
    AbstractItem::parseXML(xml);
    setPos(attribute()->getPos());
    initStatge = FINISHED;
    updateGraphic();
    emit pathChanged();
}

bool AbstractLinePath::sceneEvent(QEvent *event)
{
    if (initStatge == DISABLED && event->type() == QEvent::GrabMouse){
        auto attr = attribute();
        if (predefine) {
            // create item by predefined
            createPredefinedItem();
            initEnd();
        }else{
            // create item by draw
            attr->appendPoint({0,0});
            onAddPoint("",{-1,-1});
            setSelected(true);
            initStatge = CAPTURED;
        }
        event->accept();
        return true;
    }
    if (event->type() == QEvent::GraphicsSceneMouseMove){
        if (initStatge == CAPTURED || initStatge == DRAWING){
            // 初始化阶段
            auto mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
            auto pos = mEvent->scenePos();
            auto lastPoint = attribute()->getPointList().back();
            onPointMoved(lastPoint.id, pos);
            initStatge = DRAWING;
            setSelected(true);
            event->accept();
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseDoubleClick){
        if(initStatge == DRAWING){
            auto attr = attribute();
            auto list = attr->getPointList();
            beforeDelPoint(list.back().id);
            attr->removePoint(list.back().id);
            initEnd();
            event->accept();
            return true;
        }
    }else if (event->type() == QEvent::GraphicsSceneMousePress){
        auto mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        if (initStatge == DRAWING) {
            if (mEvent->button() == Qt::RightButton) {
                initEnd();
            } else if(mEvent->button() == Qt::LeftButton){
                auto attr = attribute();
                if(singleFlag && attr->getPointCount() == pointUpperLimit){
                    // 绘制单条线段
                    initEnd();
                } else {
                    onAddPoint("", mEvent->pos());
                }
            }
            event->accept();
            return true;
        }
    }
    return AbstractItem::sceneEvent(event);
}

QVariant AbstractLinePath::itemChange(GraphicsItemChange change, const QVariant &value)
{
    auto result = AbstractItem::itemChange(change, value);
    if (change == QGraphicsItem::ItemPositionChange) {
        if (initStatge != FINISHED) {
            if (attribute()->getPos() != QPointF{0,0}) {
                return attribute()->getPos();
            }
        }
    }
    if (change == ItemPositionHasChanged) {
        attribute()->setPos(pos());
        emit pathChanged();
    } else if(change == ItemRotationHasChanged){
        attribute()->setRotate(rotation());
    } else if (change ==QGraphicsItem::ItemTransformHasChanged){
        updateSelector();
    } else if(initStatge == DISABLED && change == QGraphicsItem::ItemSceneHasChanged && !value.isNull()){
        // 加入scene后首先捕获鼠标
        grabMouse();
    }
    return result;
}

void AbstractLinePath::setSingle(int pointNumber)
{
    if (pointNumber > 0){
        singleFlag = true;
        pointUpperLimit = pointNumber;
    } else {
        singleFlag = false;
        pointUpperLimit = 0;
    }
}

void AbstractLinePath::afterInit()
{

}

void AbstractLinePath::afterPointMoved(const QString &id)
{
    Q_UNUSED(id)
}

void AbstractLinePath::afterPointMoveEnd()
{

}

void AbstractLinePath::beforeAddPoint(const QString &id, const QPointF &pos)
{
    Q_UNUSED(id)
    Q_UNUSED(pos)
}

void AbstractLinePath::beforeDelPoint(const QString &id)
{
    Q_UNUSED(id)
}

void AbstractLinePath::onPointMoved(const QString &id, const QPointF &pos)
{
    prepareGeometryChange();
    auto attr = attribute();
    attr->updatePoint(id, mapFromScene(pos));
    // 点移动后的处理
    afterPointMoved(id);
    updateGraphic();
    updateForm();
    updateSelector();
}

void AbstractLinePath::onAddPoint(const QString &id, const QPointF &pos)
{
    beforeAddPoint(id, pos);
    // attribute()->insertPoint(pos, id);
    // updateGraphic();
    // updateForm();
    // updateSelector();

    if (attribute()->getPointCount() < 2) {
        attribute()->insertPoint(pos, id);
        updateGraphic();
        updateForm();
        updateSelector();
        return;
    }
    // 更新属性
    auto attr = LinePathProperty();
    attr.copy(*attribute());
    attr.insertPoint(pos, id);
    updateAttribute(&attr);
}

void AbstractLinePath::onDelPoint(const QString &id)
{
    beforeDelPoint(id);
    // attribute()->removePoint(id);
    auto attr = LinePathProperty();
    attr.copy(*attribute());
    attr.removePoint(id);
    updateAttribute(&attr);
}

void AbstractLinePath::onPointMoveStart(const QString &id)
{
    Q_UNUSED(id)
    // 记录调整前矩形属性
    oldAttr->copy(*attributes[attrIndex]);
    pointMoveFlag = true;
}

void AbstractLinePath::onPointMoveEnd(const QString &id)
{
    Q_UNUSED(id)
    pointMoveFlag = false;
    undoTrigger("update attribute", {"updateAttr", attr2Variant(*oldAttr), attr2Variant(*attribute())});
}


void AbstractLinePath::syncLogicRect()
{
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    updateSelector();
}

void AbstractLinePath::createStartType(const QPointF &center)
{
    startType.clear();
    QRectF rect{0,0,8,8};
    rect.moveCenter(center);
    startType.addEllipse(rect);
}

void AbstractLinePath::createEndType(const QPointF &end, qreal angle)
{
    endType.clear();
    int r = 6;
    endType.moveTo({end.x(),end.y()-r});
    endType.lineTo({end.x(),end.y()+r});
    endType.moveTo(end);
    endType.lineTo({end.x()-r,end.y()-r});
    endType.lineTo({end.x()-r,end.y()+r});
    endType.lineTo(end);
    endType.closeSubpath();
    QTransform trans;
    trans.translate(end.x(), end.y());
    trans.rotate(angle);
    trans.translate(-end.x()+r, -end.y());
    endType = trans.map(endType);
}


void AbstractLinePath::initEnd()
{
    initStatge = FINISHED;
    ungrabMouse();
    afterInit();

    // 更新图元位置及大小
    // updatePos(attribute());
    updateGraphic();
    setSelected(true);
    updateForm();
    updateSelector();
}

void AbstractLinePath::drawEndType(QPainter *painter)
{
    QPen pen = painter->pen();
    QBrush brush = painter->brush();
    painter->save();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::green);
    painter->strokePath(startType, pen);
    painter->fillPath(startType, brush);
    pen.setColor(Qt::red);
    painter->strokePath(endType, pen);
    painter->fillPath(endType, brush);
    painter->restore();
}


void AbstractLinePath::updatePos()
{
    // 初始化完成前不调整图元位置
    if (initStatge != FINISHED) {
        return;
    }
    auto attr = attribute();
    auto points = attr->getPoints();
    QPainterPath path = linePath(points);
    auto rect = path.boundingRect();
    auto center = rect.center();
    if (center.x() != 0 || center.y() != 0) {
        auto offset = center - QPointF{0,0};
        auto pointList = attr->getPointList();
        foreach (auto item, pointList) {
            // 根据新原点，调整线条上的其它点的位置
            attr->updatePoint(item.id, item.pt - offset);
        }
        center = mapToParent(center);
        setPos(center);
        attr->setWidth(logicRect.width());
        attr->setHeight(logicRect.height());
        attr->setPos(center);
    }
    logicRect = attr->getLogicRect();
}

QList<NamedPoint> AbstractLinePath::createEditPoint()
{
    QList<NamedPoint> editPoints;
    auto points = attribute()->getPointList();
    QPainterPath path;
    for (int i = 1; i < points.count(); ++i) {
        editPoints << NamedPoint{points[i].id,(points[i-1].pt + points[i].pt)/2};
    }
    return editPoints;
}
