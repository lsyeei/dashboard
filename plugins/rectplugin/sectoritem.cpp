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

#include "sectoritem.h"
#include "zoneproperty.h"

QString SectorItem::SHAPE_ID = "SECTOR_2024";
SectorItem::SectorItem(QGraphicsItem *parent)
    :AbstractZoneItem(parent)
{
    setSize({80,60});
    attribute()->setExtraP1(10);
    attribute()->setExtraP2(40);
}

SectorItem::SectorItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString SectorItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath SectorItem::shapePath() const
{
    QPainterPath path;
    qreal offset = attribute()->getExtraP1();
    auto top = logicRect.topLeft() + QPointF{attribute()->getExtraP2(), 0};
    auto pt1 = logicRect.bottomLeft() + QPointF{0,-offset};
    auto pt2 = logicRect.bottomRight() + QPointF{0,-offset};
    path.addRect({pt1,
                 QSizeF{logicRect.width(), offset}});

    QPainterPath ellipse;
    ellipse.addEllipse({logicRect.bottomLeft() + QPointF{0,-offset*2},
                        QSizeF{logicRect.width(), offset*2}});
    QPainterPath triangle;
    triangle.moveTo(pt1);
    triangle.lineTo(top);
    triangle.lineTo(pt2);
    triangle.closeSubpath();
    return (triangle + (path & ellipse)).simplified();
}


AbstractSelector *SectorItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    directAdjuster = new AdjustPoint("direct", this);
    directAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                          Qt::NoPen, {0xFCA000}, 45});
    ellipseAdjuster = new AdjustPoint("ellipse", this);
    ellipseAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                                   Qt::NoPen, {0xFCA000}, 45});
    connect(directAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onAdjusterMove(QPointF,QPointF)));
    connect(ellipseAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onAdjusterMove(QPointF,QPointF)));
    updateAdjuster();
    return s;
}

void SectorItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (directAdjuster) {
        delete directAdjuster;
        directAdjuster = nullptr;
    }
    if (ellipseAdjuster) {
        delete ellipseAdjuster;
        ellipseAdjuster = nullptr;
    }
}

void SectorItem::onAdjusterMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto obj = sender();
    auto attr = attribute();
    auto pos = mapFromScene(to);
    if (obj == directAdjuster) {
        auto x = pos.x();
        if (x < logicRect.left()) {
            x = logicRect.left();
        }
        if (x > logicRect.right()) {
            x = logicRect.right();
        }
        attr->setExtraP2(x-logicRect.left());
    }
    if (obj == ellipseAdjuster) {
        auto y = pos.y();
        if (y < logicRect.top()) {
            y = logicRect.top();
        }
        if (y > logicRect.bottom()) {
            y = logicRect.bottom();
        }
        attr->setExtraP1(logicRect.bottom() - y);
    }
    updateAdjuster();
    prepareGeometryChange();
    update();
}


void SectorItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto ratioTop = attr->getExtraP2() / logicRect.width();
    auto ratioLeft = attr->getExtraP1() / logicRect.height();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratioLeft*logicRect.height());
    attr->setExtraP2(ratioTop*logicRect.width());
    updateAdjuster();
}

void SectorItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateAdjuster();
}

void SectorItem::updateAdjuster()
{
    auto attr = attribute();
    directAdjuster->setPos(logicRect.topLeft() + QPointF{attr->getExtraP2(),0});
    ellipseAdjuster->setPos((logicRect.bottomLeft()-QPointF{0,attr->getExtraP1()}));
}
