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

#ifndef ABSTRACTSELECTOR_H
#define ABSTRACTSELECTOR_H

#include "adjustpoint.h"
#include <QObject>
class AbstractSelector : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    enum AdjustType{POS, SIZE, CORNER, ROATATE, CUSTOM};
    // AbstractSelector() = delete;
    explicit AbstractSelector(QGraphicsItem *parent = nullptr);
    ~AbstractSelector();

    /**
     * @brief 手动移除选择框
     */
    void remove();
    /**
     * @brief 添加控制点
     * @param id 控制点ID，用于后续检索该控制点
     * @param type 控制点类型
     * @return 控制点对象
     */
    AdjustPoint *addAdjustPoint(QString id, AdjustType type);
    /**
     * @brief getAdjustType 获取控制点类型
     * @param item 控制点
     * @return 类型
     */
    AdjustType getAdjustType(AdjustPoint *item) const;

Q_SIGNALS:
    void adjustStart(AdjustType type);
    void adjustEnd(AdjustType type);

protected Q_SLOTS:
    // 调整点移动
    virtual void onAdjusterMove(const QPointF &from, const QPointF &to) = 0;
    // 调整点捕获鼠标，开始移动
    virtual void onAdjusterMoveStart();
    // 调整点释放鼠标，移动结束
    virtual void onAdjusterMoveEnd();
protected:
    // 调整点集合
    QMap<QString, AdjustPoint*> adjuster;
    /**
     * @brief 删除调节点
     */
    void removeAdjusters();

    virtual void syncTransfrom();
    QTransform viewTransform() const;
    QPointF mapToView(const QPointF &pt) const;
    QPointF mapFromView(const QPointF &pt) const;
    QRectF mapToView(const QRectF &rect) const;
    QPainterPath mapToView(const QPainterPath &path) const;
};

#endif // ABSTRACTSELECTOR_H
