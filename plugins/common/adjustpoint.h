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

#ifndef ADJUSTPOINT_H
#define ADJUSTPOINT_H

#include "pointstyle.h"
#include <QObject>
#include <QGraphicsItem>
#include <QCursor>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneDragDropEvent>

/**
 * @brief 图形调整点
 */
class AdjustPoint : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit AdjustPoint(QGraphicsItem *parent = nullptr);
    explicit AdjustPoint(const QString id, QGraphicsItem *parent = nullptr);
    ~AdjustPoint();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QString getId() const;
    PointStyle style();
    void setStyle(const PointStyle &style);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    /**
     * @brief setCursor 设置光标
     * @param cursor 光标对象
     * @param StickyFlag 粘滞标记，true 时光标随对象一起旋转，false 光标不会旋转
     */
    void setCursor(const QCursor &cursor, bool StickyFlag = false);

Q_SIGNALS:
    // 捕获调整点，即鼠标左键按下
    void captureEvent();
    // 调整点移动信号
    void moveEvent(QPointF from, QPointF to);
    // 释放调整点信号，即鼠标左键释放
    void releaseEvent();

protected:
    bool sceneEvent(QEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    void init();
    // 调整光标角度，重新设置光标
    void resetCursor();

    QString m_id{""};
    // 外观
    PointStyle m_style;
    // 光标
    QCursor m_cursor;
    // 光标粘滞标记
    bool m_stickyCursor{false};
    // 屏幕缩放比例
    qreal screenRatio{1};

};

#endif // ADJUSTPOINT_H
