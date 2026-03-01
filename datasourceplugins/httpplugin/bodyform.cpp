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
#include "bodyform.h"
#include "ui_bodyform.h"

BodyForm::BodyForm(QWidget *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::BodyForm)
{
    ui->setupUi(this);
    initUI();
}

BodyForm::~BodyForm()
{
    delete ui;
}

void BodyForm::setData(const QVariant &data)
{
    body = data.value<HttpBody>();
    // 更新UI
    QSignalBlocker blocker1(ui->contentTypeCombo);
    QSignalBlocker blocker2(ui->contentEdit);
    auto index = ui->contentTypeCombo->findData(body.getContentType());
    ui->contentTypeCombo->setCurrentIndex(index);
    ui->contentEdit->setPlainText(body.getContent());
}

QVariant BodyForm::getData() const
{
    return QVariant::fromValue(body);
}

void BodyForm::initUI()
{
    ui->contentTypeCombo->clear();
    auto list = HttpBody::contentTypeList();
    foreach (auto item, list) {
        ui->contentTypeCombo->addItem(item.first, item.second);
    }
    ui->contentTypeCombo->setCurrentIndex(-1);
    ui->tipLabel->setVisible(false);
    ui->contentEdit->setVisible(false);
    connect(ui->contentTypeCombo, &QComboBox::currentIndexChanged, this, [&]{
        bool flag = ui->contentTypeCombo->currentIndex()!=0;
        ui->tipLabel->setVisible(flag);
        ui->contentEdit->setVisible(flag);
        body.setContentType(ui->contentTypeCombo->currentData().toString());
        emit dataChangedEvent(getData());
    });
    connect(ui->contentEdit, &QTextEdit::textChanged, this, [&]{
        body.setContent(ui->contentEdit->toPlainText());
        emit dataChangedEvent(getData());
    });
}
