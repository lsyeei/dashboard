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

#ifndef ILINEPATH_H
#define ILINEPATH_H

#include <QPainterPath>

class ILinePath
{
public:
    /**
     * @brief linePath 根据给定点绘制路径
     * @param points 给定点
     * @return 绘制的路径
     */
    virtual QPainterPath linePath(QList<QPointF> points) const = 0;
    // 起点、终点形状路径
    virtual QPainterPath startShape() const = 0;
    virtual QPainterPath endShape() const = 0;
    /**
     * @brief previewPath 给出指定点集和参数的路径
     * @param points 指定点集
     * @param args 附加参数
     * @return 绘制路径
     */
    virtual QPainterPath previewPath(QList<QPointF> points, QVariant args) const = 0;
};

#endif // ILINEPATH_H
