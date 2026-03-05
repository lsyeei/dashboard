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
#include "spnegoform.h"
#include "ui_spnegoform.h"

SPNEGOForm::SPNEGOForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::SPNEGOForm)
{
    ui->setupUi(this);
    initEvent();
}

SPNEGOForm::~SPNEGOForm()
{
    delete ui;
}

void SPNEGOForm::setData(const QVariant &data)
{
    config = data.value<SPNEGOConfig>();

    QSignalBlocker blocker1(ui->userNameEdit);
    QSignalBlocker blocker2(ui->passwordEdit);
    QSignalBlocker blocker3(ui->spnEdit);

    ui->userNameEdit->setText(config.getUserName());
    ui->passwordEdit->setText(config.getPassword());
    ui->spnEdit->setText(config.getSpn());
}

QVariant SPNEGOForm::getData() const
{
    return QVariant::fromValue(config);
}

void SPNEGOForm::initEvent()
{
    connect(ui->userNameEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setUserName(ui->userNameEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->passwordEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setPassword(ui->passwordEdit->text());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->spnEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setSpn(ui->spnEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
}
