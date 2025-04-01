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

#include "colorindicator.h"

#include <QMouseEvent>
#include <QPainter>
#include <QVBoxLayout>

ColorIndicator::ColorIndicator(const QColor &indicatorColor, qreal pos, QWidget *parent)
    : QWidget{parent}, color{indicatorColor}, colorPos{pos}
{
    show();
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(width+1);
}

void ColorIndicator::setSelected(bool flag)
{
    selected = flag;
    update();
}

void ColorIndicator::setColor(const QColor &value)
{
    if (color == value) {
        return;
    }
    color = value;
    update();
}

void ColorIndicator::setColorPos(qreal pos)
{
    if (qFuzzyCompare(pos, colorPos)) {
        return;
    }
    colorPos = pos;
}

bool ColorIndicator::isSelected()
{
    return selected;
}

QGradientStop ColorIndicator::getColor()
{
    return {colorPos, color};
}


int ColorIndicator::heightForWidth(int width) const
{
    return width + qTan(60*M_PI/180) * width/2+3;
}


bool ColorIndicator::hasHeightForWidth() const
{
    return true;
}

QSize ColorIndicator::sizeHint() const
{
    return {width+1, heightForWidth(width)};
}

void ColorIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    // 绘制三角指示器
    qreal angleHeight = qTan(60*M_PI/180)*width/2;
    QPolygonF polygon{{width*1.0/2+0.5,0},{width*1.0+1, angleHeight},{0, angleHeight}};
    QBrush brush{Qt::lightGray};
    QPen pen{Qt::NoPen};
    if (selected) {
        brush.setColor(Qt::black);
    }
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawPolygon(polygon);
    // 绘制色块
    brush.setColor(color);
    pen = QPen{Qt::white, 1, Qt::SolidLine};
    painter.setPen(pen);
    painter.setBrush(brush);
    QRectF colorRect{0.5,angleHeight+1.5,width*1.0,width*1.0};
    painter.drawRect(colorRect);
    painter.end();
}


void ColorIndicator::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)){
        selected = true;
        lastPos = event->globalPosition();
        emit selectEvent();
        grabMouse();
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}

void ColorIndicator::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        releaseMouse();
        if (deleteFlag) {
            emit deleteEvent();
        } else if (moveFlag) {
            emit moveEndEvent();
        }
        deleteFlag = false;
        moveFlag = false;
    }else if(event->button() == Qt::RightButton){
        // 删除
        emit deleteEvent();
    }

    QWidget::mouseReleaseEvent(event);
}


void ColorIndicator::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)){
        int offset = event->globalPosition().x() - lastPos.x();
        lastPos = event->globalPosition();
        if (event->position().y() > rect().bottom()) {
            deleteFlag = true;
            hide();
        }else{
            show();
            deleteFlag = false;
        }
        emit posMoveEvent({offset,0});
        moveFlag = true;
        event->accept();
        return;
    }
    QWidget::mouseMoveEvent(event);
}
