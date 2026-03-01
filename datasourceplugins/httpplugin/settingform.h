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
#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include "httpconfig.h"
#include <QWidget>

namespace Ui {
class SettingForm;
}

class SettingForm : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit SettingForm(QWidget *parent = nullptr);
    ~SettingForm();
    void setData(const QVariant &data) override;
    QVariant getData() const override;

protected Q_SLOTS:
    void onVersionChanged();
    void onSslChanged();
    void onTimeoutChanged();
    void onRedirectChanged();
private:
    Ui::SettingForm *ui;

    HttpSetting setting;

    void initVersion();
    void initRedirect();
};

#endif // SETTINGFORM_H
