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

#include "star4item.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString Star4Item::SHAPE_ID = "STAR4_2024";
Star4Item::Star4Item(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({60,60});
    attribute()->setExtraP1(35.4);
}

Star4Item::Star4Item(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString Star4Item::classId() const
{
    return SHAPE_ID;
}

QPainterPath Star4Item::shapePath() const
{
    auto width = logicRect.width()/2;
    auto height = logicRect.height()/2;
    QPointF p1{logicRect.topLeft() + QPointF{width, 0}};
    QPointF p2{logicRect.topLeft() + QPointF{0, height}};
    QPointF p3{logicRect.bottomLeft() + QPointF{width, 0}};
    QPointF p4{logicRect.topRight() + QPointF{0, height}};

    auto offset = attribute()->getExtraP1();
    QLineF l{logicRect.topLeft(), logicRect.center()};
    l.setLength(offset);
    auto n1 = l.p2();
    l.setPoints(logicRect.bottomLeft(), logicRect.center());
    l.setLength(offset);
    auto n2 = l.p2();
    l.setPoints(logicRect.bottomRight(), logicRect.center());
    l.setLength(offset);
    auto n3 = l.p2();
    l.setPoints(logicRect.topRight(), logicRect.center());
    l.setLength(offset);
    auto n4 = l.p2();
    auto attr = attribute();
    auto arcSize = 0;
    if (attr->getRound()){
        arcSize = attr->getArcSize();
    }
    QPainterPath path;
    path.moveTo(n4);
    PaintHelper::drawRoundCorner(&path, QLineF{p1,n4}, QLineF{p1,n1}, arcSize);
    path.lineTo(n1);
    PaintHelper::drawRoundCorner(&path, QLineF{p2,n1}, QLineF{p2,n2}, arcSize);
    path.lineTo(n2);
    PaintHelper::drawRoundCorner(&path, QLineF{p3,n2}, QLineF{p3,n3}, arcSize);
    path.lineTo(n3);
    PaintHelper::drawRoundCorner(&path, QLineF{p4,n3}, QLineF{p4,n4}, arcSize);
    path.lineTo(n4);
    return path;
}


AbstractSelector *Star4Item::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    shapeAdjuster = new AdjustPoint("starShape", this);
    shapeAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                          Qt::NoPen, {0xFCA000}, 45});
    connect(shapeAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onShapeAdjusterMove(QPointF,QPointF)));
    updateShapeAdjuster();
    return s;
}

void Star4Item::delSelector()
{
    AbstractZoneItem::delSelector();
    if(shapeAdjuster){
        delete shapeAdjuster;
        shapeAdjuster = nullptr;
    }
}

void Star4Item::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    QLineF l{logicRect.topLeft(), logicRect.bottomRight()};
    auto ratio = attr->getExtraP1()/l.length();
    AbstractZoneItem::sizeChanged(offsetValue);
    l.setPoints(logicRect.topLeft(), logicRect.bottomRight());
    attr->setExtraP1(ratio*l.length());
    updateShapeAdjuster();
}

void Star4Item::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateShapeAdjuster();
}


void Star4Item::onShapeAdjusterMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto pos = mapFromScene(to);
    auto attr = attribute();
    if (pos.x() < logicRect.left()) {
        pos.setX(logicRect.left());
    }
    if (pos.x() > logicRect.center().x()) {
        pos.setX(logicRect.center().x());
    }
    if (pos.y() < logicRect.top()){
        pos.setY(logicRect.top());
    }
    if (pos.y() > logicRect.center().y()){
        pos.setY(logicRect.center().y());
    }
    QLineF l{logicRect.topLeft(), pos};
    attr->setExtraP1(l.length());
    updateShapeAdjuster();
    updateForm();
    prepareGeometryChange();
    update();
}

void Star4Item::updateShapeAdjuster()
{
    auto attr = attribute();
    QLineF l{logicRect.topLeft(), logicRect.center()};
    l.setLength(attr->getExtraP1());
    shapeAdjuster->setPos(l.p2());
}
