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

#include <LineProperty.h>
#include <QResizeEvent>
#include <QVBoxLayout>
#include <linepropertyform.h>

LineProperty::LineProperty(QWidget *parent) :
    QWidget(parent), form(new LinePropertyForm(this))
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
}
LineProperty::~LineProperty()
{}

Qt::PenStyle LineProperty::lineStyle() const
{
    return form->lineStyle();
}

void LineProperty::setLineStyle(Qt::PenStyle newLineStyle)
{
    form->setLineStyle(newLineStyle);
}

int LineProperty::lineWidth() const
{
    return form->lineWidth();
}

void LineProperty::setLineWidth(int newLineWidth)
{
    form->setLineWidth(newLineWidth);
}

QColor LineProperty::lineColor() const
{
    return form->lineColor();
}

void LineProperty::setLineColor(const QColor &newLineColor)
{
    form->setLineColor(newLineColor);
}

void LineProperty::formValueChanged()
{
    Qt::PenStyle style = Qt::NoPen;
    if (form->getShowLine()) {
        style = form->lineStyle();
    }
    emit propertyChanged(style, form->lineColor(), form->lineWidth());
}

bool LineProperty::showLine() const
{
    return form->getShowLine();
}

void LineProperty::setShowLine(bool newShowLine)
{
    if (form->getShowLine() == newShowLine)
        return;
    form->setShowLine(newShowLine);
}

bool LineProperty::alwaysShow() const
{
    return form->alwaysShow();
}

void LineProperty::setAlwaysShow(bool value)
{
    return form->setAlwaysShow(value);
}
