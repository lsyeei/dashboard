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
#include "datamarketdo.h"
#include "datasourcedo.h"
#include <QHeaderView>
#include <QPointer>

namespace Ui {
class DataSourceForm;
}
class  QToolBar;
class DataDirService;
class DataSourceService;
class DataMarketService;
class DataDirDialog;
class DataDialog;
class QTreeWidgetItem;

class DataSourceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataSourceForm(QWidget *parent = nullptr);
    ~DataSourceForm();
    // QObject interface
    bool event(QEvent *event) override;
    /**
     * @brief setEditable 切换编辑状态
     * @param flag true 允许编辑，false 不允许编辑
     */
    void setEditable(bool flag);
    /**
     * @brief getSelectedData 获取当前选中的数据
     * @return 数据对象
     */
    DataMarketDO getSelectedData();
Q_SIGNALS:
    void dataSourceChanged(DataSourceDO source);
    void dataChanged(DataMarketDO data);
public Q_SLOTS:
    void onLoadProjectData(const QString &projectName, QList<DataMarketDO> dataList);
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
    void onTreeSelectionChanged();
private:
    Ui::DataSourceForm *ui;
    QToolBar *toolBar;
    DataDirService *dataDirService;
    DataSourceService *dataSourceService;
    DataMarketService *dataMarketService;
    QMap<int, DataSourceDO> sourceMap;
    QPointer<DataDirDialog> dataDirDlg;
    QPointer<DataDialog> dataDlg;

    void paletteCanged();
    void initToolBar();    
    void initDataDir();
    void initDataTable();
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
    void updateDataMarket(int dirId);
    /**
     * @brief addDataTableItem 将 DataMarketDO 对象加入控件
     * @param dataMarket DataMarketDO对象
     */
    void addDataTableItem(DataMarketDO dataMarket);
    /**
     * @brief updateDataTableItem 更新打他他变了数据
     * @param row 指定行号
     * @param dataMarket 需要更新的数据
     */
    void updateDataTableItem(int row, DataMarketDO dataMarket);
    /**
     * @brief delDataDir 删除存储的数据目录
     * @param id 目录 ID
     * @return true 删除成功，false 删除失败
     */
    bool delDataDir(int id);
    /**
     * @brief childDir 获取所有下级目录ID
     * @param dirId 当前目录ID
     * @return 所有下级目录ID集合
     */
    QList<int> childDir(int dirId);
};
class NumberHeader : public QHeaderView{
public:
    NumberHeader(Qt::Orientation orientation, QWidget *parent = nullptr)
        :QHeaderView(orientation, parent){}

    // QHeaderView interface
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
};
#endif // DATASOURCEFORM_H
