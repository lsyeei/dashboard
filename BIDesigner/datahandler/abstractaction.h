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

#ifndef ABSTRACTACTION_H
#define ABSTRACTACTION_H

#include <QMutexLocker>
#include <QVariant>
#include <QMap>

#define REGISTER_ACTION(SubClass) \
namespace { \
    AbstractAction* varTo##SubClass(QVariant *var) { \
        SubClass* ptr = static_cast<SubClass*>(var->data()); \
        return static_cast<AbstractAction*>(ptr); \
    } \
    const bool g_##SubClass##_registered = []() { \
          auto typeId = qRegisterMetaType<SubClass>(); \
          AbstractAction::registerType(typeId, varTo##SubClass); \
          return true; \
      }(); \
}

class QGraphicsItem;
class AbstractAction
{
public:
    // 转换函数原型：QVariant → AbstractAction*
    using CastFunc = AbstractAction* (*)(QVariant*);
    AbstractAction();
    virtual ~AbstractAction() = default;
    virtual void triggerAction(QVariant data, QGraphicsItem * graphic) = 0;
    virtual QString summary() = 0;

    // 注册子类：存入类型ID和对应转换函数
    static void registerType(int typeId, CastFunc castFunc);
    static AbstractAction* fromVariant(QVariant *var);
protected:
    bool switchState(QGraphicsItem * graphic, const QString &stateId);
    bool playAnimation(QGraphicsItem * graphic, const QString &animationId);
    bool setProperty(QGraphicsItem * graphic, const QString &propertyName, QVariant value);
private:
    static QMap<int, CastFunc> typeMap;
    static QMutex mutex;
};

#endif // ABSTRACTACTION_H
