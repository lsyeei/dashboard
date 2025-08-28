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
#include "abstractlineitem.h"
#include "endtypefactory.h"
#include "ui_linepropertyform.h"

LinePropertyForm::LinePropertyForm(QWidget *parent)
    : IPropertyForm(parent)
    , ui(new Ui::LinePropertyForm)
{
    ui->setupUi(this);
    initUI();
    initEvent();
}

LinePropertyForm::~LinePropertyForm()
{
    delete ui;
}


void LinePropertyForm::updateData()
{
    attr.copy(*graphicItem->attribute());
    auto pen = attr.getPen();
    QSignalBlocker posXBlocker(ui->centerX);
    QSignalBlocker posYBlocker(ui->centerY);
    ui->centerX->setValue(attr.getPos().x());
    ui->centerY->setValue(attr.getPos().y());
    QSignalBlocker penBlocker(ui->linePen);
    ui->linePen->setLineColor(pen.getColor());
    ui->linePen->setLineStyle(pen.getStyle());
    ui->linePen->setLineWidth(pen.getWidth());
    auto start = attr.getStart();
    ui->startTypeOptions->blockSignals(true);
    if (start.isEmpty()) {
        ui->startTypeOptions->setCurrentIndex(-1);
    }else{
        auto index = ui->startTypeOptions->findData(start.getTypeId());
        ui->startTypeOptions->setCurrentIndex(index);
    }
    ui->startTypeOptions->blockSignals(false);
    ui->startSize->blockSignals(true);
    ui->startSize->setValue(start.getSize());
    ui->startSize->blockSignals(false);
    auto end = attr.getEnd();
    ui->endTypeOptions->blockSignals(true);
    if (end.isEmpty()) {
        ui->endTypeOptions->setCurrentIndex(-1);
    }else{
        auto index = ui->endTypeOptions->findData(end.getTypeId());
        ui->endTypeOptions->setCurrentIndex(index);
    }
    ui->endTypeOptions->blockSignals(false);
    ui->endSize->blockSignals(true);
    ui->endSize->setValue(end.getSize());
    ui->endSize->blockSignals(false);
    ui->flowAnimation->blockSignals(true);
    ui->flowAnimation->setChecked(attr.getFlowAnimation());
    ui->flowAnimation->blockSignals(false);
    ui->backward->blockSignals(true);
    ui->backward->setChecked(attr.getBackward());
    ui->backward->blockSignals(false);
    ui->duration->blockSignals(true);
    ui->duration->setValue(attr.getDuration());
    ui->duration->blockSignals(false);
    ui->dashLen->blockSignals(true);
    ui->dashLen->setValue(attr.getDashLen());
    ui->dashLen->blockSignals(false);
    ui->dashRatio->blockSignals(true);
    ui->dashRatio->setValue(attr.getDashRatio());
    ui->dashRatio->blockSignals(false);
    if (attr.getFlowAnimation()) {
        ui->animationParam->show();
    } else {
        ui->animationParam->hide();
    }

    QMap<int, QString> stateSet = graphicItem->getAttributes();
    auto index = -1;
    auto state = graphicItem->state();
    ui->stateBox->blockSignals(true);
    ui->stateBox->clear();
    if (!stateSet.empty()){
        int j = -1;
        for (auto i = stateSet.begin(), end = stateSet.end(); i != end; i++) {
            ui->stateBox->addItem(i.value(), i.key());
            j++;
            if (state == i.key()) {
                index  = j;
            }
        }
        if (index == -1 || index >= stateSet.count()) {
            index = 0;
        }
        ui->stateBox->setCurrentItem(index);
    }
    ui->stateBox->blockSignals(false);
}

ICustomGraphic *LinePropertyForm::getGraphicItem()
{
    return graphicItem;
}

void LinePropertyForm::setGraphicItem(ICustomGraphic *graphic)
{
    auto obj = dynamic_cast<AbstractLineItem *>(graphic);
    if (obj == nullptr) {
        return;
    }
    graphicItem = obj;
    // 初始化页面数据
    updateData();
}

void LinePropertyForm::showCornerProperty()
{
    ui->corner->show();
    connect(ui->roundCorner, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onRoundCornerClicked()));
    connect(ui->cornerSzie, SIGNAL(valueChanged(int)), this, SLOT(onCornerSizeChanged()));
}

void LinePropertyForm::onLinePenChanged(Qt::PenStyle style, const QColor &color, int width)
{
    auto pen = attr.getPen();
    pen.setStyle(style);
    pen.setColor(color);
    pen.setWidth(width);
    attr.setPen(pen);
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onStartTypeChanged(int index)
{
    Q_UNUSED(index)
    auto start = attr.getStart();
    start.setTypeId(ui->startTypeOptions->currentData().toString());
    attr.setStart(start);
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onStartSizeChanged(int value)
{
    auto start = attr.getStart();
    start.setSize(value);
    attr.setStart(start);
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onEndTypeChanged(int index)
{
    Q_UNUSED(index)
    auto end = attr.getEnd();
    end.setTypeId(ui->endTypeOptions->currentData().toString());
    attr.setEnd(end);
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onEndSizeChanged(int value)
{
    auto end = attr.getEnd();
    end.setSize(value);
    attr.setEnd(end);
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onFlowAnimationClicked()
{
    attr.setFlowAnimation(ui->flowAnimation->isChecked());
    graphicItem->updateAttribute(&attr);
    if (ui->flowAnimation->isChecked()){
        ui->animationParam->show();
    }else{
        ui->animationParam->hide();
    }
}

void LinePropertyForm::onRoundCornerClicked()
{
    if(ui->roundCorner->isChecked()){
        ui->cornerSzie->setDisabled(false);
    }else{
        ui->cornerSzie->setDisabled(true);
    }
    attr.setRounded(ui->roundCorner->isChecked());
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onCornerSizeChanged()
{
    attr.setArcSize(ui->cornerSzie->value());
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::onFlowAnimationChanged()
{
    attr.setDuration(ui->duration->value());
    attr.setBackward(ui->backward->isChecked());
    attr.setDashLen(ui->dashLen->value());
    attr.setDashRatio(ui->dashRatio->value());
    graphicItem->updateAttribute(&attr);
}

void LinePropertyForm::initUI()
{
    layout()->setAlignment(Qt::AlignTop);
    ui->linePen->setAlwaysShow(true);
    ui->cornerSzie->setDisabled(true);
    ui->roundCorner->setChecked(false);
    ui->corner->hide();
    ui->startTypeOptions->clear();
    ui->endTypeOptions->clear();
    ui->flowAnimation->setChecked(false);
    ui->animationParam->hide();
    // 初始化线端箭头
    initArrowType();
}

void LinePropertyForm::initEvent()
{
    connect(ui->linePen, SIGNAL(propertyChanged(Qt::PenStyle,QColor,int)), this, SLOT(onLinePenChanged(Qt::PenStyle,QColor,int)));
    connect(ui->startTypeOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(onStartTypeChanged(int)));
    connect(ui->startSize, SIGNAL(valueChanged(int)), this, SLOT(onStartSizeChanged(int)));
    connect(ui->endTypeOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(onEndTypeChanged(int)));
    connect(ui->endSize, SIGNAL(valueChanged(int)), this, SLOT(onEndSizeChanged(int)));
    connect(ui->flowAnimation, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onFlowAnimationClicked()));
    connect(ui->duration, SIGNAL(valueChanged(int)), this, SLOT(onFlowAnimationChanged()));
    connect(ui->backward, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onFlowAnimationChanged()));
    connect(ui->dashLen, SIGNAL(valueChanged(int)), this, SLOT(onFlowAnimationChanged()));
    connect(ui->dashRatio, SIGNAL(valueChanged(double)), this, SLOT(onFlowAnimationChanged()));
    connect(ui->stateBox, SIGNAL(itemAdded(int)), this, SLOT(onStateAdded(int)));
    connect(ui->stateBox, SIGNAL(itemModified(int)), this, SLOT(onStateModified(int)));
    connect(ui->stateBox, SIGNAL(itemRemoved(QString, QVariant)), this, SLOT(onStateRemoved(QString,QVariant)));
    connect(ui->stateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onStateIndexChanged(int)));
    connect(ui->centerX, SIGNAL(valueChanged(int)), this, SLOT(onPosChanged(int)));
    connect(ui->centerY, SIGNAL(valueChanged(int)), this, SLOT(onPosChanged(int)));
}

void LinePropertyForm::initArrowType()
{
    if (ui->startTypeOptions->count() <= 0) {
        auto startType = EndTypeFactory::instance()->getEndTypeList(LineEndType::Start);
        ui->startTypeOptions->addItem("", "");
        for(auto type=startType.begin(); type!=startType.end(); type++){
            ui->startTypeOptions->addItem(type.value(), "", type.key());
        }
    }
    if (ui->endTypeOptions->count() <= 0) {
        auto endType = EndTypeFactory::instance()->getEndTypeList(LineEndType::End);
        ui->endTypeOptions->addItem("", "");
        for(auto type=endType.begin(); type!=endType.end(); type++){
            ui->endTypeOptions->addItem(type.value(), "", type.key());
        }
    }
}

void LinePropertyForm::onStateAdded(int index)
{
    auto name = ui->stateBox->itemText(index);
    int id = graphicItem->addAttribute(name);
    ui->stateBox->getComboBox()->setItemData(index, id);
}

void LinePropertyForm::onStateModified(int index)
{
    auto name = ui->stateBox->itemText(index);
    auto id = ui->stateBox->itemData(index);
    graphicItem->modifyAttribute(id.toInt(), name);
}


void LinePropertyForm::onStateRemoved(const QString &name, const QVariant &data)
{
    Q_UNUSED(name)
    graphicItem->removeAttribute(data.toInt());
}


void LinePropertyForm::onStateIndexChanged(int index)
{
    auto id = ui->stateBox->itemData(index);
    graphicItem->changeAttribute(id.toInt());
}

void LinePropertyForm::onPosChanged(int value)
{
    Q_UNUSED(value)
    auto obj = sender();
    auto pos = attr.getPos();
    if (obj == ui->centerX) {
        pos.setX(ui->centerX->value());
    }
    if (obj == ui->centerY) {
        pos.setY(ui->centerY->value());
    }
    attr.setPos(pos);
    graphicItem->updateAttribute(&attr);
}
