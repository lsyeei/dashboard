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
#ifndef DATAEDITORFORM_H
#define DATAEDITORFORM_H

#include "datahandler/dataaction.h"
#include <QWidget>

class DataSourceForm;
class DataControlForm;
class DataAssignForm;

class QGraphicsItem;
namespace Ui {
class DataEditorForm;
}

class DataEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataEditorForm(QWidget *parent = nullptr);
    ~DataEditorForm();
    void reset();
    void setGraphicsItem(QGraphicsItem *item);
    /**
     * @brief setData 设置数据
     * @param action 数据
     */
    void setData(DataAction data);
Q_SIGNALS:
    /**
     * @brief changedEvent 数据改变事件
     * @param data 改变后的数据
     */
    void changedEvent(DataAction data);
protected Q_SLOTS:
    void changeDetailWidget();
    void onSelectData();
    void onActionChanged(QVariant data);
private:
    Ui::DataEditorForm *ui;
    QGraphicsItem *graphic;
    DataControlForm *controlForm{nullptr};
    DataAssignForm *assignForm{nullptr};
    QDialog *selectorDlg{nullptr};
    DataSourceForm *dataSource{nullptr};
    // 当前数据
    DataAction action;

    void initUI();
    /**
     * @brief updateDataEdit 更新控件dataEdit的文本
     * @param data 数据
     */
    void updateDataEdit(DataMarketDO data);
};

#endif // DATAEDITORFORM_H
