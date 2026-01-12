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
#include "dataassignform.h"
#include "ui_dataassignform.h"

#include <datahandler/assignaction.h>

DataAssignForm::DataAssignForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataAssignForm)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);
    connect(ui->propertyOptions, &QComboBox::currentIndexChanged,
            this, &DataAssignForm::dataChanged);
    connect(ui->defaultValueEdit, &QLineEdit::editingFinished,
            this, &DataAssignForm::dataChanged);
}

DataAssignForm::~DataAssignForm()
{
    delete ui;
}

void DataAssignForm::setGraphicsItem(QGraphicsItem *item)
{
    graphic = item;
    ui->propertyOptions->clear();
    // todo: 设置图元可用属性
}

void DataAssignForm::setData(QVariant data)
{
    QSignalBlocker editBlocker(ui->defaultValueEdit);
    QSignalBlocker optionsBlocker(ui->propertyOptions);
    reset();
    if (!data.canConvert<AssignAction>()) {
        return;
    }
    action = data.value<AssignAction>();
    auto property = action.getPropertyName();
    auto index = ui->propertyOptions->findData(property);
    ui->propertyOptions->setCurrentIndex(index);
    ui->defaultValueEdit->setText(action.getDefaultValue());
}

void DataAssignForm::dataChanged()
{
    action.setDefaultValue(ui->defaultValueEdit->text().trimmed());
    action.setPropertyName(ui->propertyOptions->currentData().toString());
    action.setPropertyAlias(ui->propertyOptions->currentText());
    emit changedEvent(QVariant::fromValue(action));
}

void DataAssignForm::reset()
{
    ui->defaultValueEdit->setText("");
    ui->propertyOptions->setCurrentIndex(-1);
}
