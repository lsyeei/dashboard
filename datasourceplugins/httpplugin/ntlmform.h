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
#ifndef NTLMFORM_H
#define NTLMFORM_H

#include "abstractsubform.h"
#include "ntlmconfig.h"

namespace Ui {
class NTLMForm;
}

class NTLMForm : public AbstractSubForm
{
    Q_OBJECT

public:
    explicit NTLMForm(AbstractSubForm *parent = nullptr);
    ~NTLMForm();

    // AbstractAuthForm interface
    void setData(const QVariant &data) override;
    QVariant getData() const override;

private:
    Ui::NTLMForm *ui;
    NTLMConfig config;

    void initEvent();
};

#endif // NTLMFORM_H
