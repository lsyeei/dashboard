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

#ifndef PAGEPROPERTY_H
#define PAGEPROPERTY_H

#include "brushproperty.h"
#include "penproperty.h"

class PageProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(PageProperty)
public:
    explicit PageProperty();
    ~PageProperty(){};
private:
    QString name{"new Page"};
    int width;
    int height;
    bool fillBackground{true};
    BrushProperty brushProperty;
    bool showLine{true};
    PenProperty penProperty;

    JSONFIELD(name, Name)
    JSONFIELD(width, Width)
    JSONFIELD(height, Height)
    JSONFIELD(fillBackground, FillBackground)
    JSONFIELD(brushProperty, BrushProperty)
    JSONFIELD(showLine, ShowLine)
    JSONFIELD(penProperty, PenProperty)
};

inline PageProperty::PageProperty()
    : Serializable()
{
    penProperty.setStyle(Qt::DashLine);
    penProperty.setWidth(0.5);
    penProperty.setColor(0x424242);
    brushProperty.setStyle(Qt::SolidPattern);
    brushProperty.setColor(0x18141D);
}

#endif // PAGEPROPERTY_H
