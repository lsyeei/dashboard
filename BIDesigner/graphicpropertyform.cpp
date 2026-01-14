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
#include "graphicrootwidget.h"
#include "graphicpropertyform.h"
#include "grouppropertyform.h"
#include "ui_graphicproperty.h"
#include "igraphicplugin.h"
#include "bigraphicsview.h"
#include "bigraphicsscene.h"
#include <QResizeEvent>

GraphicPropertyForm::GraphicPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GraphicProperty)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);
    // 组属性
    auto groupForm = new GroupPropertyForm();
    groupForm->setObjectName("group");
    widgets["group"] = groupForm;

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

void GraphicPropertyForm::setView(BIGraphicsView *newView)
{
    view = newView;
}

void GraphicPropertyForm::onGraphicPluginLoaded(QList<GraphicGroup *> groups)
{
    // 一次创建所有插件的属性窗口，导致启动慢，可以延迟到使用时再创建
    // // 加载图元属性控件
    // foreach(auto group, groups){
    //     foreach(auto graphic, group->list){
    //         auto widget = graphic->propertyWidget();
    //         widget->setObjectName(graphic->id());
    //         widgets[graphic->id()] = widget;
    //     }
    // }
}

QWidget *GraphicPropertyForm::findOrCreateForm(const QString &graphicId)
{
    QWidget *form = widgets[graphicId];
    if (form) {
        return form;
    }
    auto graphicPlugin = GraphicsManager::instance()->getPluginById(graphicId);
    if (graphicPlugin == nullptr) {
        return nullptr;
    }
    form = graphicPlugin->propertyWidget();
    form->setObjectName(graphicId);
    widgets[graphicId] = form;
    return form;
}

bool GraphicPropertyForm::setGraphicItem(QGraphicsItem *item)
{
    if (item == graphicItem) {
        return true;
    }
    auto biScene = dynamic_cast<BIGraphicsScene*>(item->scene());
    auto itemName = biScene->itemName(item);
    graphicItem = item;
    auto group = dynamic_cast<GraphicsItemGroup *>(item);

    if (current) {
        current->hide();
        layout() ->removeWidget(current);
    }
    if (group) {
        ui->graphicName->setText(itemName);
        QWidget *property = widgets["group"];
        if (property){
            group->setPropertyWidget(property);
            layout()->addWidget(property);
            property->show();
            current = property;
            return true;
        }
    } else {
        ICustomGraphic *curItem = dynamic_cast<ICustomGraphic*>(item);
        if (curItem) {
            ui->graphicName->setText(itemName);
            QWidget *property = findOrCreateForm(curItem->classId());
            if (property){
                curItem->setPropertyWidget(property);
                layout()->addWidget(property);
                property->show();
                current = property;
                return true;
            }
        }
    }
    return false;
}
