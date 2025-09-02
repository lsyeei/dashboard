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
#ifndef USERPLUGINGROUPDIALOG_H
#define USERPLUGINGROUPDIALOG_H

#include <QDialog>
#include <QKeyEvent>
#include <QLineEdit>

namespace Ui {
class UserPluginGroupDialog;
}

class UserPluginGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserPluginGroupDialog(QWidget *parent = nullptr);
    ~UserPluginGroupDialog();
    int getGroupId();
Q_SIGNALS:
    void addNewGroup(const QString &name);
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
private Q_SLOTS:
    void onSelectChanged(int index);
    void onNewBtnClicked(bool checked);
    void onNewGroup();
private:
    Ui::UserPluginGroupDialog *ui;
    void loadGroup();

};

#endif // USERPLUGINGROUPDIALOG_H
