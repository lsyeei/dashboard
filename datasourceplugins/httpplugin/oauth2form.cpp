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
#include "oauth2client.h"
#include <QMessageBox>

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
    if (oauth2Client) {
        delete oauth2Client;
        oauth2Client = nullptr;
    }
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
    QSignalBlocker blocker9(ui->userNameEdit);
    QSignalBlocker blocker10(ui->passwordEdit);
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
    ui->userNameEdit->setText(config.getUserName());
    ui->passwordEdit->setText(config.getPassword());
    updateUIByAuthModel();
}

QVariant OAuth2Form::getData() const
{
    return QVariant::fromValue(config);
}

void OAuth2Form::initLocation()
{
    ui->locationCombo->clear();
    auto list = AuthLocationDef::list();
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
                updateUIByAuthModel();
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
    connect(ui->testBtn, &QPushButton::clicked,
            this, &OAuth2Form::onTestBtnClicked);
}

void OAuth2Form::onTestBtnClicked()
{
    // 检查是否支持自动获取token的授权模式
    AuthModel authModel = config.getAuthModel();
    if (authModel != AuthModel::Credentials_Password &&
        authModel != AuthModel::Credentials_Client) {
        QMessageBox::warning(this, "不支持",
                          "当前授权模式不支持自动获取token。\n"
                          "请使用 Authorization Code 或 Implicit 模式手动完成授权流程。");
        return;
    }

    // 检查必要配置
    if (config.getAccessTokenUrl().isEmpty() || config.getClientId().isEmpty()) {
        QMessageBox::warning(this, "配置不完整",
                          "Access Token URL 和 Client ID 不能为空。");
        return;
    }

    // 对于 Password 模式，还需要用户名和密码
    if (authModel == AuthModel::Credentials_Password) {
        if (config.getUserName().isEmpty() || config.getPassword().isEmpty()) {
            QMessageBox::warning(this, "配置不完整",
                              "Password Credentials 模式需要用户名和密码。");
            return;
        }
    }

    // 创建 OAuth2Client 并请求 token
    if (!oauth2Client) {
        oauth2Client = new OAuth2Client(this);
    }

    oauth2Client->setConfig(config);

    if (oauth2Client->refreshToken()) {
        QString accessToken = oauth2Client->getAccessToken();
        QString idToken = oauth2Client->getIdToken();

        QString message = "Token 获取成功！\n\n";
        if (!accessToken.isEmpty()) {
            message += "Access Token:\n" + accessToken + "\n\n";
        }
        if (!idToken.isEmpty()) {
            message += "ID Token:\n" + idToken + "\n\n";
        }
        message += "Token 已缓存到配置中。";

        QMessageBox::information(this, "成功", message);
    } else {
        QMessageBox::critical(this, "失败",
                           "Token 获取失败！\n\n"
                           "请检查配置是否正确，网络连接是否正常。\n"
                           "详细信息请查看控制台输出。");
    }
}

void OAuth2Form::updateUIByAuthModel()
{
    bool isPasswordMode = (config.getAuthModel() == AuthModel::Credentials_Password);
    ui->label_9->setVisible(isPasswordMode);
    ui->userNameEdit->setVisible(isPasswordMode);
    ui->label_10->setVisible(isPasswordMode);
    ui->passwordEdit->setVisible(isPasswordMode);
}
