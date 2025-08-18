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

#ifndef ABSTRACTPARAMWIDGET_H
#define ABSTRACTPARAMWIDGET_H

#include "animationParam.h"

#include <QWidget>

class QVBoxLayout;
class QDoubleSpinBox;
class QSpinBox;
class QRadioButton;
class AbstractParamWidget: public QWidget
{
    Q_OBJECT
public:
    AbstractParamWidget(const QString &typeId, QWidget* parent = nullptr);
    virtual void initWidget() = 0;
    virtual void update(const AnimationParam &value);
    AnimationParam getParam();
    /**
     * @brief setOwner 设置动画的使用者
     * @param item 使用动画的图元对象
     */
    void setOwner(QGraphicsItem *item);
Q_SIGNALS:
    virtual void paramChanged();
protected Q_SLOTS:
    virtual void onValueChanged();
    void onInfiniteStateChanged();
protected:
    // 动画的使用者
    QGraphicsItem *owner{nullptr};
    // 动画类型ID
    QString animationType;
    // 动画参数
    AnimationParam param;
    QVBoxLayout *layout;
    virtual void initUI();

private:
    QDoubleSpinBox *delay;
    QDoubleSpinBox *duration;
    QSpinBox *loopCount;
    QCheckBox *infinite;
    QRadioButton *directional;
    QRadioButton *bidirectional;
};


#endif // ABSTRACTPARAMWIDGET_H
