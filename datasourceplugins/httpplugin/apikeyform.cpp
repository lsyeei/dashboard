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
#include "apikeyform.h"
#include "qjsonobject.h"
#include "ui_apikeyform.h"

APIKeyForm::APIKeyForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::APIKeyForm)
{
    ui->setupUi(this);
    ui->locationCombo->clear();
    ui->locationCombo->addItem("Header", "Header");
    ui->locationCombo->addItem("Query Param", "Query");
    connect(ui->locationCombo, &QComboBox::currentIndexChanged,
            this, [&]{emit dataChangedEvent(getData());});
    connect(ui->keyEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
    connect(ui->valueEdit, &QLineEdit::editingFinished,
            this, [&]{emit dataChangedEvent(getData());});
}

APIKeyForm::~APIKeyForm()
{
    delete ui;
}

void APIKeyForm::setData(const QVariant &data)
{
    QSignalBlocker keyBlocker(ui->keyEdit);
    QSignalBlocker valueBlocker(ui->valueEdit);
    auto obj = data.toJsonObject();
    ui->keyEdit->setText(obj["key"].toString());
    ui->valueEdit->setText(obj["value"].toString());
}

QVariant APIKeyForm::getData() const
{
    QJsonObject data;
    data["location"] = ui->locationCombo->currentData().toString();
    data["key"] = ui->keyEdit->text().trimmed();
    data["value"] = ui->valueEdit->text().trimmed();
    return data;
}
