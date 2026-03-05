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
#include "ntlmform.h"
#include "ui_ntlmform.h"

NTLMForm::NTLMForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::NTLMForm)
{
    ui->setupUi(this);
    initEvent();
}

NTLMForm::~NTLMForm()
{
    delete ui;
}

void NTLMForm::setData(const QVariant &data)
{
    config = data.value<NTLMConfig>();

    QSignalBlocker blocker1(ui->userNameEdit);
    QSignalBlocker blocker2(ui->passwordEdit);
    QSignalBlocker blocker3(ui->realmEdit);
    QSignalBlocker blocker4(ui->spnEdit);

    ui->userNameEdit->setText(config.getUserName());
    ui->passwordEdit->setText(config.getPassword());
    ui->realmEdit->setText(config.getRealm());
    ui->spnEdit->setText(config.getSpn());
}

QVariant NTLMForm::getData() const
{
    return QVariant::fromValue(config);
}

void NTLMForm::initEvent()
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
    connect(ui->realmEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setRealm(ui->realmEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->spnEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setSpn(ui->spnEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
}
