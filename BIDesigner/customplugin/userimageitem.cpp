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
#include "userimageitem.h"
#include "zoneproperty.h"

UserImageItem::UserImageItem(const QString &classId, const QString &imgPath, QGraphicsItem *parent)
    : AbstractZoneItem(parent), id(classId) {
    auto attr = attribute();
    attr->setData(id);
    auto brush = attr->getBrush();
    brush.setImage(imgPath);
    attr->setBrush(brush);
}

UserImageItem::UserImageItem(const QString &xml, QGraphicsItem *parent) : AbstractZoneItem(parent)
{
    parseXML(xml);
}


QString UserImageItem::classId() const
{
    return id;
}

QPainterPath UserImageItem::shapePath() const
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


void UserImageItem::parseXML(const QString &xml)
{
    AbstractZoneItem::parseXML(xml);
    id = attribute()->getData().toString();
}
