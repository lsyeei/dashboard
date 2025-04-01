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

#include "colorpicker.h"
#include "colorpickerprivate.h"
#include <QPainter>
// #include <QFontDatabase>
#include <QMouseEvent>
#include <QColorDialog>
#include <QDebug>
#include <QScreen>
#include <QGuiApplication>
#include <QSvgRenderer>

ColorPickerPrivate::ColorPickerPrivate(ColorPicker *parent) :
    QObject(parent), q_ptr(parent)
{}

ColorPicker::ColorPicker(QWidget *parent) :
    QWidget(parent), d_ptr(new ColorPickerPrivate(this))
{
    Q_D(ColorPicker);
    // setMinimumSize(d->minSize);
    resize(d->defaultSize);
    // int familyId = QFontDatabase::addApplicationFont(":/icons/fontawesome-webfont.ttf");
    // fontFamily = QFontDatabase::applicationFontFamilies(familyId).at(0);

}

ColorPicker::~ColorPicker()
{}

QColor ColorPicker::getColor() const
{
    Q_D(const ColorPicker);
    return d->color;
}

void ColorPicker::setColor(QColor newColor)
{
    Q_D(ColorPicker);
    if (newColor.isValid() && newColor != d->color){
        d->color = newColor;
        update();
    }
}

QSize ColorPicker::sizeHint() const
{
    Q_D(const ColorPicker);
    return d->hintSize;
}

QSize ColorPicker::minimumSizeHint() const
{
    Q_D(const ColorPicker);
    return d->minSize;
}

int ColorPicker::heightForWidth(int width) const
{
    Q_D(const ColorPicker);
    qreal height = width * d->minSize.height() / d->minSize.width();
    return qRound(height);
}

bool ColorPicker::hasHeightForWidth() const
{
    return true;
}

void ColorPicker::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    Q_D(ColorPicker);

    //绘制界面组件
    QPainter painter(this);
    //视口矩形区
    QRect rect(0,0,width(),height());
    //设置视口
    painter.setViewport(rect);
    // 设置窗口大小，逻辑坐标
    QRect logicRect{0, 0, 90, 44};
    painter.setWindow(logicRect);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    auto p = palette();
    QPalette::ColorGroup group = QPalette::Normal;
    if (!isEnabled()) {
        group = QPalette::Disabled;
    }
    //绘制
    // QPen pen(QColor(0xD8D8D8));
    QPen pen(p.brush(group, QPalette::Shadow).color());
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::BevelJoin);
    painter.setPen(pen);
    // QBrush brush(d->normalColor);
    QBrush brush = p.brush(group, QPalette::Button);
    if (d->isHover){
        // brush.setColor(d->hoverColor);
        brush = p.brush(group, QPalette::Light);
    }
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    qint16 radius{5};
    painter.drawRoundedRect(logicRect, radius, radius);

    // 绘制颜色样例
    // pen.setColor(Qt::white);
    painter.setPen(pen);
    brush.setColor(d->color);
    painter.setBrush(brush);
    painter.drawRect(8, 8, 48, 28);

    // 绘制图标
    // pen.setColor((d->isHover?Qt::black:Qt::gray);
    // painter.setPen(pen);
    // QFont font(fontFamily);
    // font.setPixelSize(16);
    // painter.setFont(font);
    // painter.drawText(QRectF{60, 8, 22, 22}, Qt::AlignVCenter | Qt::AlignCenter, "\uf040");
    // d->icon.setFillColor(d->isHover ? Qt::black : Qt::gray);
    d->icon.setFillColor(d->isHover ? p.brush(group, QPalette::Highlight).color()
                                    : p.brush(group, QPalette::ButtonText).color());
    d->icon.render(&painter, QRect{62, 11, 22, 22});
}

void ColorPicker::mousePressEvent(QMouseEvent *event)
{
    Q_D(ColorPicker);
    if (event->button() == Qt::LeftButton){
        QColor oldColor = d->color;
        d->pickerColor();
        if (oldColor != d->color) {
            emit colorChanged(oldColor, d->color);
        }
    }

    QWidget::mousePressEvent(event);
}

void ColorPicker::enterEvent(QEnterEvent *event)
{
    Q_D(ColorPicker);
    d->isHover = true;
    update();

    return QWidget::enterEvent(event);
}

void ColorPicker::leaveEvent(QEvent *event)
{
    Q_D(ColorPicker);
    d->isHover = false;
    update();

    return QWidget::leaveEvent(event);
}

void ColorPicker::resizeEvent(QResizeEvent *event)
{
    Q_D(ColorPicker);
    int width = event->size().width();
    // setFixedSize({width, heightForWidth(width)});
    d->hintSize = {width, heightForWidth(width)};
    QRect rect = this->geometry();
    rect.setHeight(d->hintSize.height());
    this->setGeometry(rect);
    QWidget::resizeEvent(event);
}

void ColorPickerPrivate::pickerColor()
{
    Q_Q(ColorPicker);
    QColor newColor = QColorDialog::getColor(color, q, u8"选择颜色");
    q->setColor(newColor);
}



