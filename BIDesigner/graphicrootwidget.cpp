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

#include <QVBoxLayout>
#include "graphicrootwidget.h"
#include "customgraphic/userplugingroupdialog.h"
#include "customgraphic/userplugingroupdo.h"
#include "igraphicplugin.h"
#include "graphicgroupwidget.h"
#include "qmimedata.h"
#include "configmaster.h"
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QDragEnterEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QPluginLoader>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <icustomgraphic.h>

GraphicRootWidget::GraphicRootWidget(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    setObjectName("groupCollect");
    setMinimumHeight(100);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);

    addGroupBtn = new QPushButton(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew),
                            tr("新建图库"));
    layout->addWidget(addGroupBtn);
    connect(addGroupBtn.data(), SIGNAL(clicked(bool)), this, SLOT(onAddNewGroup()));

    scroll = new QScrollArea(this);
    layout->addWidget(scroll);
    scroll->setAlignment(Qt::AlignTop);
    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    groupPanel = new QWidget(scroll);
    scroll->setWidget(groupPanel);
    groupPanel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    auto panelLayout = new QVBoxLayout(groupPanel);
    panelLayout->setAlignment(Qt::AlignTop);
    panelLayout->setSizeConstraint(QLayout::SetMinimumSize);
    panelLayout->setContentsMargins(0,0,0,0);
    panelLayout->setSpacing(0);

    auto manager = GraphicsManager::instance();
    connect(manager, SIGNAL(groupRemovedEvent(int)), this, SLOT(onRemoveGroup(int)));
}

GraphicRootWidget::~GraphicRootWidget()
{
    delete layout;
    layout = nullptr;
    selectedPlugin = nullptr;
}

bool GraphicRootWidget::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteChanged();
    }
    return QWidget::event(event);
}

IGraphicPlugin *GraphicRootWidget::getSelectedPlugin() const
{
    return selectedPlugin;
}

void GraphicRootWidget::createGraphicGroup(const GraphicGroup &group)
{
    // 创建组控件
    GraphicGroupWidget *groupWidget = createGroupWidget(group.groupId, group.groupName, group.type);
    // 创建图元控件
    foreach(auto graphic, group.list){
        // 将图元加入控件组
        groupWidget->addPlugin(graphic);
    }
}

int GraphicRootWidget::selectGroup()
{
    auto dlg = new UserPluginGroupDialog(this);
    connect(dlg, &UserPluginGroupDialog::addNewGroup,
            this, [&](const QString name){addNewGroup(name);});
    dlg->exec();
    auto id = dlg->getGroupId();
    delete dlg;
    return id;
}

void GraphicRootWidget::addGraphic(int groupId, IGraphicPlugin *graphic)
{
    auto groupWidget = groupWidgetMap[groupId];
    if (groupWidget) {
        groupWidget->addPlugin(graphic);
    }
}

void GraphicRootWidget::dragEnterEvent(QDragEnterEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicGroupWidget)) {
        return;
    }
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void GraphicRootWidget::dragMoveEvent(QDragMoveEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicGroupWidget)) {
        return;
    }
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void GraphicRootWidget::onGraphicPluginLoaded(QList<GraphicGroup*> groups)
{
    auto obj = sender();
    disconnect(obj, SIGNAL(loadEndEvent(QList<GraphicGroup*>)), this, nullptr);
    foreach(auto group, groups){
        createGraphicGroup(*group);
    }
}

void GraphicRootWidget::onGraphicItemSelected(QString itemId)
{
    auto plugin = GraphicsManager::instance()->getPluginById(itemId);
    if (plugin)
        emit graphicItemChanged(plugin);
}

void GraphicRootWidget::onAddNewGroup()
{
    auto groupName = QInputDialog::getText(this, tr("新建分组"), tr("组名"));
    if (groupName.isEmpty()) {
        return;
    }
    addNewGroup(groupName);
    auto bar = scroll->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void GraphicRootWidget::onRemoveGroup(int groupId)
{
    // 找到并移除控件
    auto groupWidget = groupWidgetMap[groupId];
    if (groupWidget == nullptr) {
        return;
    }
    delete groupWidget;
    groupWidgetMap.remove(groupId);
}

void GraphicRootWidget::paletteChanged()
{
    auto p = palette();
    auto windowColor = p.brush(QPalette::Window).color().name();
    auto windowLightColor = p.brush(QPalette::Light).color().name();
    for(const auto &[id, widget]:groupWidgetMap.asKeyValueRange()){
        widget->setStyleSheet("#" + widget->objectName() + "{border:1px solid "+windowLightColor+"; background:"+windowColor+";}");
    }
}

GraphicGroupWidget *GraphicRootWidget::createGroupWidget(int groupId, const QString &groupName, GraphicType type)
{
    // 创建组控件
    GraphicGroupWidget *groupWidget = new GraphicGroupWidget(groupName, groupWidgetMap.count(), groupPanel);
    groupPanel->layout()->addWidget(groupWidget);
    groupWidgetMap[groupId] = groupWidget;
    connect(groupWidget, SIGNAL(graphicItemClicked(QString)),
            this, SLOT(onGraphicItemSelected(QString)));
    if (type == GraphicType::USER) {
        groupWidget->setUserGroupId(groupId);
        groupWidget->setEditable(true);
    }
    return groupWidget;
}

bool GraphicRootWidget::addNewGroup(const QString &groupName)
{
    UserPluginGroupDO group;
    group.set_name(groupName);
    auto flag = ConfigMaster::instance()->userPluginGroup->save(&group);
    if (flag) {
        auto groupId = group.get_id();
        GraphicsManager::instance()->addGroup(groupId, groupName);
        auto widget = createGroupWidget(groupId, groupName, GraphicType::USER);
        widget->setUserGroupId(groupId);
        return true;
    }
    return false;
}
