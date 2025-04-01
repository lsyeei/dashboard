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

#ifndef OPACITYANIMATION_H
#define OPACITYANIMATION_H

#include "animationParam.h"

#include <QAbstractAnimation>
class QGraphicsItem;

class OpacityAnimation : public QAbstractAnimation
{
    Q_OBJECT
public:
    enum ActType{Fixed, Range};
    explicit OpacityAnimation(QGraphicsItem *obj, const AnimationParam &param, ActType type = Range);
    int duration() const Q_DECL_OVERRIDE;
protected:
    void updateCurrentTime(int currentTime) Q_DECL_OVERRIDE;
protected Q_SLOTS:
    void onFinished();
    void onStateChanged(QAbstractAnimation::State newState,QAbstractAnimation::State oldState);
private:
    // 执行动画的对象
    QGraphicsItem *obj;
    AnimationParam param;
    ActType type;
    qreal opcity{1};
    bool selected{false};
};

#endif // OPACITYANIMATION_H
