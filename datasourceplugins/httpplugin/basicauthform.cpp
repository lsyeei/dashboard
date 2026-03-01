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
#include "basicauthform.h"
#include "qjsonobject.h"
#include "ui_basicauthform.h"

BasicAuthForm::BasicAuthForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::BasicAuthForm)
{
    ui->setupUi(this);
    connect(ui->userNameEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
    connect(ui->passwordEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
    connect(ui->realmEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
    connect(ui->spnEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
}

BasicAuthForm::~BasicAuthForm()
{
    delete ui;
}

void BasicAuthForm::setData(const QVariant &data)
{
    QSignalBlocker userBlocker(ui->userNameEdit);
    QSignalBlocker pswBlocker(ui->passwordEdit);
    QSignalBlocker realmBlocker(ui->realmEdit);
    QSignalBlocker spnBlocker(ui->spnEdit);
    auto obj = data.toJsonObject();
    ui->userNameEdit->setText(obj["userName"].toString());
    ui->passwordEdit->setText(obj["password"].toString());
    ui->realmEdit->setText(obj["realm"].toString());
    ui->spnEdit->setText(obj["spn"].toString());
}

QVariant BasicAuthForm::getData() const
{
    QJsonObject data;
    data["userName"] = ui->userNameEdit->text().trimmed();
    data["password"] = ui->passwordEdit->text().trimmed();
    data["realm"] = ui->realmEdit->text().trimmed();
    data["spn"] = ui->spnEdit->text().trimmed();
    return data;
}
