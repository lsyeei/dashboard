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

#pragma once
#ifndef FILETEMPLATE_H
#define FILETEMPLATE_H
#include <QObject>
// 文件格式定义
class XmlTemplate
{
public:
    constexpr static char root[] = "root";
    constexpr static char project[] = "project";
    class projectTemplate {
    public:
        constexpr static char projectName[] = "name";
        constexpr static char author[] = "author";
        constexpr static char createTime[] = "createTime";
        constexpr static char modifyTime[] = "modifytime";
    };
    constexpr static char board[] = "board";
    class boardTemplate {
    public:
        constexpr static char boardName[] = "name";
        constexpr static char boardSize[] = "size";
        constexpr static char background[] = "background";
    };
    constexpr static char shapes[] = "shapes";
    class shapesTemplate {
    public:
        constexpr static char group[] = "group";
        class groupTemplate {
        public:
            constexpr static char groupId[] = "id";
            constexpr static char groupName[] = "name";
            constexpr static char index[] = "index";
            constexpr static char property[] = "transform";
            constexpr static char childs[] = "childs";
        };
        constexpr static char item[] = "item";
        class itemTemplate {
        public:
            constexpr static char classId[] = "classId";
            constexpr static char itemId[] = "id";
            constexpr static char itemName[] = "name";
        };
    };
    constexpr static char animates[] = "animates";
    class animatesTemplate {
    public:
        constexpr static char animate[] = "animate";
        class animateTemplate {
        public:
            constexpr static char itemId[] = "itemId";
            constexpr static char actions[] = "actions";
        };
    };
    constexpr static char dataSource[] = "dataSource";
};
#endif // FILETEMPLATE_H
