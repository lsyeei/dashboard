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
#include "graphicplugins.h"
#include "customplugin/usergraphicplugins.h"
#include "igraphicplugin.h"
#include "graphicplugingroup.h"
#include "predefgraphicplugins.h"
#include "qmimedata.h"
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

QPointer<UserGraphicPlugins> GraphicPlugins::userGraphics{nullptr};
QPointer<PredefGraphicPlugins> GraphicPlugins::predefGraphics{nullptr};

GraphicPlugins::GraphicPlugins(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
    QSizePolicy policy;
    policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    setSizePolicy(policy);
    setObjectName("groupCollect");
    setMinimumHeight(100);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);

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
    groupPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    auto panelLayout = new QVBoxLayout(groupPanel);
    panelLayout->setAlignment(Qt::AlignTop);
    panelLayout->setSizeConstraint(QLayout::SetMinimumSize);
    panelLayout->setContentsMargins(0,0,0,0);
    panelLayout->setSpacing(0);
    groupPanel->setLayout(panelLayout);
    // 加载控件
    loadPredefGraphicPlugin();
    // 加载用户图元控件
    loadUserGraphicPlugin();

}

GraphicPlugins::~GraphicPlugins()
{
    delete layout;
    layout = nullptr;
    selectedPlugin = nullptr;
}

bool GraphicPlugins::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteChanged();
    }
    return QWidget::event(event);
}

IGraphicPlugin *GraphicPlugins::getSelectedPlugin() const
{
    return selectedPlugin;
}

IGraphicPlugin *GraphicPlugins::getPluginById(const QString id)
{
    if (predefGraphics) {
        auto plugin = predefGraphics->getPluginById(id);
        if (plugin) {
            return plugin;
        }
    }
    return userGraphics?userGraphics->getPluginById(id):nullptr;
}

ICustomGraphic *GraphicPlugins::createGraphic(const QString &graphicId)
{
    auto plugin = getPluginById(graphicId);
    if (plugin) {
        return plugin->createItem();
    }
    return nullptr;
}

QList<IGraphicPlugin *> GraphicPlugins::getAllPlugins()
{
    QList<IGraphicPlugin *> result;
    if (predefGraphics) {
        result << predefGraphics->plugins();
    }
    if (userGraphics) {
        result << userGraphics->plugins();
    }
    return result;
}

ICustomGraphic *GraphicPlugins::createGraphic(const QString &graphicId, const QString &xmlText)
{
    auto plugin = getPluginById(graphicId);
    if (plugin) {
        return plugin->createItem(xmlText);
    }
    return nullptr;
}

void GraphicPlugins::saveToLib(QList<QGraphicsItem *> items)
{
    userGraphics->saveToLib(items);
}

void GraphicPlugins::dragEnterEvent(QDragEnterEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicPluginGroup)) {
        return;
    }
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void GraphicPlugins::dragMoveEvent(QDragMoveEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicPluginGroup)) {
        return;
    }
    if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    }
}

void GraphicPlugins::onAddNewGroup()
{
    if (userGraphics == nullptr) {
        return;
    }
    // tr("新建分组");
    auto groupName = QInputDialog::getText(this, tr("新建分组"), tr("组名"));
    if (groupName.isEmpty()) {
        return;
    }
    userGraphics->addNewGroup(groupName);
    auto bar = scroll->verticalScrollBar();
    bar->setValue(bar->maximum());
}

// QString GraphicPlugins::genItemKey(const QString &group, const QString &name)
// {
//     QCryptographicHash hash(QCryptographicHash::Md5);
//     hash.addData(group.toUtf8() + name.toUtf8());
//     return hash.result().toHex();
// }

void GraphicPlugins::loadPredefGraphicPlugin()
{
    predefGraphics = new PredefGraphicPlugins(groupPanel);
    predefGraphics->load();
    connect(predefGraphics, SIGNAL(graphicItemChanged(IGraphicPlugin*)),
            this, SIGNAL(graphicItemChanged(IGraphicPlugin*)));
}

void GraphicPlugins::loadUserGraphicPlugin()
{
    userGraphics = new UserGraphicPlugins(groupPanel);
    userGraphics->load();
    connect(userGraphics, SIGNAL(graphicItemChanged(IGraphicPlugin*)),
                        this, SIGNAL(graphicItemChanged(IGraphicPlugin*)));
}

void GraphicPlugins::paletteChanged()
{
    auto p = palette();
    auto windowColor = p.brush(QPalette::Window).color().name();
    auto windowLightColor = p.brush(QPalette::Light).color().name();
    if (predefGraphics) {
        foreach (auto item, predefGraphics->groupWidgets()){
            item->setStyleSheet("#" + item->getGroupId() + "{border:1px solid "+windowLightColor+"; background:"+windowColor+";}");
        }
    }
    if (userGraphics) {
        foreach (auto item, userGraphics->groupWidgets()){
            item->setStyleSheet("#" + item->getGroupId() + "{border:1px solid "+windowLightColor+"; background:"+windowColor+";}");
        }
    }
}
