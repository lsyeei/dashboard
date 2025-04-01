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

#include "straightlineitem.h"
#include "endtypefactory.h"
#include "lineitemproperty.h"
#include "lineselector.h"

QString StraightLineItem::SHAPE_ID = "STRAIGHT_LINE_2024";

StraightLineItem::StraightLineItem(QGraphicsItem *parent)
    : AbstractItem(parent)
{
    setTransformOriginPoint({0,0});
    auto attr = new LineItemProperty();
    PenProperty pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    pen.setColor(Qt::gray);
    attr->setPen(pen);
    attr->appendPoint({0,60});
    attr->appendPoint({80, 0});
    attributes[0] = attr;
    attributes[0]->setId(attrIndex);
    attributes[0]->setName("default");
    attrIndex = 0;
    oldAttr = new LineItemProperty();
    oldAttr->copy(*attributes[0]);
}

StraightLineItem::StraightLineItem(const QString &xml, QGraphicsItem *parent)
    : StraightLineItem(parent)
{
    parseXML(xml);
}

QString StraightLineItem::classId() const
{
    return SHAPE_ID;
}


QRectF StraightLineItem::boundingRect() const
{
    QPolygonF polygon(attribute()->getPoints());
    // polygon = mapFromScene(polygon);
    auto rect =polygon.boundingRect();
    // qDebug() << "polygon bound:" << rect;//-rect.width()/2, -rect.height()/2
    auto width = rect.width();
    auto height = rect.height();
    rect = {-width/2, -height/2, width, height};
    auto pen = attribute()->getPen();
    auto borderWidth = pen.getWidth() / 2;

    return rect.adjusted(-borderWidth, -borderWidth, borderWidth, borderWidth);
}

QPainterPath StraightLineItem::shape() const
{
    return shapePath();
}

void StraightLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    auto pen = attribute()->getPen().getPen();
    painter->setPen(pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(pen.color());
    painter->setBrush(brush);
    // 处理翻转情况
    auto parentTrans = sceneTransform();
    QTransform trans{parentTrans.m11(), parentTrans.m12(), parentTrans.m13(),
                     parentTrans.m21(), parentTrans.m22(), parentTrans.m23(),
                     0, 0, parentTrans.m33()};
    auto path = trans.map(shapePath());
    painter->drawPath(path);

    pen.setColor(Qt::red);
    painter->setPen(pen);
    brush.setStyle(Qt::NoBrush);
    painter->setBrush(brush);
    painter->drawRect(boundingRect());
    painter->restore();
}

void StraightLineItem::setSize(const QSizeF &size)
{
    // abstractRect = QRectF({0,0}, size);
    // abstractRect.moveCenter(pos());
}

LineItemProperty *StraightLineItem::attribute() const
{
    auto attr = attributes[attrIndex];
    return dynamic_cast<LineItemProperty*>(attr);
}

QPainterPath StraightLineItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto points = attr->getPoints();
    auto count = points.count();
    path.addPolygon(points);
    // 获取终端类型的path
    // auto startPath = EndTypeFactory::instance()->getEndTypePath(attr->getStart().getTypeId(), EndTypeFactory::Start);
    // startPath.translate(points[0]);
    // auto trans = trans4Line(points[0], points[1]);
    // startPath = trans.map(startPath);

    // auto endPath = EndTypeFactory::instance()->getEndTypePath(attr->getEnd().getTypeId(), EndTypeFactory::End);
    // auto endRect = endPath.boundingRect();
    // trans = trans4Line(points[count - 2], points[count - 1]);
    // trans.translate(-endRect.width(), -endRect.height());
    // endPath.translate(points[count - 1]);
    // endPath = trans.map(endPath);
    // // 与绘制线条合并
    // path = path.united(startPath);
    // path = path.united(endPath);
    path = mapFromParent(path);

    return path;
}

void StraightLineItem::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
}

void StraightLineItem::attributeSwitched(int oldIndex, int newIndex)
{
}

void StraightLineItem::customUndoAction(QString action, QVariant data, bool isUndo)
{
}

AbstractSelector *StraightLineItem::createSelector()
{
    auto pointList = attribute()->getPointList();
    auto s = new LineSelector(pointList, this);
    connect(s, SIGNAL(pointMoved(QString,QPointF)), this, SLOT(onPointMoved(QString,QPointF)));
    return s;
}

BaseProperty *StraightLineItem::newProperty()
{
    return new LineItemProperty();
}

QVariant StraightLineItem::attr2Variant(const BaseProperty &attr)
{
    auto data = dynamic_cast<const LineItemProperty*>(&attr);
    if (data == nullptr) {
        return QVariant::fromValue(attr);
    }
    return QVariant::fromValue(*data);
}

void StraightLineItem::copyProperty(QVariant from, BaseProperty *to)
{
    if (!from.canConvert<LineItemProperty>()) {
        return;
    }
    auto f =from.value<LineItemProperty>();
    auto t = dynamic_cast<LineItemProperty*>(to);
    if (t == nullptr) {
        return;
    }
    t->copy(f);
}

void StraightLineItem::updateSelector()
{
    auto s = dynamic_cast<LineSelector*>(selector);
    if (s == nullptr) {
        return;
    }
    s->updatePoints(attribute()->getPointList());
}

void StraightLineItem::updateGraphic()
{
    update();
}

QTransform StraightLineItem::trans4Line(QPointF p2, QPointF p1) const
{
    QTransform trans;
    QLineF l1{{0,0}, {1,0}};
    l1.translate(p1);
    QLineF l2{p1, p2};
    auto angle = l1.angleTo(l2);
    trans.rotate(angle);
    return trans;
}


bool StraightLineItem::sceneEvent(QEvent *event)
{
    if (!initFlag) {
        // auto attr = attribute();
        // auto pointlist = attr->getPointList();
        // auto lastPoint = pointlist.back();
        // if (event->type() == QEvent::GraphicsSceneMouseMove) {
        //     auto *mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        //     attr->updatePoint(lastPoint.first, mEvent->pos());
        // }
        // if (event->type() == QEvent::GraphicsSceneMousePress) {
        //     auto *mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        //     attr->updatePoint(lastPoint.first, mEvent->pos());
        //     initFlag = true;
        // }
    }
    return QGraphicsItem::sceneEvent(event);
}

void StraightLineItem::onPointMoved(const QString &id, const QPointF &pos)
{
    prepareGeometryChange();
    auto attr = attribute();
    attr->updatePoint(id, pos);
    // 重新确定原点
    QPolygonF polygon(attr->getPoints());
    auto newRect = polygon.boundingRect();
    // qDebug() << "point moved, polygn rect:" << newRect;
    adjustMove = true;
    setPos(newRect.topLeft());
    update();
    updateForm();
    updateSelector();
}


QVariant StraightLineItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    auto result = AbstractItem::itemChange(change, value);
    if (change == QGraphicsItem::ItemPositionHasChanged) {
        // 起点，终点等都移动
        if (!adjustMove) {
            auto pos = this->pos();
            auto attr = attribute();
            auto points = attr->getPointList();
            foreach (auto item, points) {
                attr->updatePoint(item.id, item.pt + pos);
            }
            updateSelector();
            updateGraphic();
        }else{
            adjustMove = false;
        }
    }
    return result;
}
