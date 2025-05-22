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
#ifndef USERPLUGINMANAGEFORM_H
#define USERPLUGINMANAGEFORM_H

#include "userplugindo.h"
#include <QDialog>
#include <QWidget>
#include <dbutil/entitytablemodel.h>

namespace Ui {
class UserPluginManageForm;
}

class UserPluginManageForm : public QDialog
{
    Q_OBJECT

public:
    explicit UserPluginManageForm(qint32 group, QWidget *parent = nullptr);
    ~UserPluginManageForm();
    void setGroup(qint32 group);
Q_SIGNALS:
    void remove(const UserPluginDO &data);
    void dataChanged(const UserPluginDO &data);
    void importEvent(qint32 groupId);
protected Q_SLOTS:
    void onUpdateData(QVariant data);
private slots:
    void on_delBtn_clicked();

    void on_importBtn_clicked();

private:
    Ui::UserPluginManageForm *ui;
    qint32 groupId{-1};
    EntityTableModel<UserPluginDO> *model{nullptr};
    void loadData();
    void refreshData();
};

#endif // USERPLUGINMANAGEFORM_H
