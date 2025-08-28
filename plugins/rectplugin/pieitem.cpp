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

#include "pieitem.h"
#include "zoneproperty.h"

QString PieItem::SHAPE_ID = "PIE_2024";
PieItem::PieItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({60,60});
    attribute()->setExtraP1(30);
    attribute()->setExtraP2(-30);
}

PieItem::PieItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

PieItem::~PieItem()
{
    if (startAdjuster) {
        delete startAdjuster;
    }
    if(endAdjuster){
        delete endAdjuster;
    }
}

QString PieItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath PieItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto start = attr->getExtraP1();
    auto end = attr->getExtraP2();
    if (end < 0) {
        end += 360;
    }
    auto rect = logicRect;
    path.moveTo(rect.center());
    path.arcTo(rect, start, end - start);
    path.closeSubpath();
    return path;
}


AbstractSelector *PieItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();

    startAdjuster = new AdjustPoint("arcStart",this);
    startAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                          Qt::NoPen, {0xFCA000}, 45});
    endAdjuster = new AdjustPoint("arcEnd",this);
    endAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                               Qt::NoPen, {0xFCA000}, 45});
    connect(startAdjuster, SIGNAL(moveEvent(QPointF,QPointF)), this, SLOT(arcAdjusterMove(QPointF,QPointF)));
    connect(endAdjuster, SIGNAL(moveEvent(QPointF,QPointF)), this, SLOT(arcAdjusterMove(QPointF,QPointF)));

    updateArcAdjuster();
    return s;
}

void PieItem::delSelector()
{
    AbstractItem::delSelector();
    if(startAdjuster){
        delete startAdjuster;
        startAdjuster = nullptr;
    }
    if (endAdjuster){
        delete endAdjuster;
        endAdjuster = nullptr;
    }
}

void PieItem::sizeChanged(QRectF offsetValue)
{
    AbstractZoneItem::sizeChanged(offsetValue);
    updateArcAdjuster();
}

void PieItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateArcAdjuster();
}

void PieItem::arcAdjusterMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto attr = attribute();
    auto obj = sender();
    QLineF base{{0,0}, {1,0}};
    QPointF pt{mapFromScene(to)};
    // 保持正圆状态下再计算角度
    pt.setX(logicRect.height() * pt.x() / logicRect.width());
    QLineF l({0,0}, pt);
    auto angle = base.angleTo(l);
    if (obj == startAdjuster) {
        attr->setExtraP1(angle);
    } else if(obj == endAdjuster){
        attr->setExtraP2(angle);
    }
    prepareGeometryChange();
    updateArcAdjuster();
    updateForm();
    update();
}

void PieItem::updateArcAdjuster()
{
    QPainterPath path = shapePath();
    startAdjuster->setPos(path.elementAt(1));
    endAdjuster->setPos(path.elementAt(path.elementCount() - 2));
}
