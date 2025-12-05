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
#ifndef DATADIRDIALOG_H
#define DATADIRDIALOG_H

#include "datadirdo.h"
#include <QDialog>

namespace Ui {
class DataDirDialog;
}

class DataDirDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDirDialog(QWidget *parent = nullptr);
    ~DataDirDialog();
    /**
     * @brief setData 设置初始数据
     * @param dataDir 目录数据
     */
    void setData(DataDirDO dataDir);
    DataDirDO getData();
protected Q_SLOTS:
    void onCheckDataSource(Qt::CheckState state);
    void onDataSourceChanged(int index);
    void onTopChecked();
private:
    Ui::DataDirDialog *ui;
    DataDirDO data;
    /**
     * @brief toInitState 定位到初始状态
     */
    void toInitState();
    /**
     * @brief validation 用户输入校验
     * @return true 校验成功， false 校验失败
     */
    bool validation();
};

#endif // DATADIRDIALOG_H
