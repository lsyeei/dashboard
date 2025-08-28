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

#ifndef BASEPROEPRTY_H
#define BASEPROEPRTY_H

#include "serializable.h"
class BaseProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(BaseProperty)
public:
    BaseProperty() : Serializable() {}
private:
    // 属性集ID
    qint32 id{0};
    // 属性集合名称
    QString name{""};

    JSONFIELD(id, Id)
    JSONFIELD(name, Name)
};

#endif // BASEPROEPRTY_H
