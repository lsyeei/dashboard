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

#ifndef LINEPATHPROPERTY_H
#define LINEPATHPROPERTY_H

#include "baseproperty.h"
#include "penproperty.h"
#include "namedpoint.h"

class LinePathProperty : public BaseProperty
{
    Q_GADGET
    SERIALIZE(LinePathProperty)
public:
    LinePathProperty() : BaseProperty(){
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setColor(Qt::gray);
    }
    /**
     * @brief getLogicRect 点组成的矩形外框，矩形中心为原点{0，0}
     * @return 图形外框
     */
    QRectF getLogicRect(){return {-width/2, -height/2, width, height};}
    /**
     * @brief getPoints获取组成线的所有点
     * @return QPointF列表
     */
    QList<QPointF> getPoints(){
        QList<QPointF> result;
        foreach (auto item, pointList) {
            result.append(item.pt);
        }
        return result;
    }
    /**
     * @brief getPointCount 获取点的个数
     * @return 点的个数
     */
    int getPointCount(){return pointList.count();}
    /**
     * @brief updatePoint 更新坐标值
     * @param id 坐标ID
     * @param point 新值
     */
    void updatePoint(const QString &id, QPointF point){
        for(auto it=pointList.begin();it != pointList.end(); it++){
            if (it->id.compare(id) == 0) {
                it->pt = point;
                break;
            }
        }
    }
    /**
     * @brief insertPoint 插入一个点
     * @param point 坐标
     * @param beforePoint 在beforePoint前插入
     * @return 新插入点ID
     */
    QString insertPoint(QPointF point, const QString &beforePoint = ""){
        if (beforePoint.isEmpty()){
            return appendPoint(point);
        }
        QString id = QString::number(++maxId);
        NamedPoint item{id, point};
        for(auto it=pointList.cbegin();it != pointList.cend(); it++){
            if (it->id.compare(beforePoint) == 0) {
                pointList.insert(it, item);
                break;
            }
        }
        return id;
    }
    /**
      * @brief appendPoint 在尾部追加点
      * @param point 坐标
      * @return 插入点ID
      */
    QString appendPoint(QPointF point){
        QString id = QString::number(++maxId);
        NamedPoint item{id, point};
        pointList.push_back(item);
        return id;
    }
    /**
     * @brief removePoint 删除指定的点
     * @param id 指定点的ID
     */
    void removePoint(const QString &id){
        // pointList.remove_if([&](QPair<QString, QPointF> item){return item.first.compare(id) == 0;});
        pointList.removeIf([&](NamedPoint item){return item.id.compare(id) == 0;});
    }
private:
    // 区域大小及位置
    qreal width;
    qreal height;
    QPointF pos;
    // 旋转角度
    qreal rotate{0};
    // 线形
    PenProperty pen;
    // 组成线段点的集合
    QList<NamedPoint> pointList;
    int maxId{0};

    JSONFIELD(width, Width)
    JSONFIELD(height, Height)
    JSONFIELD(rotate, Rotate)
    JSONFIELD(pos, Pos)
    JSONFIELD(pen, Pen)
    JSONFIELD(pointList, PointList)
    JSONFIELD(maxId, MaxId)
};
#endif // LINEBASEPROPERTY_H
