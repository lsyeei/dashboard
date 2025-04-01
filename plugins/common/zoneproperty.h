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

#ifndef ZONEPROPERTY_H
#define ZONEPROPERTY_H

#include "baseproperty.h"
#include "brushproperty.h"
#include "penproperty.h"

class ZoneProperty : public BaseProperty
{
    Q_GADGET
    SERIALIZE(ZoneProperty)
public:
    ZoneProperty() : BaseProperty(){
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setColor(Qt::gray);
    };
    QRectF getLogicRect(){return {-width/2, -height/2, width, height};};
    bool hasBorder(){return !pen.noPen();}
    bool isFill(){return !brush.noBrush();}
private:
    // 区域大小及位置
    qreal width;
    qreal height;
    QPointF pos;
    // 旋转角度
    qreal rotate{0};
    // 固定宽高比
    bool aspectRatio{false};
    // 圆角
    bool rounded{false};
    // 圆角大小
    qreal arcSize{0};
    // 画笔
    PenProperty pen;
    // 画刷
    BrushProperty brush;
    // 扩展参数
    qreal extraP1;
    qreal extraP2;
    QVariant data;

    JSONFIELD(width, Width)
    JSONFIELD(height, Height)
    JSONFIELD(rotate, Rotate)
    JSONFIELD(pos, Pos)
    JSONFIELD(aspectRatio, AspectRatio)
    JSONFIELD(rounded, Round)
    JSONFIELD(arcSize, ArcSize)
    JSONFIELD(pen, Pen)
    JSONFIELD(brush, Brush)
    JSONFIELD(extraP1, ExtraP1)
    JSONFIELD(extraP2, ExtraP2)
    JSONFIELD(data, Data)
};

#endif // ZONEPROPERTY_H
