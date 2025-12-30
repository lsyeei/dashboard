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

#include "chartpropertyform.h"
#include "abstractgooglechart.h"
#include "syntaxfactory.h"
#include "ui_chartpropertyform.h"
#include <QComboBox>
#include <QResizeEvent>
#include "isubwidget.h"

ChartPropertyForm::ChartPropertyForm(QWidget *parent)
    : IPropertyForm(parent), ui(new Ui::ChartPropertyForm)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);
    SyntaxFactory::instance()->highlightDocument(ui->options->document(), "json");
    SyntaxFactory::instance()->highlightDocument(ui->defaultData->document(), "json");
    // 关联事件
    connect(ui->posProperty, SIGNAL(propertyChanged(qint32,qint32,qint32,qint32,bool)),
            this, SLOT(posChanged(qint32,qint32,qint32,qint32,bool)));
    connect(ui->lineProperty, SIGNAL(propertyChanged(Qt::PenStyle,QColor,int)),
            this, SLOT(lineStyleChanged(Qt::PenStyle,QColor,int)));
    connect(ui->fillProperty, SIGNAL(propertyChanged(Qt::BrushStyle,QColor,QString)),
            this, SLOT(brushChanged(Qt::BrushStyle,QColor,QString)));
    connect(ui->fillProperty, SIGNAL(gradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)),
            this, SLOT(onGradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)));
    connect(ui->updateBtn, SIGNAL(clicked(bool)), this, SLOT(onChartChanged()));
}

ChartPropertyForm::~ChartPropertyForm()
{
    delete ui;
}

void ChartPropertyForm::updateData()
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

    QSignalBlocker chartDataBlocker(ui->defaultData);
    QSignalBlocker chartOptionsBolcker(ui->options);
    ui->defaultData->setText(attr.getDataTable());
    ui->options->setText(attr.getOptions());

    if (!subWidget.isNull()) {
        auto data = attr.getData();
        if (!data.isNull()) {
            subWidget->setData(data);
        }
    }
}

void ChartPropertyForm::hideRound()
{
    for(auto i =0;i<ui->roundLayout->count();i++){
        QWidget *w = ui->roundLayout->itemAt(i)->widget();
        if(w != nullptr){
            w->setVisible(false);
        }
    }
}

void ChartPropertyForm::addSubWidget(ISubWidget *widget)
{
    subWidget.reset(widget);
    ui->extendWidget->layout()->addWidget(widget);
    connect(widget, SIGNAL(dataChanged(QVariant)), this, SLOT(onSubWidgetDataChanged(QVariant)));
}

ISubWidget *ChartPropertyForm::getSubWidget()
{
    return subWidget.data();
}

void ChartPropertyForm::setGraphicItem(ICustomGraphic *item)
{
    auto obj = dynamic_cast<AbstractGoogleChart *>(item);
    if (obj == nullptr) {
        return;
    }
    graphicItem = obj;

    // 初始化页面数据
    updateData();
}

ICustomGraphic *ChartPropertyForm::getGraphicItem()
{
    return graphicItem;
}

void ChartPropertyForm::on_roundChecked_toggled(bool checked)
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

void ChartPropertyForm::on_roundSize_valueChanged(int arg1)
{
    if (ui->roundChecked->isChecked()) {
        attr.setArcSize(arg1);
        graphicItem->updateAttribute(&attr);
    }
}

void ChartPropertyForm::on_rotation_valueChanged(double arg1)
{
    attr.setRotate(arg1);
    graphicItem->updateAttribute(&attr);
}

void ChartPropertyForm::posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio)
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

void ChartPropertyForm::lineStyleChanged(Qt::PenStyle style, QColor Color, int width)
{
    auto pen = attr.getPen();
    pen.setColor(Color.name());
    pen.setStyle(style);
    pen.setWidth(width);
    attr.setPen(pen);
    graphicItem->updateAttribute(&attr);
}

void ChartPropertyForm::brushChanged(Qt::BrushStyle brushStyle, const QColor &baseColor, const QString imageFile)
{
    if (graphicItem == nullptr) {
        return;
    }
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

void ChartPropertyForm::onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops,
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

void ChartPropertyForm::on_stateBox_itemAdded(int index)
{
    auto name = ui->stateBox->itemText(index);
    int id = graphicItem->addAttribute(name);
    ui->stateBox->getComboBox()->setItemData(index, id);
}

void ChartPropertyForm::on_stateBox_itemModified(int index)
{
    auto name = ui->stateBox->itemText(index);
    auto id = ui->stateBox->itemData(index);
    graphicItem->modifyAttribute(id.toInt(), name);
}

void ChartPropertyForm::on_stateBox_itemRemoved(const QString &name, const QVariant &data)
{
    Q_UNUSED(name)
    graphicItem->removeAttribute(data.toInt());
}

void ChartPropertyForm::on_stateBox_currentIndexChanged(int index)
{
    auto id = ui->stateBox->itemData(index);
    graphicItem->changeAttribute(id.toInt());
}

void ChartPropertyForm::onSubWidgetDataChanged(const QVariant &data)
{
    attr.setData(data);
    graphicItem->updateAttribute(&attr);
}

void ChartPropertyForm::onChartChanged()
{
    attr.setDataTable(ui->defaultData->toPlainText());
    attr.setOptions(ui->options->toPlainText());
    graphicItem->updateAttribute(&attr);
}
