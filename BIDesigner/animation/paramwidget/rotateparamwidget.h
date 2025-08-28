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

#ifndef ROTATEPARAMWIDGET_H
#define ROTATEPARAMWIDGET_H

#include "animation/abstractparamwidget.h"
class RotateParamWidget : public AbstractParamWidget
{
    Q_OBJECT
public:
    RotateParamWidget(const QString &typeId, QWidget* parent = nullptr);

    // AbstractParamWidget interface
    void initWidget() override;
    void update(const AnimationParam &value) override;

protected slots:
    void onValueChanged() override;

protected:
    void initUI() override;
private:
    QSpinBox *from, *to;
};

#endif // ROTATEPARAMWIDGET_H
