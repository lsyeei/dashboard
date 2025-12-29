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
#include "datadirdialog.h"
#include "datadirservice.h"
#include "datamarketservice.h"
#include "datasourceform.h"
#include "datasourceservice.h"
#include "dbutil/transactionmanager.h"
#include "datadialog.h"
#include "svghelper.h"
#include "ui_datasourceform.h"
#include <QDropEvent>
#include <QMessageBox>
#include <QToolBar>
#include <configmaster.h>

static const int DATA_ROLE = QTreeWidgetItem::UserType + 10;
DataSourceForm::DataSourceForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataSourceForm)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    // 建立数据库表映射
    dataDirService = new DataDirService(ConfigMaster::connName);
    dataSourceService = new DataSourceService(ConfigMaster::connName);
    dataMarketService = new DataMarketService(ConfigMaster::connName);
    // 初始化工具栏
    initToolBar();
    // 初始化数据目录
    initDataDir();
    // 初始化数据表格
    initDataTable();
    // 加载配置
    loadConfig();

    dataDirDlg = new DataDirDialog(this);
    dataDirDlg->hide();
    dataDlg = new DataDialog(this);
    dataDlg->hide();
}

DataSourceForm::~DataSourceForm()
{
    delete ui;
}

bool DataSourceForm::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteCanged();
    }
    return QDialog::event(event);
}

void DataSourceForm::onAddCategory(bool flag)
{
    Q_UNUSED(flag)
    DataDirDO dataDir;
    dataDir.set_id(0);
    auto treeItem = ui->dataDir->currentItem();
    if (treeItem) {
        auto parentDir = treeItem->data(0, DATA_ROLE).value<DataDirDO>();
        dataDir.set_parentId(parentDir.get_id());
        dataDir.setParentName(treeItem->text(0));
    }
    dataDirDlg->setWindowTitle(tr("添加分类"));
    dataDirDlg->setData(dataDir);
    if (dataDirDlg->exec() == QDialog::Accepted) {
        dataDir = dataDirDlg->getData();
        // 存储数据目录
        if (dataDirService->save(&dataDir)){
            auto dataSource = dataDir.getDataSource();
            // 存储数据源信息
            dataSource.set_dataDirId(dataDir.get_id());
            if (dataSourceService->save(&dataSource)){
                sourceMap[dataSource.get_dataDirId()] = dataSource;
            }
            dataDir.setDataSource(dataSource);
            // 新建树节点
            auto newItem = newTreeItem(dataDir);

            if (dataDir.get_parentId() >= 0){
                treeItem->addChild(newItem);
            }else{
                ui->dataDir->addTopLevelItem(newItem);
            }
        }
    }
}

void DataSourceForm::onDelCategory(bool flag)
{
    Q_UNUSED(flag)
    auto treeItem = ui->dataDir->currentItem();
    if (!treeItem) {
        return;
    }
    if (QMessageBox::question(this, tr("删除确认"), tr("确定要删除") + treeItem->text(0)) != QMessageBox::Yes){
        return;
    }
    auto dataDir = treeItem->data(0, DATA_ROLE).value<DataDirDO>();
    // 开启事务
    TransactionManager transaction;
    if (!transaction.addService(dataDirService) ||
        !transaction.addService(dataSourceService) ||
        !transaction.addService(dataMarketService)){
        QMessageBox::information(this, tr("提示"), tr("删除失败"));
        return;
    }
    if (!transaction.beginTransaction()){
        QMessageBox::information(this, tr("提示"), tr("删除失败"));
        return;
    }
    // 删除相关数据
    if (delDataDir(dataDir.get_id())){
        if (!transaction.commit()){
            QMessageBox::information(this, tr("提示"), tr("删除失败"));
            return;
        }
    }else{
        transaction.rollback();
        QMessageBox::information(this, tr("提示"), tr("删除失败"));
        return;
    }
    // 删除节点
    auto parent = treeItem->parent();
    if (parent) {qDebug()<<"has parent...";
        parent->takeChild(parent->indexOfChild(treeItem));
    }else{
        ui->dataDir->takeTopLevelItem(ui->dataDir->indexOfTopLevelItem(treeItem));
    }
}

void DataSourceForm::onEditCategory(bool flag)
{
    Q_UNUSED(flag)
    auto treeItem = ui->dataDir->currentItem();
    if (!treeItem) {
        return;
    }
    // 设置节点信息
    auto dataDir = treeItem->data(0, DATA_ROLE).value<DataDirDO>();
    auto parentItem = treeItem->parent();
    if (parentItem) {
        dataDir.setParentName(parentItem->text(0));
    }
    dataDir.setDataSource(sourceMap[dataDir.get_id()]);
    dataDirDlg->setWindowTitle(tr("编辑分类"));
    dataDirDlg->setData(dataDir);
    if (dataDirDlg->exec() == QDialog::Accepted){
        // 获取更新并存储
        dataDir = dataDirDlg->getData();
        TransactionManager trans;
        if (!trans.addService(dataDirService) ||
            !trans.addService(dataSourceService)){
            QMessageBox::information(this, tr("提示"), tr("更新失败"));
            return;
        }
        if (!trans.beginTransaction()){
            QMessageBox::information(this, tr("提示"), tr("更新失败"));
            return;
        }
        bool success = dataDirService->updateById(dataDir);
        auto source = dataDir.getDataSource();qDebug() << __FUNCTION__ << "sourceArgs=" << source.getColPropery("sourceArgs");
        if(!source.isEmpty()){
            source.set_dataDirId(dataDir.get_id());
            if (source.get_id() > 0) {
                success &= dataSourceService->updateById(source);
            } else {
                success &= dataSourceService->save(&source);
            }
        }
        if (success){
            if (!trans.commit()){
                QMessageBox::information(this, tr("提示"), tr("更新失败"));
            }else{
                dataDir.setDataSource(source);
                // 更新树节点
                treeItem->setText(0, dataDir.get_name());
                treeItem->setData(0, DATA_ROLE, QVariant::fromValue(dataDir));
                sourceMap[dataDir.get_id()] = source;
                // 是否变为顶层节点
                if (parentItem && dataDir.get_parentId() <= 0) {
                    parentItem->removeChild(treeItem);
                    ui->dataDir->addTopLevelItem(treeItem);
                }
            }
        }else{
            if (!trans.rollback()){
                QMessageBox::information(this, tr("提示"), tr("更新失败"));
            }
        }
    }
}

void DataSourceForm::onAddData(bool flag)
{
    Q_UNUSED(flag)
    auto item = ui->dataDir->currentItem();
    if (item == nullptr) {
        return;
    }
    auto dataDir = item->data(0, DATA_ROLE).value<DataDirDO>();
    auto source = dataDir.getDataSource();
    if (source.isEmpty()) {
        return;
    }
    dataDlg->setWindowTitle(tr("添加数据"));
    DataMarketDO dataMarket;
    dataMarket.setDataSource(source);
    dataDlg->setData(dataMarket);
    if (dataDlg->exec() == QDialog::Accepted) {
        dataMarket = dataDlg->getData();
        // 保存数据
        if(dataMarketService->save(&dataMarket)){
            addDataTableItem(dataMarket);
        }
    }
}

void DataSourceForm::onDelData(bool flag)
{
    Q_UNUSED(flag)    
    int row = ui->dataTable->currentRow();
    auto item = ui->dataTable->item(row, 0);
    if (item == nullptr){
        return;
    }
    if (QMessageBox::question(this, tr("删除确认"), tr("确定要删除") + item->text()) != QMessageBox::Yes){
        return;
    }
    auto dataMarket = item->data(DATA_ROLE).value<DataMarketDO>();
    // 执行删除
    if(dataMarketService->deleteById(dataMarket)){
        ui->dataTable->removeRow(row);
    }else{
        QMessageBox::information(this, tr("提示"), tr("删除失败！"));
    }
}

void DataSourceForm::onEditData(bool flag)
{
    Q_UNUSED(flag)
    int row = ui->dataTable->currentRow();
    auto item = ui->dataTable->item(row, 0);
    if (item == nullptr){
        return;
    }
    auto dataMarket = item->data(DATA_ROLE).value<DataMarketDO>();
    dataDlg->setWindowTitle(tr("编辑数据"));
    dataDlg->setData(dataMarket);
    if (dataDlg->exec() == QDialog::Accepted) {
        dataMarket = dataDlg->getData();
        // 保存数据
        if(dataMarketService->updateById(dataMarket)){
            updateDataTableItem(row, dataMarket);
        }
    }
}

void DataSourceForm::onTreeItemClicked(const QModelIndex &index)
{
    auto treeItem = ui->dataDir->itemFromIndex(index);
    auto dataDir = treeItem->data(0, DATA_ROLE).value<DataDirDO>();
    auto source = dataDir.getDataSource();
    // 使能添加数据按钮
    if (source.isEmpty()){
        ui->addData->setDisabled(true);
    }else{
        ui->addData->setEnabled(true);
    }
    if (treeItem->childCount() > 0) {
        // 展开下级
        ui->dataDir->expandItem(treeItem);
        return;
    }
    // 获取下级数据并展开下级
    auto items = getDataDir(dataDir.get_id());
    if (items.count() > 0){
        foreach (auto item, items) {
            item.setDataSource(sourceMap[item.get_id()]);
            treeItem->addChild(newTreeItem(item));
        }
        ui->dataDir->expandItem(treeItem);
    }
}

void DataSourceForm::onTreeItemChanged(QTreeWidgetItem *item, int column)
{
    if (column ==0) {
        // 更新数据分类名称
        auto dataDir = item->data(0, DATA_ROLE).value<DataDirDO>();
        dataDir.set_name(item->text(0));
        if (!dataDirService->updateById(dataDir)){
            dataDir = dataDirService->getOne(dataDir.get_id());
            item->setText(0, dataDir.get_name());
        }
    }
}

void DataSourceForm::onTreeItemDroped(QTreeWidgetItem *item, QTreeWidgetItem *from, QTreeWidgetItem *to)
{
    if (item == nullptr) {
        return;
    }
    auto dir = item->data(0, DATA_ROLE).value<DataDirDO>();
    if (to) {
        auto toDir = to->data(0, DATA_ROLE).value<DataDirDO>();
        dir.set_parentId(toDir.get_id());
    }else{
        dir.set_parentId(-1);
    }
    if (!dataDirService->updateById(dir)){
        if(to) to->removeChild(item);
        if(from) from->addChild(item);
    }
}

void DataSourceForm::onTreeSelectionChanged()
{
    auto item = ui->dataDir->currentItem();
    auto dataDir = item->data(0, DATA_ROLE).value<DataDirDO>();
    // 刷新数据列表
    updateDataMarket(dataDir.get_id());
}

void DataSourceForm::paletteCanged()
{
    ui->addCategory->setIcon(QIcon{SvgHelper{QString{":/icons/icons/tree_add.svg"}}
                                       .toPixmap(ui->addCategory->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->delCategory->setIcon(QIcon{SvgHelper{QString{":/icons/icons/tree_delete.svg"}}
                                       .toPixmap(ui->delCategory->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->editCategory->setIcon(QIcon{SvgHelper{QString{":/icons/icons/tree_edit.svg"}}
                                       .toPixmap(ui->editCategory->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->addData->setIcon(QIcon{SvgHelper{QString{":/icons/icons/data_add.svg"}}
                                       .toPixmap(ui->addData->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->delData->setIcon(QIcon{SvgHelper{QString{":/icons/icons/data_delete.svg"}}
                                       .toPixmap(ui->delData->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->editData->setIcon(QIcon{SvgHelper{QString{":/icons/icons/data_edit.svg"}}
                                       .toPixmap(ui->editData->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
}

void DataSourceForm::initToolBar()
{
    paletteCanged();
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->setOrientation(Qt::Horizontal);
    toolBar->setIconSize({16,16});
    toolBar->addAction(ui->addCategory);
    toolBar->addAction(ui->editCategory);
    toolBar->addAction(ui->delCategory);
    toolBar->addSeparator();
    toolBar->addAction(ui->addData);
    toolBar->addAction(ui->editData);
    toolBar->addAction(ui->delData);
    layout()->replaceWidget(ui->toolWidget, toolBar);
    ui->addData->setEnabled(false);
    ui->editData->setEnabled(false);
    ui->delData->setEnabled(false);
    // 链接事件
    connect(ui->addCategory, &QAction::triggered, this, &DataSourceForm::onAddCategory);
    connect(ui->delCategory, &QAction::triggered, this, &DataSourceForm::onDelCategory);
    connect(ui->editCategory, &QAction::triggered, this, &DataSourceForm::onEditCategory);
    connect(ui->addData, &QAction::triggered, this, &DataSourceForm::onAddData);
    connect(ui->delData, &QAction::triggered, this, &DataSourceForm::onDelData);
    connect(ui->editData, &QAction::triggered, this, &DataSourceForm::onEditData);
}

void DataSourceForm::initDataDir()
{
    connect(ui->dataDir, &QTreeWidget::clicked,
            this, &DataSourceForm::onTreeItemClicked);
    connect(ui->dataDir, &QTreeWidget::itemChanged,
            this, &DataSourceForm::onTreeItemChanged);
    connect(ui->dataDir, &CustomTreeWidget::itemDroped,
            this, &DataSourceForm::onTreeItemDroped);
    connect(ui->dataDir, &QTreeWidget::itemSelectionChanged,
            this, &DataSourceForm::onTreeSelectionChanged);
    ui->dataDir->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void DataSourceForm::initDataTable()
{
    ui->dataTable->setColumnCount(5);
    ui->dataTable->setHorizontalHeaderLabels({tr("数据"), tr("刷新周期（秒）"),
                                tr("注释"),tr("创建时间"),tr("修改时间")});
    ui->dataTable->setColumnWidth(0, 100);
    ui->dataTable->setColumnWidth(1, 90);
    ui->dataTable->setColumnWidth(2, 200);
    ui->dataTable->setColumnWidth(3, 140);
    ui->dataTable->setColumnWidth(4, 140);
    // ui->dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->dataTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->dataTable->setVerticalHeader(new NumberHeader{Qt::Vertical});
    ui->dataTable->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->dataTable, &QTableWidget::itemSelectionChanged, this,[&]{
        auto items = ui->dataTable->selectedItems();
        bool flag = items.count() > 0;
        ui->editData->setEnabled(flag);
        ui->delData->setEnabled(flag);
    });
}

void DataSourceForm::getDataSourceMap()
{
    auto dataSourceList = dataSourceService->list();
    foreach (auto source, dataSourceList) {
        sourceMap[source.get_dataDirId()] = source;
    }
}

QList<DataDirDO> DataSourceForm::getDataDir(int parentId)
{
    auto where = QString{"group_id=%1 and parent_id=%2"}
                     .arg(DataDirDO::GROUP_ID)
                     .arg(parentId);
    return dataDirService->list(where);
}

void DataSourceForm::loadConfig()
{
    getDataSourceMap();
    auto rootItems = getDataDir(-1);

    foreach (auto item, rootItems) {
        item.setDataSource(sourceMap[item.get_id()]);
        ui->dataDir->addTopLevelItem(newTreeItem(item));
    }
}

QTreeWidgetItem *DataSourceForm::newTreeItem(const DataDirDO &item)
{
    auto treeItem = new QTreeWidgetItem();
    treeItem->setText(0, item.get_name());
    // treeItem->setData(0, ID_ROLE, item.get_id());
    treeItem->setData(0, DATA_ROLE, QVariant::fromValue(item));
    auto source = item.getDataSource();
    if (source.get_id() >= 0) {
        // treeItem->setData(0, SOURCE_PLUGIN_ROLE, source.get_sourcePluginId());
        // treeItem->setData(0, SOURCE_ARG_ROLE, source.get_sourceArgs());
        treeItem->setIcon(0, QIcon::fromTheme(QIcon::ThemeIcon::EditCopy));
    }else{
        treeItem->setIcon(0, QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
    }
    // 允许编辑
    treeItem->setFlags(treeItem->flags() | Qt::ItemIsEditable);
    return treeItem;
}


void DataSourceForm::updateDataMarket(int dirId)
{
    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);
    // 获取下级目录ID
    auto childDirIds = childDir(dirId);
    QString idSet{""};
    foreach (auto id, childDirIds) {
        idSet += QString("%1").arg(id) + ",";
    }
    idSet += QString("%1").arg(dirId);
    // 获取数据源ID
    auto sourceList = dataSourceService->list(QString("data_dir_id in(%1)").arg(idSet));
    QString sourceIds{""};
    QMap<int, DataSourceDO> sourceMap;
    foreach (auto source, sourceList) {
        if (!sourceIds.isEmpty()){
            sourceIds += ",";
        }
        sourceIds += QString("%1").arg(source.get_id());
        sourceMap[source.get_id()] = source;
    }
    // 获取数据点
    auto dataList = dataMarketService->list(QString("data_source_id in(%1)").arg(sourceIds));
    // 显示数据
    foreach (auto data, dataList) {
        data.setDataSource(sourceMap[data.get_dataSourceId()]);
        addDataTableItem(data);
    }
}

void DataSourceForm::addDataTableItem(DataMarketDO dataMarket)
{
    auto count = ui->dataTable->rowCount();
    ui->dataTable->insertRow(count);
    auto data = new QTableWidgetItem{dataMarket.get_dataName()};
    data->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    data->setData(DATA_ROLE, QVariant::fromValue(dataMarket));
    ui->dataTable->setItem(count,0,data);
    auto period = new QTableWidgetItem{QString("%1").arg(dataMarket.get_requestPeriod())};
    period->setTextAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    ui->dataTable->setItem(count,1,period);
    auto note = new QTableWidgetItem{dataMarket.get_note()};
    note->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    note->setToolTip(dataMarket.get_note());
    ui->dataTable->setItem(count,2,note);
    QString format{"yyyy-MM-dd hh:mm:ss"};
    auto create = new QTableWidgetItem{dataMarket.get_createTime().toString(format)};
    create->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->dataTable->setItem(count,3,create);
    auto modify = new QTableWidgetItem{dataMarket.get_modifyTime().toString(format)};
    modify->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->dataTable->setItem(count,4,modify);
}

void DataSourceForm::updateDataTableItem(int row, DataMarketDO dataMarket)
{
    auto item = ui->dataTable->item(row, 0);
    item->setText(dataMarket.get_dataName());
    item->setData(DATA_ROLE, QVariant::fromValue(dataMarket));
    item = ui->dataTable->item(row, 1);
    item->setText(QString("%1").arg(dataMarket.get_requestPeriod()));
    item = ui->dataTable->item(row, 2);
    item->setText(dataMarket.get_note());
    QString format{"yyyy-MM-dd hh:mm:ss"};
    item = ui->dataTable->item(row, 3);
    item->setText(dataMarket.get_createTime().toString(format));
    item = ui->dataTable->item(row, 4);
    item->setText(dataMarket.get_modifyTime().toString(format));
}

bool DataSourceForm::delDataDir(int id)
{
    bool result{true};
    auto where = QString{"parent_id=%1 and group_id=%2"}.arg(id).arg(DataDirDO::GROUP_ID);
    auto childs = dataDirService->list(where);
    // 删除下级目录
    foreach (auto child, childs) {
        delDataDir(child.get_id());
    }
    // 删除数据源
    where = QString{"data_dir_id=%1"}.arg(id);
    auto sourceList = dataSourceService->list(where);
    foreach (auto source, sourceList) {
        auto sourceId = source.get_id();
        if (!dataSourceService->deleteById(sourceId) ||
            !dataMarketService->deleteBatch(QString{"data_source_id=%1"}.arg(sourceId))){
            result = false;
            break;
        }
    }
    if (!dataDirService->deleteById(id)){
        result = false;
    }
    return result;
}

QList<int> DataSourceForm::childDir(int dirId)
{
    QList<int> childs;
    auto list = dataDirService->list(QString("parent_id=%1").arg(dirId));
    foreach (auto item, list) {
        auto id = item.get_id();
        childs << id << childDir(id);
    }
    return childs;
}

void NumberHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    QString index = QString{"%1"}.arg(visualIndex(logicalIndex)+1);
    painter->drawText(rect,Qt::AlignCenter|Qt::AlignVCenter,index);
}
