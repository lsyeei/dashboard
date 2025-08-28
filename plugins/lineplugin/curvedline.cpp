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

#include "curvedline.h"

QString CurvedLine::SHAPE_ID = "CURVED_LINE_2024";
CurvedLine::CurvedLine(QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
}

CurvedLine::CurvedLine(const QString &xml, QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
    parseXML(xml);
}

QString CurvedLine::classId() const
{
    return SHAPE_ID;
}

QPainterPath CurvedLine::linePath(QList<QPointF> points) const
{
    QPainterPath path;

    auto count = points.count();
    if (count <= 2){
        path.addPolygon(points);
    } else {
        path.moveTo(points[0]);
        for (int i = 1; i < count-2; ++i) {
            QPointF pt{(points[i] + points[i+1])/2};
            path.quadTo(points[i], pt);
        }
        path.quadTo(points[count-2], points[count-1]);
    }
    return path;
}

void CurvedLine::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-50, 50});
    attr->appendPoint({50, 50});
    attr->appendPoint({-50, -50});
    attr->appendPoint({50, -50});
    setSize({100,100});
}
