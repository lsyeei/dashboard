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

#ifndef BRUSHPROPERTY_H
#define BRUSHPROPERTY_H
#include "serializable.h"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QImage>
#include <QLinearGradient>

class BrushProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(BrushProperty)
public:
    explicit BrushProperty();
    ~BrushProperty();
    bool noBrush(){return style == Qt::NoBrush;}
    /**
     * @brief 生成画刷
     * @param rect 画刷绘制的图形大小
     * @return  画刷
     */
    QBrush getBrush(QRect rect);
private:
    Qt::BrushStyle style{Qt::NoBrush};
    QColor color{Qt::white};
    QString image;
    // 渐变色， <位置, 颜色>列表
    QGradientStops gradientStops;
    // 渐变色绘制位置参数
    QPolygonF location;
    // 填充方式
    QGradient::Spread gradientSpread{QGradient::PadSpread};

    JSONFIELD(style, Style)
    JSONFIELD(color, Color)
    JSONFIELD(image, Image)
    JSONFIELD(gradientStops, GradientStops)
    JSONFIELD(gradientSpread, gradientSpread)
    JSONFIELD(location, Location)
};

inline BrushProperty::BrushProperty()
    : Serializable()
{
    gradientStops << QGradientStop{0, Qt::white} << QGradientStop{1, Qt::black};
}

inline BrushProperty::~BrushProperty()
{
}

#include <QDebug>
inline QBrush BrushProperty::getBrush(QRect rect)
{
    QBrush brush;
    if (style == Qt::TexturePattern) {
        if (!image.isNull() &&
            !image.isEmpty() &&
            QFile::exists(image)){
            auto screenRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
            QImage imageObj;
            imageObj.load(image);
            QImage paintImage = imageObj.scaled(rect.width() * screenRatio,
                            rect.height() * screenRatio,
                            Qt::IgnoreAspectRatio,
                            Qt::SmoothTransformation);
            paintImage.setDevicePixelRatio(screenRatio);
            brush.setTextureImage(paintImage);
            return brush;
        }
    } else if (style == Qt::LinearGradientPattern){
        QLinearGradient linearGrad(rect.left(),rect.top(),rect.right(),rect.top());
        if (!location.isEmpty()) {
            linearGrad.setStart(location[0]);
            linearGrad.setFinalStop(location[1]);
        }
        linearGrad.setStops(gradientStops);
        linearGrad.setSpread(gradientSpread);
        return linearGrad;
    } else if (style == Qt::RadialGradientPattern) {
        QRadialGradient radialGrad(rect.center(), qMax(rect.width(), rect.height()));
        if (!location.isEmpty()) {
            radialGrad.setCenter(location[0]);
            radialGrad.setFocalPoint(location.at(1));
            radialGrad.setCenterRadius(qAbs(location[2].x()));
            radialGrad.setFocalRadius(qAbs(location[2].y()));
            // radialGrad.setCenterRadius(qMin(rect.width(), rect.height()) / 3.0);
        }
        radialGrad.setStops(gradientStops);
        radialGrad.setSpread(gradientSpread);
        return radialGrad;
    } else if (style == Qt::ConicalGradientPattern){
        QConicalGradient conicalGrad(rect.center(),0);
        if (!location.isEmpty()) {
            QLineF l(location.at(0), location.at(1));
            qreal angle = QLineF(0, 0, 1, 0).angleTo(l);
            conicalGrad.setCenter(location[0]);
            conicalGrad.setAngle(angle);
        }
        conicalGrad.setStops(gradientStops);
        conicalGrad.setSpread(gradientSpread);
        return conicalGrad;
    }else {
        brush.setStyle(style);
        brush.setColor(color);
    }
    return brush;
}

#endif // BRUSHPROPERTY_H
