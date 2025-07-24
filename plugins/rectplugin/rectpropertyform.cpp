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

#include "htmlpropertyform.h"
#include "rectpropertyform.h"
#include "textpropertyform.h"
#include "timepropertyform.h"
#include "ui_rectpropertyform.h"
#include "zoneproperty.h"
#include <QComboBox>

RectPropertyForm::RectPropertyForm(QWidget *parent)
    : IPropertyForm(parent), ui(new Ui::RectPropertyForm)
{
    ui->setupUi(this);
    textAttr = nullptr;
    htmlAttr = nullptr;
    timeAttr = nullptr;
    layout()->setAlignment(Qt::AlignTop);

    // 关联事件
    connect(ui->posProperty, SIGNAL(propertyChanged(qint32,qint32,qint32,qint32,bool)),
            this, SLOT(posChanged(qint32,qint32,qint32,qint32,bool)));
    connect(ui->lineProperty, SIGNAL(propertyChanged(Qt::PenStyle,QColor,int)),
            this, SLOT(lineStyleChanged(Qt::PenStyle,QColor,int)));
    connect(ui->fillProperty, SIGNAL(propertyChanged(Qt::BrushStyle,QColor,QString)),
            this, SLOT(brushChanged(Qt::BrushStyle,QColor,QString)));
    connect(ui->fillProperty, SIGNAL(gradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)),
            this, SLOT(onGradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)));
}

RectPropertyForm::~RectPropertyForm()
{
    delete ui;
}

void RectPropertyForm::updateData()
{
    attr.copy(*graphicItem->attribute());
    QSignalBlocker posBlocker(ui->posProperty);
    QSignalBlocker lineBlocker(ui->lineProperty);
    QSignalBlocker fillBlocker(ui->fillProperty);
    auto width = attr.getWidth();
    auto height = attr.getHeight();
    auto pos = graphicItem->mapToScene(QPointF{-width/2, -height/2});
    ui->posProperty->setLeft(pos.x());
    ui->posProperty->setTop(pos.y());
    ui->posProperty->setWidth(width);
    ui->posProperty->setHeight(height);
    ui->posProperty->setAspectRatio(attr.getAspectRatio());
    auto pen = attr.getPen();
    ui->lineProperty->setShowLine(!pen.noPen());
    ui->lineProperty->setLineStyle(pen.getStyle());
    ui->lineProperty->setLineColor(pen.getColor());
    ui->lineProperty->setLineWidth(pen.getWidth());
    auto brush = attr.getBrush();
    ui->fillProperty->setBrushStyle(brush.getStyle());
    ui->fillProperty->setBaseColor(brush.getColor());
    ui->fillProperty->setImageFile(brush.getImage());
    ui->fillProperty->setGradientStops(brush.getGradientStops());
    ui->fillProperty->setGradientSpread(brush.getgradientSpread());
    ui->fillProperty->setControlPoint(graphicItem->shape(), brush.getLocation());

    QSignalBlocker roundBlocker(ui->roundSize);
    QSignalBlocker roundBlocker2(ui->roundChecked);
    QSignalBlocker rotationBlocker(ui->rotation);
    QSignalBlocker stateBlocker(ui->stateBox);
    ui->roundSize->setValue(attr.getArcSize());
    ui->roundChecked->setChecked(attr.getRound());
    if (!attr.getRound()) {
        ui->roundSize->hide();
    }
    ui->rotation->setValue(remainder(attr.getRotate(), 360));

    QMap<int, QString> stateSet = graphicItem->getAttributes();
    auto index = -1;
    auto state = graphicItem->state();
    ui->stateBox->clear();
    if (!stateSet.empty()){
        int j = -1;
        for (auto i = stateSet.begin(), end = stateSet.end(); i != end; i++) {
            ui->stateBox->addItem(i.value(), i.key());
            j ++;
            if (state == i.key()) {
                index  = j;
            }
        }
        if (index == -1 || index >= stateSet.count()) {
            index = 0;
        }
        ui->stateBox->setCurrentItem(index);
    }

    if (htmlAttr != nullptr) {
        htmlAttr->setHtml(attr.getData().toString());
    }
    if (timeAttr != nullptr) {
        auto data = attr.getData();
        if (!data.isNull()) {
            timeAttr->setData(data.value<TimeProperty>());
        }
    }
}

void RectPropertyForm::hideRound()
{
    for(auto i =0;i<ui->roundLayout->count();i++){
        QWidget *w = ui->roundLayout->itemAt(i)->widget();
        if(w != nullptr){
            w->setVisible(false);
        }
    }
}

void RectPropertyForm::addTextProperty()
{
    if (textAttr != nullptr) {
        return;
    }
    textAttr = new TextPropertyForm(this);
    ui->textWidget->layout()->addWidget(textAttr);
    connect(textAttr, SIGNAL(textFormatChanged(QTextFormat)), this, SLOT(onTextFormatChanged(QTextFormat)));
}

void RectPropertyForm::addHtmlProperty()
{
    if (htmlAttr != nullptr) {
        return;
    }
    htmlAttr = new HtmlPropertyForm(this);
    ui->textWidget->layout()->addWidget(htmlAttr);
    connect(htmlAttr, SIGNAL(htmlChanged(QString)), this, SLOT(onHtmlChanged(QString)));
}

void RectPropertyForm::addTimeProperty()
{
    if (timeAttr != nullptr) {
        return;
    }
    timeAttr = new TimePropertyForm(this);
    ui->textWidget->layout()->addWidget(timeAttr);
    connect(timeAttr, SIGNAL(dataChanged(TimeProperty)), this, SLOT(onTimeStyleChanged(TimeProperty)));
}

void RectPropertyForm::setGraphicItem(ICustomGraphic *item)
{
    auto obj = dynamic_cast<AbstractZoneItem *>(item);
    if (obj == nullptr) {
        return;
    }
    graphicItem = obj;

    // 初始化页面数据
    updateData();
}

ICustomGraphic *RectPropertyForm::getGraphicItem()
{
    return graphicItem;
}

void RectPropertyForm::on_roundChecked_toggled(bool checked)
{
    ui->roundSize->setVisible(checked);
    if (!checked){
        attr.setArcSize(0);
    } else {
        attr.setArcSize(ui->roundSize->value());
    }
    attr.setRound(checked);
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::on_roundSize_valueChanged(int arg1)
{
    if (ui->roundChecked->isChecked()) {
        attr.setArcSize(arg1);
        graphicItem->updateAttribute(&attr);
    }
}

void RectPropertyForm::on_rotation_valueChanged(double arg1)
{
    attr.setRotate(arg1);
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio)
{
    if (attr.getAspectRatio() != aspectRatio) {
        attr.setAspectRatio(aspectRatio);
    }else{
        auto oldTopLeft = graphicItem->mapToParent(QPointF{-attr.getWidth()/2, -attr.getHeight()/2});
        attr.setPos(attr.getPos() + QPointF{left - oldTopLeft.x(), top - oldTopLeft.y()});
        if (width != attr.getWidth() || height != attr.getHeight()) {
            auto logicRect = attr.getLogicRect();
            auto dx = width - attr.getWidth();
            auto dy = height - attr.getHeight();
            logicRect.adjust(0,0,dx,dy);
            attr.setPos(graphicItem->mapToParent(logicRect.center()));
            attr.setWidth(width);
            attr.setHeight(height);
        }
    }
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::lineStyleChanged(Qt::PenStyle style, QColor Color, int width)
{
    auto pen = attr.getPen();
    pen.setColor(Color.name());
    pen.setStyle(style);
    pen.setWidth(width);
    attr.setPen(pen);
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::brushChanged(Qt::BrushStyle brushStyle, const QColor &baseColor, const QString imageFile)
{
    auto brush = attr.getBrush();
    brush.setStyle(brushStyle);
    brush.setColor(baseColor.rgb());
    brush.setImage(imageFile);
    brush.setGradientStops(ui->fillProperty->gradientStops());//QGradientStops{});
    brush.setLocation(ui->fillProperty->controlPoint());//QPolygonF{});
    brush.setgradientSpread(ui->fillProperty->gradientSpread());
    attr.setBrush(brush);

    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops,
                                         QGradient::Spread spread, const QPolygonF &points)
{
    auto brush = attr.getBrush();
    brush.setStyle(brushStyle);
    brush.setGradientStops(stops);
    brush.setgradientSpread(spread);
    brush.setLocation(points);
    attr.setBrush(brush);
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::on_stateBox_itemAdded(int index)
{
    auto name = ui->stateBox->itemText(index);
    int id = graphicItem->addAttribute(name);
    ui->stateBox->getComboBox()->setItemData(index, id);
}

void RectPropertyForm::on_stateBox_itemModified(int index)
{
    auto name = ui->stateBox->itemText(index);
    auto id = ui->stateBox->itemData(index);
    graphicItem->modifyAttribute(id.toInt(), name);
}


void RectPropertyForm::on_stateBox_itemRemoved(const QString &name, const QVariant &data)
{
    Q_UNUSED(name)
    graphicItem->removeAttribute(data.toInt());
}


void RectPropertyForm::on_stateBox_currentIndexChanged(int index)
{
    auto id = ui->stateBox->itemData(index);
    graphicItem->changeAttribute(id.toInt());
}

void RectPropertyForm::onTextFormatChanged(const QTextFormat &format)
{
        auto obj = dynamic_cast<ITextObject*>(graphicItem);
        if (obj == nullptr) {
            return;
        }
        obj->setTextFormat(format);
}

void RectPropertyForm::onHtmlChanged(const QString &data)
{
    if (htmlAttr == nullptr) {
        return;
    }
    attr.setData(data);
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::onTimeStyleChanged(const TimeProperty &data)
{
    if (timeAttr == nullptr) {
        return;
    }
    attr.setData(QVariant::fromValue(data));//qDebug() << "-----------" << data;
    graphicItem->updateAttribute(&attr);
}

void RectPropertyForm::setTextFormat(const QTextFormat &format)
{
    if (textAttr == nullptr) {
        return;
    }
    textAttr->blockSignals(true);
    textAttr->setTextFormat(format);
    textAttr->blockSignals(false);
}
