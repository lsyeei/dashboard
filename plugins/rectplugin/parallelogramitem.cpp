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

#include "parallelogramitem.h"
#include "zoneproperty.h"

QString ParallelogramItem::SHAPE_ID = "PARALLELOGRAM_2024";
ParallelogramItem::ParallelogramItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({80,40});
    attribute()->setExtraP1(30);
}

ParallelogramItem::ParallelogramItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString ParallelogramItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath ParallelogramItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    qreal tilt = attr->getExtraP1();
    if (attr->getRound()) {
        qreal angle = qAtan(attr->getHeight()/tilt);
        qreal degree = angle * 180 / M_PI;
        auto arcSize = attr->getArcSize();
        auto x1 = logicRect.bottomLeft() + QPointF{arcSize * qCos(angle), -arcSize * qSin(angle)};
        auto r1 = arcSize * qTan(angle/2);
        auto r2 = arcSize * qTan((M_PI - angle)/2);
        path.moveTo(x1);
        path.arcTo({logicRect.bottomLeft() + QPointF{arcSize - r1, -r1*2}, QSizeF{r1*2, r1*2}}, 90 + degree, 180-degree);
        path.lineTo(logicRect.bottomRight() + QPointF{-tilt-arcSize,0});
        path.arcTo({logicRect.bottomRight() + QPointF{- tilt - arcSize - r2,-r2*2}, QSizeF{r2*2, r2*2}}, 270, degree);
        path.lineTo(logicRect.topRight() + QPointF{-arcSize * qCos(angle),arcSize * qSin(angle)});
        path.arcTo({logicRect.topRight() + QPointF{- arcSize - r1,0}, QSizeF{r1*2, r1*2}}, degree - 90, 180 - degree);
        path.lineTo(logicRect.topLeft() + QPointF{tilt + arcSize,0});
        path.arcTo({logicRect.topLeft() + QPointF{tilt + arcSize - r2,0}, QSizeF{r2*2, r2*2}}, 90, degree);
        path.lineTo(x1);

    }else{
        path.moveTo(logicRect.bottomLeft());
        path.lineTo(logicRect.topLeft() + QPointF{tilt,0});
        path.lineTo(logicRect.topRight());
        path.lineTo(logicRect.bottomRight() + QPointF{-tilt,0});
        path.lineTo(logicRect.bottomLeft());
    }
    path.closeSubpath();

    return path;
}

AbstractSelector *ParallelogramItem::createSelector()
{
    auto selector = AbstractZoneItem::createSelector();

    tiltAdjuster = new AdjustPoint("tilt", this);
    tiltAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                        Qt::NoPen, {0xFCA000}, 45});
    connect(tiltAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onTiltMove(QPointF,QPointF)));
    updateTiltAdjuster();
    return selector;
}

void ParallelogramItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (tiltAdjuster) {
        delete tiltAdjuster;
        tiltAdjuster = nullptr;
    }
}

void ParallelogramItem::onTiltMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto offset = mapFromScene(to).x() - logicRect.left();
    if (offset < 0) {
        offset = 0;
    }
    if (offset > logicRect.width()) {
        offset = logicRect.width();
    }
    attribute()->setExtraP1(offset);
    updateTiltAdjuster();
    updateForm();
    prepareGeometryChange();
    update();
}


void ParallelogramItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto ratio = attr->getExtraP1()/logicRect.width();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratio * logicRect.width());
    updateTiltAdjuster();
}

void ParallelogramItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateTiltAdjuster();
}

void ParallelogramItem::updateTiltAdjuster()
{
    auto tilt = attribute()->getExtraP1();
    tiltAdjuster->setPos(logicRect.topLeft() + QPointF{tilt,0});
}
