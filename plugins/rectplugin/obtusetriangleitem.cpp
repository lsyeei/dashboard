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

#include "obtusetriangleitem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString ObtuseTriangleItem::SHAPE_ID = "OBTUSETRIANGLE_2024";
ObtuseTriangleItem::ObtuseTriangleItem(QGraphicsItem *parent)
    :AbstractZoneItem(parent)
{
    setSize({80,60});
    attribute()->setExtraP1(30);
}

ObtuseTriangleItem::ObtuseTriangleItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString ObtuseTriangleItem::classId() const
{
    return  SHAPE_ID;
}

QPainterPath ObtuseTriangleItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto offset = attr->getExtraP1();
    auto p1 = logicRect.topLeft();
    auto p2 = logicRect.bottomLeft() + QPointF{offset, 0};
    auto p3 = logicRect.bottomRight();
    auto arcSize = 0;
    if (attr->getRound()) {
        arcSize = attr->getArcSize();
    }
    if (arcSize > 0) {
        QLineF l{p1,p3};
        path.moveTo(l.center());
        PaintHelper::drawRoundCorner(&path, QLineF{p1, p3}, QLineF{p1, p2}, arcSize);
        PaintHelper::drawRoundCorner(&path, QLineF{p2, p1}, QLineF{p2, p3}, arcSize);
        PaintHelper::drawRoundCorner(&path, QLineF{p3, p2}, QLineF{p3, p1}, arcSize);
    } else{
    path.moveTo(p1);
    path.lineTo(p2);
    path.lineTo(p3);
    }
    path.closeSubpath();
    return path;
}

AbstractSelector *ObtuseTriangleItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    tiltAdjuster = new AdjustPoint("tilt", this);
    tiltAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                          Qt::NoPen, {0xFCA000}, 45});
    connect(tiltAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onTiltMove(QPointF,QPointF)));
    updateTiltAdjuster();
    return s;
}

void ObtuseTriangleItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (tiltAdjuster) {
        delete tiltAdjuster;
        tiltAdjuster = nullptr;
    }
}

void ObtuseTriangleItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto value = attr->getExtraP1();
    auto ratio = value/logicRect.width();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratio*logicRect.width());
    updateTiltAdjuster();
}

void ObtuseTriangleItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateTiltAdjuster();
}

void ObtuseTriangleItem::onTiltMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto x = mapFromScene(to).x();
    if (x < logicRect.left()) {
        x = logicRect.left();
    }
    if (x > logicRect.right()) {
        x = logicRect.right();
    }
    attribute()->setExtraP1(x - logicRect.left());
    updateTiltAdjuster();
    updateForm();
    prepareGeometryChange();
    update();
}

void ObtuseTriangleItem::updateTiltAdjuster()
{
    auto attr = attribute();
    auto offset = attr->getExtraP1();
    tiltAdjuster->setPos(logicRect.bottomLeft() + QPointF{offset, 0});
}
