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

#ifndef LINEITEMPROPERTY_H
#define LINEITEMPROPERTY_H

#include "baseproperty.h"
#include "lineendtype.h"
#include "namedpoint.h"
#include "penproperty.h"

class LineItemProperty : public BaseProperty
{
    Q_GADGET
    SERIALIZE(LineItemProperty)
public:
    LineItemProperty() : BaseProperty() {}
    QList<QPointF> getPoints(){
        QList<QPointF> result;
        foreach (auto item, pointList) {
            result.append(item.pt);
        }
        return result;
    }
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
    QString insertPoint(QPointF point, const QString &beforePoint)
    {
        QString id = QString::number(++maxId);
        NamedPoint item{id, point};
        for(auto it=pointList.begin();it != pointList.end(); it++){
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
     QString appendPoint(QPointF point)
    {
         QString id = QString::number(++maxId);
         NamedPoint item{id, point};
         pointList.append(item);
         return id;
    }
    void removePoint(const QString &id){
        // pointList.removeIf([&](QPair<QString, QPointF> item){return item.first.compare(id) == 0;});
        pointList.removeIf([&](NamedPoint item){return item.id.compare(id) == 0;});
    }
    // Serializable interface
    // QVariant getValue(QString fieldName) override;
    // void setValue(QString fieldName, QVariant value) override;
private:
    // 画笔
    PenProperty pen;
    // 端点类型
    LineEndType start;
    LineEndType end;
    // 组成线段点的集合
    QList<NamedPoint> pointList;
    int maxId{0};
    // 流动动画
    bool flowAnimation;

    JSONFIELD(pen, Pen)
    JSONFIELD(start, Start)
    JSONFIELD(end, End)
    JSONFIELD(pointList, PointList)
    JSONFIELD(flowAnimation, FlowAnimation)

};

#endif // LINEITEMPROPERTY_H
