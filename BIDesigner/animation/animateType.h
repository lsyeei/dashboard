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

#ifndef ANIMATETYPE_H
#define ANIMATETYPE_H

#include "qicon.h"
#include <QString>

class QAbstractAnimation;
class QGraphicsItem;
class AnimationParam;
class AbstractParamWidget;
class AnimateType
{
public:
    typedef std::function<QAbstractAnimation *(QGraphicsItem *graphic, const AnimationParam &act)> CreateFunc;
    explicit AnimateType(const QString &id, const QString &name, const QIcon &icon, CreateFunc func, AbstractParamWidget *paramWidget);
    ~AnimateType();
    QAbstractAnimation * createAnimation(QGraphicsItem *graphic, const AnimationParam &act);
    AbstractParamWidget *paramWidget();
    bool isEmpty(){return id.isEmpty();}
    QString getId() const;

    QString getName() const;

    QIcon getIcon() const;

private:
    QString id;
    QString name;
    QIcon icon;
    CreateFunc create{nullptr};
    AbstractParamWidget *widget{nullptr};

    Q_DISABLE_COPY_MOVE(AnimateType)
};


#endif // ANIMATETYPE_H
