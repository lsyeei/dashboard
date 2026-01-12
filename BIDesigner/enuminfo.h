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
#ifndef ENUMINFO_H
#define ENUMINFO_H

#include "serializable.h"

class EnumInfo : public Serializable
{
    Q_GADGET
    SERIALIZE(EnumInfo)
public:
    EnumInfo(int id, const QString &name):
        id(id), name(name){}
    EnumInfo(int id, const QString &name, const QString &detail):
        id(id), name(name), detail(detail){}
    EnumInfo(int id, const QString &name, const QString &detail, QVariant data):
        id(id), name(name), detail(detail), data(data){}
private:
    int id;
    QString name;
    QString detail;
    QVariant data;

    JSONFIELD(id, Id)
    JSONFIELD(data, Data)
    JSONFIELD(name, Name)
    JSONFIELD(detail, Detail)
};

#endif // ENUMINFO_H
