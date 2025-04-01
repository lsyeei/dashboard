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

#include "rulerwidget.h"

#include <QMetaEnum>
#include <QPaintEvent>
#include <QPainter>

RulerWidget::RulerWidget(QWidget *parent)
    : QObject(parent),
    topRuler(new Ruler(this, Qt::Horizontal)),
    leftRuler(new Ruler(this, Qt::Vertical)),
    corner(new RulerCorner(this))
{
    setObjectName("ruler container");
    parent->installEventFilter(this);
}

RulerWidget::~RulerWidget()
{
}

void RulerWidget::resize(const QSize &size)
{
    topRuler->resize({size.width(), scaleWidth});
    topRuler->update();
    leftRuler->resize({scaleWidth, size.height()});
    leftRuler->update();
    corner->resize({scaleWidth, scaleWidth});
}

void RulerWidget::update()
{
    topRuler->update();
    leftRuler->update();
    corner->update();
}

void RulerWidget::show(bool show)
{
    topRuler->setVisible(show);
    leftRuler->setVisible(show);
    corner->setVisible(show);
}

qint16 RulerWidget::getScaleWidth() const
{
    return scaleWidth;
}

RulerWidget * RulerWidget::setScaleWidth(qint16 newScaleWidth)
{
    scaleWidth = newScaleWidth;
    return this;
}

QColor RulerWidget::getBackgroundColor() const
{
    return backgroundColor;
}

RulerWidget * RulerWidget::setBackgroundColor(const QColor &newBackgroundColor)
{
    backgroundColor = newBackgroundColor;
    return this;
}

QColor RulerWidget::getForegroundColor() const
{
    return foregroundColor;
}

RulerWidget * RulerWidget::setForegroundColor(const QColor &newForegroundColor)
{
    foregroundColor = newForegroundColor;
    return this;
}

qint16 RulerWidget::getScaleStep() const
{
    return scaleStep;
}

RulerWidget * RulerWidget::setScaleStep(qint16 newScaleStep)
{
    scaleStep = newScaleStep;
    return this;
}

QColor RulerWidget::getFontColor() const
{
    return fontColor;
}

RulerWidget * RulerWidget::setFontColor(const QColor &newFontColor)
{
    fontColor = newFontColor;
    return this;
}

qint16 RulerWidget::getFontSize() const
{
    return fontSize;
}

RulerWidget * RulerWidget::setFontSize(qint16 newFontSize)
{
    fontSize = newFontSize;
    return this;
}

RulerWidget * RulerWidget::setViewRect(const QRect &rect)
{
    topRuler->setViewRect({rect.left(), 0, rect.width(), scaleWidth});
    leftRuler->setViewRect({0, rect.top(), scaleWidth, rect.height()});
    return this;
}

RulerWidget * RulerWidget::setMarkBound(const Bound &hBound, const Bound &vBound)
{
    topRuler->setMarkBound(hBound);
    leftRuler->setMarkBound(vBound);
    return this;
}

void RulerWidget::setTraceFlag(bool flag)
{
    leftRuler->setTraceFlag(flag);
    topRuler->setTraceFlag(flag);
}

Ruler::Ruler(RulerWidget *panel, Qt::Orientation orientation)
    : QWidget(static_cast<QWidget *>(panel->parent())),
    groupPanel(panel), orientation(orientation)
{
    QMetaEnum meta = QMetaEnum::fromType<Qt::Orientation>();
    setObjectName(QString("%1 ruler widget").arg(meta.valueToKey(orientation)));
}

void Ruler::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    drawSceneRuler(&painter);
}

void Ruler::setTraceFlag(bool flag)
{
    traceFlag = flag;
    update();
}

void Ruler::setViewRect(const QRect &newViewRect)
{
    viewRect = newViewRect;
}

void Ruler::setMarkBound(const Bound &bound)
{
    markFrom = bound.lower;
    markTo = bound.upper;
}

void Ruler::setTtracePos(qreal start, qreal middle, qreal end)
{
    startPos = start;
    middlePos = middle;
    endPos = end;
    update();
}

void RulerWidget::setTraceZone(const QRectF &zone)
{
    leftRuler->setTtracePos(zone.top(), zone.center().y(), zone.bottom());
    topRuler->setTtracePos(zone.left(), zone.center().x(), zone.right());
}


void Ruler::resizeEvent(QResizeEvent *event)
{
    // QRect parentRect = static_cast<QWidget *>(groupPanel->parent())->geometry();
    // move(0, 0);//parentRect.left(), parentRect.y());
    // qDebug() << "ruler receive resize event";
    QWidget::resizeEvent(event);
}

void Ruler::drawSceneRuler(QPainter *painter)
{
    QBrush brush = painter->brush();
    brush.setColor(groupPanel->getBackgroundColor());
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    QPen pen = painter->pen();
    pen.setColor(groupPanel->getForegroundColor());
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    painter->setPen(pen);
    QFont font = painter->font();
    font.setPixelSize(groupPanel->getFontSize());
    painter->setFont(font);
    painter->setCompositionMode(QPainter::CompositionMode_Source);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);

    painter->drawRect(rect());
    if (orientation == Qt::Horizontal) {
        // 绘制水平尺子
        drawHorizontalRuler(painter);
    } else {
        // 绘制垂直尺子
        drawVerticalRuler(painter);
    }
}

void Ruler::drawTraceLine(QPainter *painter, QList<QLineF> lines)
{
    auto pen = painter->pen();
    auto color = QColor(Qt::blue);//pen.color();
    // color.setAlphaF(0.6);
    pen.setColor(color.lighter());
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->drawLines(lines);
}

void Ruler::drawHorizontalRuler(QPainter *painter)
{
    painter->save();

    QRect paintRect = getPaintRect();

    painter->setViewport(paintRect);
    int width = paintRect.width();
    int height = paintRect.height();
    QRect logicRect{paintRect.left(), -paintRect.bottom(), width, height};
    painter->setWindow(logicRect);

    qint16 h1 = qRound(height * 1.0 / 3);
    qint16 h2 = h1 * 2;
    qint16 h3 = qRound(height * 1.0 / 2);

    qreal step = groupPanel->getScaleStep();
    qint32 start = paintRect.left();
    qint32 end = paintRect.right() + 1;
    qint32 lineCount = viewRect.width() / step;
    qint32 valueUnit = qFloor((markTo - markFrom) / lineCount);
    if (valueUnit == 0) {
        valueUnit = 1;
    }
    // 保证绘制的每个步长代表一个整数值，如果stepUnit不是整数，调整step长度
    step = viewRect.width() * valueUnit * 1.0 / (markTo - markFrom);
    // 计算绘制的起始位置
    qint32 count = 0;
    if (viewRect.left() < 0) {
        qint32 hideLine = qFloor( - viewRect.left() / step);
        count = hideLine;
        start = hideLine * step + viewRect.left() + paintRect.left();
    }
    if (viewRect.right() > paintRect.width()) {
        end = paintRect.right() + 1;
    }
    qint32 countStart = count;
    QFontMetrics metrics(painter->font());
    for (qreal i = start; i <= end + step - 1;) {
        qint16 mod = count % 10;
        if (mod == 0) {
            painter->drawLine(QPointF(i, 0), QPointF(i, -h2));
            QPen oldPen = painter->pen();
            painter->setPen(QPen(groupPanel->getFontColor()));
            QString text = QString::asprintf("%d",
                                             qRound(markFrom + count * valueUnit));
            QRect textBound = metrics.boundingRect(text);
            painter->drawText(QPointF(i + 2, -h2 + textBound.height() / 2 - 2), text);
            painter->setPen(oldPen);
        }else if (mod == 5){
            painter->drawLine(QPointF(i, 0), QPointF(i, -h3));
        }else{
            painter->drawLine(QPointF(i, 0), QPointF(i, -h1));
        }
        count ++;
        i += step;
    }
    if (traceFlag) {
        // qDebug() << "horizion ruler: step=" << step << ";unit=" << valueUnit
        //          << ";markFrom=" << markFrom << ";start=" << start;
        QList<QLineF> lines;
        auto x1 = start + ((startPos - markFrom) / valueUnit -countStart) * step;
        auto x2 = start + ((middlePos - markFrom) / valueUnit -countStart) * step;
        auto x3 = start + ((endPos - markFrom) / valueUnit -countStart) * step;
        // qDebug() << "x1=" << x1 << ";x2=" << x2 << ";x3=" << x3;
        lines.append({QPointF{x1, 0}, QPointF{x1, -height*1.0}});
        lines.append({QPointF{x2, 0}, QPointF{x2, -height*0.5}});
        lines.append({QPointF{x3, 0}, QPointF{x3, -height*1.0}});
        drawTraceLine(painter, lines);
    }
    painter->restore();
}

void Ruler::drawVerticalRuler(QPainter *painter)
{
    painter->save();

    QRect paintRect = getPaintRect();

    int width = paintRect.width();
    int height = paintRect.height();
    painter->setViewport(paintRect);
    painter->setWindow({-paintRect.right(), paintRect.top(), width, height});
    painter->rotate(-90);

    qint16 h1 = qRound(width *1.0 / 3);
    qint16 h2 = h1 * 2;
    qint16 h3 = qRound(width * 1.0 / 2);

    qreal step = groupPanel->getScaleStep();
    qint32 start = paintRect.top();
    qint32 end = paintRect.bottom() + 1;
    qint32 lineCount = paintRect.height() / step;
    qreal valueUnit = qFloor((markTo - markFrom) / lineCount);

    // 保证绘制的每个步长代表一个整数值，如果stepUnit不是整数，调整step长度
    step = viewRect.height() * valueUnit * 1.0 / (markTo - markFrom);;
    // 计算绘制的起始位置
    qint32 count = 0;
    if (viewRect.top() < 0) {
        qint32 hideLine = qFloor( - viewRect.top() / step);
        count = hideLine;
        start = hideLine * step + viewRect.top() + paintRect.top();
    }
    if (viewRect.bottom() > paintRect.height()) {
        end = paintRect.bottom() + 1;
    }

    qint32 countStart = count;
    QFontMetrics metrics(painter->font());

    for (qreal i = start; i <= end + step - 1; ) {
        qint16 mod = count % 10;
        if (mod == 0) {
            painter->drawLine(QPointF(-i, 0), QPointF(-i, -h2));
            QPen oldPen = painter->pen();
            painter->setPen(QPen(groupPanel->getFontColor()));
            QString text = QString::asprintf("%d",
                    qRound(markFrom + count * valueUnit));
            QRect textBound = metrics.boundingRect(text);
            painter->drawText(QPointF(- i - textBound.width() - 4, -h2 + textBound.height() / 2 - 2), text);
            painter->setPen(oldPen);
        }else if (mod == 5){
            painter->drawLine(QPointF(-i, 0), QPointF(-i, -h3));
        }else{
            painter->drawLine(QPointF(-i, 0), QPointF(-i, -h1));
        }
        count ++;
        i += step;
    }
    if (traceFlag) {
        QList<QLineF> lines;
        auto x1 = start + ((startPos - markFrom) / valueUnit -countStart) * step;
        auto x2 = start + ((middlePos - markFrom) / valueUnit -countStart) * step;
        auto x3 = start + ((endPos - markFrom) / valueUnit -countStart) * step;
        lines.append({QPointF{-x1, 0}, QPointF{-x1, -width*1.0}});
        lines.append({QPointF{-x2, 0}, QPointF{-x2, -width*0.5}});
        lines.append({QPointF{-x3, 0}, QPointF{-x3, -width*1.0}});
        drawTraceLine(painter, lines);
    }
    painter->restore();
}

QRect Ruler:: getPaintRect()
{
    QRect drawRect(viewRect);
    if (orientation == Qt::Horizontal) {
        int leftPad = size().height();
        drawRect.adjust(leftPad, 0, leftPad, 0);
        // qDebug() << "ruler paint rect=" << drawRect;
        if (viewRect.left() < 0) {
            drawRect.setLeft(leftPad);
        }
        if (viewRect.right() > size().width() - leftPad) {
            drawRect.setRight(drawRect.left() + size().width() - leftPad);
        }

    } else {
        int topPad = size().width();
        drawRect.adjust(0, topPad, 0, topPad);
        if (viewRect.top() < 0) {
            drawRect.setTop(topPad);
        }
        if (viewRect.bottom() > size().height() - topPad) {
            drawRect.setBottom(drawRect.top() + size().height() - topPad);
        }
    }
    return drawRect;
}

RulerCorner::RulerCorner(RulerWidget *panel)
    : QWidget(static_cast<QWidget *>(panel->parent())), groupPanel(panel)
{
    setObjectName("ruler corner widget");
}

void RulerCorner::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QBrush brush(groupPanel->getBackgroundColor());
    painter.setBrush(brush);
    painter.drawRect(rect());
}


void RulerCorner::resizeEvent(QResizeEvent *event)
{
    // QRect parentRect = static_cast<QWidget *>(groupPanel->parent())->geometry();
    // move(parentRect.left(), parentRect.y());
    QWidget::resizeEvent(event);
}
