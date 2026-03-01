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
#ifndef QUERYFORM_H
#define QUERYFORM_H

#include "bodyform.h"
#include "headerform.h"
#include "idatasourceplugin.h"
#include "keyvalueform.h"
#include "queryconfig.h"
#include <QPointer>
#include <QWidget>

namespace Ui {
class QueryForm;
}

class QueryForm : public IDataQueryWidget
{
    Q_OBJECT

public:
    explicit QueryForm(IDataQueryWidget *parent = nullptr);
    ~QueryForm();

    // IDataSourceWidget interface
    QString getArgs() override;
    void setArgs(const QString &args) override;

    // IDataQueryWidget interface
    void setDataSource(const QString &dataSourceArgs) override;

private Q_SLOTS:
    void onTabChanged();
    void onDataChanged();
    void onTestBtnClicked();
private:
    Ui::QueryForm *ui;

    QueryConfig config;
    QPointer<HeaderForm> headerForm;
    QPointer<BodyForm> bodyForm;
    QPointer<KeyValueForm> paramForm;

    void updateParam();
    void updateUI();
    void initBodyForm();
    void initHeaderForm();
    void initParamForm();
};

#endif // QUERYFORM_H
