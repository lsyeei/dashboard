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

#include "star6item.h"
#include "zoneproperty.h"

#include <paintHelper.h>


QString Star6Item::SHAPE_ID = "STAR6_2024";
Star6Item::Star6Item(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({60,60});
    attribute()->setExtraP1(13);
    ratio = 13.0/60;
}

Star6Item::Star6Item(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString Star6Item::classId() const
{
    return SHAPE_ID;
}

QPainterPath Star6Item::shapePath() const
{
    auto attr = attribute();
    qreal tilt = attr->getExtraP1();
    auto arcSize = 0;
    if (attr->getRound()){
        arcSize = attr->getArcSize();
    }
    return PaintHelper::starPath(logicRect, 6, tilt, arcSize);
}


void Star6Item::sizeChanged(QRectF offsetValue)
{
    AbstractZoneItem::sizeChanged(offsetValue);
    auto attr = attribute();
    attr->setExtraP1(qMin(logicRect.width(), logicRect.height()) * ratio);
}
