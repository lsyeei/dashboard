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

#include "rotateparamwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

RotateParamWidget::RotateParamWidget(const QString &typeId, QWidget* parent)
    :AbstractParamWidget(typeId, parent){
    initUI();
}


void RotateParamWidget::initWidget()
{
    AnimationParam data;
    data.setTypeId(animationType);
    data.setValueFrom(0);
    data.setValueTo(60);

    update(data);
}

void RotateParamWidget::update(const AnimationParam &value)
{
    AbstractParamWidget::update(value);
    QSignalBlocker fromBlocker(from);
    QSignalBlocker toBlocker(to);
    from->setValue(value.getValueFrom().toInt());
    to->setValue(value.getValueTo().toInt());
}

void RotateParamWidget::onValueChanged()
{
    param.setValueFrom(from->value());
    param.setValueTo(to->value());
    AbstractParamWidget::onValueChanged();
}

void RotateParamWidget::initUI()
{
    auto r = new QHBoxLayout();
    r->setContentsMargins(0,0,0,0);
    layout->addLayout(r);

    r->addWidget(new QLabel{tr("角度：")});
    r->addWidget(new QLabel{tr("从")});

    from = new QSpinBox();
    r->addWidget(from);
    from->setRange(0, 360);
    from->setValue(0);
    from->setSuffix("°");
    from->setSingleStep(1);
    from->setAlignment(Qt::AlignCenter);
    from->setButtonSymbols(QAbstractSpinBox::NoButtons);

    r->addWidget(new QLabel{"到"});

    to = new QSpinBox();
    r->addWidget(to);
    to->setRange(0, 360);
    to->setValue(60);
    to->setSuffix("°");
    to->setSingleStep(1);
    to->setAlignment(Qt::AlignCenter);
    to->setButtonSymbols(QAbstractSpinBox::NoButtons);
    r->addStretch();

    connect(from, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
    connect(to, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
}
