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
#ifndef DATASOURCEFORM_H
#define DATASOURCEFORM_H

#include "datadirdo.h"
#include "datasourcedo.h"

#include <QDialog>
// #include <QTreeWidget>

namespace Ui {
class DataSourceForm;
}
class  QToolBar;
class DataDirService;
class DataSourceService;
class DataMarketService;
class DataDirDialog;
class QTreeWidgetItem;

class DataSourceForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataSourceForm(QWidget *parent = nullptr);
    ~DataSourceForm();
    // QObject interface
    bool event(QEvent *event) override;
protected Q_SLOTS:
    void onAddCategory(bool flag);
    void onDelCategory(bool flag);
    void onEditCategory(bool flag);

    void onAddData(bool flag);
    void onDelData(bool flag);
    void onEditData(bool flag);

    void onTreeItemClicked(const QModelIndex &index);
    void onTreeItemChanged(QTreeWidgetItem *item, int column);
    void onTreeItemDroped(QTreeWidgetItem *item,QTreeWidgetItem *from,QTreeWidgetItem *to);
private:
    Ui::DataSourceForm *ui;
    QToolBar *toolBar;
    DataDirService *dataDirService;
    DataSourceService *dataSourceService;
    DataMarketService *dataMarketService;
    QMap<int, DataSourceDO> sourceMap;
    DataDirDialog *dataDirDlg;

    void paletteCanged();
    void initToolBar();    
    void initDataDir();
    /**
     * @brief getDataSourceMap 获取全部数据源
     */
    void getDataSourceMap();
    /**
     * @brief getDataDir 获取数据目录
     * @param parentId 父节点ID
     * @return 数据目录
     */
    QList<DataDirDO> getDataDir(int parentId);
    /**
     * @brief loadConfig 加载已有数据源配置
     */
    void loadConfig();
    /**
     * @brief addTreeItem 根据目录信息创建目录树节点
     * @param item 目录数据
     * @return 目录树节点
     */
    QTreeWidgetItem *newTreeItem(const DataDirDO &item);
    /**
     * @brief updateDataMarket 更新数据集
     * @param id 数据目录 ID
     */
    void updateDataMarket(int id);
    /**
     * @brief delDataDir 删除存储的数据目录
     * @param id 目录 ID
     * @return true 删除成功，false 删除失败
     */
    bool delDataDir(int id);
};

// class CustomTreeWidget:public QTreeWidget{
//     Q_OBJECT
// public:
//     CustomTreeWidget(QWidget *parent=nullptr):QTreeWidget(parent){
//         // 启用拖放模式（控件内部移动）
//         setDragEnabled(true);
//         setAcceptDrops(true);
//         setDropIndicatorShown(true);
//         setDragDropMode(QAbstractItemView::InternalMove);
//     };
// Q_SIGNALS:
//     void itemDroped(QTreeWidgetItem *item,QTreeWidgetItem *from,QTreeWidgetItem *to);
//     // QWidget interface
// protected:
//     void dropEvent(QDropEvent *event) override;
// };
#endif // DATASOURCEFORM_H
