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

#ifndef MOVEPARAMWIDGET_H
#define MOVEPARAMWIDGET_H

#include "animation/abstractparamwidget.h"

class QComboBox;
class IMovePath;
class MoveParamWidget : public AbstractParamWidget
{
    Q_OBJECT
public:
    MoveParamWidget(const QString &typeId, QWidget* parent = nullptr);

    // AbstractParamWidget interface
    void initWidget() override;
    void update(const AnimationParam &value) override;

protected slots:
    void onPathOptionChanged();
    void onDrawPath();
    void onPathChanged();

protected:
    void initUI() override;
private:
    QComboBox *pathOption;
    QPushButton *drawBtn;
    // 移动路径图元
    QMap<int, IMovePath*> pathItems;
    // 当前移动路径类型
    int pathType{-1};
    /**
     * @brief clearPath 清除原有的路径
     */
    void clearPath();
    /**
     * @brief restorePath 恢复路径
     * @param pathPluginId 路径插件
     * @param xml 路径XML
     * @return 路径指针
     */
    IMovePath *restorePath(const QString &pathPluginId, const QString &xml);

    // QWidget interface
protected:
    void hideEvent(QHideEvent *event);
};

#endif // MOVEPARAMWIDGET_H
