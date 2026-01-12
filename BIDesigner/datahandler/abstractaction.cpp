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
#include "abstractaction.h"

QMap<int, AbstractAction* (*)(QVariant*)> AbstractAction::typeMap;
QMutex AbstractAction::mutex;

AbstractAction::AbstractAction() {}

void AbstractAction::registerType(int typeId, CastFunc castFunc) {
    QMutexLocker locker(&mutex);
    typeMap.insert(typeId, castFunc);
}

AbstractAction *AbstractAction::fromVariant(QVariant *var) {
    // 基础校验：QVariant无效直接返回
    if (var->isNull() || var->userType() == QMetaType::UnknownType) {
        qWarning() << "QVariant无效或存储未知类型";
        return nullptr;
    }
    QMutexLocker locker(&mutex);
    auto targetTypeId = var->typeId();
    // 遍历已注册类型，匹配则执行转换
    for (auto it = typeMap.constBegin(); it != typeMap.constEnd(); ++it) {
        if (it.key() == targetTypeId) {
            // 调用对应子类的转换函数
            return it.value()(var);
        }
    }

    // 无匹配子类
    qWarning() << "未找到匹配的AbstractAction子类，类型名：" << var->typeName();
    return nullptr;
}

bool AbstractAction::switchState(QGraphicsItem *graphic, const QString &stateId)
{
    return false;
}

bool AbstractAction::playAnimation(QGraphicsItem *graphic, const QString &animationId)
{
    return false;
}

bool AbstractAction::setProperty(QGraphicsItem *graphic, const QString &propertyName, QVariant value)
{
    return false;
}
