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

#include "fillproperty.h"
#include "fillpropertyform.h"
#include <QResizeEvent>
#include <QLayout>
#include <QThread>

FillProperty::FillProperty(QWidget *parent) :
    QWidget(parent), form(new FillPropertyForm(this))
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    auto layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(form.data());
    setLayout(layout);
    // 处理属性值改变
    connect(form.data(), SIGNAL(valueChanged()), this, SLOT(formValueChanged()));
    connect(form.data(), SIGNAL(gradientChanged()), this, SLOT(gradientValueChanged()));
}

FillProperty::~FillProperty()
{
}

bool FillProperty::isFill() const
{
    return form->getIsFill();
}

void FillProperty::setIsFill(bool newFill)
{
    if (form->getIsFill() == newFill)
        return;
    form->setIsFill(newFill);
}

Qt::BrushStyle FillProperty::brushStyle() const
{
    return form->getStyle();
}

void FillProperty::setBrushStyle(Qt::BrushStyle newBrushStyle)
{
    if (form->getStyle() == newBrushStyle)
        return;
    form->setStyle(newBrushStyle);
}

QColor FillProperty::baseColor() const
{
    return form->getBaseColor();
}

void FillProperty::setBaseColor(const QColor &newBaseColor)
{
    if (form->getBaseColor() == newBaseColor)
        return;
    form->setBaseColor(newBaseColor);
}

QString FillProperty::imageFile() const
{
    return form->getImageFileName();
}

void FillProperty::setImageFile(const QString &newImageFile)
{
    if (form->getImageFileName() == newImageFile)
        return;
    form->setImageFileName(newImageFile);
}

bool FillProperty::gradient() const
{
    return form->getIsGradient();
}

void FillProperty::setGradient(bool newGradient)
{
    if (form->getIsGradient() == newGradient)
        return;
    form->setIsGradient(newGradient);
}

bool FillProperty::fillImage() const
{
    return form->getIsImage();
}

void FillProperty::setFillImage(bool newFillImage)
{
    if (form->getIsImage() == newFillImage)
        return;
    form->setIsImage(newFillImage);
}

QGradientStops FillProperty::gradientStops() const
{
    return form->getGradientStops();
}

void FillProperty::setGradientStops(const QGradientStops &newGradientStops)
{
    form->setGradientStops(newGradientStops);
}

void FillProperty::setGradientSpread(QGradient::Spread spread)
{
    form->setGradientSpread(spread);
}

QGradient::Spread FillProperty::gradientSpread()
{
    return form->getGradientSpread();
}

void FillProperty::setControlPoint(const QPainterPath &path, const QPolygonF &points)
{
    form->setControlPoint(path, points);
}

QPolygonF FillProperty::controlPoint()
{
    return form->getControlPoint();
}

void FillProperty::formValueChanged()
{
    auto style = form->getStyle();
    auto baseColor = form->getBaseColor();
    auto image = form->getImageFileName();
    if (style != Qt::TexturePattern) {
        image = "";
    }
    if (style == Qt::LinearGradientPattern ||
        style == Qt::RadialGradientPattern ||
        style == Qt::ConicalGradientPattern) {
        baseColor = Qt::transparent;
    }
    emit propertyChanged(style, baseColor, image);
}

void FillProperty::gradientValueChanged()
{
    emit gradientChanged(form->getStyle(), form->getGradientStops(), form->getGradientSpread(), form->getControlPoint());
}
