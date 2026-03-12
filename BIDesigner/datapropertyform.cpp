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
    graphicItem = item;
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

void DataPropertyForm::undo(QVariant undoData)
{
    parseUndoAction(undoData, true);
}

void DataPropertyForm::redo(QVariant redoData)
{
    parseUndoAction(redoData, false);
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
    QVariantList undoData;
    undoData << row << item->data(DATA_ROLE);
    undoTrigger(tr("删除数据"),{{"removeData", undoData, undoData}});
}

void DataPropertyForm::onDataChanged(DataAction action)
{
    action.setGraphicId(graphicId);
    QVariant undoData, redoData;
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
        newFlag = false;
        undoData = QVariant::fromValue(action);
        undoTrigger(tr("添加数据"), {{"addData", undoData, undoData}});
    }else{
        // 修改数据
        auto row = ui->dataTable->currentRow();
        if (row < 0) {
            return;
        }
        auto item = ui->dataTable->item(row, 0);
        UndoAction delAction;
        // 检查数据是否变更
        auto oldData = item->data(DATA_ROLE).value<DataAction>();
        auto oldId = oldData.getDataId();
        auto newId = action.getDataId();
        if (!oldId.isEmpty() && oldId.compare(newId) != 0) {
            // 数据变更
            auto newAction = DataActionManager::instance()->getDataAction(graphicId, newId);
            if (newAction.getDataId().isEmpty()) {
                // 删除旧数据
                delAction.id = "clearData";
                delAction.redoData = QVariant::fromValue(oldData);
                delAction.undoData = delAction.redoData;
            }else{
                QMessageBox::warning(this, tr("警告"),
                                     QString(tr("数据[%1]已经存在，不能重复添加！"))
                                         .arg(action.getData().get_dataName()));
                return;
            }
        }
        QVariantList undoList, redoList;
        undoList << newId << item->data(DATA_ROLE);
        redoList << oldId << QVariant::fromValue(action);
        if (delAction.id.isEmpty()) {
            undoTrigger(tr("修改数据"), {{"modifyData", undoList, redoList}});
        }else{
            undoTrigger(tr("修改数据"), {delAction, {"modifyData", undoList, redoList}});
        }
    }
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

void DataPropertyForm::addTableItem(DataAction action, int beforeIndex)
{
    auto data = action.getData();
    auto dataName = data.get_dataName();
    QString trigger = action.typeToString();
    QString actionDetail = action.actionToString();
    auto index = beforeIndex;
    if (index < 0) {
        index = ui->dataTable->rowCount();
    }

    ui->dataTable->insertRow(index);
    auto item = new QTableWidgetItem(dataName);
    item->setData(DATA_ROLE,QVariant::fromValue(action));
    ui->dataTable->setItem(index, 0, item);
    ui->dataTable->setItem(index, 1, new QTableWidgetItem{trigger});
    ui->dataTable->setItem(index, 2, new QTableWidgetItem{actionDetail});
}

void DataPropertyForm::undoTrigger(QString text, QList<UndoAction> actions)
{
    QList<QPair<QString, QVariant>> undoAction;
    QList<QPair<QString, QVariant>> redoAction;

    auto count = actions.count();
    for(int i = 0; i<count; ++i){
        undoAction.append({actions[count - i - 1].id, actions[count - i - 1].undoData});
        redoAction.append({actions[i].id, actions[i].redoData});
    }

    // 统一携带graphic
    QVariantList undoObj, redoObj;
    undoObj << QVariant::fromValue(graphicItem) << QVariant::fromValue(undoAction);
    redoObj << QVariant::fromValue(graphicItem) << QVariant::fromValue(redoAction);
    static const QMetaMethod undoSignal = QMetaMethod::fromSignal(&DataPropertyForm::undoEvent);
    if (isSignalConnected(undoSignal)) {
        emit undoEvent(text, undoObj, redoObj);
    } else {
        parseUndoAction(redoObj, false);
    }
}

void DataPropertyForm::parseUndoAction(QVariant undoData, bool isUndo)
{
    auto list = undoData.toList();
    if (list.count() < 2) {
        return;
    }
    auto item = list[0].value<ICustomGraphic*>();
    if (item == nullptr) {
        return;  // 安全检查
    }
    graphicItem = item;
    dataEditor->setGraphicsItem(item);
    item->setSelected(true);
    // 切换到本窗口
    auto parent = parentWidget()->parentWidget();
    if (parent) {
        auto tab = dynamic_cast<QTabWidget*>(parent);
        if (tab) {
            tab->setTabVisible(tab->indexOf(this), true);
            tab->setCurrentWidget(this);
        }
    }

    auto data = list[1].value<QList<QPair<QString, QVariant>>>();

    foreach (auto command, data) {
        commonAction(command.first, command.second, isUndo);
    }
}

void DataPropertyForm::commonAction(QString action, QVariant data, bool isUndo)
{
    ui->dataTable->blockSignals(true);
    if (action == "addData") {
        auto dataAction = data.value<DataAction>();
        if (isUndo) {
            auto index = findTableItem(dataAction.getDataId());
            if (index >= 0) {
                ui->dataTable->removeRow(index);
                ui->dataTable->setRowCount(ui->dataTable->rowCount() - 1);
                ui->dataTable->selectRow(-1);
            }
            // 删除数据
            DataActionManager::instance()->removeDataAction(dataAction);
        }else{
            addTableItem(dataAction);
            auto index = ui->dataTable->rowCount() - 1;
            ui->dataTable->selectRow(index);
            ui->dataTable->setCurrentItem(ui->dataTable->item(index,0));
            // 数据更新到 manager
            DataActionManager::instance()->updateDataAction(dataAction);
        }
    } else if (action == "modifyData") {
        auto list = data.toList();
        if (list.count() < 2) {
            return;
        }
        auto dataId = list[0].toString();
        auto row = findTableItem(dataId);
        if (row < 0) {
            return;
        }
        auto item = ui->dataTable->item(row, 0);
        auto dataAction = list[1].value<DataAction>();
        auto data = dataAction.getData();
        auto dataName = data.get_dataName();
        QString trigger = dataAction.typeToString();
        QString actionDetail = dataAction.actionToString();
        item->setData(DATA_ROLE,QVariant::fromValue(dataAction));
        item->setText(dataName);
        item = ui->dataTable->item(row, 1);
        item->setText(trigger);
        item = ui->dataTable->item(row, 2);
        item->setText(actionDetail);
        // ui->dataTable->setItem(row, 0, item);
        ui->dataTable->selectRow(row);
        ui->dataTable->setCurrentCell(row, 0);
        if (!isUndo) {
            // 数据更新到 manager
            DataActionManager::instance()->updateDataAction(dataAction);
        }
    } else if (action == "clearData") {
        auto dataAction = data.value<DataAction>();
        if (isUndo) {
            DataActionManager::instance()->addDataAction(dataAction);
        }else{
            DataActionManager::instance()->removeDataAction(graphicId, dataAction.getDataId());
        }
    } else if (action == "removeData") {
        auto list = data.toList();
        if (list.count() < 2) {
            return;
        }
        auto row = list[0].toInt();
        if (row < 0) {
            return;
        }
        auto dataAction = list[1].value<DataAction>();
        if (isUndo) {
            addTableItem(dataAction, row);
            ui->dataTable->selectRow(row);
            ui->dataTable->setCurrentCell(row, 0);
            DataActionManager::instance()->addDataAction(dataAction);
        }else{
            ui->dataTable->removeRow(row);
            ui->dataTable->selectRow(-1);
            DataActionManager::instance()->removeDataAction(graphicId, dataAction.getDataId());
        }
    }
    ui->dataTable->blockSignals(false);
    onEditDataProperty();
}

int DataPropertyForm::findTableItem(const QString &dataId){
    if (dataId.isEmpty()) {
        return -1;
    }
    auto count = ui->dataTable->rowCount();
    for(int i=0; i<count; i++){
        auto itemData = ui->dataTable->item(i, 0)->data(DATA_ROLE).value<DataAction>();
        if (dataId.compare(itemData.getDataId()) == 0) {
            return i;
        }
    }
    return -1;
}
