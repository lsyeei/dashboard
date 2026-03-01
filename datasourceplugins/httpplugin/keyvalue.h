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
#ifndef KEYVALUE_H
#define KEYVALUE_H

#include "serializable.h"
/**
 * @brief The KeyValue class
 * HTTP 参数，用于 HEADER 或 GET 方法中的参数
 */
class KeyValue : public Serializable
{
    Q_GADGET
    SERIALIZE(KeyValue)
public:
    KeyValue(){};
private:
    QString key;
    QString value;
    QString note;

    JSONFIELD(key, Key)
    JSONFIELD(value, Value)
    JSONFIELD(note, Note)
};
typedef QList<KeyValue> KVList;
#endif // KEYVALUE_H
