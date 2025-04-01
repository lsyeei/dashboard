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

#ifndef TEXTPROPERTY_H
#define TEXTPROPERTY_H

#include "serializable.h"

#include <QFont>

class TextProperty :  public Serializable
{
    Q_GADGET
    SERIALIZE(TextProperty)
public:
    explicit TextProperty():Serializable(){};
private:
    // 字体
    QFont font;
    // 颜色
    QColor color;
    // 自动换行
    bool lineWrape;
    // 行间距
    float lineSpace;
    // 缩进字体宽度
    float indent;
};

#endif // TEXTPROPERTY_H
