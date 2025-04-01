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

#include "circleslider.h"

#include <QPaintEvent>
#include <QPainter>

CircleSlider::CircleSlider(QWidget *parent) :
    QWidget(parent)
{
}

qreal CircleSlider::getMin() const
{
    return min;
}

void CircleSlider::setMin(qreal newMin)
{
    if (qFuzzyCompare(min, newMin))
        return;
    if (newMin >= max) {
        return;
    }
    min = newMin;
    emit minChanged();
}

qreal CircleSlider::getMax() const
{
    return max;
}

void CircleSlider::setMax(qreal newMax)
{
    if (qFuzzyCompare(max, newMax))
        return;
    if (newMax <= min) {
        return;
    }
    max = newMax;
    emit maxChanged();
}

qreal CircleSlider::getValue() const
{
    return value;
}

void CircleSlider::setValue(qreal newValue)
{
    if (qFuzzyCompare(value, newValue))
        return;
    value = newValue;
    update();
}

int CircleSlider::heightForWidth(int width) const
{
    return width;
}

bool CircleSlider::hasHeightForWidth() const
{
    return true;
}

QSize CircleSlider::sizeHint() const
{
    return {25,25};
}

QSize CircleSlider::minimumSizeHint() const
{
    return {20,20};
}


void CircleSlider::mousePressEvent(QMouseEvent *event)
{
    mouseEvent(event);
    QWidget::mousePressEvent(event);
}


void CircleSlider::mouseReleaseEvent(QMouseEvent *event)
{
    // mouseEvent(event);
    QWidget::mouseReleaseEvent(event);
}

void CircleSlider::mouseMoveEvent(QMouseEvent *event)
{
    mouseEvent(event);
    QWidget::mouseMoveEvent(event);
}


void CircleSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    auto textColor = palette().brush(QPalette::Text).color();
    QPen pen{textColor, 2, Qt::SolidLine};
    QBrush brush(textColor, Qt::SolidPattern);
    QPainter painter(this);
    int r = 50;
    QPoint center{r,r};
    painter.setWindow(0,0,2*r,2*r);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setPen(pen);
    // 绘制外框
    painter.drawEllipse(center, r-1, r-1);
    // 绘制指针
    QLineF l{center,{0,0}};
    l.setLength(r);
    l.setAngle(value*360/(max-min));
    painter.drawLine(l);
    // 绘制圆心
    painter.setBrush(brush);
    painter.drawEllipse(center, 2,2);
    painter.end();
}

void CircleSlider::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    update();
}


void CircleSlider::mouseEvent(QMouseEvent *event)
{
    if (event->buttons().testFlag(Qt::LeftButton)){
        // 计算值
        QLineF l{rect().center(), event->pos()};
        float angle = l.angle();
        if (qAbs(angle) > 360) {
            angle = std::fmod(angle, 360.0);
        }
        if (angle < 0) {
            angle += 360;
        }
        value = (max - min)*angle/360;
        emit valueChanged(value);
        update();
        event->accept();
    }
}
