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

#include "gradientcolorpickerform.h"
#include "colorindicator.h"
#include "ui_gradientcolorpickerform.h"

#include <QMouseEvent>
#include <QPainter>

GradientColorPickerForm::GradientColorPickerForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GradientColorPickerForm)
{
    ui->setupUi(this);

    layout()->setAlignment(Qt::AlignTop);
    addIndicator(0, Qt::white);
    addIndicator(0.3, Qt::red);
    addIndicator(0.6, Qt::green);
    addIndicator(1, Qt::black);
    ui->markPanel->installEventFilter(this);
    ui->colorView->installEventFilter(this);
    connect(ui->colorPicker, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(onColorChanged(QColor,QColor)));
    connect(ui->colorPos, SIGNAL(valueChanged(int)), this, SLOT(onColorPosChanged(int)));
    connect(ui->delColor, SIGNAL(clicked(bool)), this, SLOT(onDelColorClicked()));
    connect(ui->colorAlpha, SIGNAL(valueChanged(int)), this, SLOT(onColorAlphaChanged(int)));
}

GradientColorPickerForm::~GradientColorPickerForm()
{
    for (int i = 0; i < indicators.count(); ++i) {
        delete indicators[i];
    }
    indicators.clear();
    delete ui;
}

bool GradientColorPickerForm::eventFilter(QObject *watched, QEvent *event)
{
    auto type = event->type();

    if (!event->isAccepted() && indicators.contains(watched)) {
        if(type == QEvent::KeyPress){
            // 监控键盘操作， 删除指示器
            auto kEvent = dynamic_cast<QKeyEvent*>(event);
            if (kEvent->key() == Qt::Key_Delete) {
                delIndicator(dynamic_cast<ColorIndicator*>(watched));
                emit valueChanged();
                event->accept();
            }
        }
    } else if (watched == ui->colorView && type == QEvent::Paint) {
        paintColorView(dynamic_cast<QPaintEvent*>(event));
        event->accept();
    }else if (watched == ui->markPanel && type == QEvent::MouseButtonRelease) {
        auto mEvent = dynamic_cast<QMouseEvent*>(event);
        if (mEvent->button()==Qt::LeftButton) {
            // 点击空白处新建指示器
            auto pos = mEvent->position();
            auto rect = ui->markPanel->rect();
            auto x = pos.x() - rect.left();
            if (rect.contains(pos.toPoint() - rect.topLeft())) {
                qreal percent = pos2Percent(x);
                bool flag = false;
                QGradientStop preItem = indicators[0]->getColor();
                auto minOffset = currentIndicator->rect().width();
                qreal temp = -1;
                foreach(auto item, indicators){
                    if(qAbs(item->pos().x() - x) < minOffset){
                        flag = true;
                        break;
                    }
                    if (temp == -1) {
                        temp = qAbs(item->pos().x() - x);
                        preItem = item->getColor();
                        continue;
                    }
                    if (qAbs(item->pos().x() - x) < temp) {
                        temp = qAbs(item->pos().x() - x);
                        preItem = item->getColor();
                    }
                }
                if(!flag){
                    addIndicator(percent, preItem.second);
                    emit valueChanged();
                    event->accept();
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

QGradientStops GradientColorPickerForm::getGradientStops()
{
    QGradientStops stops;
    foreach (auto item, indicators) {
        stops << item->getColor();
    }
    return stops;
}

void GradientColorPickerForm::setGradientStops(const QGradientStops &stops)
{
    if (stops.isEmpty() || stops.count() < 2) {
        return;
    }
    QGradientStops newStop{stops};
    for(int i=0; i<indicators.count(); i++) {
        QGradientStop stop = indicators[i]->getColor();
        int j = 0;
        for (; j < newStop.count(); ++j) {
            if (stop.first == newStop[j].first) {
                indicators[i]->setColor(newStop[j].second);
                newStop.removeAt(j);
                break;
            }
        }
        if (j > 0 && j == newStop.count()) {
            delIndicator(indicators[i]);
            i--;
        }
    }

    foreach(auto item, newStop){
        addIndicator(item.first, item.second);
    }
    ui->colorView->update();
}

void GradientColorPickerForm::onColorChanged(const QColor &oldColor, const QColor &newColor)
{
    Q_UNUSED(oldColor)
    if (currentIndicator == nullptr) {
        return;
    }
    currentIndicator->setColor(newColor);
    ui->colorView->update();
    emit valueChanged();
}

void GradientColorPickerForm::onColorPosChanged(int value)
{
    currentIndicator->setColorPos(value*1.0 / 100);
    currentIndicator->move(percent2Pos(value*1.0 / 100), 0);
    ui->colorView->update();
    emit valueChanged();
}

void GradientColorPickerForm::onDelColorClicked()
{
    if (indicators.count() <= 1) {
        return;
    }
    delIndicator(currentIndicator);
    emit valueChanged();
}

void GradientColorPickerForm::onIndicatorSelect()
{
    deselecteIndicators();
    currentIndicator = dynamic_cast<ColorIndicator*>(sender());
    currentIndicator->update();
    auto stop = currentIndicator->getColor();
    //更新其它控件的值
    ui->colorPicker->blockSignals(true);
    ui->colorPicker->setColor(stop.second);
    ui->colorPicker->blockSignals(false);
    ui->colorPos->blockSignals(true);
    ui->colorPos->setValue(stop.first * 100);
    ui->colorPos->blockSignals(false);
    ui->colorAlpha->blockSignals(true);
    ui->colorAlpha->setValue(stop.second.alpha());
    ui->colorAlpha->blockSignals(false);

}

void GradientColorPickerForm::onIndicatorMoved(const QPoint &offset)
{
    auto indicator = dynamic_cast<ColorIndicator*>(sender());
    auto width = ui->markPanel->width();
    int maxX = width - indicator->rect().width();
    auto geometry = indicator->geometry();
    int x = geometry.left() + offset.x();
    if (x < 0) {
        x = 0;
    }
    if (x > maxX) {
        x = maxX;
    }
    indicator->move(x,0);

    auto percent = pos2Percent(x);
    indicator->setColorPos(percent);
    ui->colorPos->blockSignals(true);
    ui->colorPos->setValue(100*percent);
    ui->colorPos->blockSignals(false);
    ui->colorView->update();
}

void GradientColorPickerForm::onIndicatorMoveEnd()
{
    emit valueChanged();
}

void GradientColorPickerForm::onIndicatorDelete()
{
    auto indicator = dynamic_cast<ColorIndicator*>(sender());
    if (indicators.count() > 1) {
        delIndicator(indicator);
        emit valueChanged();
    }else{
        indicator->show();
    }
}

void GradientColorPickerForm::paintColorView(QPaintEvent *event)
{
    if (indicators.isEmpty() || indicators.count() < 2) {
        return;
    }
    auto width = indicators[0]->rect().width();
    QRectF rect = event->rect();
    rect.setWidth(rect.width()-width/2);
    rect.setLeft(rect.left()+width/2);
    auto center = rect.center();
    QPainter painter(ui->colorView);
    QLinearGradient gradient(QPointF{rect.left(),center.y()}, QPointF{rect.right(), center.y()});
    gradient.setStops(getGradientStops());
    painter.setBrushOrigin(rect.left(),center.y());
    painter.setBrush(gradient);
    painter.drawRect(rect);
    painter.end();
}

void GradientColorPickerForm::addIndicator(qreal pos, const QColor &color)
{
    deselecteIndicators();
    auto indicator = new ColorIndicator(color, pos, ui->markPanel);
    indicator->show();
    indicators.append(indicator);
    currentIndicator = indicator;
    indicator->setSelected(true);
    auto x = percent2Pos(pos);
    indicator->move(x, 0);
    connect(indicator, SIGNAL(selectEvent()), this, SLOT(onIndicatorSelect()));
    connect(indicator, SIGNAL(posMoveEvent(QPoint)), this, SLOT(onIndicatorMoved(QPoint)));
    connect(indicator, SIGNAL(moveEndEvent()), this, SLOT(onIndicatorMoveEnd()));
    connect(indicator, SIGNAL(deleteEvent()), this, SLOT(onIndicatorDelete()));

    ui->colorView->update();
}

void GradientColorPickerForm::delIndicator(ColorIndicator *indicator)
{
    indicators.removeOne(indicator);
    if (indicator == currentIndicator || currentIndicator == nullptr) {
        if (indicators.count() > 0) {
            currentIndicator = indicators[0];
        } else {
            currentIndicator = nullptr;
        }
    }
    indicator->deleteLater();
    indicator = nullptr;

    ui->colorView->update();
}

void GradientColorPickerForm::deselecteIndicators()
{
    foreach (auto item, indicators) {
        if (item->isSelected()) {
            item->setSelected(false);
        }
    }
}

qreal GradientColorPickerForm::pos2Percent(int pos)
{
    auto rect = ui->markPanel->geometry();
    auto width = rect.width() - indicators[0]->rect().width();
    auto percent = pos*1.0/width;
    if (percent < 0) {
        percent = 0;
    }
    if (percent > 1){
        percent = 1;
    }
    return percent;
}

int GradientColorPickerForm::percent2Pos(qreal percent)
{
    auto rect = ui->markPanel->geometry();
    auto width = rect.width() - indicators[0]->rect().width();
    return percent * width;
}

void GradientColorPickerForm::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    foreach(auto item, indicators){
        item->move(percent2Pos(item->getColor().first), 0);
        ui->colorView->update();
    }
}

void GradientColorPickerForm::onColorAlphaChanged(int value)
{
    auto stop = currentIndicator->getColor();
    stop.second.setAlpha(value);
    currentIndicator->setColor(stop.second);
    ui->colorView->update();
    emit valueChanged();
}

