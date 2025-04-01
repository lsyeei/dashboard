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

#ifndef IMOVEPATH_H
#define IMOVEPATH_H

#include <QPainterPath>
#include <abstractitem.h>

class IMovePath : public AbstractItem
{
public:
    IMovePath(QGraphicsItem *parent=nullptr):AbstractItem(parent){};
    virtual QPainterPath path() = 0;
    /**
     * @brief setMaster 设置路径的所有者
     * @param master 所有者对象
     */
    virtual void setMaster(QGraphicsItem *master) = 0;
    /**
     * @brief getMaster 获取路径的所有者
     * @return 所有者对象
     */
    virtual QGraphicsItem * getMaster() = 0;
Q_SIGNALS:
    virtual void pathChanged() = 0;
};

#endif // IMOVEPATH_H
