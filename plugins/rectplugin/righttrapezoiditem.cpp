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

#include "righttrapezoiditem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString RightTrapezoidItem::SHAPE_ID = "RIGHTTRAPEZOID_2024";
RightTrapezoidItem::RightTrapezoidItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({80,60});
    attribute()->setExtraP1(35);
}

RightTrapezoidItem::RightTrapezoidItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString RightTrapezoidItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath RightTrapezoidItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = attr->getArcSize();
    qreal tilt = attr->getExtraP1();
    if (attr->getRound() && arcSize > 0) {
        QLineF l1{logicRect.bottomLeft(), logicRect.topLeft() + QPointF{tilt, 0}};
        QLineF l2{logicRect.bottomLeft(), logicRect.bottomRight()};
        path.moveTo(l1.center());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.bottomRight(), logicRect.bottomLeft());
        l2.setPoints(logicRect.bottomRight(), logicRect.topRight());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.topRight(), logicRect.bottomRight());
        l2.setPoints(logicRect.topRight(), logicRect.topLeft() + QPointF{tilt, 0});
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.topLeft() + QPointF{tilt, 0}, logicRect.topRight());
        l2.setPoints(logicRect.topLeft() + QPointF{tilt, 0}, logicRect.bottomLeft());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
    } else {
        path.moveTo(logicRect.bottomLeft());
        path.lineTo(logicRect.bottomRight());
        path.lineTo(logicRect.topRight());
        path.lineTo(logicRect.topLeft() + QPointF{tilt, 0});
        path.lineTo(logicRect.bottomLeft());
    }
    path.closeSubpath();
    return path;
}

AbstractSelector *RightTrapezoidItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    cutAdjuster = new AdjustPoint("cutShape", this);
    cutAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                          Qt::NoPen, {0xFCA000}, 45});
    connect(cutAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onCutAdjusterMove(QPointF,QPointF)));
    updateCutAdjuster();
    return s;
}

void RightTrapezoidItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (cutAdjuster) {
        delete cutAdjuster;
        cutAdjuster = nullptr;
    }
}

void RightTrapezoidItem::onCutAdjusterMove(const QPointF &from, const QPointF &to)
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
    updateCutAdjuster();
    prepareGeometryChange();
    updateForm();
    update();
}

void RightTrapezoidItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto ratio = attr->getExtraP1()/logicRect.width();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratio*logicRect.width());
    updateCutAdjuster();
}

void RightTrapezoidItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateCutAdjuster();
}

void RightTrapezoidItem::updateCutAdjuster()
{
    auto attr = attribute();
    cutAdjuster->setPos(logicRect.topLeft() + QPointF{attr->getExtraP1(),0});
}
