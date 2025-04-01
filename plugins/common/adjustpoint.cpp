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

#include "adjustpoint.h"
#include <QImage>
#include <QScreen>
#include <QGuiApplication>

AdjustPoint::AdjustPoint(QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    init();
}

AdjustPoint::AdjustPoint(const QString id, QGraphicsItem *parent)
    :QGraphicsItem{parent}, m_id(id)
{
    init();
}

AdjustPoint::~AdjustPoint()
{
    disconnect();
}

QRectF AdjustPoint::boundingRect() const
{
    QSizeF size = m_style.boundRect().size();
    qreal width = size.width();
    qreal height = size.height();
    return {-width/2.0, -height/2.0, width, height};
}

void AdjustPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();
    m_style.draw(painter);
    painter->restore();
}

QString AdjustPoint::getId() const
{
    return m_id;
}

PointStyle AdjustPoint::style()
{
    return m_style;
}

void AdjustPoint::setStyle(const PointStyle &style)
{
    m_style = style;
    update();
}

void AdjustPoint::setPen(const QPen &pen)
{
    m_style.setPen(pen);
    update();
}

void AdjustPoint::setBrush(const QBrush &brush)
{
    m_style.setBrush(brush);
    update();
}

void AdjustPoint::setCursor(const QCursor &cursor, bool StickyFlag)
{
    m_cursor = cursor;
    m_stickyCursor = StickyFlag;
    QGraphicsItem::setCursor(cursor);
}

bool AdjustPoint::sceneEvent(QEvent *event)
{
#define CASE_END event->setAccepted(true);\
        return true;\
        break;
    switch (event->type()) {
    case QEvent::GraphicsSceneMousePress:
        mousePressEvent((QGraphicsSceneMouseEvent*)(event));
        CASE_END
    case QEvent::GraphicsSceneMouseRelease:
        mouseReleaseEvent((QGraphicsSceneMouseEvent*)(event));
        CASE_END
    case QEvent::GraphicsSceneMouseMove:
        mouseMoveEvent((QGraphicsSceneMouseEvent*)(event));
        CASE_END
    case QEvent::GraphicsSceneHoverEnter:
        hoverEnterEvent((QGraphicsSceneHoverEvent*)(event));
        CASE_END
    case QEvent::GraphicsSceneHoverMove:
        hoverMoveEvent((QGraphicsSceneHoverEvent*)(event));
        CASE_END
    case QEvent::GraphicsSceneHoverLeave:
        hoverLeaveEvent((QGraphicsSceneHoverEvent*)(event));
        CASE_END
    default:
        break;
    }
    return QGraphicsItem::sceneEvent(event);
}

void AdjustPoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);

    if (m_stickyCursor) {
        resetCursor();
    }
    return QGraphicsItem::hoverEnterEvent(event);
}

void AdjustPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    return QGraphicsItem::hoverLeaveEvent(event);
}

void AdjustPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        emit captureEvent();
    }
    // 使能鼠标事件，使其可以接收move事件，否则，mouseMoveEvent不起作用
    event->accept();
    // 需要阻止事件继续传播
    // return QGraphicsItem::mousePressEvent(event);
}
/**
 * @brief 将鼠标在screne中的坐标广播出去
 * @param event
 */
void AdjustPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        emit releaseEvent();
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void AdjustPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 发出事件
    QPointF lastPos = event->lastScenePos();
    QPointF newPos = event->scenePos();
    if (event->buttons().testFlag(Qt::LeftButton) && lastPos != newPos) {
        emit moveEvent(lastPos, newPos);
    }
    return QGraphicsItem::mouseMoveEvent(event);
}

void AdjustPoint::init()
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    setObjectName("AdjustPoint");
    setAcceptHoverEvents(true);

    screenRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
}

void AdjustPoint::resetCursor()
{
    auto angle = std::fmod(rotation(), 360);
    if (angle == 0) {
        QGraphicsItem::setCursor(m_cursor);
        return;
    }
    auto img = m_cursor.pixmap();
    if (img.isNull()) {
        return;
    }
    QTransform trans;
    trans.rotate(rotation());
    auto pixmap = img.transformed(trans, Qt::SmoothTransformation);
    QGraphicsItem::setCursor(QCursor(pixmap));
}
