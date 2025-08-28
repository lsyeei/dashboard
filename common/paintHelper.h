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

#ifndef PAINTHELPER_H
#define PAINTHELPER_H

#include "qmath.h"
#include <QPainterPath>


class PaintHelper
{
public:

    /**
     * @brief drawRoundCorner 将l1 l2交接位置改为圆弧，在起始线和终止线的夹角内绘制一段与两条线相切的弧线
     * @param path 路径对象
     * @param l1 起始线
     * @param l2 终止线
     * @param cutSize 弧线切入点位置
     */
    static void drawRoundCorner(QPainterPath *path, QLineF l1, QLineF l2, qreal cutSize)
    {
        auto degree = l2.angleTo(l1);
        l1.setLength(cutSize);
        auto x1 = l1.p2();
        path->lineTo(x1);
        auto angle = degree * M_PI / 180;
        auto r = qAbs(cutSize * qTan(angle/2));
        auto hypotenuse = qAbs(cutSize/ qCos(angle/2));
        QLineF l3{l1};
        if (degree > 180) {
            l3.setAngle(l1.angle() - (degree - 360) / 2);
        } else {
            l3.setAngle(l1.angle() - degree / 2);
        }
        l3.setLength(hypotenuse);
        QRectF circleRect{0,0,2*r,2*r};
        circleRect.moveCenter(l3.p2());
        QLineF l4{l3.p2(), x1};
        path->arcTo(circleRect, l4.angle(), 180 - degree);
    };
    /**
     * @brief 计算多边形顶点位置
     * @param line 起始线
     * @param r 半径
     * @param count 数量
     * @return 从line开始逆时针排列的顶点坐标
     */
    static QList<QPointF> calcVertices(QLineF line, qreal r, int count)
    {
        QList<QPointF> list;
        qreal angle = 360 / count;
        line.setLength(r);
        for(int i = 0; i<count; i++){
            list.append(line.p2());
            if (i < count - 1) {
                line.setAngle(line.angle() + angle);
            }
        }
        return list;
    };

    /**
     * @brief 绘制多角星路径
     * @param rect 限制大小的矩形
     * @param n 角的个数
     * @param curved 内角位置相对矩形的凹进度
     * @param arcSize 圆角大小
     * @return 多角星路径
     */
    static QPainterPath starPath(QRectF rect, int n, qreal curved, qreal arcSize)
    {
        QPainterPath path;
        auto width = rect.width()/2;
        auto height = rect.height()/2;
        auto dx = qMin(width, height);
        auto t = rect.center();
        // 变换到标准坐标
        rect = {-width, -height, width*2, height*2};
        auto c = rect.center();
        // 计算星顶点
        QLineF l2{c, rect.topRight()};
        l2.setAngle(90);
        auto k = calcVertices(l2, dx, n);
        // 计算内多边形的顶点
        QLineF l1{c, rect.topRight()};
        l1.setAngle(90-180/n);
        auto p = calcVertices(l1, dx - curved, n);
        if (arcSize > 0) {
            path.moveTo(p[0]);
            QLineF l1,l2;
            for (int i = 0; i < n; ++i) {
                int j = (i + 1) % n;
                l1.setPoints(k[i], p[i]);
                l2.setPoints(k[i], p[j]);
                drawRoundCorner(&path, l1, l2, arcSize);
                path.lineTo(p[j]);
            }
        } else {
            path.moveTo(p[0]);
            for(int i=0; i<n; i++){
                path.lineTo(p[i]);
                path.lineTo(k[i]);
            }
        }
        path.closeSubpath();
        // 按照矩形大小缩放
        auto pathRect = path.boundingRect();
        auto pathCenter = pathRect.center();
        QTransform trans;
        trans.translate(t.x() - pathCenter.x(), t.y() - pathCenter.y());
        trans.scale(width*2/pathRect.width(),height*2/pathRect.height());
        return trans.map(path);
    };

    /**
     * @brief 绘制多边形
     * @param rect 外部矩形框
     * @param n 边的数量
     * @return 多边形路径
     */
    static QPainterPath polygonPath(QRectF rect, int n)
    {
        QPainterPath path;
        auto width = rect.width()/2;
        auto height = rect.height()/2;
        auto dx = qMin(width, height);
        auto t = rect.center();
        // 变换到标准坐标
        rect = {-width, -height, width*2, height*2};
        auto c = rect.center();
        QLineF l{c, rect.topRight()};
        if (n % 2 == 0) {
            if (n/2 % 2 == 0) {
                // 保证8边形等图形的边与矩形重合
                l.setAngle(180/n);
            }else{
                l.setAngle(0);
            }
        }else{
            l.setAngle(90);
        }
        auto p = PaintHelper::calcVertices(l, dx, n);
        path.moveTo(p[0]);
        for (int i = 1; i < n; ++i) {
            path.lineTo(p[i]);
        }
        path.closeSubpath();

        // 按照矩形大小缩放
        auto pathRect = path.boundingRect();
        auto pathCenter = pathRect.center();
        QTransform trans;
        trans.translate(t.x() - pathCenter.x(), t.y() - pathCenter.y());
        trans.scale(width*2/pathRect.width(),height*2/pathRect.height());
        return trans.map(path);
    }
    /**
     * @brief drawArc 从start到end逆时针方向已直径radius绘制一段圆弧
     * @param path 路径对象
     * @param start 起点位置
     * @param end 终点位置
     * @param radius 圆弧直径
     */
    static void drawArc(QPainterPath *path, QPointF start, QPointF end, qreal radius)
    {
        QLineF l{start, end};
        auto len = l.length();
        auto angle = qAsin(len/2 / radius);
        auto degree = angle * 180 / M_PI;
        l.setAngle(l.angle() + 90 - degree);
        l.setLength(radius);
        auto c = l.p2();
        QRectF rect{c.x() - radius, c.y() - radius, radius * 2, radius * 2};
        // path->lineTo(start);
        path->arcTo(rect, 180 + 90 - degree, degree * 2);
    };
};

#endif // PAINTHELPER_H
