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

#include "rightttriangleitem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString RightTriangleItem::SHAPE_ID = "RIGHTTRIANGLE_2024";
RightTriangleItem::RightTriangleItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({80,60});
}

RightTriangleItem::RightTriangleItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString RightTriangleItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath RightTriangleItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = attr->getArcSize();
    if (attr->getRound() && arcSize > 0) {
        QLineF l1{logicRect.topRight(), logicRect.bottomRight()};
        QLineF l2{logicRect.topRight(), logicRect.bottomLeft()};
        path.moveTo(l1.center());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.bottomLeft(), logicRect.topRight());
        l2.setPoints(logicRect.bottomLeft(), logicRect.bottomRight());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
        l1.setPoints(logicRect.bottomRight(), logicRect.bottomLeft());
        l2.setPoints(logicRect.bottomRight(), logicRect.topRight());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
    }else{
        path.moveTo(logicRect.topRight());
        path.lineTo(logicRect.bottomLeft());
        path.lineTo(logicRect.bottomRight());
    }
    path.closeSubpath();
    return path;
}
