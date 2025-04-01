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

#include "abstractparamwidget.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

AbstractParamWidget::AbstractParamWidget(const QString &typeId, QWidget *parent)
    : QWidget{parent}, animationType(typeId)
{
    param.setTypeId(typeId);
    initUI();
}

void AbstractParamWidget::update(const AnimationParam &value)
{
    param = value;
    // todo: update UI
    QSignalBlocker delayBolcker(delay);
    QSignalBlocker durationBolcker(duration);
    QSignalBlocker loopCountBolcker(loopCount);
    QSignalBlocker infiniteBolcker(infinite);
    QSignalBlocker directBolcker(directional);
    QSignalBlocker bidirectBolcker(bidirectional);
    delay->setValue(param.getDelay());
    duration->setValue(param.getDuration());
    auto loop = param.getLoopCount();
    if (loop < 0) {
        loopCount->setValue(1);
        loopCount->setDisabled(true);
        infinite->setChecked(true);
    }else{
        loopCount->setValue(loop);
        infinite->setChecked(false);
    }
    directional->setChecked(param.getDirectional());
    bidirectional->setChecked(!param.getDirectional());
}

AnimationParam AbstractParamWidget::getParam()
{
    return param;
}

void AbstractParamWidget::setOwner(QGraphicsItem *item)
{
    if (item) {
        owner = item;
    }
}

void AbstractParamWidget::onValueChanged()
{
    param.setDelay(delay->value());
    param.setDuration(duration->value());
    param.setLoopCount(loopCount->value());
    if (infinite->isChecked()) {
        param.setLoopCount(-1);
    }
    param.setDirectional(directional->isChecked());

    emit paramChanged();
}

void AbstractParamWidget::onInfiniteStateChanged()
{
    if (infinite->isChecked()) {
        loopCount->setDisabled(true);
    }else{
        loopCount->setEnabled(true);
    }
    onValueChanged();
}

void AbstractParamWidget::initUI()
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    layout = new QVBoxLayout();
    this->setLayout(layout);
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(6);
    layout->setContentsMargins(0,0,0,0);
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    auto row1 = new QHBoxLayout();
    layout->addLayout(row1);
    row1->setContentsMargins(0,0,0,0);
    row1->addWidget(new QLabel{tr("延迟:")});
    delay = new QDoubleSpinBox();
    row1->addWidget(delay);
    delay->setSuffix(tr("秒"));
    delay->setMinimum(0.0);
    delay->setSingleStep(0.1);
    delay->setDecimals(1);
    delay->setAlignment(Qt::AlignRight);
    delay->setButtonSymbols(QDoubleSpinBox::NoButtons);
    row1->addStretch();
    row1->addWidget(new QLabel{tr("持续：")});
    duration = new QDoubleSpinBox();
    row1->addWidget(duration);
    duration->setSuffix(tr("秒"));
    duration->setMinimum(0.0);
    duration->setSingleStep(0.5);
    duration->setDecimals(1);
    duration->setAlignment(Qt::AlignRight);
    duration->setButtonSymbols(QDoubleSpinBox::NoButtons);

    auto row2 = new QHBoxLayout();
    layout->addLayout(row2);
    row2->setContentsMargins(0,0,0,0);
    directional = new QRadioButton{tr("单向重复")};
    row2->addWidget(directional);
    directional->setChecked(true);
    bidirectional = new QRadioButton(tr("双向重复"));
    row2->addWidget(bidirectional);
    bidirectional->setChecked(false);

    auto row3 = new QHBoxLayout();
    layout->addLayout(row3);
    row3->setContentsMargins(0,0,0,0);
    row3->addWidget(new QLabel{tr("重复:")});
    loopCount = new QSpinBox();
    row3->addWidget(loopCount);
    loopCount->setSuffix(tr("次"));
    loopCount->setMinimum(1);
    loopCount->setSingleStep(1);
    loopCount->setAlignment(Qt::AlignRight);
    loopCount->setButtonSymbols(QAbstractSpinBox::NoButtons);
    infinite = new QCheckBox{tr("循环播放")};
    row3->addWidget(infinite);
    row3->addStretch();

    connect(delay, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
    connect(duration, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
    connect(loopCount, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
    connect(infinite, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onInfiniteStateChanged()));
    connect(directional, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(bidirectional, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
}
