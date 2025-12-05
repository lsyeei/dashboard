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
#include "svghelper.h"
#include "ui_datasourceform.h"

#include <QDropEvent>
#include <QMessageBox>
#include <QToolBar>
#include <configmaster.h>

// static const int ID_ROLE = QTreeWidgetItem::UserType + 1;
// static const int SOURCE_PLUGIN_ROLE = ID_ROLE + 1;
// static const int SOURCE_ARG_ROLE = SOURCE_PLUGIN_ROLE + 1;
static const int DATA_ROLE = QTreeWidgetItem::UserType + 10;
DataSourceForm::DataSourceForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataSourceForm)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 1);
    ui->splitter->setStretchFactor(1, 3);
    // 建立数据库表映射
    dataDirService = new DataDirService(QSqlDatabase::database(ConfigMaster::connName));
    dataSourceService = new DataSourceService(QSqlDatabase::database(ConfigMaster::connName));
    dataMarketService = new DataMarketService(QSqlDatabase::database(ConfigMaster::connName));
    // 初始化工具栏
    initToolBar();
    // 初始化数据目录
    initDataDir();
    // 加载配置
    loadConfig();

    dataDirDlg = new DataDirDialog(this);
    dataDirDlg->hide();
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
        auto source = dataDir.getDataSource();
        if(!source.isEmpty()){
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
}

void DataSourceForm::onDelData(bool flag)
{
    Q_UNUSED(flag)
}

void DataSourceForm::onEditData(bool flag)
{
    Q_UNUSED(flag)
}

void DataSourceForm::onTreeItemClicked(const QModelIndex &index)
{
    auto treeItem = ui->dataDir->itemFromIndex(index);
    if (treeItem->childCount() > 0) {
        ui->dataDir->expandItem(treeItem);
        return;
    }
    auto dataDir = treeItem->data(0, DATA_ROLE).value<DataDirDO>();
    auto source = dataDir.getDataSource();
    if (source.isEmpty()){
        // 获取下级数据并展开下级
        auto items = getDataDir(dataDir.get_id());
        foreach (auto item, items) {
            item.setDataSource(sourceMap[item.get_id()]);
            treeItem->addChild(newTreeItem(item));
        }
        ui->dataDir->expandItem(treeItem);
        return;
    }
    // 刷新数据列表
    updateDataMarket(source.get_id());
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
        to->removeChild(item);
        from->addChild(item);
    }
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
    // ui->dataDir->setDragEnabled(true);
    // ui->dataDir->setAcceptDrops(true);
    // ui->dataDir->setDropIndicatorShown(true);
    // ui->dataDir->setDragDropMode(QAbstractItemView::InternalMove);
    ui->dataDir->setEditTriggers(QAbstractItemView::DoubleClicked);
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


void DataSourceForm::updateDataMarket(int id)
{

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
            !dataMarketService->deleteBatch(QString{"where data_source_id=%1"}.arg(sourceId))){
            result = false;
            break;
        }
    }
    if (!dataDirService->deleteById(id)){
        result = false;
    }
    return result;
}

// void CustomTreeWidget::dropEvent(QDropEvent *event)
// {
//     // 在放下操作发生前，先获取当前选中的项（即被拖动的源节点）
//     QTreeWidgetItem *draggedItem = this->currentItem();
//     if (!draggedItem) {
//         // 如果意外没有源节点，调用基类方法或直接返回
//         QTreeWidget::dropEvent(event);
//         return;
//     }

//     // 获取源节点的原父节点
//     auto *originalParent = draggedItem->parent();
//     // 如果 originalParent 为空，表示源节点原先是顶级节点
//     // 顶级节点可以理解为属于 invisibleRootItem[citation:10]
//     if (!originalParent) {
//         originalParent = this->invisibleRootItem();
//     }

//     // 获取放下事件发生位置的目标项（新位置的父节点或兄弟节点）
//     // QTreeWidgetItem *targetItem = this->itemAt(event->pos());
//     // QTreeWidgetItem *newParent = nullptr;
//     // bool isOnItem = (targetItem != nullptr);

//     // if (isOnItem) {
//     //     // 如果放在了某个项上，这个项就是新的父节点
//     //     newParent = targetItem;
//     // } else {
//     //     // 如果放到了空白区域，新父节点就是虚拟根节点（即成为顶级节点）
//     //     newParent = this->invisibleRootItem();
//     // }
//     // 必须调用基类的 dropEvent，让 Qt 完成默认的移动操作
//     QTreeWidget::dropEvent(event);

//     // 拖放完成后，可以再次验证节点的新位置（可选）
//     QTreeWidgetItem *actualNewParent = draggedItem->parent();
//     // if (!actualNewParent) {
//     //     actualNewParent = this->invisibleRootItem();
//     // }
//     emit itemDroped(draggedItem, originalParent, actualNewParent);
// }
