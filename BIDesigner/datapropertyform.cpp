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
#include "datapropertyform.h"
#include "datasource/datasourceform.h"
#include "bigraphicsscene.h"
#include "datahandler/dataeditorform.h"
#include "ui_datapropertyform.h"

#include <icustomgraphic.h>

#include <datahandler/dataactionmanager.h>

#define DATA_ROLE  Qt::UserRole + 1
DataPropertyForm::DataPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataPropertyForm)
{
    ui->setupUi(this);
    initUI();
}

DataPropertyForm::~DataPropertyForm()
{
    delete ui;
}

void DataPropertyForm::setGraphicItem(ICustomGraphic *item)
{
    if (item == nullptr || graphicItem == item) {
        return;
    }
    auto graphicScene = dynamic_cast<BIGraphicsScene*>(item->scene());
    if (graphicScene == nullptr) {
        return;
    }
    dataEditor->setGraphicsItem(item);
    graphicId = graphicScene->getItemId(item);
    QSignalBlocker tableBlocker(ui->dataTable);
    QSignalBlocker editorBlocker(dataEditor);
    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);
    dataEditor->reset();
    dataEditor->setVisible(false);
    // 获取该图元配置的数据
    auto dataActions = DataActionManager::instance()->getGraphicDataActions(graphicId);
    if (dataActions.isEmpty()){
        return;
    }
    // 显示已配置数据
    foreach (auto data, dataActions) {
        addTableItem(data);
    }
    ui->dataTable->clearSelection();
}

void DataPropertyForm::onNewDataProperty()
{
    dataEditor->setVisible(true);
    dataEditor->reset();
    newFlag = true;
}

void DataPropertyForm::onEditDataProperty()
{
    newFlag = false;
    dataEditor->setVisible(true);
    int row = ui->dataTable->currentRow();
    if(row < 0){
        dataEditor->setVisible(false);
        return;
    }
    auto item = ui->dataTable->item(row, 0);
    auto data = item->data(DATA_ROLE).value<DataAction>();
    dataEditor->setData(data);
}

void DataPropertyForm::onDelDataProperty()
{
    int row = ui->dataTable->currentRow();
    if (row < 0) {
        return;
    }
    auto item = ui->dataTable->item(row, 0);
    auto data = item->data(DATA_ROLE).value<DataAction>();
    DataActionManager::instance()->removeDataAction(data);
    ui->dataTable->removeRow(row);
}

void DataPropertyForm::onDataChanged(DataAction action)
{
    action.setGraphicId(graphicId);
    if (newFlag) {
        // 添加数据
        auto old = DataActionManager::instance()->getDataAction(graphicId, action.getDataId());
        if (!old.getDataId().isEmpty()){
            QMessageBox::warning(this, tr("警告"),
                                 QString(tr("数据[%1]已经存在，不能重复添加！"))
                                     .arg(action.getData().get_dataName()));
            dataEditor->reset();
            return;
        }
        addTableItem(action);
        ui->dataTable->blockSignals(true);
        auto index = ui->dataTable->rowCount() - 1;
        ui->dataTable->selectRow(index);
        ui->dataTable->setCurrentItem(ui->dataTable->item(index,0));
        ui->dataTable->blockSignals(false);
        newFlag = false;
    }else{
        // 修改数据
        auto row = ui->dataTable->currentRow();
        if (row < 0) {
            return;
        }
        auto item = ui->dataTable->item(row, 0);
        // 检查数据是否变更
        auto oldData = item->data(DATA_ROLE).value<DataAction>();
        auto oldId = oldData.getDataId();
        auto newId = action.getDataId();
        if (!oldId.isEmpty() && oldId.compare(newId) != 0) {
            // 数据变更
            auto newAction = DataActionManager::instance()->getDataAction(graphicId, newId);
            if (newAction.getDataId().isEmpty()) {
                // 删除旧数据
                DataActionManager::instance()->removeDataAction(graphicId, oldId);
            }else{
                QMessageBox::warning(this, tr("警告"),
                                     QString(tr("数据[%1]已经存在，不能重复添加！"))
                                         .arg(action.getData().get_dataName()));
                return;
            }
        }
        auto data = action.getData();
        auto dataName = data.get_dataName();
        QString trigger = action.typeToString();
        QString actionDetail = action.actionToString();
        item->setData(DATA_ROLE,QVariant::fromValue(action));
        item->setText(dataName);
        item = ui->dataTable->item(row, 1);
        item->setText(trigger);
        item = ui->dataTable->item(row, 2);
        item->setText(actionDetail);
    }
    // 数据更新到 manager
    DataActionManager::instance()->updateDataAction(action);
}

void DataPropertyForm::initUI()
{
    ui->dataTable->setColumnCount(3);
    ui->dataTable->setHorizontalHeaderLabels({tr("数据"), tr("行为"), tr("动作")});
    ui->dataTable->setColumnWidth(0, 60);
    ui->dataTable->setColumnWidth(1, 80);
    ui->dataTable->setColumnWidth(2, 80);
    ui->dataTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->dataTable->setVerticalHeader(new NumberHeader{Qt::Vertical});
    ui->dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    dataEditor = new DataEditorForm(this);
    auto scrollLayout = ui->scrollAreaWidgetContents->layout();
    scrollLayout->addWidget(dataEditor);
    dataEditor->hide();

    connect(ui->dataTable, &QTableWidget::itemSelectionChanged,
            this, &DataPropertyForm::onEditDataProperty);
    connect(ui->addBtn, &QPushButton::clicked,
            this, &DataPropertyForm::onNewDataProperty);
    connect(ui->delBtn, &QPushButton::clicked,
            this, &DataPropertyForm::onDelDataProperty);
    connect(dataEditor, &::DataEditorForm::changedEvent,
            this, &DataPropertyForm::onDataChanged);
}

void DataPropertyForm::addTableItem(DataAction action)
{
    auto data = action.getData();
    auto dataName = data.get_dataName();
    QString trigger = action.typeToString();
    QString actionDetail = action.actionToString();
    auto index = ui->dataTable->rowCount();
    ui->dataTable->insertRow(index);
    auto item = new QTableWidgetItem(dataName);
    item->setData(DATA_ROLE,QVariant::fromValue(action));
    ui->dataTable->setItem(index, 0, item);
    ui->dataTable->setItem(index, 1, new QTableWidgetItem{trigger});
    ui->dataTable->setItem(index, 2, new QTableWidgetItem{actionDetail});
}
