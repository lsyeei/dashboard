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
#include "oauth2form.h"
#include "ui_oauth2form.h"

OAuth2Form::OAuth2Form(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::OAuth2Form)
{
    ui->setupUi(this);
    initLocation();
    initTokenType();
    initAuthModel();
    initEvent();
}

OAuth2Form::~OAuth2Form()
{
    delete ui;
}

void OAuth2Form::setData(const QVariant &data)
{
    config = data.value<Auth2Config>();
    // 更新UI
    QSignalBlocker blocker1(ui->authModelCombo);
    QSignalBlocker blocker2(ui->authUrlEdit);
    QSignalBlocker blocker3(ui->locationCombo);
    QSignalBlocker blocker4(ui->tokenTypeCombo);
    QSignalBlocker blocker5(ui->tokenUrlEdit);
    QSignalBlocker blocker6(ui->callbackUrlEdit);
    QSignalBlocker blocker7(ui->clientIdEdit);
    QSignalBlocker blocker8(ui->clientSecretEdit);
    auto index = ui->locationCombo->findData(QVariant::fromValue(config.getLocation()));
    ui->locationCombo->setCurrentIndex(index);
    index = ui->authModelCombo->findData(QVariant::fromValue(config.getAuthModel()));
    ui->authModelCombo->setCurrentIndex(index);
    index = ui->tokenTypeCombo->findData(QVariant::fromValue(config.getTokenType()));
    ui->tokenTypeCombo->setCurrentIndex(index);
    ui->authUrlEdit->setText(config.getAuthUrl());
    ui->tokenUrlEdit->setText(config.getAccessTokenUrl());
    ui->callbackUrlEdit->setText(config.getCallbackUrl());
    ui->clientIdEdit->setText(config.getClientId());
    ui->clientSecretEdit->setText(config.getClientSecret());
}

QVariant OAuth2Form::getData() const
{
    return QVariant::fromValue(config);
}

void OAuth2Form::initLocation()
{
    ui->locationCombo->clear();
    auto list = Auth2Config::locationList();
    foreach (auto item, list) {
        ui->locationCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
}

void OAuth2Form::initTokenType()
{
    ui->tokenTypeCombo->clear();
    auto list = Auth2Config::tokenTypeList();
    foreach (auto item, list) {
        ui->tokenTypeCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
}

void OAuth2Form::initAuthModel()
{
    ui->authModelCombo->clear();
    auto list = Auth2Config::authModelList();
    foreach (auto item, list) {
        ui->authModelCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
}

void OAuth2Form::initEvent()
{
    connect(ui->locationCombo, &QComboBox::currentIndexChanged,
            this, [&]{
            config.setLocation(ui->locationCombo->currentData().value<AuthLocation>());
            emit dataChangedEvent(QVariant::fromValue(config));
        });
    connect(ui->authModelCombo, &QComboBox::currentIndexChanged,
            this, [&]{
                config.setAuthModel(ui->authModelCombo->currentData().value<AuthModel>());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->tokenTypeCombo, &QComboBox::currentIndexChanged,
            this, [&]{
                config.setTokenType(ui->tokenTypeCombo->currentData().value<TokenType>());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->authUrlEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setAuthUrl(ui->authUrlEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->tokenUrlEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setAccessTokenUrl(ui->tokenUrlEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->callbackUrlEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setCallbackUrl(ui->callbackUrlEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->clientIdEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setClientId(ui->clientIdEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
    connect(ui->clientSecretEdit, &QLineEdit::editingFinished,
            this, [&]{
                config.setClientSecret(ui->clientSecretEdit->text().trimmed());
                emit dataChangedEvent(QVariant::fromValue(config));
            });
}
