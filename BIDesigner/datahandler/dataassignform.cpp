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
#include "icustomgraphic.h"
#include "ui_dataassignform.h"

#include <datahandler/assignaction.h>

DataAssignForm::DataAssignForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataAssignForm)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);
    connect(ui->propertyOptions, &QComboBox::currentIndexChanged,
            this, &DataAssignForm::onPropertyChanged);
    connect(ui->defaultValueEdit, &QLineEdit::editingFinished,
            this, &DataAssignForm::dataChanged);
}

DataAssignForm::~DataAssignForm()
{
    delete ui;
}

void DataAssignForm::initPropertyOption(auto customGraphic)
{
    QSignalBlocker optionBlocker(ui->propertyOptions);
    ui->propertyOptions->clear();
    auto list = customGraphic->metadataList();
    foreach (auto meta, list) {
        if (meta.mode== OperateMode::ReadOnly ||
            meta.name.compare("state") == 0) {
            continue;
        }
        ui->propertyOptions->addItem(meta.alias, QVariant::fromValue(meta));
    }
    ui->propertyOptions->setCurrentIndex(-1);
}

void DataAssignForm::setGraphicsItem(QGraphicsItem *item)
{
    graphic = item;
    auto customGraphic = dynamic_cast<ICustomGraphic*>(item);
    initPropertyOption(customGraphic);
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
    auto index = ui->propertyOptions->count() - 1;
    for (; index >= 0; -- index) {
        auto meta = ui->propertyOptions->itemData(index).value<CustomMetadata>();
        if (meta.name.compare(property) == 0) {
            break;
        }
    }
    ui->propertyOptions->setCurrentIndex(index);
    ui->defaultValueEdit->setText(action.getDefaultValue());
}

void DataAssignForm::dataChanged()
{
    action.setDefaultValue(ui->defaultValueEdit->text().trimmed());    
    auto meta = ui->propertyOptions->currentData().value<CustomMetadata>();
    action.setPropertyName(meta.name);
    action.setPropertyAlias(ui->propertyOptions->currentText());
    emit changedEvent(QVariant::fromValue(action));
}

void DataAssignForm::onPropertyChanged()
{
    if (ui->propertyOptions->currentIndex() < 0) {
        ui->propertyLabel->setText("");
        return;
    }
    auto meta = ui->propertyOptions->currentData().value<CustomMetadata>();
    QString text{"数据类型：%1 \r\n例:  %2"};
    text = text.arg(meta.dataTypeName(), meta.dataExample);
    ui->propertyLabel->setText(text);
    dataChanged();
}

void DataAssignForm::reset()
{
    ui->defaultValueEdit->setText("");
    ui->propertyOptions->setCurrentIndex(-1);
}

void DataAssignForm::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    if (graphic == nullptr) {
        return;
    }
    auto customGraphic = dynamic_cast<ICustomGraphic*>(graphic);
    if (customGraphic == nullptr) {
        return;
    }
    initPropertyOption(customGraphic);
}
