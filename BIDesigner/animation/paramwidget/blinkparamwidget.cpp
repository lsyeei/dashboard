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

#include "blinkparamwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>

BlinkParamWidget::BlinkParamWidget(const QString &typeId, QWidget* parent)
    : AbstractParamWidget(typeId, parent) {
    initUI();
}

void BlinkParamWidget::initWidget()
{
    AnimationParam data;
    data.setTypeId(animationType);
    data.setValueFrom(1);

    update(data);
}

void BlinkParamWidget::update(const AnimationParam &value)
{
    AbstractParamWidget::update(value);
    QSignalBlocker blocker(count);
    count->setValue(value.getValueFrom().toInt());
}

void BlinkParamWidget::initUI()
{
    auto r = new QHBoxLayout();
    r->setContentsMargins(0,0,0,0);
    layout->addLayout(r);

    r->addWidget(new QLabel{tr("闪烁：")});
    count = new QSpinBox();
    count->setRange(1,99);
    count->setValue(1);
    count->setSuffix(tr("次"));
    count->setAlignment(Qt::AlignRight);
    count->setSingleStep(1);
    r->addWidget(count);

    r->addStretch();

    connect(count, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
}


void BlinkParamWidget::onValueChanged()
{
    param.setValueFrom(QVariant::fromValue(count->value()));
    AbstractParamWidget::onValueChanged();
}
