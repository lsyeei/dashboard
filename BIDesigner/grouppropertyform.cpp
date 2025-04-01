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

#include "grouppropertyform.h"
#include "ui_grouppropertyform.h"
#include <QComboBox>

GroupPropertyForm::GroupPropertyForm(QWidget *parent)
    : IPropertyForm(parent)
    , ui(new Ui::GroupPropertyForm)
{
    ui->setupUi(this);
    ui->mergeOptions->hide();

    // 关联事件
    connect(ui->posProperty, SIGNAL(propertyChanged(qint32,qint32,qint32,qint32,bool)),
            this, SLOT(posChanged(qint32,qint32,qint32,qint32,bool)));
    connect(ui->lineProperty, SIGNAL(propertyChanged(Qt::PenStyle,QColor,int)),
            this, SLOT(lineStyleChanged(Qt::PenStyle,QColor,int)));
    connect(ui->fillProperty, SIGNAL(propertyChanged(Qt::BrushStyle,QColor,QString)),
            this, SLOT(brushChanged(Qt::BrushStyle,QColor,QString)));
    connect(ui->fillProperty, SIGNAL(gradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)),
            this, SLOT(onGradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)));
    connect(ui->mergeCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(mergeCheckChanged()));
    connect(ui->unit, SIGNAL(toggled(bool)), this, SLOT(groupReshape(bool)));
    connect(ui->intersect, SIGNAL(toggled(bool)), this, SLOT(groupReshape(bool)));
    connect(ui->subtract, SIGNAL(toggled(bool)), this, SLOT(groupReshape(bool)));
    connect(ui->exclude, SIGNAL(toggled(bool)), this, SLOT(groupReshape(bool)));
}

GroupPropertyForm::~GroupPropertyForm()
{
    delete ui;
}

void GroupPropertyForm::setGraphicItem(ICustomGraphic *item)
{
    auto obj = dynamic_cast<GraphicsItemGroup *>(item);
    if (obj == nullptr) {
        return;
    }
    graphicItem = obj;

    // 初始化页面数据
    updateData();
}

ICustomGraphic *GroupPropertyForm::getGraphicItem()
{
    return graphicItem;
}

void GroupPropertyForm::updateData()
{
    property.copy(*graphicItem->attribute());
    auto width = property.getWidth();
    auto height = property.getHeight();
    auto pos = graphicItem->mapToScene(QPointF{-width/2, -height/2});
    ui->posProperty->blockSignals(true);
    ui->posProperty->setLeft(pos.x());
    ui->posProperty->setTop(pos.y());
    ui->posProperty->setWidth(width);
    ui->posProperty->setHeight(height);
    ui->posProperty->setAspectRatio(property.getAspectRatio());
    ui->posProperty->blockSignals(false);

    ui->lineProperty->blockSignals(true);
    ui->lineProperty->setLineStyle(property.getPen().getStyle());
    ui->lineProperty->setLineColor(property.getPen().getColor());
    ui->lineProperty->setLineWidth(property.getPen().getWidth());
    ui->lineProperty->blockSignals(false);

    auto brush = property.getBrush();
    ui->fillProperty->blockSignals(true);
    ui->fillProperty->setBrushStyle(brush.getStyle());
    ui->fillProperty->setBaseColor(brush.getColor());
    ui->fillProperty->setImageFile(brush.getImage());
    ui->fillProperty->setGradientSpread(brush.getgradientSpread());
    ui->fillProperty->setGradientStops(brush.getGradientStops());
    ui->fillProperty->setControlPoint(graphicItem->shape(), brush.getLocation());
    ui->fillProperty->blockSignals(false);

    ui->roundSize->blockSignals(true);
    ui->roundSize->setValue(property.getArcSize());
    ui->roundSize->blockSignals(false);
    ui->roundChecked->blockSignals(true);
    ui->roundChecked->setChecked(property.getRound());
    ui->roundChecked->blockSignals(false);
    if (!property.getRound()) {
        ui->roundSize->hide();
    }
    ui->rotation->blockSignals(true);
    ui->rotation->setValue(remainder(property.getRotate(), 360));
    ui->rotation->blockSignals(false);

    QMap<int, QString> stateSet = graphicItem->getAttributes();
    auto index = -1;
    auto state = graphicItem->state();
    ui->stateBox->blockSignals(true);
    ui->stateBox->clear();
    if (!stateSet.empty()){
        int j = -1;
        for (auto i = stateSet.begin(), end = stateSet.end(); i != end; i++) {
            ui->stateBox->addItem(i.value(), i.key());
            j ++;
            if (state == i.key()) {
                index = j;
            }
        }
        if (index == -1 || index >= stateSet.count()) {
            index = 0;
        }
        ui->stateBox->setCurrentItem(index);
    }

    auto mergeType = graphicItem->getMergeType();
    ui->mergeCheck->blockSignals(true);
    if (mergeType == GraphicsItemGroup::None) {
        ui->mergeCheck->setChecked(false);
        disableMergeOptions();
    }else{
        switch (mergeType) {
        case GraphicsItemGroup::Unit:
            ui->unit->blockSignals(true);
            ui->unit->setChecked(true);
            ui->unit->blockSignals(false);
            break;
        case GraphicsItemGroup::Intersect:
            ui->intersect->blockSignals(true);
            ui->intersect->setChecked(true);
            ui->intersect->blockSignals(false);
            break;
        case GraphicsItemGroup::Subtract:
            ui->subtract->blockSignals(true);
            ui->subtract->setChecked(true);
            ui->subtract->blockSignals(false);
            break;
        case GraphicsItemGroup::Exclude:
            ui->exclude->blockSignals(true);
            ui->exclude->setChecked(true);
            ui->exclude->blockSignals(false);
            break;
        default:
            break;
        }
    }
    ui->mergeCheck->blockSignals(false);
}

void GroupPropertyForm::on_roundChecked_toggled(bool checked)
{
    ui->roundSize->setVisible(checked);
    if (!checked){
        property.setArcSize(0);
    } else {
        property.setArcSize(ui->roundSize->value());
    }
    property.setRound(checked);
    graphicItem->updateAttribute(&property);
}


void GroupPropertyForm::on_roundSize_valueChanged(int arg1)
{
    if (ui->roundChecked->isChecked()) {
        property.setArcSize(arg1);
        graphicItem->updateAttribute(&property);
    }
}


void GroupPropertyForm::on_rotation_valueChanged(double arg1)
{
    property.setRotate(arg1);
    graphicItem->updateAttribute(&property);
}

void GroupPropertyForm::posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio)
{
    if (property.getAspectRatio() != aspectRatio) {
        property.setAspectRatio(aspectRatio);
    }else{
        auto oldTopLeft = graphicItem->mapToParent(QPointF{-property.getWidth()/2, -property.getHeight()/2});
        property.setPos(property.getPos() + QPointF{left - oldTopLeft.x(), top - oldTopLeft.y()});
        if (width != property.getWidth() || height != property.getHeight()) {
            auto logicRect = property.getLogicRect();
            auto dx = width - property.getWidth();
            auto dy = height - property.getHeight();
            logicRect.adjust(0,0,dx,dy);
            property.setPos(graphicItem->mapToParent(logicRect.center()));
            property.setWidth(width);
            property.setHeight(height);
        }
    }
    graphicItem->updateAttribute(&property);
}

void GroupPropertyForm::lineStyleChanged(Qt::PenStyle style, QColor Color, int width)
{
    auto pen = property.getPen();
    pen.setColor(Color.name());
    pen.setStyle(style);
    pen.setWidth(width);
    property.setPen(pen);
    graphicItem->updateAttribute(&property);
}

void GroupPropertyForm::brushChanged(Qt::BrushStyle brushStyle, const QColor &baseColor, const QString imageFile)
{
    auto brush = property.getBrush();
    brush.setStyle(brushStyle);
    brush.setColor(baseColor.rgb());
    brush.setImage(imageFile);
    brush.setGradientStops(ui->fillProperty->gradientStops());//QGradientStops{});
    brush.setLocation(ui->fillProperty->controlPoint());//QPolygonF{});
    property.setBrush(brush);
    graphicItem->updateAttribute(&property);
}


void GroupPropertyForm::on_stateBox_itemAdded(int index)
{
    auto name = ui->stateBox->itemText(index);
    int id = graphicItem->addAttribute(name);
    ui->stateBox->getComboBox()->setItemData(index, id);
}


void GroupPropertyForm::on_stateBox_itemModified(int index)
{
    auto name = ui->stateBox->itemText(index);
    auto id = ui->stateBox->itemData(index);
    graphicItem->modifyAttribute(id.toInt(), name);
}


void GroupPropertyForm::on_stateBox_itemRemoved(const QString &name, const QVariant &data)
{
    Q_UNUSED(name)
    graphicItem->removeAttribute(data.toInt());
}


void GroupPropertyForm::on_stateBox_currentIndexChanged(int index)
{
    auto id = ui->stateBox->itemData(index);
    graphicItem->changeAttribute(id.toInt());
}

void GroupPropertyForm::mergeCheckChanged()
{
    if (ui->mergeCheck->isChecked()) {
        ui->mergeOptions->show();
        ui->unit->setChecked(true);
        graphicItem->setMergeType(GraphicsItemGroup::Unit);
    } else {
        disableMergeOptions();
        graphicItem->setMergeType(GraphicsItemGroup::None);
    }
}

void GroupPropertyForm::groupReshape(bool checked)
{
    if (!checked) {
        return;
    }
    auto obj = dynamic_cast<QObject*>(sender());
    auto name = obj->objectName();
    if (name.compare("unit") == 0) {
        graphicItem->setMergeType(GraphicsItemGroup::Unit);
    } else if (name.compare("intersect") == 0){
        graphicItem->setMergeType(GraphicsItemGroup::Intersect);
    } else if (name.compare("subtract") == 0){
        graphicItem->setMergeType(GraphicsItemGroup::Subtract);
    } else if (name.compare("exclude") == 0){
        graphicItem->setMergeType(GraphicsItemGroup::Exclude);
    }
}

void GroupPropertyForm::onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops,
                                         QGradient::Spread spread, const QPolygonF &points)
{
    auto brush = property.getBrush();
    brush.setStyle(brushStyle);
    brush.setGradientStops(stops);
    brush.setgradientSpread(spread);
    brush.setLocation(points);
    property.setBrush(brush);
    graphicItem->updateAttribute(&property);
}


void GroupPropertyForm::disableMergeOptions()
{
    ui->mergeOptions->hide();
    ui->unit->setChecked(false);
    ui->intersect->setChecked(false);
    ui->subtract->setChecked(false);
    ui->exclude->setChecked(false);
}
