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

#include "zoneproperty.h"
#include "rectitem.h"

QString RectItem::SHAPE_ID = "RECT_2024";

RectItem::RectItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({80,60});
}

RectItem::RectItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString RectItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath RectItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = 0;
    if (attr->getRound()) {
        arcSize = attr->getArcSize();
    }

    path.addRoundedRect(logicRect, arcSize, arcSize);
    return path;
}
