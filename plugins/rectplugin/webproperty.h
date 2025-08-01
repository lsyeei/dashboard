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
#ifndef WEBPROPERTY_H
#define WEBPROPERTY_H

#include "serializable.h"

enum class PageType{
    // url 地址或本地文件地址
    URL,
    FILE,
    // html或js代码
    CODE
};

class WebProperty:public Serializable
{
    Q_GADGET
    SERIALIZE(WebProperty)
public:
    explicit WebProperty(){}
private:
    // true 控件允许拖动（此时网页内容不可操作），false 控件不允许拖动（此时可以操作网页内容）
    bool dragFlag{true};
    PageType type;
    QString content;
    JSONFIELD(type, Type)
    JSONFIELD(dragFlag, DragFlag)
    JSONFIELD(content, Content)
};
Q_DECLARE_METATYPE(WebProperty)
#endif // WEBPROPERTY_H
