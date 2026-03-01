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
#ifndef HEADERFORM_H
#define HEADERFORM_H

#include "abstractsubform.h"
#include "httpheader.h"
#include <QTableWidgetItem>
#include <QWidget>

namespace Ui {
    class HeaderForm;
}
struct CustomData{
    HeaderItemType type;
    QHttpHeaders::WellKnownHeader knownHeader;
    QString text;
};
class HeaderForm : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit HeaderForm(QWidget *parent = nullptr);
    ~HeaderForm();

    void setData(const QVariant &data) override;
    QVariant getData() const override;

Q_SIGNALS:
    void dataChangedEvent(const QList<HttpHeaderItem> &data);
protected Q_SLOTS:
    void onDataChanged(int row, int column);
    void onAddBtnClicked(bool checked);
    void onDelBtnClicked(bool checked);
private:
    Ui::HeaderForm *ui;
    HttpHeader headerParams;
    QMenu *popMenu;

    void initMenu();
    void initDataTable();
    void updateUI();
    int addTableRow(const HttpHeaderItem &param);
    HttpHeaderItem getTableRow(int row) const;
    QString knownHeaderName(QHttpHeaders::WellKnownHeader knownHeader);
};

#endif // HEADERFORM_H
