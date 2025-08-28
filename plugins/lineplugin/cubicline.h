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

#ifndef CUBICLINE_H
#define CUBICLINE_H

#include <QObject>
#include "abstractlineitem.h"
#include "curvecontrolparam.h"

class CubicLine : public AbstractLineItem
{
    Q_OBJECT
public:
    static QString SHAPE_ID;
    explicit CubicLine(QGraphicsItem *parent = nullptr);
    explicit CubicLine(const QString &xml, QGraphicsItem *parent = nullptr);
    QString classId() const override;
    QPainterPath previewPath(QList<QPointF> points, QVariant args) const override;
    // AbstractLineItem interface
protected:
    void parseXML(const QString &xml) override;
    QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    void createPredefinedItem() Q_DECL_OVERRIDE;
    void afterCreateSelector(LineSelector *s) Q_DECL_OVERRIDE;
    qreal calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const Q_DECL_OVERRIDE;
    void afterAddPoint(const QString &id) override;
    void beforeDelPoint(const QString &id) override;
    void afterPointMoved(const QString &id) override;
    void afterInit() override;
    void dragPoint(const NamedPoint &pt, const QPointF &pos) override;
    /**
     * @brief createEditPoint 生成可编辑的点
     * @return 点的集合， ID为插入位置点的ID，pt为可编辑点的坐标
     */
    QList<NamedPoint> createEditPoint() override;
protected Q_SLOTS:
    void onPointSelected(const QString &id);
    void onLeftCurveChanged(const CurveControlParam &param);
    void onRightCurveChanged(const CurveControlParam &param);
private:
    /**
     * @brief calcControlPoint 根据描述点生成绘制曲线用的控制点
     * @param points 描述点的集合
     * @return 控制点集合
     */
    void calcControlPoint(const QList<QPointF> &points);
    // 曲线控制点集合
    QList<CurveControlParam> controlInfo;
    int currentIndex{-1};
    /**
     * @brief indexOfPoint 查找指定点的索引
     * @param id 点对应的ID
     * @return 索引
     */
    int indexOfPoint(const QString &id) const;
    /**
     * @brief deduceCurveParam 推断曲线参数
     * @param i 当前点的索引
     * @param pts 使用前3个元素，依次为前一个点、当前点、后一个点的坐标，
     *              如果当前点是第一个点pts的count()=1;
     *              如果当前点是最后一个点pts的count()=2
     */
    void deduceCurveParam(int i, const QList<QPointF> &pts);
    /**
     * @brief updateCurveParam 更新指定索引的弧度参数
     * @param i 弧度参数索引
     * @param param 新参数
     */
    void updateCurveParam(int i, const CurveControlParam &param);
};

#endif // CUBICLINE_H
