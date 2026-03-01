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
#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include "authform.h"
#include "headerform.h"
#include "idatasourceplugin.h"
#include "keyvalueform.h"
#include "settingform.h"

#include <QPointer>
#include <QWidget>

namespace Ui {
class ConnectForm;
}

class ConnectForm : public IDataSourceWidget
{
    Q_OBJECT

public:
    explicit ConnectForm(IDataSourceWidget *parent = nullptr);
    ~ConnectForm();

    // IDataSourceWidget interface
    QString getArgs() override;
    void setArgs(const QString &args) override;

protected Q_SLOTS:
    void onTabChanged();
    void onDataChanged();
private:
    Ui::ConnectForm *ui;

    QPointer<AuthForm> authForm;
    QPointer<HeaderForm> headerForm;
    QPointer<KeyValueForm> cookieForm;
    QPointer<SettingForm> settingForm;

    HttpConfig httpConfig;

    void updateParam();
    void updateUI();
    void initHeaderForm();
    void initCookieForm();
    void initSettingForm();
    void initAuthForm();
};

#endif // CONNECTFORM_H
