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

#ifndef PENPROPERTY_H
#define PENPROPERTY_H
#include <QPen>
#include "serializable.h"

class PenProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(PenProperty)
public:
    PenProperty() : Serializable() {};
    ~PenProperty(){};
    QPen getPen();
    bool noPen(){return style == Qt::NoPen;}
private:
    Qt::PenStyle style{Qt::NoPen};
    qreal width{0};
    QColor color{Qt::gray};
    Qt::PenCapStyle capStyle{Qt::FlatCap};
    Qt::PenJoinStyle joinStyle{Qt::MiterJoin};
    qreal miterLimit{1};

    JSONFIELD(style, Style)
    JSONFIELD(width, Width)
    JSONFIELD(color, Color)
    JSONFIELD(capStyle, Capstyle)
    JSONFIELD(joinStyle, JoinStyle)
    JSONFIELD(miterLimit, MiterLimit)
};

inline QPen PenProperty::getPen()
{
    QPen pen;
    pen.setWidthF(width);
    pen.setColor(color);
    pen.setStyle(style);
    pen.setCapStyle(capStyle);
    pen.setJoinStyle(joinStyle);
    pen.setMiterLimit(miterLimit);

    return pen;
}
#endif // PENPROPERTY_H
