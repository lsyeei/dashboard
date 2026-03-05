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
#include "queryconfig.h"
#include "queryform.h"
#include "ui_queryform.h"

QueryForm::QueryForm(IDataQueryWidget *parent)
    : IDataQueryWidget(parent)
    , ui(new Ui::QueryForm)
{
    ui->setupUi(this);

    ui->replyWidget->hide();
    ui->queryMethodCombo->clear();
    auto list = QueryConfig::queryMethodList();
    foreach(auto item, list){
        ui->queryMethodCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
    ui->queryMethodCombo->setCurrentIndex(-1);
    ui->paramRadio->setChecked(true);
    initParamForm();
    paramForm->show();

    connect(ui->paramRadio, &QRadioButton::clicked, this, &QueryForm::onTabChanged);
    connect(ui->bodyRadio, &QRadioButton::clicked, this, &QueryForm::onTabChanged);
    connect(ui->headerRadio, &QRadioButton::clicked, this, &QueryForm::onTabChanged);
    connect(ui->queryUrlEdit, &QLineEdit::editingFinished,
            this, &QueryForm::onDataChanged);
    connect(ui->queryMethodCombo, &QComboBox::currentIndexChanged,
            this, &QueryForm::onDataChanged);
    connect(ui->switchBtn, &QToolButton::clicked, this, [&]{
        auto flag = ui->replyEdit->isVisible();
        ui->switchBtn->setArrowType(flag?Qt::RightArrow:Qt::DownArrow);
        ui->replyEdit->setVisible(!flag);
    });
}

QueryForm::~QueryForm()
{
    delete ui;
    if (client) {
        delete client;
        client = nullptr;
    }
}

QString QueryForm::getArgs()
{
    updateParam();
    return config.toJson();
}

void QueryForm::setArgs(const QString &args)
{
    config = QueryConfig::fromJson(args);
    updateUI();
}

void QueryForm::setDataSource(const QString &dataSourceArgs)
{
    connectArgs = dataSourceArgs;
}

QJsonDocument QueryForm::doTest()
{
    updateParam();
    if (client == nullptr) {
        client = new HttpClient();
    }
    client->connect(connectArgs);
    auto result = client->query(config.toJson());
    ui->replyEdit->setPlainText(result.toJson());
    ui->replyWidget->show();
    return result;
}

void QueryForm::initParamForm()
{
    paramForm = new KeyValueForm(this);
    auto vLayout = dynamic_cast<QVBoxLayout*>(layout());
    auto index = vLayout->indexOf(ui->replyWidget);
    vLayout->insertWidget(index, paramForm);
    connect(paramForm, &KeyValueForm::dataChangedEvent,
            this, &QueryForm::onDataChanged);
    paramForm->hide();
}

void QueryForm::initBodyForm()
{
    bodyForm = new BodyForm(this);
    auto vLayout = dynamic_cast<QVBoxLayout*>(layout());
    auto index = vLayout->indexOf(ui->replyWidget);
    vLayout->insertWidget(index, bodyForm);
    connect(bodyForm, &BodyForm::dataChangedEvent,
            this, &QueryForm::onDataChanged);
    bodyForm->hide();
}

void QueryForm::initHeaderForm()
{
    headerForm = new HeaderForm(this);
    auto vLayout = dynamic_cast<QVBoxLayout*>(layout());
    auto index = vLayout->indexOf(ui->replyWidget);
    vLayout->insertWidget(index, headerForm);
    connect(headerForm, &HeaderForm::dataChangedEvent,
            this, &QueryForm::onDataChanged);
    headerForm->hide();
}

void QueryForm::onTabChanged()
{
    auto name = sender()->objectName();
    paramForm->hide();
    if (!headerForm.isNull()) {
        headerForm->hide();
    }
    if (!bodyForm.isNull()) {
        bodyForm->hide();
    }
    if (name.compare("paramRadio") == 0) {
        paramForm->show();
    }else if(name.compare("bodyRadio") == 0) {
        if (bodyForm.isNull()) {
            initBodyForm();
        }
        bodyForm->show();
    }else if(name.compare("headerRadio") == 0) {
        if (headerForm.isNull()) {
            initHeaderForm();
        }
        headerForm->show();
    }
}

void QueryForm::onDataChanged()
{
    auto obj = sender();
    if (obj == ui->queryUrlEdit){
        config.setUrl(ui->queryUrlEdit->text().trimmed());
    }else if(obj == ui->queryMethodCombo){
        config.setMethod(ui->queryMethodCombo->currentData().value<QueryMethod>());
    }else if(obj == paramForm){
        config.setQueryParams(paramForm->getData().value<KVList>());
    }else if(obj == headerForm){
        config.setHeaders(headerForm->getData().value<HttpHeader>());
    }else if(obj == bodyForm){
        config.setBody(bodyForm->getData().value<HttpBody>());
    }
}

void QueryForm::updateParam()
{
    config.setUrl(ui->queryUrlEdit->text().trimmed());
    config.setMethod(ui->queryMethodCombo->currentData().value<QueryMethod>());
    if (!bodyForm.isNull()) {
        config.setBody(bodyForm->getData().value<HttpBody>());
    }
    if(!headerForm.isNull()){
        config.setHeaders(headerForm->getData().value<HttpHeader>());
    }
    if(!paramForm.isNull()){
        config.setQueryParams(paramForm->getData().value<KVList>());
    }
}

void QueryForm::updateUI()
{
    auto index = ui->queryMethodCombo->findData(QVariant::fromValue(config.getMethod()));
    ui->queryMethodCombo->setCurrentIndex(index);
    ui->queryUrlEdit->setText(config.getUrl());
    if (paramForm.isNull()) {
        initParamForm();
    }
    paramForm->setData(QVariant::fromValue(config.getQueryParams()));
    if (bodyForm.isNull()) {
        initBodyForm();
    }
    bodyForm->setData(QVariant::fromValue(config.getBody()));
    if (headerForm.isNull()) {
        initHeaderForm();
    }
    headerForm->setData(QVariant::fromValue(config.getHeaders()));
    ui->replyEdit->clear();
    ui->replyWidget->hide();
}
