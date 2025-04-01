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

#ifndef NAMEDPOINT_H
#define NAMEDPOINT_H

#include <QPointF>
#include <QString>
#include "serializable.h"

class NamedPoint : public Serializable
{
    Q_GADGET
    SERIALIZE(NamedPoint)
public:
    NamedPoint(){}
    NamedPoint(QString idName, QPointF point) : id{idName}, pt{point}{}
    ~NamedPoint(){}
    bool isEmpty(){return id.isEmpty();}
    QString id;
    QPointF pt;

    JSONFIELD(id, Id)
    JSONFIELD(pt, Pt)
};
#endif // NAMEDPOINT_H
