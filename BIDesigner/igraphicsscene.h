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

#ifndef IGRAPHICSSCENE_H
#define IGRAPHICSSCENE_H

#include <QGraphicsScene>


class IGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    IGraphicsScene(QObject *parent = nullptr):QGraphicsScene(parent){}

    /**
     * @brief setItemId 设置图元ID
     * @param item 图元对象
     * @param id ID值
     */
    virtual void setItemId(QGraphicsItem *item, const QString &id) = 0;
    /**
     * @brief getItemId 获取图元ID
     * @param item 图元对象
     * @return  图元ID
     */
    virtual QString getItemId(QGraphicsItem *item) = 0;
    /**
     * @brief getItemById 根据ID查找图元
     * @param id 图元ID
     * @return 图元对象
     */
    virtual QGraphicsItem *getItemById(const QString &id) = 0;
};

#endif // IGRAPHICSSCENE_H
