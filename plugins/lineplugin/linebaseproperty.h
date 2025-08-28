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

#ifndef LINEBASEPROPERTY_H
#define LINEBASEPROPERTY_H

#include "curvecontrolparam.h"
#include "lineendtype.h"
#include "baseproperty.h"
#include "penproperty.h"
#include "namedpoint.h"

class LineBaseProperty : public BaseProperty
{
    Q_GADGET
    SERIALIZE(LineBaseProperty)
public:
    LineBaseProperty() : BaseProperty(){
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1);
        pen.setColor(Qt::gray);
        start.setCategory(LineEndType::Start);
        end.setCategory(LineEndType::End);
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
    qreal width{0};
    qreal height{0};
    QPointF pos{0,0};
    // 旋转角度
    qreal rotate{0};
    // 线形
    PenProperty pen;
    // 端点类型
    LineEndType start;
    LineEndType end;
    // 组成线段点的集合
    QList<NamedPoint> pointList;
    int maxId{0};
    // 流动动画
    bool flowAnimation{false};
    // 动画速度
    qreal duration{1000};
    // 动画方向，true 反向， true 正向
    bool backward{false};
    // 虚线长度
    qreal dashLen{10};
    // 占空比
    qreal dashRatio{0.5};
    // 圆角
    bool rounded{false};
    // 圆角大小
    qreal arcSize{0};
    // 曲线参数
    QList<CurveControlParam> curveParam;

    JSONFIELD(width, Width)
    JSONFIELD(height, Height)
    JSONFIELD(rotate, Rotate)
    JSONFIELD(pos, Pos)
    JSONFIELD(pen, Pen)
    JSONFIELD(start, Start)
    JSONFIELD(end, End)
    JSONFIELD(pointList, PointList)
    JSONFIELD(maxId, MaxId)
    JSONFIELD(flowAnimation, FlowAnimation)
    JSONFIELD(duration, Duration)
    JSONFIELD(backward, Backward)
    JSONFIELD(dashLen, DashLen)
    JSONFIELD(dashRatio, DashRatio)
    JSONFIELD(rounded, Rounded)
    JSONFIELD(arcSize, ArcSize)
    JSONFIELD(curveParam, CurveParam)
};
#endif // LINEBASEPROPERTY_H
