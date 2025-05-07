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

#include "pointstyle.h"
#include "qdebug.h"
#include <QPainter>

PointStyle::PointStyle() : PointStyle(Circle, {10,10})
{}

PointStyle::PointStyle(PointShape shape, const QSizeF &size,
                       const QPen &pen, const QBrush &brush, qreal angle)
    : m_size(size), m_pen(pen), m_brush(brush), m_rotation(angle)
{
    QRectF rect{{0,0},size};
    rect.moveCenter(center);

    switch (shape) {
    case Circle:
        m_path.addEllipse(rect);
        break;
    case Rectangle:
        m_path.addRect(rect);
        break;
    case Recycle:
        m_path = createRecycle(size);
        m_pen.setJoinStyle(Qt::MiterJoin);
        m_pen.setCapStyle(Qt::FlatCap);
        m_pen.setMiterLimit(5);
        m_brush = Qt::NoBrush;
        break;
    default:
        break;
    }
}

PointStyle::PointStyle(const QPainterPath &path, const QSizeF &size,
                       const QPen &pen, const QBrush &brush, qreal angle)
    : m_path(path), m_pen(pen), m_brush(brush), m_rotation(angle)
{
    if (size.isEmpty()) {
        m_size = path.boundingRect().size();
    }
}

PointStyle::PointStyle(const PointStyle &style)
{
    copy(style);
}

PointStyle &PointStyle::operator=(const PointStyle &style)
{
    copy(style);
    return *this;
}

void PointStyle::copy(const PointStyle &other)
{
    m_size = other.size();
    m_path = other.path();
    m_pen = other.pen();
    m_brush = other.brush();
    m_rotation = other.rotation();
}

QRectF PointStyle::boundRect() const
{
    QRectF rect{{-m_size.width()/2,-m_size.height()/2},m_size};
    if (qAbs(m_rotation) > 0) {
        QTransform trans;
        trans.rotate(m_rotation);
        rect = trans.mapRect(rect);
    }
    return rect;
}

QSizeF PointStyle::size() const
{
    return m_size;
}

PointStyle PointStyle::setSize(const QSizeF &newSize)
{
    auto oldSize = m_size;
    m_size = newSize;
    if (m_path.isEmpty()) {
        return *this;
    }
    QTransform trans;
    trans.scale(newSize.width() / oldSize.width(),
                newSize.height() / oldSize.height());
    m_path = trans.map(m_path);
    return *this;
}

QPainterPath PointStyle::path() const
{
    return m_path;
}

PointStyle PointStyle::setPath(QPainterPath newPath)
{
    m_path = newPath;
    return *this;
}

QPen PointStyle::pen() const
{
    return m_pen;
}

PointStyle PointStyle::setPen(const QPen &newPen)
{
    m_pen = newPen;
    return *this;
}

QBrush PointStyle::brush() const
{
    return m_brush;
}

PointStyle PointStyle::setBrush(const QBrush &newBrush)
{
    m_brush = newBrush;
    return *this;
}

QPainterPath PointStyle::createRecycle(const QSizeF &size)
{
    auto radius = qMin(size.width(), size.height())/2;
    qreal triWidth = m_pen.widthF() * 1.2;
    qreal cycleRadius = radius - m_pen.widthF()/2 - triWidth/2;
    QRectF cycleRect(-cycleRadius, -cycleRadius, cycleRadius*2, cycleRadius*2);
    // 画圆圈
    QPainterPath path;
    path.arcMoveTo(cycleRect, 90);
    path.arcTo(cycleRect,90,180);
    path.arcMoveTo(cycleRect, -75);
    path.arcTo(cycleRect,-75,40);
    path.arcMoveTo(cycleRect, -15);
    path.arcTo(cycleRect,-15,20);
    // path.arcMoveTo(cycleRect, 30);
    // path.arcTo(cycleRect,30,15);
    // 画三角
    path.moveTo(0, -cycleRadius - triWidth/2);
    path.lineTo(triWidth*qSin(M_PI/3), -cycleRadius);
    path.lineTo(0, -cycleRadius + triWidth/2);
    path.lineTo(0, -cycleRadius - triWidth/2);
    return path;
}

PointStyle PointStyle::rotate(qreal rotation)
{
    m_rotation = rotation;
    return *this;
}

qreal PointStyle::rotation() const
{
    return m_rotation;
}

void PointStyle::draw(QPainter *painter) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::SmoothPixmapTransform);
    painter->setRenderHint(QPainter::VerticalSubpixelPositioning);
    painter->setRenderHint(QPainter::LosslessImageRendering);
    auto drawPath = m_path;
    painter->rotate(m_rotation);
    painter->fillPath(drawPath, m_brush);
    painter->strokePath(drawPath, m_pen);
    painter->restore();
}
