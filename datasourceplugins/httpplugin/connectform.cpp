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
#include "connectform.h"
#include "ui_connectform.h"

ConnectForm::ConnectForm(IDataSourceWidget *parent)
    : IDataSourceWidget(parent)
    , ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    ui->authRadio->setChecked(true);
    initAuthForm();
    authForm->show();

    connect(ui->authRadio, &QRadioButton::clicked, this, &ConnectForm::onTabChanged);
    connect(ui->headerRadio, &QRadioButton::clicked, this, &ConnectForm::onTabChanged);
    connect(ui->cookieRadio, &QRadioButton::clicked, this, &ConnectForm::onTabChanged);
    connect(ui->settingRadio, &QRadioButton::clicked, this, &ConnectForm::onTabChanged);
    connect(ui->urlEdit, &QPlainTextEdit::textChanged, this, &ConnectForm::onDataChanged);
}

ConnectForm::~ConnectForm()
{
    delete ui;
}

void ConnectForm::initAuthForm()
{
    authForm = new AuthForm(this);
    layout()->addWidget(authForm);
    connect(authForm, &AuthForm::dataChangedEvent,
            this, &ConnectForm::onDataChanged);
    authForm->hide();
}

void ConnectForm::initHeaderForm()
{
    headerForm = new HeaderForm(this);
    layout()->addWidget(headerForm);
    connect(headerForm, &HeaderForm::dataChangedEvent,
            this, &ConnectForm::onDataChanged);
    headerForm->hide();
}

void ConnectForm::initCookieForm()
{
    cookieForm = new KeyValueForm(this);
    layout()->addWidget(cookieForm);
    connect(cookieForm, &KeyValueForm::dataChangedEvent,
            this, &ConnectForm::onDataChanged);
    cookieForm->hide();
}

void ConnectForm::initSettingForm()
{
    settingForm = new SettingForm(this);
    layout()->addWidget(settingForm);
    connect(settingForm, &SettingForm::dataChangedEvent,
            this, &ConnectForm::onDataChanged);
    settingForm->hide();
}

void ConnectForm::onTabChanged()
{
    auto name = sender()->objectName();
    authForm->hide();
    if (!headerForm.isNull()) {
        headerForm->hide();
    }
    if (!cookieForm.isNull()) {
        cookieForm->hide();
    }
    if (!settingForm.isNull()) {
        settingForm->hide();
    }
    if (name.compare("authRadio") == 0) {
        authForm->show();
    }else if(name.compare("headerRadio") == 0) {
        if (headerForm.isNull()) {
            initHeaderForm();
        }
        headerForm->show();
    }else if(name.compare("cookieRadio") == 0) {
        if (cookieForm.isNull()) {
            initCookieForm();
        }
        cookieForm->show();
    }else if(name.compare("settingRadio") == 0) {
        if (settingForm.isNull()) {
            initSettingForm();
        }
        settingForm->show();
    }
}

void ConnectForm::onDataChanged()
{
    auto obj = sender();
    if (obj == ui->urlEdit){
        httpConfig.setURL(ui->urlEdit->toPlainText().trimmed());
    }else if(obj == authForm){
        httpConfig.setAuthConfig(authForm->getData().value<AuthConfig>());
    }else if(cookieForm){
        httpConfig.setCookies(cookieForm->getData().value<KVList>());
    }else if(headerForm){
        httpConfig.setheaders(headerForm->getData().value<HttpHeader>());
    }else if(settingForm){
        httpConfig.setSetting(settingForm->getData().value<HttpSetting>());
    }
}

QString ConnectForm::getArgs()
{
    updateParam();
    return httpConfig.toJson();
}

void ConnectForm::setArgs(const QString &args)
{
    httpConfig = HttpConfig::fromJson(args);
    updateUI();
}

void ConnectForm::updateParam()
{
    httpConfig.setURL(ui->urlEdit->toPlainText().trimmed());
    if (authForm){
        httpConfig.setAuthConfig(authForm->getData().value<AuthConfig>());
    }
    if(cookieForm){
        httpConfig.setCookies(cookieForm->getData().value<KVList>());
    }
    if(headerForm){
        httpConfig.setheaders(headerForm->getData().value<HttpHeader>());
    }
    if(settingForm){
        httpConfig.setSetting(settingForm->getData().value<HttpSetting>());
    }
}

void ConnectForm::updateUI()
{
    ui->urlEdit->setPlainText(httpConfig.getURL());
    if (authForm.isNull()){
        initAuthForm();
    }
    authForm->setData(QVariant::fromValue(httpConfig.getAuthConfig()));
    if(cookieForm.isNull()){
        initCookieForm();
    }
    cookieForm->setData(QVariant::fromValue(httpConfig.getCookies()));
    if(headerForm.isNull()){
        initHeaderForm();
    }
    headerForm->setData(QVariant::fromValue(httpConfig.getheaders()));
    if(settingForm.isNull()){
        initSettingForm();
    }
    settingForm->setData(QVariant::fromValue(httpConfig.getSetting()));
}

