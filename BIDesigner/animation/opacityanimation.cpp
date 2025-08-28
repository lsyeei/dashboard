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

#include "opacityanimation.h"

#include <QGraphicsItem>

OpacityAnimation::OpacityAnimation(QGraphicsItem *obj, const AnimationParam &param, ActType type)
    : QAbstractAnimation{}, obj{obj}, param{param}, type{type}
{
    if (param.getDuration() <= 0) {
        return;
    }
    opcity = obj->opacity();
    selected = obj->isSelected();
    setLoopCount(param.getLoopCount());
    connect(this, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(this, SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)),
            this,SLOT(onStateChanged(QAbstractAnimation::State,QAbstractAnimation::State)));

}

int OpacityAnimation::duration() const
{
    return param.getDuration() * 1000;
}

void OpacityAnimation::updateCurrentTime(int currentTime)
{
    qreal ratio = currentTime*1.0 / param.getDuration() / 1000;
    qreal total = param.getValueTo().toDouble() - param.getValueFrom().toDouble();
    qreal value{0};
    if (type == Range) {
        if (param.getDirectional()) {
            value = param.getValueFrom().toDouble() + ratio*total;
        }else{
            if (ratio < 0.5) {
                value = param.getValueFrom().toDouble() + 2*ratio*total;
            }else{
                ratio -= 0.5;
                value = param.getValueTo().toDouble() - 2*ratio*total;
            }
        }
    } else if (type == Fixed) {
        auto count = param.getValueFrom().toInt();
        auto seg = 1.0/count/2.0;
        qreal i = fmodf(ratio/seg,2.0);
        if (i < 1) {
            value = 0.2;
        }else{
            value = 1;
        }
    }

    obj->setOpacity(value);
}

void OpacityAnimation::onFinished()
{
    obj->setOpacity(opcity);
    // obj->setSelected(selected);
}

void OpacityAnimation::onStateChanged(State newState, State oldState)
{
    Q_UNUSED(newState)
    Q_UNUSED(oldState)
    // if (oldState == Stopped && newState == Running) {
    //     obj->setSelected(false);
    // }
}
