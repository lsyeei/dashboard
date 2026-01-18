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

#ifndef ANIMATIONPARAM_H
#define ANIMATIONPARAM_H

#include "animateType.h"
#include "serializable.h"

class AnimationParam : public Serializable
{
    Q_GADGET
    SERIALIZE(AnimationParam)
public:
    AnimationParam(){}
private:
    // 动画类型
    QString typeId;
    // 持续时间，单位：秒
    qreal duration{1};
    // 延迟时间，单位：秒
    qreal delay{0};
    // 重复次数
    int loopCount{1};
    // 单向true， 双向 false
    bool directional{true};
    // 属性名称
    QString propertyName;
    // 属性起始值
    QVariant valueFrom;
    // 属性终止值
    QVariant valueTo;

    JSONFIELD(typeId, TypeId)
    JSONFIELD(duration, Duration)
    JSONFIELD(delay, Delay)
    JSONFIELD(loopCount, LoopCount)
    JSONFIELD(directional, Directional)
    JSONFIELD(propertyName, PropertyName)
    JSONFIELD(valueFrom, ValueFrom)
    JSONFIELD(valueTo, ValueTo)
};

class AnimationGroup : public Serializable{
    Q_GADGET
    SERIALIZE(AnimationGroup)
public:
    AnimationGroup(){id = -1; enable = true;}
    AnimationGroup(int groupId, const QString &groupName, bool enableFlag=true)
        : id(groupId), name(groupName), enable(enableFlag){}
    void clearAnimation(){animationList.clear();}
private:
    // 组 ID
    int id;
    // 组名
    QString name;
    // 是否启用，true 启用，可以自动播放；false 禁用， 不会自动播放
    bool enable;
    // 组内的动画
    QList<AnimationParam> animationList;

    JSONFIELD(id, Id)
    JSONFIELD(name, Name)
    JSONFIELD(enable, Enable)
    JSONFIELD(animationList, AnimationList)
};

#endif // ANIMATIONPARAM_H
