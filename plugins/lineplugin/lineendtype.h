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

#ifndef LINEENDTYPE_H
#define LINEENDTYPE_H

#include "serializable.h"

class LineEndType : public Serializable
{
    Q_GADGET
    SERIALIZE(LineEndType)
public:
    enum Category{Start, End};
    LineEndType() : Serializable(){}
    LineEndType(Category type) : Serializable(){category = type;}
    LineEndType(Category type, const QString &id) : Serializable(){category = type; typeId = id;}
    bool isEmpty(){return typeId.isEmpty();}
    void setFixRotation(qreal value){autoRotate = false; rotation = value;}
private:
    Category category;
    // 端点类型ID
    QString typeId;
    // 端点大小
    int size{10};
    // 位置
    QPointF pos;
    // 旋转角度，度数degree
    qreal rotation;
    // 自动旋转标记， true 根据线段指向自动旋转
    bool autoRotate{true};

    JSONFIELD(category, Category)
    JSONFIELD(typeId, TypeId)
    JSONFIELD(size, Size)
    JSONFIELD(pos, Pos)
    JSONFIELD(rotation, Rotation)
    JSONFIELD(autoRotate, AutoRotate)
};

#endif // LINEENDTYPE_H
