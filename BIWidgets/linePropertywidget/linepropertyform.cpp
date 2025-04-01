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

#include "linepropertyform.h"
#include "qscreen.h"
#include "ui_linepropertyform.h"

#include <QAbstractItemView>
#include <QMetaEnum>
#include <QPainter>
#include <QResizeEvent>

LinePropertyForm::LinePropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LinePropertyForm)
{
    ui->setupUi(this);

    screenRatio = QGuiApplication::primaryScreen()->devicePixelRatio();

    initLineStyleName();
    initLineStyle();
    // 设置comboBox的视图为自定义视图，拦截view的事件Q_D();
    QAbstractItemView* view = ui->lineStyle->view();
    if (view) {
        view->installEventFilter(this);
    }
    // 初始化
    setLineColor(color);
    setLineStyle(style);
    setLineWidth(width);
}

LinePropertyForm::~LinePropertyForm()
{
    delete ui;
}

bool LinePropertyForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->lineStyle->view() && event->type() == QEvent::Resize)
    {
        // view 大小改变时重新初始化
        initLineStyle();
    }
    return QWidget::eventFilter(watched, event);
}

void LinePropertyForm::initLineStyleName()
{
    lineStyleName["NoPen"] = tr("无");
    lineStyleName["SolidLine"] = tr("实线");
    lineStyleName["DashLine"] = tr("虚线");
    lineStyleName["DotLine"] = tr("点线");
    lineStyleName["DashDotLine"] = tr("点划线");
    lineStyleName["DashDotDotLine"] = tr("双点划线");
}

void LinePropertyForm::initLineStyle()
{
    QComboBox *lineStyleComboBox = ui->lineStyle;
    qint16 width = lineStyleComboBox->size().width() - 8;
    qint16 height = lineStyleComboBox->iconSize().height();
    int index = lineStyleComboBox->currentIndex();
    lineStyleComboBox->clear();
    lineStyleComboBox->setIconSize({width, height});

    auto textColor = palette().brush(QPalette::Text).color();

    styleIndex.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<Qt::PenStyle>();
    for (int i = 0; i < metaEnum.keyCount() - 1; i++)
    {
        QPixmap pixmap(width * screenRatio, height * screenRatio);
        pixmap.fill(Qt::transparent);
        pixmap.setDevicePixelRatio(screenRatio);
        // 绘制
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
        painter.setRenderHint(QPainter::LosslessImageRendering);
        QPen pen;
        pen.setStyle(Qt::PenStyle(metaEnum.value(i)));
        pen.setColor(textColor);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(0, height / 2,
                         width, height / 2);
        painter.end();
        QIcon icon(pixmap);
        // metaEnum.value(i)是每一个枚举成员后面对应的值
        lineStyleComboBox->addItem(icon,"", metaEnum.value(i));
        // metaEnum.key(i) 是枚举类型每一个枚举成员的名称；
        int itemIndex = lineStyleComboBox->count() - 1;
        lineStyleComboBox->setItemData(itemIndex,
                                       lineStyleName[metaEnum.key(i)], Qt::ToolTipRole);
        styleIndex[Qt::PenStyle(metaEnum.value(i))] = itemIndex;
    }

    if (index > -1){
        lineStyleComboBox->setCurrentIndex(index);
    }
}

Qt::PenStyle LinePropertyForm::lineStyle() const
{
    return style;
}

void LinePropertyForm::setLineStyle(Qt::PenStyle newLineStyle)
{
    if (style == newLineStyle)
        return;
    style = newLineStyle;
    ui->lineStyle->blockSignals(true);
    ui->lineStyle->setCurrentIndex(styleIndex[newLineStyle]);
    ui->lineStyle->blockSignals(false);
    if (Qt::NoPen == newLineStyle) {
        setShowLine(false);
    }else{
        setShowLine(true);
    }
}

int LinePropertyForm::lineWidth() const
{
    return width;
}

void LinePropertyForm::setLineWidth(int newLineWidth)
{
    if (width == newLineWidth)
        return;
    width = newLineWidth;
    ui->lineWidth->blockSignals(true);
    ui->lineWidth->setValue(newLineWidth);
    ui->lineWidth->blockSignals(false);
}

QColor LinePropertyForm::lineColor() const
{
    return color;
}

void LinePropertyForm::setLineColor(const QColor &newLineColor)
{
    if (color == newLineColor)
        return;
    color = newLineColor;
    ui->lineColor->blockSignals(true);
    ui->lineColor->setColor(newLineColor);
    ui->lineColor->blockSignals(false);
}

void LinePropertyForm::on_lineStyle_currentIndexChanged(int index)
{
    if (index < 0) {
        return;
    }
    int colorIndex = ui->lineStyle->itemData(index).toInt();
    style = Qt::PenStyle(colorIndex);

    emit valueChanged();
}


void LinePropertyForm::on_lineColor_colorChanged(const QColor &oldColor, const QColor &newColor)
{
    if(newColor != oldColor){
        color = newColor;
        emit valueChanged();
    }
}


void LinePropertyForm::on_lineWidth_valueChanged(int arg1)
{
    width = arg1;
    emit valueChanged();
}

bool LinePropertyForm::getShowLine() const
{
    return showLine;
}

void LinePropertyForm::showLineChanged()
{
    if (showLine) {
        setConstraint(QLayout::SetMinimumSize);
        ui->lineColor->show();
        ui->lineStyle->show();
        ui->lineWidth->show();
        if (style == Qt::NoPen){
            setLineStyle(Qt::SolidLine);
        }
        if (ui->lineWidth->value() == 0) {
            ui->lineWidth->blockSignals(true);
            ui->lineWidth->setValue(1);
            ui->lineWidth->blockSignals(false);
        }
    }else{
        setConstraint(QLayout::SetFixedSize);
        ui->lineColor->hide();
        ui->lineStyle->hide();
        ui->lineWidth->hide();
    }
}

void LinePropertyForm::setConstraint(QLayout::SizeConstraint constraint)
{
    auto localLayout = layout();
    localLayout->setSizeConstraint(constraint);
    setLayout(localLayout);
}

void LinePropertyForm::setShowLine(bool newShowLine)
{
    showLine = newShowLine;
    ui->lineChecked->blockSignals(true);
    ui->lineChecked->setChecked(showLine);
    ui->lineChecked->blockSignals(false);
    showLineChanged();
}

bool LinePropertyForm::alwaysShow() const
{
    return hideCheck;
}

void LinePropertyForm::setAlwaysShow(bool value)
{
    hideCheck = value;
    ui->lineChecked->setCheckable(!value);
    if (value) {
        ui->lineChecked->setStyleSheet("QCheckBox::indicator{width:0;height:0;border:none;background:none;}");
    }
}

void LinePropertyForm::on_lineChecked_toggled(bool checked)
{
    showLine = checked;
    showLineChanged();
    emit valueChanged();
}



void LinePropertyForm::resizeEvent(QResizeEvent *event)
{
    emit sizeChanged(event->size());
}
