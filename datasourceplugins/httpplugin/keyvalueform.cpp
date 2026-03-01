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
#include "keyvalueform.h"
#include "ui_keyvalueform.h"

KeyValueForm::KeyValueForm(QWidget *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::KeyValueForm)
{
    ui->setupUi(this);
    initDataTable();
    ui->delBtn->setEnabled(false);
    connect(ui->addBtn, &QToolButton::clicked, this, &KeyValueForm::onAddBtnClicked);
    connect(ui->delBtn, &QToolButton::clicked, this, &KeyValueForm::onDelBtnClicked);
}

KeyValueForm::~KeyValueForm()
{
    delete ui;
}

void KeyValueForm::initDataTable()
{
    ui->keyValueTable->setColumnCount(3);
    ui->keyValueTable->setHorizontalHeaderLabels({tr("参数"), tr("默认值"),
                                              tr("注释")});
    ui->keyValueTable->setColumnWidth(0, 90);
    ui->keyValueTable->setColumnWidth(1, 100);
    ui->keyValueTable->setColumnWidth(2, 80);
    auto header = ui->keyValueTable->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Interactive);
    header->setSectionResizeMode(1, QHeaderView::Interactive);
    header->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->keyValueTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->keyValueTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->keyValueTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->keyValueTable, &QTableWidget::itemSelectionChanged, this,[&]{
        auto items = ui->keyValueTable->selectedItems();
        bool flag = items.count() > 0;
        ui->delBtn->setEnabled(flag);
    });
    connect(ui->keyValueTable, &QTableWidget::cellChanged,
            this, &KeyValueForm::onDataChanged);
}

void KeyValueForm::updateUI()
{
    ui->keyValueTable->clearContents();
    ui->keyValueTable->setRowCount(0);
    foreach (auto item, keyValues) {
        addTableRow(item);
    }
}

int KeyValueForm::addTableRow(const KeyValue &param)
{
    auto index = ui->keyValueTable->rowCount();
    ui->keyValueTable->insertRow(index);
    ui->keyValueTable->setItem(index, 0, new QTableWidgetItem(param.getKey()));
    ui->keyValueTable->setItem(index, 1, new QTableWidgetItem(param.getValue()));
    ui->keyValueTable->setItem(index, 2, new QTableWidgetItem(param.getNote()));
    return index;
}

KeyValue KeyValueForm::getTableRow(int row) const
{
    KeyValue param;
    auto item = ui->keyValueTable->item(row,0);
    param.setKey(item->text().trimmed());
    item = ui->keyValueTable->item(row,1);
    param.setValue(item->text().trimmed());
    item = ui->keyValueTable->item(row,2);
    param.setNote(item->text().trimmed());
    return param;
}

void KeyValueForm::setData(const QVariant &data)
{
    keyValues = data.value<KVList>();
    updateUI();
}

QVariant KeyValueForm::getData() const
{
    return QVariant::fromValue(keyValues);
}

void KeyValueForm::onDataChanged(int row, int column)
{
    auto item = ui->keyValueTable->item(row, column);
    if (column == 0){
        keyValues[row].setKey(item->text().trimmed());
    }else if (column == 1){
        keyValues[row].setValue(item->text().trimmed());
    }else if (column == 2){
        keyValues[row].setNote(item->text().trimmed());
    }
    emit dataChangedEvent(QVariant::fromValue(keyValues));
}

void KeyValueForm::onAddBtnClicked()
{
    KeyValue param;
    keyValues << param;
    auto index = addTableRow(param);
    ui->keyValueTable->scrollToBottom();
    ui->keyValueTable->setCurrentCell(index, 0);
    ui->keyValueTable->setFocus();
}

void KeyValueForm::onDelBtnClicked()
{    
    auto row = ui->keyValueTable->currentRow();
    ui->keyValueTable->removeRow(row);
    keyValues.remove(row);
    emit dataChangedEvent(QVariant::fromValue(keyValues));
}
