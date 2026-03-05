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
#ifndef OAUTH2FORM_H
#define OAUTH2FORM_H

#include "abstractsubform.h"
#include "auth2config.h"


class OAuth2Client;
namespace Ui {
class OAuth2Form;
}

class OAuth2Form : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit OAuth2Form(AbstractSubForm *parent = nullptr);
    ~OAuth2Form();

    // AbstractAuthForm interface
    void setData(const QVariant &data) override;
    QVariant getData() const override;

private Q_SLOTS:
    void onTestBtnClicked();

private:
    Ui::OAuth2Form *ui;
    Auth2Config config;
    OAuth2Client *oauth2Client{nullptr};

    void initLocation();
    void initTokenType();
    void initAuthModel();
    void initEvent();
    void updateUIByAuthModel();
};

#endif // OAUTH2FORM_H
