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
#include "headerform.h"
#include "ui_headerform.h"
#include <QComboBox>
#include <QLineEdit>
#include <QMenu>
#include <QtNetwork/qnetworkrequest.h>

HeaderForm::HeaderForm(QWidget *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::HeaderForm)
{
    ui->setupUi(this);
    initMenu();
    initDataTable();
    ui->delBtn->setEnabled(false);
    connect(ui->addBtn, &QToolButton::clicked,
            this, &HeaderForm::onAddBtnClicked);
    connect(ui->delBtn, &QToolButton::clicked,
            this, &HeaderForm::onDelBtnClicked);
}

HeaderForm::~HeaderForm()
{
    delete ui;
}

void HeaderForm::setData(const QVariant &data)
{
    headerParams = data.value<HttpHeader>();
    updateUI();
}

QVariant HeaderForm::getData() const
{
    return QVariant::fromValue(headerParams);
}

void HeaderForm::onDataChanged(int row, int column)
{
    if (row < 0 || column < 0) {
        return;
    }
    auto item = ui->keyValueTable->item(row, column);
    if (item == nullptr) {
        return;
    }
    if (column == 0){
        auto data = item->data(Qt::UserRole).value<CustomData>();
        if (data.type == HeaderItemType::Custom) {
            headerParams[row].setKey(item->text().trimmed());
        }else{
            headerParams[row].setKey(QVariant::fromValue(data.knownHeader));
        }
    }else if (column == 1){
        headerParams[row].setValue(item->text().trimmed());
    }else if (column == 2){
        headerParams[row].setNote(item->text().trimmed());
    }
    emit dataChangedEvent(headerParams);
}

void HeaderForm::onAddBtnClicked(bool checked)
{
    Q_UNUSED(checked)
    HttpHeaderItem param;
    headerParams << param;
    auto index = addTableRow(param);
    ui->keyValueTable->scrollToBottom();
    ui->keyValueTable->setCurrentCell(index, 0);
    ui->keyValueTable->setFocus();
}

void HeaderForm::onDelBtnClicked(bool checked)
{
    Q_UNUSED(checked)
    auto row = ui->keyValueTable->currentRow();
    ui->keyValueTable->removeRow(row);
    headerParams.remove(row);
    // auto items = ui->keyValueTable->selectedItems();
    // foreach (auto item, items) {
    //     auto index = ui->keyValueTable->indexFromItem(item);
    //     ui->keyValueTable->removeRow(index.row());
    // }
    // auto count = ui->keyValueTable->rowCount();
    // headerParams.clear();
    // for(int i=0;i<count;i++){
    //     headerParams << getTableRow(i);
    // }
    emit dataChangedEvent(headerParams);
}

void HeaderForm::initMenu()
{
    popMenu = new QMenu();
    auto knownHeaders = HttpHeaderItem::knownHeaders();
    foreach (auto item, knownHeaders) {
        popMenu->addAction(item.first, this, [&,item]{
            auto keyItem = ui->keyValueTable->currentItem();
            if (keyItem) {
                auto customData = keyItem->data(Qt::UserRole).value<CustomData>();
                customData.type = HeaderItemType::Known;
                customData.knownHeader=item.second;
                customData.text = item.first;
                keyItem->setText(item.first);
                keyItem->setData(Qt::UserRole, QVariant::fromValue(customData));
            }
        });
    }
}

void HeaderForm::initDataTable()
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
            this, &HeaderForm::onDataChanged);
    connect(ui->keyValueTable, &QTableWidget::cellDoubleClicked,
            this, [&](int row, int col){
        if(col == 0){
            auto pos = QCursor::pos();
            popMenu->popup(pos);
        }
    });
}

void HeaderForm::updateUI()
{
    ui->keyValueTable->clearContents();
    ui->keyValueTable->setRowCount(0);
    foreach (auto item, headerParams) {
        addTableRow(item);
    }
}

int HeaderForm::addTableRow(const HttpHeaderItem &param)
{
    CustomData data;
    data.type = param.getType();
    if (param.getType() == HeaderItemType::Custom) {
        data.text = param.getKey().toString();
    }else{
        data.knownHeader = param.getKey().value<QHttpHeaders::WellKnownHeader>();
        data.text = knownHeaderName(data.knownHeader);
    }
    auto index = ui->keyValueTable->rowCount();
    ui->keyValueTable->insertRow(index);
    auto item = new QTableWidgetItem();
    item->setText(data.text);
    item->setData(Qt::UserRole, QVariant::fromValue(data));
    ui->keyValueTable->setItem(index, 0, item);
    ui->keyValueTable->setItem(index, 1, new QTableWidgetItem(param.getValue()));
    ui->keyValueTable->setItem(index, 2, new QTableWidgetItem(param.getNote()));
    return index;
}

HttpHeaderItem HeaderForm::getTableRow(int row) const
{
    HttpHeaderItem param;
    auto item = ui->keyValueTable->item(row,0);
    auto data = item->data(Qt::UserRole).value<CustomData>();
    param.setType(data.type);
    if(data.type == HeaderItemType::Custom){
        param.setKey(data.text);
    }else{
        param.setKey(QVariant::fromValue(data.knownHeader));
    }
    item = ui->keyValueTable->item(row,1);
    param.setValue(item->text().trimmed());
    item = ui->keyValueTable->item(row,2);
    param.setNote(item->text().trimmed());
    return param;
}

QString HeaderForm::knownHeaderName(QHttpHeaders::WellKnownHeader knownHeader)
{
    auto knownHeaders = HttpHeaderItem::knownHeaders();
    foreach (auto item, knownHeaders) {
        if (item.second == knownHeader) {
            return item.first;
        }
    }
    return "unkonwn";
}
