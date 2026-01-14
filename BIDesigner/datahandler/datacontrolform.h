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
#ifndef DATACONTROLFORM_H
#define DATACONTROLFORM_H

#include "datahandler/controlaction.h"
#include <QWidget>

class QGraphicsItem;
class ControlAction;
class AbstractAction;
namespace Ui {
class DataControlForm;
}

class DataControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit DataControlForm(QWidget *parent = nullptr);
    ~DataControlForm();
    void setGraphicsItem(QGraphicsItem *item);
    void setData(QVariant action);
    ControlAction getData(){return controlAction;}
    /**
     * @brief reset 重置UI控件
     * @param includeTable true 包含动作表格控件， false 不包括
     */
    void reset(bool includeTable = true);
Q_SIGNALS:
    void changedEvent(QVariant action);
protected Q_SLOTS:
    void controlTypeChanged(int index);
    void symbolChanged(int index);
    void addLogic();
    void editLogic();
    void delLogic();
    void onStateChanged();
    void onPropertyChanged();
private:
    Ui::DataControlForm *ui;
    QGraphicsItem *graphic;
    ControlAction controlAction;
    // 新建条件标记
    bool newFlag{false};

    void initUI();
    /**
     * @brief addActionTableItem 向表格控件中添加一条记录
     * @param logic 动作逻辑
     */
    void addActionTableItem(ControlLogic logic);
    /**
     * @brief showRangeValue 是否显示范围控件
     * @param flag true 显示，false 不显示
     */
    void showRangeValue(bool flag);
    /**
     * @brief dataChanged 数据改变后，包装数据，并修改数据表中的内容
     */
    void dataChanged();
    /**
     * @brief collectAndEmit
     */
    void collectAndEmit();
    void showControlOption(bool flag);
    void initStateOption(auto customGraphic);
    void initPropertyOption(auto customGraphic);
    void selectStateOption(auto data);
};

#endif // DATACONTROLFORM_H
