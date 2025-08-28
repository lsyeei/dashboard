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

#ifndef VERTICALELBOW_H
#define VERTICALELBOW_H

#include <QObject>
#include "abstractlineitem.h"

class VerticalElbow : public AbstractLineItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit VerticalElbow(QGraphicsItem *parent = nullptr);
    explicit VerticalElbow(const QString &xml, QGraphicsItem *parent = nullptr);
    QString classId() const override;

protected Q_SLOTS:
    void onPointMoveStart(const QString &id);
    void onPointMoveEnd(const QString &id);
    // AbstractLineItem interface
protected:
    QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    void createPredefinedItem() Q_DECL_OVERRIDE;
    void afterCreateSelector(LineSelector *s) Q_DECL_OVERRIDE;
    void afterInit() Q_DECL_OVERRIDE;
    void afterPointMoved(const QString &id) Q_DECL_OVERRIDE;
    void beforeAddPoint(const QString &id, const QPointF &pos) Q_DECL_OVERRIDE;
    void beforeDelPoint(const QString &id) Q_DECL_OVERRIDE;
    qreal calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const override;
private:
    // 新增标志
    bool addFlag{false};
    QPointF lastPoint{0,0};

    void updateEndRotaion();
    /**
     * @brief autoAddPoint 末端点移动时，自动在末端添加点
     */
    void autoAddPoint();
    /**
     * @brief autoDelPoit 自动合并点，点movedId移动后自动判断是否合并前后点，如果在一条直线上，自动合并
     * @param movedId 移动的点
     */
    void autoMergePoit(const QString &movedId);
};

#endif // VERTICALELBOW_H
