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
#ifndef AUTHFORM_H
#define AUTHFORM_H

#include "abstractsubform.h"
#include "httpconfig.h"

#include <QWidget>

namespace Ui {
class AuthForm;
}

class AuthForm : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);
    ~AuthForm();
    void setData(const QVariant &data) override;
    QVariant getData() const override;
protected:
    void onSelectedAuthChanged(int index);
    void onAuthDataChanged(const QVariant &data);
private:
    Ui::AuthForm *ui;
    AuthConfig authConfig;
    /**
     * @brief subFormMap 授权配置 UI 集合
     */
    QMap<AuthMethod, AbstractSubForm*> subFormMap;
    void hideSubForm();
    void createFormByMethod(AuthMethod method);
};

#endif // AUTHFORM_H
