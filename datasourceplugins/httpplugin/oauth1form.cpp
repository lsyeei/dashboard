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
#include "oauth1form.h"
#include "ui_oauth1form.h"

OAuth1Form::OAuth1Form(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::OAuth1Form)
{
    ui->setupUi(this);
    initLocation();
    initEvent();
}

OAuth1Form::~OAuth1Form()
{
    delete ui;
}

void OAuth1Form::setData(const QVariant &data)
{
    config = data.value<Auth1Config>();
    // 更新UI
    QSignalBlocker blocker1(ui->locationCombo);
    QSignalBlocker blocker2(ui->consumerKeyEdit);
    QSignalBlocker blocker3(ui->consumerSecretEdit);
    QSignalBlocker blocker4(ui->tokenEdit);
    QSignalBlocker blocker5(ui->tokenSecretEdit);
    auto index = ui->locationCombo->findData(QVariant::fromValue(config.getLocation()));
    ui->locationCombo->setCurrentIndex(index);
    ui->consumerKeyEdit->setText(config.getConsumerKey());
    ui->consumerSecretEdit->setText(config.getConsumerSecret());
    ui->tokenEdit->setText(config.getToken());
    ui->tokenSecretEdit->setText(config.getTokenSecret());
}

QVariant OAuth1Form::getData() const
{
    return QVariant::fromValue(config);
}

void OAuth1Form::initLocation()
{
    ui->locationCombo->clear();
    auto list = AuthLocationDef::list();
    foreach (auto item, list) {
        ui->locationCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
}

void OAuth1Form::initEvent()
{
    connect(ui->locationCombo, &QComboBox::currentIndexChanged,
            this, [&]{
            config.setLocation(ui->locationCombo->currentData().value<AuthLocation>());
            emit dataChangedEvent(QVariant::fromValue(config));
        });
    connect(ui->consumerKeyEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setConsumerKey(ui->consumerKeyEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->consumerSecretEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setConsumerSecret(ui->consumerSecretEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->tokenEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setToken(ui->tokenEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->tokenSecretEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setTokenSecret(ui->tokenSecretEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
}
