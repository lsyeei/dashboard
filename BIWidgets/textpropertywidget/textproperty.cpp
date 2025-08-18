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

#include "textproperty.h"
#include "textpropertyform.h"

#include <QResizeEvent>
#include <QVBoxLayout>

TextProperty::TextProperty(QWidget *parent) :
    QWidget(parent), form(new TextPropertyForm(this))
{
    QVBoxLayout vlayout(this);
    vlayout.setAlignment(Qt::AlignTop);
    vlayout.setSizeConstraint(QLayout::SetFixedSize);
    vlayout.addWidget(form.data());
    setLayout(&vlayout);

    resize(form->size());
    connect(form.data(), SIGNAL(textFormatChanged(QTextFormat)), this, SLOT(onFormChangeFormat(QTextFormat)));
}

TextProperty::~TextProperty()
{
}

QTextCharFormat TextProperty::getCharFormat() const
{
    return form->getCharFormat();
}

QTextBlockFormat TextProperty::getBlockFormat() const
{
    return form->getBlockFormat();
}

void TextProperty::setTextFormat(const QTextFormat &format)
{
    form->setTextFormat(format);
}

QSize TextProperty::sizeHint() const
{
    return {245,410};
}

QSize TextProperty::minimumSizeHint() const
{
    return {245,360};
}


void TextProperty::resizeEvent(QResizeEvent *event)
{
    form->resize(event->size());
    QWidget::resizeEvent(event);
}

void TextProperty::onFormChangeFormat(const QTextFormat &format)
{
    emit textFormatChanged(format);
}
