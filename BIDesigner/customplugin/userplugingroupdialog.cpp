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
#include "userplugingroupdialog.h"
#include "configmaster.h"
#include "ui_userplugingroupdialog.h"
#include <QPushButton>
#include <QLineEdit>

UserPluginGroupDialog::UserPluginGroupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserPluginGroupDialog)
{
    ui->setupUi(this);
    auto ok = ui->buttonBox->button(QDialogButtonBox::Ok);
    ok->setText(tr("确定"));
    ok->setDefault(false);
    ok->setAutoDefault(false);
    auto cancel = ui->buttonBox->button(QDialogButtonBox::Cancel);
    cancel->setText(tr("取消"));
    cancel->setDefault(false);
    cancel->setAutoDefault(false);
    connect(ui->pluginGroup, &QComboBox::currentIndexChanged,
            this, &UserPluginGroupDialog::onSelectChanged);
    connect(ui->newBtn, &QToolButton::clicked,
            this, &UserPluginGroupDialog::onNewBtnClicked);
    loadGroup();
}

UserPluginGroupDialog::~UserPluginGroupDialog()
{
    delete ui;
}

int UserPluginGroupDialog::getGroupId()
{
    if (ui->pluginGroup->count() > 0){
        return ui->pluginGroup->currentData().toInt();
    }
    return -1;
}

void UserPluginGroupDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 检查当前焦点控件是否为 QLineEdit
        if (qobject_cast<QLineEdit*>(focusWidget())) {
            QLineEdit *lineEdit = qobject_cast<QLineEdit*>(focusWidget());
            // lineEdit->returnPressed();
            // 触发信号
            lineEdit->editingFinished();
        } else {
            event->ignore();  // 非QLineEdit忽略事件
        }
    } else {
        QDialog::keyPressEvent(event);
    }
}

void UserPluginGroupDialog::onSelectChanged(int index)
{
    Q_UNUSED(index)
    if (ui->pluginGroup->currentData().toInt() < 0) {
        ui->pluginGroup->removeItem(ui->pluginGroup->currentIndex());
    }
    ui->pluginGroup->setEditable(false);
}

void UserPluginGroupDialog::onNewBtnClicked(bool checked)
{
    Q_UNUSED(checked)
    QSignalBlocker block(ui->pluginGroup);
    ui->pluginGroup->insertItem(0,"",-1);
    ui->pluginGroup->setCurrentIndex(0);
    ui->pluginGroup->setEditable(true);
    connect(ui->pluginGroup->lineEdit(), &QLineEdit::editingFinished,
            this, &UserPluginGroupDialog::onNewGroup);
}

void UserPluginGroupDialog::onNewGroup()
{
    auto editor = dynamic_cast<QLineEdit*>(sender());
    if (editor) {
        auto name = editor->text().trimmed();
        if (name.isEmpty()) {
            ui->pluginGroup->setEditable(false);
            ui->pluginGroup->removeItem(0);
            return;
        }
        emit addNewGroup(name);
        // UserPluginGroupDO group;ui->pluginGroup->setCurrentText()
        // group.set_name(name);
        // if (ConfigMaster::instance()->userPluginGroup->save(&group)){
        //     ui->pluginGroup->setItemData(ui->pluginGroup->currentIndex(), group.get_id());
        // }
        ui->pluginGroup->setEditable(false);
        loadGroup();
        ui->pluginGroup->setCurrentText(name);
    }
}

void UserPluginGroupDialog::loadGroup()
{
    auto groups = ConfigMaster::instance()->userPluginGroup->list();
    ui->pluginGroup->clear();
    foreach (auto item, groups) {
        ui->pluginGroup->addItem(item.get_name(), item.get_id());
    }
    if (!groups.isEmpty()) {
        ui->pluginGroup->setCurrentIndex(0);
    }
}
