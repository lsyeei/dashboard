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

#include "posproperty.h"

#include <PosPropertyForm.h>
#include <QResizeEvent>
#include <QVBoxLayout>

PosProperty::PosProperty(QWidget *parent) :
    QWidget(parent), form(new PosPropertyForm(this))
{
    QVBoxLayout vlayout(this);
    vlayout.setAlignment(Qt::AlignTop);
    vlayout.setSizeConstraint(QLayout::SetDefaultConstraint);
    vlayout.setContentsMargins(0,0,0,0);
    vlayout.addWidget(form.data());
    setLayout(&vlayout);

    resize(form->size());
    connect(form.data(), SIGNAL(valueChanged()), this, SLOT(valueChangeHandler()));
}

PosProperty::~PosProperty()
{}

qint32 PosProperty::left() const
{
    return form->getLeft();
}

void PosProperty::setLeft(qint32 newLeft)
{
    if (form->getLeft() == newLeft)
        return;
    form->setLeft(newLeft);
}

qint32 PosProperty::top() const
{
    return form->getTop();
}

void PosProperty::setTop(qint32 newTop)
{
    if (form->getTop() == newTop)
        return;
    form->setTop(newTop);
}

qint32 PosProperty::width() const
{
    return form->getWidth();
}

void PosProperty::setWidth(qint32 newWidth)
{
    if (form->getWidth() == newWidth)
        return;
    form->setWidth(newWidth);
}

qint32 PosProperty::height() const
{
    return form->getHeight();
}

void PosProperty::setHeight(qint32 newHeight)
{
    if (form->getHeight() == newHeight)
        return;
    form->setHeight(newHeight);
}

bool PosProperty::aspectRatio() const
{
    return form->getAspectRatio();
}

void PosProperty::setAspectRatio(bool newAspectRatio)
{
    if (form->getAspectRatio() == newAspectRatio)
        return;
    form->setAspectRatio(newAspectRatio);
}

QSize PosProperty::sizeHint() const
{
    return {320,110};
}

QSize PosProperty::minimumSizeHint() const
{
    return {320,110};
}


void PosProperty::resizeEvent(QResizeEvent *event)
{
    form->resize(event->size());
    QWidget::resizeEvent(event);
}

void PosProperty::valueChangeHandler()
{
    emit propertyChanged(form->getLeft(), form->getTop(),
                         form->getWidth(), form->getHeight(),
                        form->getAspectRatio());
}
