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

#include "icustomgraphic.h"
#include "graphicplugins.h"
#include "graphicpropertyform.h"
#include "grouppropertyform.h"
#include "ui_graphicproperty.h"
#include "igraphicplugin.h"
#include "bigraphicsview.h"
#include "bigraphicsscene.h"

GraphicPropertyForm::GraphicPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphicProperty)
{
    ui->setupUi(this);

    // 组属性
    auto groupForm = new GroupPropertyForm();
    groupForm->setObjectName("group");
    ui->stackedWidget->addWidget(groupForm);
    // 图元属性
    auto plugins = GraphicPlugins::getAllPlugins();
    int index = 0;
    foreach (auto plugin, plugins) {
        auto widget = plugin->propertyWidget();
        widget->setObjectName(plugin->id());
        index = ui->stackedWidget->addWidget(widget);
        ui->stackedWidget->setCurrentIndex(index);
    }
    connect(ui->stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(stackedWidgetChanged(int)));
    // 图元名称修改
    connect(ui->graphicName, SIGNAL(editingFinished()), this, SLOT(graphicItemNameChanged()));
}

GraphicPropertyForm::~GraphicPropertyForm()
{
    delete ui;
}

void GraphicPropertyForm::graphicItemNameChanged()
{
    if (view) {
        view->modifyItemName(ui->graphicName->text().trimmed());
    }
}

void GraphicPropertyForm::stackedWidgetChanged(int index)
{
    Q_UNUSED(index)
    auto widget = ui->stackedWidget->currentWidget();
    if (widget == nullptr){
        return;
    }
    QSize size = widget->size();
    if (size.isEmpty() || size.width() < 0 || size.height() < 0){
        return;
    }
    ui->stackedWidget->resize(size);
}

void GraphicPropertyForm::setView(BIGraphicsView *newView)
{
    view = newView;
}

bool GraphicPropertyForm::setGraphicItem(QGraphicsItem *item)
{
    if (item == graphicItem) {
        return true;
    }
    graphicItem = item;
    auto group = dynamic_cast<GraphicsItemGroup *>(item);
    if (group) {
        ui->graphicName->setText(group->data(BIGraphicsScene::itemNameIndex).toString());
        QWidget *property = ui->stackedWidget->findChild<QWidget *>("group");
        if (property){
            group->setPropertyWidget(property);
            ui->stackedWidget->setCurrentWidget(property);
            return true;
        }
    } else {
        ICustomGraphic *curItem = dynamic_cast<ICustomGraphic*>(item);
        if (curItem) {
            ui->graphicName->setText(curItem->data(BIGraphicsScene::itemNameIndex).toString());
            QWidget *property = ui->stackedWidget->findChild<QWidget *>(curItem->classId());
            if (property){
                curItem->setPropertyWidget(property);
                // ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(property));
                ui->stackedWidget->setCurrentWidget(property);
                return true;
            }
        }
    }
    return false;
}

