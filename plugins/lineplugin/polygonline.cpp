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

#include "polygonline.h"
#include "paintHelper.h"

QString PolygonLine::SHAPE_ID = "POLYGON_LINE_2024";
PolygonLine::PolygonLine(QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
}

PolygonLine::PolygonLine(const QString &xml, QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
    parseXML(xml);
}

QString PolygonLine::classId() const
{
    return SHAPE_ID;
}

void PolygonLine::afterPointMoved(const QString &id)
{
    Q_UNUSED(id)
}

QPainterPath PolygonLine::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    auto attr = attribute();
    bool isRound = attr->getRounded();
    qreal arcSize = attr->getArcSize();
    if (isRound) {
        path.moveTo(points[0]);
        for (int i = 1; i < points.count()-1; ++i) {
            PaintHelper::drawRoundCorner(&path, {points[i], points[i-1]}, {points[i], points[i+1]}, arcSize);
        }
        path.lineTo(points[points.count() - 1]);
    } else {
        path.addPolygon(points);
    }
    return path;
}

void PolygonLine::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-50, 50});
    attr->appendPoint({40, 40});
    attr->appendPoint({-40, -40});
    attr->appendPoint({50, -50});
    setSize({100,100});
}

