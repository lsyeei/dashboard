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
#include "jwtform.h"
#include "ui_jwtform.h"

JWTForm::JWTForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::JWTForm)
{
    ui->setupUi(this);
    initLocation();
    initEvent();
}

JWTForm::~JWTForm()
{
    delete ui;
}

void JWTForm::setData(const QVariant &data)
{
    config = data.value<JWTConfig>();

    QSignalBlocker blocker1(ui->locationCombo);
    QSignalBlocker blocker2(ui->tokenEdit);
    QSignalBlocker blocker3(ui->headerPrefixEdit);

    auto index = ui->locationCombo->findData(QVariant::fromValue(config.getLocation()));
    ui->locationCombo->setCurrentIndex(index);
    ui->tokenEdit->setPlainText(config.getToken());
    ui->headerPrefixEdit->setText(config.getHeaderPrefix());
}

QVariant JWTForm::getData() const
{
    return QVariant::fromValue(config);
}

void JWTForm::initLocation()
{
    ui->locationCombo->clear();
    auto list = AuthLocationDef::list();
    foreach (auto item, list) {
        ui->locationCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
}

void JWTForm::initEvent()
{
    connect(ui->locationCombo, &QComboBox::currentIndexChanged,
            this, [&]{
                config.setLocation(ui->locationCombo->currentData().value<AuthLocation>());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->tokenEdit, &QPlainTextEdit::textChanged,
            this, [&]{
                config.setToken(ui->tokenEdit->toPlainText());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->headerPrefixEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setHeaderPrefix(ui->headerPrefixEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
}
