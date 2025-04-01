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

#include "pentagonitem.h"
#include "paintHelper.h"

QString PentagonItem::SHAPE_ID = "PENTAGON_2024";
PentagonItem::PentagonItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({60,54});
}

PentagonItem::PentagonItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString PentagonItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath PentagonItem::shapePath() const
{
    return PaintHelper::polygonPath(logicRect, 5);
}
