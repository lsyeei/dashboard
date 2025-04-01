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

#include "triangleitem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString TriangleItem::SHAPE_ID = "TRIANGLE_2024";
TriangleItem::TriangleItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({60,60});
    attribute()->setExtraP1(30);
}

TriangleItem::TriangleItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML((xml));
}

QString TriangleItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath TriangleItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = attr->getArcSize();
    auto offset = attr->getExtraP1();
    QPointF vertex{logicRect.topLeft() + QPointF{offset, 0}};
    if (attr->getRound() && arcSize > 0) {
        QLineF l1{vertex, logicRect.bottomRight()};
        QLineF l2{vertex, logicRect.bottomLeft()};
        path.moveTo(l1.center());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.bottomLeft(), vertex);
        l2.setPoints(logicRect.bottomLeft(), logicRect.bottomRight());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.bottomRight(), logicRect.bottomLeft());
        l2.setPoints(logicRect.bottomRight(), vertex);
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
    }else{
        path.moveTo(vertex);
        path.lineTo(logicRect.bottomLeft());
        path.lineTo(logicRect.bottomRight());
    }
    path.closeSubpath();
    return path;
}


AbstractSelector *TriangleItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    vertexAdjuster = new AdjustPoint("vertex", this);
    vertexAdjuster->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                                  Qt::NoPen, {0xFCA000}, 45});
    connect(vertexAdjuster, SIGNAL(moveEvent(QPointF,QPointF)),
            this, SLOT(onVertexAdjusterMove(QPointF,QPointF)));
    updateVertexAdjuster();
    return s;
}

void TriangleItem::delSelector()
{
    AbstractZoneItem::delSelector();
    if (vertexAdjuster) {
        delete vertexAdjuster;
        vertexAdjuster = nullptr;
    }
}

void TriangleItem::sizeChanged(QRectF offsetValue)
{
    auto attr = attribute();
    auto ratio = attr->getExtraP1()/logicRect.width();
    AbstractZoneItem::sizeChanged(offsetValue);
    attr->setExtraP1(ratio*logicRect.width());
    updateVertexAdjuster();
}

void TriangleItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    updateVertexAdjuster();
}


void TriangleItem::onVertexAdjusterMove(const QPointF &from, const QPointF &to)
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
    updateVertexAdjuster();
    updateForm();
    prepareGeometryChange();
    update();
}

void TriangleItem::updateVertexAdjuster()
{
    vertexAdjuster->setPos(logicRect.topLeft() + QPointF{attribute()->getExtraP1(),0});
}
