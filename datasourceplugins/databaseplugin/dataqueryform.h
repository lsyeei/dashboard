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
#ifndef DATAQUERYFORM_H
#define DATAQUERYFORM_H

#include "database.h"
#include "idatasourceplugin.h"
#include "queryarg.h"
#include <QModelIndex>
#include <QPointer>

namespace Ui {
class DataQueryForm;
}
class QListWidgetItem;
class QSortFilterProxyModel;
class QStandardItemModel;

class DataQueryForm : public IDataQueryWidget
{
    Q_OBJECT

public:
    explicit DataQueryForm(QWidget *parent = nullptr);
    ~DataQueryForm();
    // IDataSourceWidget interface
    QString getArgs() override;
    void setArgs(const QString &args) override;
    // IDataQueryWidget interface
    void setDataSource(const QString &dataSourceArgs) override;
protected Q_SLOTS:
    void onTestBtnClicked();
    void onTableChanged(QModelIndex proxyIndex);
    void onFindTable(const QString &text);
    void onFindField(const QString &text);
private:
    Ui::DataQueryForm *ui;
    QueryArg params;
    Database db;
    QPointer<QStandardItemModel> tableModel, fieldModel;
    QPointer<QSortFilterProxyModel> tableFilter, fieldFilter;
};

#endif // DATAQUERYFORM_H
