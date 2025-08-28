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

#include "tranfromanimation.h"

#include "animation/graphicsrotationex.h"
#include "animation/qgraphicstranslation.h"
#include "animationParam.h"
#include <QGraphicsScale>
#include <QGraphicsRotation>


TranfromAnimation::TranfromAnimation(QGraphicsItem *obj, const AnimationParam &param, transType type)
    : QAbstractAnimation{}, obj{obj}, param{param}, type{type}
{
    if (param.getDuration() <= 0) {
        return;
    }
    transList = obj->transformations();
    setLoopCount(param.getLoopCount());
    connect(this, SIGNAL(finished()), this, SLOT(onFinished()));
    connect(this, SIGNAL(stateChanged(QAbstractAnimation::State,QAbstractAnimation::State)),
            this,SLOT(onStateChanged(QAbstractAnimation::State,QAbstractAnimation::State)));
}

int TranfromAnimation::duration() const
{
    return param.getDuration() * 1000;
}

void TranfromAnimation::updateCurrentTime(int currentTime)
{
    qreal ratio = currentTime*1.0 / param.getDuration() / 1000;
    auto transList = obj->transformations();

    if (type <= VSCALE) {
        auto total = param.getValueTo().toDouble() - param.getValueFrom().toDouble();
        qreal sx{0};
        if (param.getDirectional()) {
            sx = param.getValueFrom().toDouble() + ratio*total;
        }else{
            if (ratio < 0.5) {
                sx = param.getValueFrom().toDouble() + 2*ratio*total;
            }else{
                ratio -= 0.5;
                sx = param.getValueTo().toDouble() - 2*ratio*total;
            }
        }
        auto scale = new QGraphicsScale();
        if (type == SCALE) {
            scale->setXScale(sx);
            scale->setYScale(sx);
        }else if (type == HSCALE) {
            scale->setXScale(sx);
        }else if (type == VSCALE) {
            scale->setYScale(sx);
        }
        addGraphicsTransform<QGraphicsScale>(scale);
    }else if (type <= VROTATE) {
        auto total = param.getValueTo().toDouble() - param.getValueFrom().toDouble();
        qreal angle{0};
        if (param.getDirectional()) {
            angle = param.getValueFrom().toDouble() + ratio*total;
        }else{
            if (ratio < 0.5) {
                angle = param.getValueFrom().toDouble() + 2*ratio*total;
            }else{
                ratio -= 0.5;
                angle = param.getValueTo().toDouble() - 2*ratio*total;
            }
        }
        if (type == ROTATE) {
            addGraphicsTransform<GraphicsRotationZ>(new GraphicsRotationZ{angle});
        }else if (type == HROTATE) {
            addGraphicsTransform<GraphicsRotationY>(new GraphicsRotationY{angle});
        }else if (type == VROTATE) {
            addGraphicsTransform<GraphicsRotationX>(new GraphicsRotationX{angle});
        }
    }else if (type == TRANSLATION) {
        auto pathData = param.getValueFrom();
        if (!pathData.isValid()) {
            return;
        }
        auto path = pathData.value<QPainterPath>();
        QPointF pos{0,0};
        if (param.getDirectional()) {
            pos = path.pointAtPercent(ratio);
        }else{
            if (ratio < 0.5) {
                pos = path.pointAtPercent(2*ratio);
            }else{
                ratio -= 0.5;
                pos = path.pointAtPercent(1 - 2*ratio);
            }
        }
        addGraphicsTransform<QGraphicsTranslation>(new QGraphicsTranslation{pos});
    }
    obj->update();
}

void TranfromAnimation::onFinished()
{
    obj->setTransformations(transList);
}

void TranfromAnimation::onStateChanged(State newState, State oldState)
{
    Q_UNUSED(newState)
    Q_UNUSED(oldState)
    // if (oldState == Stopped && newState == Running) {
    // }
}

template<typename T>
void TranfromAnimation::addGraphicsTransform(T *trans)
{
    int j = -1;
    auto transList = obj->transformations();
    QGraphicsTransform *temp;
    for (int i=0; i<transList.count(); i++) {
        temp = transList[i];
        if (typeid(*temp) == typeid(T)){
            j = i;
            break;
        }
    }
    if (j >= 0) {
        transList.removeAt(j);
    }
    transList << trans;
    obj->setTransformations(transList);
}
