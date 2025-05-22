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
#include "userpluginmanageform.h"
#include "dbutil/imagedelegate.h"
#include "ui_userpluginmanageform.h"

#include <ConfigMaster.h>
#include <QStandardItemModel>


UserPluginManageForm::UserPluginManageForm(qint32 group, QWidget *parent)
    : QDialog(parent), ui(new Ui::UserPluginManageForm), groupId(group)
{
    ui->setupUi(this);
    loadData();
}

UserPluginManageForm::~UserPluginManageForm()
{
    delete ui;
}

void UserPluginManageForm::setGroup(qint32 group)
{
    groupId = group;
    refreshData();
}

void UserPluginManageForm::loadData()
{
    if (model == nullptr) {
        model = new EntityTableModel<UserPluginDO>();
    }
    QList<QPair<QString,QString>> header;
    header << QPair<QString,QString>{"thumb","缩略图"}
           << QPair<QString,QString>{"name", "名称"}
           << QPair<QString,QString>{"note", "备注"}
           << QPair<QString,QString>{"path", "路径"};
    model->bindHeaderNames(header);
    model->showCheckBox(true);
    model->setColumEditable(1,true);
    model->setColumEditable(2,true);
    refreshData();

    connect(model->event, SIGNAL(updateData(QVariant)),
            this, SLOT(onUpdateData(QVariant)));

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegateForColumn(1, new ImageDelegate(ImageDelegate::CONTENT));
    ui->tableView->setShowGrid(true);
    ui->tableView->setColumnWidth(0, 20);
    ui->tableView->setColumnWidth(1, 48);
    ui->tableView->resizeColumnToContents(4);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->show();
}

void UserPluginManageForm::refreshData()
{
    auto data = ConfigMaster::instance()->userPlugin->list(QString("group_id=%1").arg(groupId));
    model->bindData(data);
}

void UserPluginManageForm::onUpdateData(QVariant data)
{
    auto obj = data.value<UserPluginDO>();
    emit dataChanged(obj);
    refreshData();
}

void UserPluginManageForm::on_delBtn_clicked()
{
    auto list = model->getSelectedData();
    foreach (auto item, list) {
        emit remove(item);
    }
    model->removeSelected();
    refreshData();
}


void UserPluginManageForm::on_importBtn_clicked()
{
    emit importEvent(groupId);
    refreshData();
}

