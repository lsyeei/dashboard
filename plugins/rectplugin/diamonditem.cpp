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

#include "diamonditem.h"
#include "zoneproperty.h"
#include "paintHelper.h"

QString DiamondItem::SHAPE_ID = "DIAMOND_2024";
DiamondItem::DiamondItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    setSize({80,60});
}

DiamondItem::DiamondItem(const QString &xml, QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString DiamondItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath DiamondItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto dx = logicRect.width() / 2;
    auto dy = logicRect.height() / 2;
    auto arcSize = attr->getArcSize();
    if (attr->getRound() && arcSize > 0) {
        QLineF l1{logicRect.topLeft() + QPointF{0, dy},
                  logicRect.topLeft() + QPointF{dx, 0}};
        QLineF l2{logicRect.topLeft() + QPointF{0, dy},
                  logicRect.bottomLeft() + QPointF{dx, 0}};
        path.moveTo(l1.center());
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);

        l1.setP1(logicRect.bottomLeft() + QPointF{dx, 0});
        l1.setP2(logicRect.bottomLeft() + QPointF{0, -dy});
        l2.setP1(logicRect.bottomLeft() + QPointF{dx, 0});
        l2.setP2(logicRect.bottomRight() + QPointF{0, -dy});
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);

        l1.setP1(logicRect.bottomRight() + QPointF{0, -dy});
        l1.setP2(logicRect.bottomLeft() + QPointF{dx, 0});
        l2.setP1(logicRect.bottomRight() + QPointF{0, -dy});
        l2.setP2(logicRect.topRight() + QPointF{-dx, 0});
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);

        l1.setP1(logicRect.topLeft() + QPointF{dx, 0});
        l1.setP2(logicRect.topRight() + QPointF{0, dy});
        l2.setP1(logicRect.topLeft() + QPointF{dx, 0});
        l2.setP2(logicRect.topLeft() + QPointF{0, dy});
        PaintHelper::drawRoundCorner(&path, l1, l2, arcSize);
    } else {
        auto x1 = logicRect.topLeft() + QPointF{0, dy};
        path.moveTo(x1);
        path.lineTo(logicRect.bottomLeft() + QPointF{dx, 0});
        path.lineTo(logicRect.topRight() + QPointF{0, dy});
        path.lineTo(logicRect.topRight() + QPointF{-dx, 0});
        path.lineTo(x1);
    }
    path.closeSubpath();
    return path;
}
