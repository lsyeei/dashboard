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

#ifndef RECTPROPERTY_H
#define RECTPROPERTY_H

#include "serializable.h"
#include <QRectF>
#include <QColor>
#include <QLineF>


class RectProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(RectProperty)
public:
    explicit RectProperty();
    ~RectProperty();
private:
    // 属性集ID
    qint32 id;
    // 属性集合名称
    QString name;
    // 中心位置
    QPointF center;
    // 大小
    QSizeF size;
    // 旋转角度
    qreal rotate{0};
    // 固定宽高比
    bool aspectRatio{false};
    // 圆角
    bool rounded{false};
    // 圆角大小
    qreal arcSize{0};
    // 边
    bool isShowBorder{true};
    Qt::PenStyle borderStyle{Qt::SolidLine};
    qint32 borderWidth{1};
    QColor borderColor{Qt::gray};
    // 底色
    bool isFillBackground{false};
    Qt::BrushStyle bgBrushStyle{Qt::NoBrush};
    QColor bgColorFrom{Qt::white};
    QColor bgColorTo{Qt::darkGray};
    QString bgImage;

    JSONFIELD(id, Id)
    JSONFIELD(name, Name)
    JSONFIELD(center, Center)
    JSONFIELD(size, Size)
    JSONFIELD(rotate, Rotate)
    JSONFIELD(aspectRatio, AspectRatio)
    JSONFIELD(rounded, Rounded)
    JSONFIELD(arcSize, ArcSize)
    JSONFIELD(isShowBorder, IsShowBorder)
    JSONFIELD(borderStyle, BorderStyle)
    JSONFIELD(borderWidth, BorderWidth)
    JSONFIELD(borderColor, BorderColor)
    JSONFIELD(isFillBackground, IsFillBackground)
    JSONFIELD(bgBrushStyle, BgBrushStyle)
    JSONFIELD(bgColorFrom, BgColorFrom)
    JSONFIELD(bgColorTo, BgColorTo)
    JSONFIELD(bgImage, BgImage)

};
Q_DECLARE_METATYPE(RectProperty)
#endif // RECTPROPERTY_H
