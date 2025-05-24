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
#ifndef ENTITYTABLEMODEL_H
#define ENTITYTABLEMODEL_H

#include "dbutil/entity.h"
#include "tablemodelevent.h"
#include <QAbstractTableModel>

template<typename T>
class EntityTableModel : public QAbstractTableModel{
public:
    TableModelEvent *event;
    EntityTableModel(){event = new TableModelEvent();}
    ~EntityTableModel(){ delete event;}
    /**
     * @brief bindHeaderNames 设置列的名称
     * @param names 名称映射，first 实体类的field，second 对应的名称
     */
    void bindHeaderNames(QList<QPair<QString, QString>> names);
    /**
     * @brief bindData 绑定数据
     * @param datalist 数据列表
     */
    void bindData(const QList<T> &dataList);
    /**
     * @brief showCheckBox 首列显示 checkbox 控件
     * @param flag true 显示，false 不显示
     */
    void showCheckBox(bool flag);
    /**
     * @brief setColumEditable 设置指定列可编辑
     * @param col 列号
     * @param flag true 可编辑，false 不可编辑
     */
    void setColumEditable(int col, bool flag);
    /**
     * @brief getData 获取指定行的数据
     * @param row 行号
     * @return 该行数据
     */
    T getData(int row);
    /**
     * @brief getSelectedData 获得选中的数据
     * @return 选中的数据
     */
    QList<T> getSelectedData();
    /**
     * @brief removeSelected 删除选中的数据
     * @return true 成功，false 失败
     */
    bool removeSelected();
    void selectAll();
    void deselectAll();
    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
private:
    QList<T> modelData;
    QList<QPair<QString, QString>> headNameMap;
    bool checkFlag{false};
    QMap<int, bool> checkState;
    QMap<int, bool> editable;
};

template<typename T>
bool EntityTableModel<T>::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count);
    for(int i=0;i<count;i++){
        // emit deleteData(modelData[row]);
        modelData.removeAt(row);
    }
    endRemoveRows();
    return true;
}

template<typename T>
bool EntityTableModel<T>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (checkFlag && index.column() == 0) {
        checkState[index.row()] = value == Qt::Checked;
        return true;
    }
    if (!value.isValid() || value.isNull()) {
        return true;
    }
    T* data = &modelData[index.row()];
    auto obj = dynamic_cast<Entity*>(data);
    if (obj == nullptr) {
        return false;
    }
    if (checkFlag) {
        obj->setValue(headNameMap[index.column()-1].first,value);
    } else{
        obj->setValue(headNameMap[index.column()].first,value);
    }
    event->triggerUpdate(QVariant::fromValue(*data));
    return true;
}

template<typename T>
Qt::ItemFlags EntityTableModel<T>::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    if (checkFlag && index.column() == 0) {
        flags |= Qt::ItemIsUserCheckable; // 启用复选框
    }
    if (checkFlag) {
        if (editable[index.column() - 1]) {
            flags |= Qt::ItemIsEditable;
        }
    }else{
        if (editable[index.column()]) {
            flags |= Qt::ItemIsEditable;
        }
    }
    return flags;
}

template<typename T>
QVariant EntityTableModel<T>::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        int headCount = headNameMap.count();
        switch (orientation) {
        case Qt::Horizontal:
            if (checkFlag && section == 0) {
                return QVariant(tr("选择"));
            }
            if (checkFlag){
                headCount += 1;
            }
            if (section >= headCount) {
                return QVariant();
            }
            if (checkFlag){
                return headNameMap[section-1].second;
            }else{
                return headNameMap[section].second;
            }
            break;
        case Qt::Vertical:
            return QVariant::fromValue(section + 1);
            break;
        default:
            break;
        }
    }
    return QVariant();
}

template<typename T>
inline void EntityTableModel<T>::bindHeaderNames(QList<QPair<QString, QString>> names)
{
    headNameMap = names;
}

template<typename T>
inline void EntityTableModel<T>::bindData(const QList<T> &dataList)
{
    beginResetModel();
    modelData = dataList;
    endResetModel();
}

template<typename T>
inline void EntityTableModel<T>::showCheckBox(bool flag)
{
    beginResetModel();
    checkFlag = flag;
    if (!flag) {
        checkState.clear();
    }
    endResetModel();
}

template<typename T>
inline void EntityTableModel<T>::setColumEditable(int col, bool flag)
{
    editable[col] = flag;
}

template<typename T>
inline T EntityTableModel<T>::getData(int row)
{
    if (row < modelData.count()) {
        return modelData[row];
    }
    return modelData[0];
}

template<typename T>
inline QList<T> EntityTableModel<T>::getSelectedData()
{
    QList<T> result;
    for(auto i=checkState.cbegin(); i!=checkState.cend(); i++) {
        if (i.value()) {
            result << modelData[i.key()];
        }
    }
    return result;
}

template<typename T>
inline bool EntityTableModel<T>::removeSelected()
{
    QList<int> rows;
    for(auto i=checkState.cbegin(); i!=checkState.cend(); i++) {
        if (i.value()) {
            rows << i.key();
        }
    }
    std::sort(rows.begin(), rows.end());
    beginResetModel();
    for (int i=rows.count() - 1;i>=0;i--) {
        modelData.removeAt(rows[i]);
    }
    checkState.clear();
    endResetModel();
    return true;
}

template<typename T>
inline void EntityTableModel<T>::selectAll()
{
    beginResetModel();
    for (int i=0; i < modelData.count(); i++){
        checkState[i] = Qt::Checked;
    }
    endResetModel();
}

template<typename T>
inline void EntityTableModel<T>::deselectAll()
{
    beginResetModel();
    for (int i=0; i < modelData.count(); i++){
        checkState[i] = Qt::Unchecked;
    }
    endResetModel();
}

template<typename T>
int EntityTableModel<T>::rowCount(const QModelIndex &parent) const
{
    return modelData.count();
}

template<typename T>
int EntityTableModel<T>::columnCount(const QModelIndex &parent) const
{
    if (checkFlag) {
        return headNameMap.count() + 1;
    }
    return headNameMap.count();
}

template<typename T>
QVariant EntityTableModel<T>::data(const QModelIndex &index, int role) const
{
    if (role == Qt::CheckStateRole){
        if (index.column() == 0) {
            return checkState[index.row()]?Qt::Checked : Qt::Unchecked;
        }
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        auto row = modelData[index.row()];
        auto obj = dynamic_cast<Entity*>(&row);
        if (obj == nullptr){
            return QVariant();
        }
        auto maps = obj->getFieldMap();
        if (checkFlag && index.column() > 0) {
            return obj->getValueByColName(maps[headNameMap[index.column()-1].first]);
        }else{
            return obj->getValueByColName(maps[headNameMap[index.column()].first]);
        }
    }
    return QVariant();
}

#endif // ENTITYTABLEMODEL_H
