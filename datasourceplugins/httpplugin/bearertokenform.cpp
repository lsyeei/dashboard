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
#include "bearertokenform.h"
#include "ui_bearertokenform.h"

#include <QJsonObject>

BearerTokenForm::BearerTokenForm(AbstractSubForm *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::BearerTokenForm)
{
    ui->setupUi(this);
    connect(ui->tokenEdit, &QPlainTextEdit::textChanged,
            this, [&]{emit dataChangedEvent(getData());});
}

BearerTokenForm::~BearerTokenForm()
{
    delete ui;
}

void BearerTokenForm::setData(const QVariant &data)
{
    QSignalBlocker blocker(ui->tokenEdit);
    auto obj = data.toJsonObject();
    ui->tokenEdit->setPlainText(obj["token"].toString());
}

QVariant BearerTokenForm::getData() const
{
    QJsonObject data;
    data["token"] = ui->tokenEdit->toPlainText();
    return data;
}
