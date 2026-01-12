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
#ifndef DATAASSIGNFORM_H
#define DATAASSIGNFORM_H

#include "datahandler/assignaction.h"
#include <QWidget>

class QGraphicsItem;
namespace Ui {
class DataAssignForm;
}

class DataAssignForm : public QWidget
{
    Q_OBJECT
public:
    explicit DataAssignForm(QWidget *parent = nullptr);
    ~DataAssignForm();
    void setGraphicsItem(QGraphicsItem *item);
    void setData(QVariant data);
    AssignAction getData(){return action;}
    void reset();
Q_SIGNALS:
    void changedEvent(QVariant data);
protected Q_SLOTS:
    void dataChanged();

private:
    Ui::DataAssignForm *ui;
    QGraphicsItem *graphic;
    AssignAction action;

};

#endif // DATAASSIGNFORM_H
