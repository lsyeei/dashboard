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
#include "authform.h"
#include "ui_authform.h"
#include "authdef.h"

AuthForm::AuthForm(QWidget *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    ui->authMethodCombo->clear();
    foreach (auto item, AuthDef::list) {
        ui->authMethodCombo->addItem(item.alias, QVariant::fromValue(item.method));
    }
    connect(ui->authMethodCombo, &QComboBox::currentIndexChanged,
            this, &AuthForm::onSelectedAuthChanged);
}

AuthForm::~AuthForm()
{
    foreach (auto widget, subFormMap) {
        delete widget;
    }
    subFormMap.clear();
    delete ui;
}

void AuthForm::setData(const QVariant &data)
{
    QSignalBlocker comboBlocker(ui->authMethodCombo);
    authConfig = data.value<AuthConfig>();
    auto method = authConfig.getMethod();
    auto index = ui->authMethodCombo->findData(QVariant::fromValue(method));
    ui->authMethodCombo->setCurrentIndex(index);
    // 显示对应的配置UI，并设置数据
    hideSubForm();
    if (subFormMap[method] == nullptr) {
        return;
    }
    subFormMap[method]->setData(authConfig.getConfig());
    subFormMap[method]->show();
}

QVariant AuthForm::getData() const
{
    return QVariant::fromValue(authConfig);
}

void AuthForm::onSelectedAuthChanged(int index)
{
    hideSubForm();
    auto method = ui->authMethodCombo->currentData().value<AuthMethod>();
    if (!subFormMap.contains(method)) {
        AbstractSubForm *form{nullptr};
        foreach (auto item, AuthDef::list) {
            if (item.method == method) {
                form = item.form();
                break;
            }
        }
        layout()->addWidget(form);
        connect(form, &AbstractSubForm::dataChangedEvent,
                this, &AuthForm::onAuthDataChanged);
        subFormMap[method] = form;
    }else{
        if (subFormMap[method]) {
            subFormMap[method]->show();
        }
    }
    authConfig.setMethod(method);
    emit dataChangedEvent(QVariant::fromValue(authConfig));
}

void AuthForm::onAuthDataChanged(const QVariant &data)
{    
    auto method = ui->authMethodCombo->currentData().value<AuthMethod>();
    authConfig.setMethod(method);
    if (!subFormMap.contains(method)) {
        authConfig.setConfig(data);
    }else{
        authConfig.setConfig(QVariant());
    }
    emit dataChangedEvent(QVariant::fromValue(authConfig));
}

void AuthForm::hideSubForm()
{
    foreach (auto widget, subFormMap) {
        if (widget){
            widget->hide();
        }
    }
}
