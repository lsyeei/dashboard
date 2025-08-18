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

#ifndef POINTSTYLE_H
#define POINTSTYLE_H

#include <QPainterPath>
#include <QPen>
#include <QSize>
#include <QString>

class PointStyle{
public:
    enum PointShape{
        Rectangle,
        Circle,
        Recycle
    };
    PointStyle();
    PointStyle(PointShape shape, const QSizeF &size = {10,10},
               const QPen &pen = {Qt::white, 1, Qt::SolidLine},
               const QBrush &brush = {QColor(0x29B6F2), Qt::SolidPattern},
                qreal angle = 0);
    PointStyle(const QPainterPath &path, const QSizeF &size = QSizeF{},
               const QPen &pen = {Qt::white, 1, Qt::SolidLine},
               const QBrush &brush = {QColor(0x29B6F2), Qt::SolidPattern},
               qreal angle = 0);
    PointStyle(const PointStyle &style);
    PointStyle &operator=(const PointStyle &style);
    void copy(const PointStyle &other);

    QRectF boundRect() const;
    QSizeF size() const;
    PointStyle setSize(const QSizeF &newSize);

    QPainterPath path() const;
    PointStyle setPath(QPainterPath newPath);

    QPen pen() const;
    PointStyle setPen(const QPen &newPen);

    QBrush brush() const;
    PointStyle setBrush(const QBrush &newBrush);

    PointStyle rotate(qreal rotation);
    qreal rotation() const;

    void draw(QPainter *painter) const;

private:
    QPainterPath createRecycle(const QSizeF &size);
    // 画布大小
    QSizeF m_size{0, 0};
    // 路径
    QPainterPath m_path;
    // 画笔
    QPen m_pen{Qt::white, 1, Qt::SolidLine};
    // 画刷
    QBrush m_brush{QColor(0x29B6F2), Qt::SolidPattern};
    // 旋转角度
    qreal m_rotation{0};
    const QPointF center{0,0};
};


#endif // POINTSTYLE_H
