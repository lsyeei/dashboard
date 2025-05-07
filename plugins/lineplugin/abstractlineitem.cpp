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

#include "abstractlineitem.h"
#include "endtypefactory.h"
#include "linebaseproperty.h"
#include "lineselector.h"
#include <QApplication>
#include <QTimeLine>

AbstractLineItem::AbstractLineItem(QGraphicsItem *parent)
    : AbstractItem(parent)
{
    attributes[0] = newProperty();
    attributes[0]->setId(0);
    attributes[0]->setName("default");
    attrIndex = 0;
    oldAttr = newProperty();
}

AbstractLineItem::~AbstractLineItem()
{
    if (timeLine) {
        delete timeLine;
    }
}

void AbstractLineItem::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-40,40});
    attr->appendPoint({40, -40});
    setSize({80,80});
}

LineBaseProperty *AbstractLineItem::attribute() const
{
    auto attr = attributes[attrIndex];
    return dynamic_cast<LineBaseProperty*>(attr);
}

QRectF AbstractLineItem::boundingRect() const
{
    qreal offset = attribute()->getPen().getWidth();
    return logicRect.adjusted(-offset, -offset, offset, offset);
}

QPainterPath AbstractLineItem::shape() const
{
    return shapePath();
}

void AbstractLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    auto attr = attribute();
    auto pen = attr->getPen().getPen();
    if (attr->getFlowAnimation()) {
        pen.setStyle(Qt::CustomDashLine);
        auto penWidth = pen.width();
        qreal dash = (attr->getDashLen() * attr->getDashRatio())/penWidth;
        qreal space = attr->getDashLen()/penWidth - dash;
        pen.setDashPattern({dash, space});
        pen.setDashOffset(dashOffset);
        // pen.setCapStyle(Qt::SquareCap);
    }

    painter->setPen(pen);
    QBrush brush(pen.color(), Qt::SolidPattern);
    painter->setBrush(brush);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::VerticalSubpixelPositioning);
    auto points = attr->getPoints();
    auto startAttr = attr->getStart();
    if (!startAttr.isEmpty()) {
        drawEndType(painter, startAttr);
        points[0] = startJointPt;
    }
    auto endAttr = attr->getEnd();
    if (!endAttr.isEmpty()) {
        drawEndType(painter, endAttr);
        points[points.count() - 1] = endJointPt;
    }

    auto path = linePath(points);
    painter->setBrushOrigin(path.boundingRect().topLeft());
    painter->strokePath(path, pen);

    // pen.setColor(Qt::red);
    // painter->setPen(pen);
    // brush.setStyle(Qt::NoBrush);
    // painter->setBrush(brush);
    // painter->drawRect(boundingRect());

    painter->restore();
}

QSizeF AbstractLineItem::size()
{
    auto attr = attribute();
    return {attr->getWidth(), attr->getHeight()};
}

void AbstractLineItem::setSize(const QSizeF &size)
{
    auto attr = attribute();
    attr->setWidth(size.width());
    attr->setHeight(size.height());
    // 按比例调整所有点的位置
    auto path = linePath(attr->getPoints());
    auto bound = path.boundingRect();
    auto xRatio = size.width() / bound.width();
    auto yRatio = size.height() / bound.height();
    if(!std::isnan(xRatio) && !std::isnan(yRatio) && (xRatio != 1 || yRatio != 1)){
        auto list = attr->getPointList();
        foreach (auto item, list) {
            attr->updatePoint(item.id, {item.pt.x() * xRatio, item.pt.y()*yRatio});
        }
    }
    prepareGeometryChange();
    updateGraphic();
    updateForm();
    updateSelector();
}

QPainterPath AbstractLineItem::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    if (!startPath.isEmpty()) {
        points[0] = startJointPt;
    }
    if (!endPath.isEmpty()) {
        points[points.count() - 1] = endJointPt;
    }
    path.addPolygon(points);
    return path;
}

QPainterPath AbstractLineItem::startShape() const
{
    return startPath;
}

QPainterPath AbstractLineItem::endShape() const
{
    return endPath;
}

qreal AbstractLineItem::width() const
{
    return attribute()->getWidth();
}

void AbstractLineItem::setWidth(qreal newWidth)
{
    auto attr = attribute();
    auto height = attr->getHeight();
    setSize({newWidth, height});
}

qreal AbstractLineItem::height() const
{
    return attribute()->getHeight();
}

void AbstractLineItem::setHeight(qreal newHeight)
{
    auto attr = attribute();
    auto width = attr->getWidth();
    setSize({width, newHeight});
}

QColor AbstractLineItem::color() const
{
    return attribute()->getPen().getColor();
}

void AbstractLineItem::setColor(const QColor &newColor)
{
    auto attr = attribute();
    auto pen = attr->getPen();
    pen.setColor(newColor);
    attr->setPen(pen);
    updateGraphic();
    updateForm();
}

QPainterPath AbstractLineItem::previewPath(QList<QPointF> points, QVariant args) const
{
    Q_UNUSED(args)
    auto attr = attribute();
    QPainterPath path;
    // 获取终端类型的path
    auto startAttr = attr->getStart();
    if (!startAttr.isEmpty()) {
        startAttr.setPos(points[0]);
        startAttr.setRotation(calcEndRotation(points, startAttr));
        auto data = getEndTypePath(startAttr);
        path.addPath(data.first);
        points[0] = data.second;
    }
    auto endAttr = attr->getEnd();
    if (!endAttr.isEmpty()) {
        endAttr.setPos(points[points.count() - 1]);
        endAttr.setRotation(calcEndRotation(points, endAttr));
        auto data = getEndTypePath(endAttr);
        path.addPath(data.first);
        points[points.count() - 1] = data.second;
    }
    path.addPath(linePath(points));
    return path;
}

void AbstractLineItem::enableEdit(bool flag)
{
    editable = flag;
}

void AbstractLineItem::enablePreview(bool flag)
{
    previewMode = flag;
}

void AbstractLineItem::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    Q_UNUSED(oldAttr)
    auto newItem = dynamic_cast<const LineBaseProperty&>(newAttr);
    attribute()->copy(newItem);
    logicRect = newItem.getLogicRect();
    setPos(newItem.getPos());
    updateSelector();
}

void AbstractLineItem::attributeSwitched(int oldIndex, int newIndex)
{
    Q_UNUSED(oldIndex)
    Q_UNUSED(newIndex)
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    setPos(attr->getPos());
}

AbstractSelector *AbstractLineItem::createSelector()
{
    auto pointList = attribute()->getPointList();
    auto s = new LineSelector(pointList, this);
    connect(s, SIGNAL(pointMoved(QString,QPointF)), this, SLOT(onPointMoved(QString,QPointF)));
    connect(s, SIGNAL(addPoint(QString,QPointF)), this, SLOT(onAddPoint(QString,QPointF)));
    connect(s, SIGNAL(delPoint(QString)), this, SLOT(onDelPoint(QString)));
    connect(s, SIGNAL(pointMoveStart(QString)), this, SLOT(onPointMoveStart(QString)));
    connect(s, SIGNAL(pointMoveEnd(QString)), this, SLOT(onPointMoveEnd(QString)));
    s->setPreviewMode(previewMode);
    s->enableEdit(editable);
    if (editable) {
        s->updateEditPoint(createEditPoint());
    }
    afterCreateSelector(s);
    return s;
}

QVariant AbstractLineItem::attr2Variant(const BaseProperty &attr)
{
    auto data = dynamic_cast<const LineBaseProperty*>(&attr);
    if (data == nullptr) {
        return QVariant::fromValue(attr);
    }
    return QVariant::fromValue(*data);
}

void AbstractLineItem::copyProperty(QVariant from, BaseProperty *to)
{
    if (!from.canConvert<LineBaseProperty>()) {
        return;
    }
    auto f =from.value<LineBaseProperty>();
    auto t = dynamic_cast<LineBaseProperty*>(to);
    if (t == nullptr) {
        return;
    }
    t->copy(f);
}

void AbstractLineItem::updateSelector()
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

void AbstractLineItem::updateGraphic()
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
    auto count = points.count();
    if (count > 0) {
        auto start = attr->getStart();
        if (!start.isEmpty()) {
            start.setPos(points[0]);
            if (start.getAutoRotate() && count > 1) {
                start.setRotation(calcEndRotation(points, start));
            }
            attr->setStart(start);
            // 更新两端路径
            auto data = getEndTypePath(start);
            startPath = data.first;
            startJointPt = data.second;
            path.addPath(startPath);
        }else if(!startPath.isEmpty()){
            startPath.clear();
            startJointPt = QPointF(0,0);
        }
        auto end = attr->getEnd();
        if (!end.isEmpty()) {
            end.setPos(points.last());
            if (end.getAutoRotate() && count > 1) {
                end.setRotation(calcEndRotation(points, end));
            }
            attr->setEnd(end);
            // 更新两端路径
            auto data = getEndTypePath(end);
            endPath = data.first;
            endJointPt = data.second;
            path.addPath(endPath);
        }else if(!endPath.isEmpty()){
            endPath.clear();
            endJointPt = QPointF(0,0);
        }
    }
    // 更新logicRect
    rect = path.boundingRect();
    logicRect = rect;
    // 启动动画
    if (attr->getFlowAnimation()) {
        if (timeLine == nullptr) {
            timeLine = new QTimeLine();
            timeLine->setLoopCount(0);
            timeLine->setFrameRange(1, frameCount);
            connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(onAnimateFrameChanged(int)));
        }
        timeLine->setDirection(attr->getBackward()?QTimeLine::Backward:QTimeLine::Forward);
        timeLine->setDuration(attr->getDuration());
        timeLine->setEasingCurve(QEasingCurve::BezierSpline);
        if(timeLine->state() != QTimeLine::Running){
            timeLine->start();
        }
    } else {
        if (timeLine && timeLine->state() == QTimeLine::Running) {
            timeLine->stop();
        }
    }

    update();
}

QPainterPath AbstractLineItem::shapePath() const
{
    auto attr = attribute();
    auto points = attr->getPoints();
    QPainterPath path;
    // 获取终端类型的path
    auto startAttr = attr->getStart();
    if (!startAttr.isEmpty()) {
        path.addPath(startPath);
        points[0] = startJointPt;
    }
    auto endAttr = attr->getEnd();
    if (!endAttr.isEmpty()) {
        path.addPath(endPath);
        points[points.count() - 1] = endJointPt;
    }
    path.addPath(linePath(points));
    return path;
}

void AbstractLineItem::customUndoAction(QString action, QVariant data, bool isUndo)
{
    Q_UNUSED(action)
    Q_UNUSED(data)
    Q_UNUSED(isUndo)
}

BaseProperty *AbstractLineItem::newProperty()
{
    auto attr = new LineBaseProperty();
    if (attrIndex >=0 && attributes[attrIndex] != nullptr){
        attr->copy(*attribute());
        attr->setId(-1);
        attr->setName("");
    }
    return attr;
}

void AbstractLineItem::parseXML(const QString &xml)
{
    AbstractItem::parseXML(xml);
    setPos(attribute()->getPos());
    initStatge = FINISHED;
    updateGraphic();
}

bool AbstractLineItem::sceneEvent(QEvent *event)
{
    auto attr = attribute();
    if (initStatge == DISABLED && event->type() == QEvent::GrabMouse){
        if (QApplication::mouseButtons() == Qt::NoButton) {
            // create item by drag
            createPredefinedItem();
            initEnd();
        }else{
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
            auto list = attr->getPointList();
            if(mEvent->buttons().testFlag(Qt::LeftButton)){
                dragPoint(list[list.count()-2], pos);
            }else{
                auto lastPoint = list.back();
                onPointMoved(lastPoint.id, pos);
            }
            initStatge = DRAWING;
            setSelected(true);
            event->accept();
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseDoubleClick){
        if(initStatge == DRAWING){
            auto list = attr->getPointList();
            beforeDelPoint(list.last().id);
            attr->removePoint(list.last().id);
            initEnd();
            event->accept();
            return true;
        }
    }else if (event->type() == QEvent::GraphicsSceneMousePress){
        auto mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        if (initStatge == DRAWING) {
            if (mEvent->button() == Qt::RightButton) {
                if (attr->getPointCount() > 2) {
                    onDelPoint(attr->getPointList().last().id);
                }
                initEnd();
            } else if(mEvent->button() == Qt::LeftButton){
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

QVariant AbstractLineItem::itemChange(GraphicsItemChange change, const QVariant &value)
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

void AbstractLineItem::afterCreateSelector(LineSelector *s)
{
    Q_UNUSED(s)
}

void AbstractLineItem::setSingle(int pointNumber)
{
    if (pointNumber > 0){
        singleFlag = true;
        pointUpperLimit = pointNumber;
    } else {
        singleFlag = false;
        pointUpperLimit = 0;
    }
}

void AbstractLineItem::afterInit()
{

}

void AbstractLineItem::afterPointMoved(const QString &id)
{
    Q_UNUSED(id)
}

void AbstractLineItem::afterPointMoveEnd(const QString &id)
{
    Q_UNUSED(id)
}

void AbstractLineItem::beforeAddPoint(const QString &id, const QPointF &pos)
{
    Q_UNUSED(id)
    Q_UNUSED(pos)
}

void AbstractLineItem::afterAddPoint(const QString &id)
{
    Q_UNUSED(id)
}

void AbstractLineItem::beforeDelPoint(const QString &id)
{
    Q_UNUSED(id)
}

qreal AbstractLineItem::calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const
{
    QPointF pt1, pt2;
    if (type.getCategory() == LineEndType::Start) {
        pt1 = points[0];
        pt2 = points[1];
    } else {
        auto count = points.count();
        pt1 = points[count - 2];
        pt2 = points[count - 1];
    }
    return -QLineF{pt1,pt2}.angle();
}

void AbstractLineItem::onPointMoved(const QString &id, const QPointF &pos)
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

void AbstractLineItem::onAddPoint(const QString &id, const QPointF &pos)
{
    beforeAddPoint(id, pos);
    if (attribute()->getPointCount() < 2) {
        attribute()->insertPoint(pos, id);
        updateGraphic();
        updateForm();
        updateSelector();
        return;
    }
    // 更新属性
    auto attr = LineBaseProperty();
    attr.copy(*attribute());
    QString newId = attr.insertPoint(pos, id);
    updateAttribute(&attr);
    afterAddPoint(newId);
    updateGraphic();
    updateSelector();
}

void AbstractLineItem::onDelPoint(const QString &id)
{
    beforeDelPoint(id);
    auto attr = LineBaseProperty();
    attr.copy(*attribute());
    attr.removePoint(id);
    updateAttribute(&attr);
}

void AbstractLineItem::onPointMoveStart(const QString &id)
{
    Q_UNUSED(id)
    // 记录调整前矩形属性
    oldAttr->copy(*attributes[attrIndex]);
    pointMoveFlag = true;
}

void AbstractLineItem::onPointMoveEnd(const QString &id)
{
    Q_UNUSED(id)
    afterPointMoveEnd(id);
    // undoTrigger("update attribute", {"updateAttr", attr2Variant(*oldAttr), attr2Variant(*attribute())});
    pointMoveFlag = false;
}

void AbstractLineItem::onAnimateFrameChanged(int value)
{
    auto attr = attribute();
    auto width = attr->getPen().getWidth();
    dashOffset = (1 - value*1.0/frameCount) * attr->getDashLen()/ width;
    update();
}

void AbstractLineItem::syncLogicRect()
{
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    updateSelector();
}

void AbstractLineItem::dragPoint(const NamedPoint &pt, const QPointF &pos)
{
    Q_UNUSED(pt)
    auto last = attribute()->getPointList().last();
    onPointMoved(last.id, pos);
}

QList<NamedPoint> AbstractLineItem::createEditPoint()
{
    QList<NamedPoint> editPoints;
    auto points = attribute()->getPointList();
    QPainterPath path;
    for (int i = 1; i < points.count(); ++i) {
        editPoints << NamedPoint{points[i].id,(points[i-1].pt + points[i].pt)/2};
    }
    return editPoints;
}

void AbstractLineItem::initEnd()
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

void AbstractLineItem::drawEndType(QPainter *painter, LineEndType type)
{
    auto endType = EndTypeFactory::instance()->getEndType(type.getTypeId(), type.getCategory());
    if (endType.isEmpty()) {
        return;
    }
    QPen pen = painter->pen();
    pen.setStyle(Qt::SolidLine);
    QBrush brush = painter->brush();
    painter->save();
    painter->translate(type.getPos());
    painter->rotate(type.getRotation());
    auto list = endType.arrow;
    QTransform trans;
    auto ratio = type.getSize()/endType.arrowSize.width();
    trans.translate(0, -type.getSize()/2);
    if (type.getCategory() == LineEndType::End) {
        trans.translate(-endType.size.width()*ratio, 0);
    }
    trans.scale(ratio, ratio);
    QPainterPath realPath;
    foreach (auto path, list) {
        realPath = trans.map(path);
        if (path.getPen().style() != Qt::NoPen) {
            painter->strokePath(realPath, pen);
        }
        if (path.getBrush().style() != Qt::NoBrush){
            painter->fillPath(realPath, brush);
        }
    }
    painter->restore();
}

QPair<QPainterPath, QPointF> AbstractLineItem::getEndTypePath(LineEndType type) const
{
    auto endType = EndTypeFactory::instance()->getEndType(type.getTypeId(), type.getCategory());
    if (endType.isEmpty()) {
        return{QPainterPath{}, {0,0}};
    }

    auto list = endType.arrow;
    QTransform trans;
    auto ratio = type.getSize()/endType.arrowSize.width();
    trans.translate(0, -type.getSize()/2);
    if (type.getCategory() == LineEndType::End) {
        trans.translate(-endType.size.width()*ratio, 0);
    }
    trans.scale(ratio, ratio);

    QTransform trans2;
    trans2.translate(type.getPos().x(), type.getPos().y());
    trans2.rotate(type.getRotation());
    QPainterPath realPath;
    foreach (auto path, list) {
        realPath.addPath(trans2.map(trans.map(path)));
    }
    list = endType.line;
    QPainterPath linePath;
    foreach (auto path, list) {
        linePath.addPath(trans.map(path));
    }
    auto rect = linePath.controlPointRect();
    // QPainterPath path;
    QPointF pt;
    if (type.getCategory() == LineEndType::Start) {
        // startPath.clear();
        // startPath = realPath;
        /*startJointPt*/ pt = trans2.map(QPointF{rect.left(), rect.center().y()});
    }else if (type.getCategory() == LineEndType::End) {
        // endPath.clear();
        // endPath = realPath;
        /*endJointPt*/ pt = trans2.map(QPointF{rect.right(), rect.center().y()});
    }
    return {realPath, pt};
}


void AbstractLineItem::updatePos()
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
