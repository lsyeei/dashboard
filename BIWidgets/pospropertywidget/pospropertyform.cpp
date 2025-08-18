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

#include "pospropertyform.h"
#include "ui_pospropertyform.h"

PosPropertyForm::PosPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PosPropertyForm)
{
    ui->setupUi(this);
    ui->aspectRatioChecked->setDisabled(true);
}

PosPropertyForm::~PosPropertyForm()
{
    delete ui;
}

qint32 PosPropertyForm::getLeft() const
{
    return left;
}

void PosPropertyForm::setLeft(qint32 newLeft)
{
    left = newLeft;
    ui->leftValue->blockSignals(true);
    ui->leftValue->setValue(left);
    ui->leftValue->blockSignals(false);
}

qint32 PosPropertyForm::getTop() const
{
    return top;
}

void PosPropertyForm::setTop(qint32 newTop)
{
    top = newTop;
    ui->topValue->blockSignals(true);
    ui->topValue->setValue(top);
    ui->topValue->blockSignals(false);
}

qint32 PosPropertyForm::getWidth() const
{
    return width;
}

void PosPropertyForm::enbaleAspectRatio()
{
    if (width <= 0 || height <= 0){
        return;
    }
    if (ui->aspectRatioChecked->isEnabled()){
        return;
    }
    ui->aspectRatioChecked->setDisabled(false);
}

void PosPropertyForm::initRatio()
{
    if (!aspectRatio) {
        return;
    }
    if (ratio > 0) {
        return;
    }
    if (width <= 0 || height <= 0) {
        return;
    }
    ratio = width * 1.0 / height;
}

void PosPropertyForm::widthChanged()
{
    if (aspectRatio && ratio > 0){
        height = qRound(width / ratio);
        ui->heightValue->blockSignals(true);
        ui->heightValue->setValue(height);
        ui->heightValue->blockSignals(false);
    }
    enbaleAspectRatio();
}

void PosPropertyForm::setWidth(qint32 newWidth)
{
    width = newWidth;
    initRatio();
    ui->widthValue->blockSignals(true);
    ui->widthValue->setValue(width);
    ui->widthValue->blockSignals(false);
    widthChanged();
}

qint32 PosPropertyForm::getHeight() const
{
    return height;
}

void PosPropertyForm::heightChanged()
{
    if (aspectRatio && ratio > 0){
        width = qRound(height * ratio);
        ui->widthValue->blockSignals(true);
        ui->widthValue->setValue(width);
        ui->widthValue->blockSignals(false);
    }
    enbaleAspectRatio();
}

void PosPropertyForm::setHeight(qint32 newHeight)
{
    height = newHeight;
    initRatio();
    ui->heightValue->blockSignals(true);
    ui->heightValue->setValue(height);
    ui->heightValue->blockSignals(false);
    heightChanged();
}

bool PosPropertyForm::getAspectRatio() const
{
    return aspectRatio;
}

void PosPropertyForm::aspectRatioChanged()
{
    if (aspectRatio && height > 0){
        ratio = width * 1.0 / height;
    }
}

void PosPropertyForm::setAspectRatio(bool newAspectRatio)
{
    aspectRatio = newAspectRatio;
    ui->aspectRatioChecked->blockSignals(true);
    ui->aspectRatioChecked->setChecked(aspectRatio);
    ui->aspectRatioChecked->blockSignals(false);
    aspectRatioChanged();
}

void PosPropertyForm::on_leftValue_valueChanged(int arg1)
{
    left = arg1;
    emit valueChanged();
}


void PosPropertyForm::on_topValue_valueChanged(int arg1)
{
    top = arg1;
    emit valueChanged();
}


void PosPropertyForm::on_widthValue_valueChanged(int arg1)
{
    width = arg1;
    widthChanged();
    emit valueChanged();
}


void PosPropertyForm::on_heightValue_valueChanged(int arg1)
{
    height = arg1;
    heightChanged();
    emit valueChanged();
}


void PosPropertyForm::on_aspectRatioChecked_toggled(bool checked)
{
    aspectRatio = checked;
    aspectRatioChanged();
    emit valueChanged();
}

