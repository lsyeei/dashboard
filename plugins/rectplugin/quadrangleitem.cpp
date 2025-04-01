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

#include "quadrangleitem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString QuadrangleItem::SHAPE_ID = "QUADRANGLE_2024";
QuadrangleItem::QuadrangleItem(QGraphicsItem *parent)
    :AbstractZoneItem(parent)
{
    setSize({80,60});
    auto attr = attribute();
    attr->setExtraP1(10);
    attr->setExtraP2(16);
}

QuadrangleItem::QuadrangleItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString QuadrangleItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath QuadrangleItem::shapePath() const
{
    auto attr = attribute();
    auto leftOffset = attr->getExtraP1();
    auto rightOffset = attr->getExtraP2();
    QPainterPath path;
    QPointF p1{logicRect.topLeft() + QPointF{leftOffset, 0}};
    QPointF p2{logicRect.bottomLeft()};
    QPointF p3{logicRect.bottomRight()};
    QPointF p4{logicRect.topRight() + QPointF{-rightOffset, 0}};
    auto arcSize = 0;
    if (attr->getRound()) {
        arcSize = attr->getArcSize();
    }
    if (arcSize > 0) {
        path.moveTo(logicRect.bottomLeft() + QPointF{logicRect.width()/2, 0});
        PaintHelper::drawRoundCorner(&path, QLineF{p3, p2},  QLineF{p3, p4}, arcSize);
        PaintHelper::drawRoundCorner(&path, QLineF{p4, p3},  QLineF{p4, p1}, arcSize);
        PaintHelper::drawRoundCorner(&path, QLineF{p1, p4},  QLineF{p1, p2}, arcSize);
        PaintHelper::drawRoundCorner(&path, QLineF{p2, p1},  QLineF{p2, p3}, arcSize);
    }else{
        path.moveTo(p1);
        path.lineTo(p2);
        path.lineTo(p3);
        path.lineTo(p4);
    }
    path.closeSubpath();
    return path;
}


AbstractSelector *QuadrangleItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    tiltLAdjuster = new AdjustPoint("tiltL", this);
    tiltLAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                        Qt::NoPen, {0xFCA000}, 45});
    tiltRAdjuster = new AdjustPoint("tiltR", this);
    tiltRAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                                       Qt::NoPen, {0xFCA000}, 45});
    connect(tiltLAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onTiltMove(QPointF,QPointF)));
    connect(tiltRAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onTiltMove(QPointF,QPointF)));
    updateTiltAdjuster();
    return s;
}

void QuadrangleItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (tiltLAdjuster) {
        delete tiltLAdjuster;
        tiltLAdjuster = nullptr;
    }
    if (tiltRAdjuster) {
        delete tiltRAdjuster;
        tiltRAdjuster = nullptr;
    }
}

void QuadrangleItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto ratioL = attr->getExtraP1()/logicRect.width();
    auto ratioR = attr->getExtraP2()/logicRect.width();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratioL*logicRect.width());
    attr->setExtraP2(ratioR*logicRect.width());
    updateTiltAdjuster();
}


void QuadrangleItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateTiltAdjuster();
}

void QuadrangleItem::onTiltMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto attr = attribute();
    auto obj = sender();
    auto x = mapFromScene(to).x();
    auto centerX = logicRect.center().x();
    if (obj == tiltLAdjuster) {
        if (x < logicRect.left()) {
            x = logicRect.left();
        }
        if (x > centerX) {
            x = centerX;
        }
        attr->setExtraP1(x - logicRect.left());
    }
    if (obj == tiltRAdjuster) {
        if (x > logicRect.right()) {
            x = logicRect.right();
        }
        if (x < centerX) {
            x = centerX;
        }
        attr->setExtraP2(logicRect.right() - x);
    }
    updateTiltAdjuster();
    prepareGeometryChange();
    updateForm();
    update();
}

void QuadrangleItem::updateTiltAdjuster()
{
    auto attr = attribute();
    tiltLAdjuster->setPos(logicRect.topLeft() + QPointF{attr->getExtraP1(),0});
    tiltRAdjuster->setPos(logicRect.topRight() - QPointF{attr->getExtraP2(),0});
}
