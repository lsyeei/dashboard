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

#include "solidline.h"

QString SolidLine::SHAPE_ID = "SOLIDLINE_2024";
SolidLine::SolidLine(QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    setSingle(2);
    auto attr = attribute();
    auto pen = attr->getPen();
    pen.setStyle(Qt::SolidLine);
    attr->setPen(pen);
}

SolidLine::SolidLine(const QString &xml, QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    parseXML(xml);
}

QString SolidLine::classId() const
{
    return SHAPE_ID;
}

void SolidLine::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-40,40});
    attr->appendPoint({40, -40});
    setSize({80,80});
}

QPainterPath SolidLine::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    path.addPolygon(points);
    return path;
}
