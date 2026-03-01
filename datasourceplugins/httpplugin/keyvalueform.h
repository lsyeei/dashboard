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
#ifndef KEYVALUEFORM_H
#define KEYVALUEFORM_H

#include "abstractsubform.h"
#include "keyvalue.h"
#include <QWidget>

namespace Ui {
class KeyValueForm;
}

class KeyValueForm : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit KeyValueForm(QWidget *parent = nullptr);
    ~KeyValueForm();
    void setData(const QVariant &data) override;
    QVariant getData() const override;

protected Q_SLOTS:
    void onDataChanged(int row, int column);
    void onAddBtnClicked();
    void onDelBtnClicked();
private:
    Ui::KeyValueForm *ui;
    KVList keyValues;

    void initDataTable();
    void updateUI();
    int addTableRow(const KeyValue &param);
    KeyValue getTableRow(int row) const;
};

#endif // KEYVALUEFORM_H
