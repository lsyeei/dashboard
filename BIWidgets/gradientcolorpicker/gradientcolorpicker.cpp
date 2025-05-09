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

#include "gradientcolorpicker.h"
#include "gradientcolorpickerform.h"

#include <QResizeEvent>
#include <QVBoxLayout>

GradientColorPicker::GradientColorPicker(QWidget *parent) :
    QWidget(parent)
{
    form = new GradientColorPickerForm(this);
    QVBoxLayout layout(this);
    setLayout(&layout);
    layout.setAlignment(Qt::AlignTop);
    layout.setSizeConstraint(QLayout::SetNoConstraint);
    layout.setContentsMargins(0,0,0,0);
    layout.setSpacing(0);
    layout.addWidget(form);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    resize(form->size());
    connect(form, SIGNAL(valueChanged()), this, SLOT(onGradientValueChanged()));
}

GradientColorPicker::~GradientColorPicker()
{
    if (form) {
        delete form;
    }
}

QGradientStops GradientColorPicker::gradientStops()
{
    return form->getGradientStops();
}

void GradientColorPicker::setGradientStops(const QGradientStops stops)
{
    if (form) {
        form->setGradientStops(stops);
    }
}

QSize GradientColorPicker::sizeHint() const
{
    return {260, 160};
}


QSize GradientColorPicker::minimumSizeHint() const
{
    return {250,150};
}

void GradientColorPicker::onGradientValueChanged()
{
    emit gradientStopsChanged(form->getGradientStops());
}

void GradientColorPicker::resizeEvent(QResizeEvent *event)
{
    if (form) {
        form->resize(event->size());
    }

    QWidget::resizeEvent(event);
}
