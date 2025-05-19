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
#include "userpluginpropertyform.h"
#include "abstractzoneitem.h"
#include "ui_userpluginpropertyform.h"

UserPluginPropertyForm::UserPluginPropertyForm(QWidget *parent)
    : IPropertyForm(parent)
    , ui(new Ui::UserPluginPropertyForm)
{
    ui->setupUi(this);
    // 关联事件
    connect(ui->posProperty, SIGNAL(propertyChanged(qint32,qint32,qint32,qint32,bool)),
            this, SLOT(posChanged(qint32,qint32,qint32,qint32,bool)));
}

UserPluginPropertyForm::~UserPluginPropertyForm()
{
    delete ui;
}


void UserPluginPropertyForm::updateData()
{
    attr.copy(*graphicItem->attribute());
    QSignalBlocker posBlocker(ui->posProperty);
    auto width = attr.getWidth();
    auto height = attr.getHeight();
    auto pos = graphicItem->mapToScene(QPointF{-width/2, -height/2});
    ui->posProperty->setLeft(pos.x());
    ui->posProperty->setTop(pos.y());
    ui->posProperty->setWidth(width);
    ui->posProperty->setHeight(height);
    ui->posProperty->setAspectRatio(attr.getAspectRatio());

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

}

ICustomGraphic *UserPluginPropertyForm::getGraphicItem()
{
    return graphicItem;
}

void UserPluginPropertyForm::setGraphicItem(ICustomGraphic *graphic)
{
    auto obj = dynamic_cast<AbstractZoneItem *>(graphic);
    if (obj == nullptr) {
        return;
    }
    graphicItem = obj;

    // 初始化页面数据
    updateData();
}

void UserPluginPropertyForm::on_roundChecked_toggled(bool checked)
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

void UserPluginPropertyForm::on_roundSize_valueChanged(int arg1)
{
    if (ui->roundChecked->isChecked()) {
        attr.setArcSize(arg1);
        graphicItem->updateAttribute(&attr);
    }
}

void UserPluginPropertyForm::on_rotation_valueChanged(double arg1)
{
    attr.setRotate(arg1);
    graphicItem->updateAttribute(&attr);
}

void UserPluginPropertyForm::posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio)
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
