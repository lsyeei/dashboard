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
#ifndef ASSIGNACTION_H
#define ASSIGNACTION_H

#include "abstractaction.h"
#include "serializable.h"

#include <QCoreApplication>
class AssignAction : public Serializable,public AbstractAction
{
    Q_GADGET
    SERIALIZE(AssignAction)
public:
    AssignAction(){}
    // AbstractAction interface
    void triggerAction(QVariant data, QGraphicsItem *graphic) override{
        if (data.isNull()) {
            data.setValue(defaultValue);
        }
        setProperty(graphic, propertyName, data);
    }
    QString summary() override
    {
        return QString(QCoreApplication::tr("给属性[%1]赋值")).arg(propertyAlias);
    }
private:
    // 属性名
    QString propertyName;
    // 属性别名，通常为可读名称
    QString propertyAlias;
    // 默认值
    QString defaultValue;

    JSONFIELD(propertyName, PropertyName)
    JSONFIELD(propertyAlias, PropertyAlias)
    JSONFIELD(defaultValue, DefaultValue)

};
REGISTER_ACTION(AssignAction)

#endif // ASSIGNACTION_H
