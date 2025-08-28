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

#include "scaleparamwidget.h"
#include "qboxlayout.h"

#include <QLabel>
#include <QSpinBox>

ScaleParamWidget::ScaleParamWidget(const QString &typeId, QWidget* parent)
    : AbstractParamWidget(typeId, parent) {
    initUI();
}


void ScaleParamWidget::initWidget()
{
    AnimationParam data;
    data.setTypeId(animationType);
    data.setValueFrom(0.1);
    data.setValueTo(0.8);

    update(data);
}

void ScaleParamWidget::update(const AnimationParam &value)
{
    AbstractParamWidget::update(value);
    QSignalBlocker fromBlocker(from);
    QSignalBlocker toBlocker(to);
    from->setValue(value.getValueFrom().toFloat()*100);
    to->setValue(value.getValueTo().toFloat()*100);
}

void ScaleParamWidget::onValueChanged()
{
    param.setValueFrom(from->value()*1.0 / 100);
    param.setValueTo(to->value()*1.0 / 100);
    AbstractParamWidget::onValueChanged();
}


void ScaleParamWidget::initUI()
{
    auto r = new QHBoxLayout();
    r->setContentsMargins(0,0,0,0);
    layout->addLayout(r);

    r->addWidget(new QLabel{tr("缩放比例：")});

    from = new QSpinBox();
    r->addWidget(from);
    from->setRange(1, 500);
    from->setSuffix("%");
    from->setSingleStep(5);
    from->setAlignment(Qt::AlignRight);
    from->setButtonSymbols(QAbstractSpinBox::NoButtons);

    r->addWidget(new QLabel{"-"});

    to = new QSpinBox();
    r->addWidget(to);
    to->setRange(1, 500);
    to->setSuffix("%");
    to->setSingleStep(5);
    to->setAlignment(Qt::AlignRight);
    to->setButtonSymbols(QAbstractSpinBox::NoButtons);

    r->addStretch();
    connect(from, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
    connect(to, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
}
