﻿/**
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
#include "igraphicplugin.h"
#include "graphicplugingroup.h"
#include "igraphicpluginCollection.h"
#include "qmimedata.h"

#include <QCoreApplication>
#include <QCryptographicHash>
#include <QDir>
#include <QDragEnterEvent>
#include <QMessageBox>
#include <QPluginLoader>
#include <icustomgraphic.h>

QMap<QString, IGraphicPlugin *> GraphicPlugins::pluginMap = QMap<QString, IGraphicPlugin *>{};
GraphicPlugins::GraphicPlugins(QWidget *parent)
    : QWidget{parent}
{
    setAcceptDrops(true);
    QSizePolicy policy;
    policy.setVerticalPolicy(QSizePolicy::Fixed);
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    setSizePolicy(policy);
    setObjectName("groupCollect");

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setSizeConstraint(QLayout::SetDefaultConstraint);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    setLayout(layout);

    // 加载控件
    loadGraphicPlugin();
}

GraphicPlugins::~GraphicPlugins()
{
    delete layout;
    layout = nullptr;
    selectedPlugin = nullptr;
    if (!pluginMap.isEmpty()) {
        for (auto plugin : pluginMap.values()){
            delete plugin;
            plugin = nullptr;
        }
        pluginMap.clear();
    }
    if (!graphicItemGroup.isEmpty()) {
        for (auto group : graphicItemGroup.values()){
            delete group;
            group = nullptr;
        }
        graphicItemGroup.clear();
    }
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
    if (pluginMap.contains(id)) {
        return pluginMap[id];
    }
    return nullptr;
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
    if (pluginMap.isEmpty()){
        return QList<IGraphicPlugin *>();
    }
    return pluginMap.values();
}

ICustomGraphic *GraphicPlugins::createGraphic(const QString &graphicId, const QString &xmlText)
{
    auto plugin = getPluginById(graphicId);
    if (plugin) {
        return plugin->createItem(xmlText);
    }
    return nullptr;
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

void GraphicPlugins::graphicItemSelected(const QString item)
{
    // GraphicItemGroupWidget *widget = static_cast<GraphicItemGroupWidget *>(sender());
    // QString id = genItemKey(widget->getGroupName(), itemName);
    if (!pluginMap.contains(item)) {
        return;
    }
    selectedPlugin = pluginMap[item];
    emit graphicItemChanged(pluginMap[item]);
}

// QString GraphicPlugins::genItemKey(const QString &group, const QString &name)
// {
//     QCryptographicHash hash(QCryptographicHash::Md5);
//     hash.addData(group.toUtf8() + name.toUtf8());
//     return hash.result().toHex();
// }

void GraphicPlugins::loadGraphicPlugin()
{
    QDir pluginsDir(QCoreApplication::applicationDirPath());
    pluginsDir.setNameFilters({"*.dll", "*.so"});
#if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
        pluginsDir.cdUp();
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif
    if (!pluginsDir.cd("plugins")){
        QMessageBox::information(this, tr("提示"), tr("未找到插件目录"));
        return;
    }
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        if (!pluginLoader.load()){
            qDebug() << "库加载失败：" << fileName << "; 错误提示：" << pluginLoader.errorString();
            continue;
        }
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            auto *pluginCollection = qobject_cast<IGraphicPluginCollection *>(plugin);
            if (pluginCollection){
                auto pluginList = pluginCollection->graphicPlugins();
                foreach (auto plugin, pluginList) {
                    installPlugin(plugin);
                }
            }else{
                IGraphicPlugin *graphicPlugin = qobject_cast<IGraphicPlugin *>(plugin);
                if (graphicPlugin == nullptr){
                    pluginLoader.unload();
                } else {
                    installPlugin(graphicPlugin);
                }
            }
        }
    }
}

void GraphicPlugins::installPlugin(IGraphicPlugin *graphicItem)
{
    QString group = graphicItem->group();
    // 如果该组已存在，加入该组，否则新建一组并加入
    if (!graphicItemGroup.contains(group)){
        createGroupWidget(group);
    }
    // 将图元加入控件组
    if (graphicItemGroup[group]->addPlugin(graphicItem)) {
        QString id = graphicItem->id();
        pluginMap[id] = graphicItem;
    }
}


void GraphicPlugins::createGroupWidget(QString group)
{
    GraphicPluginGroup *groupWidget = new GraphicPluginGroup(group, graphicItemGroup.count(), this);
    layout->addWidget(groupWidget);
    graphicItemGroup[group] = groupWidget;
    connect(groupWidget, SIGNAL(graphicItemClicked(QString)),
            this, SLOT(graphicItemSelected(QString)));
}

void GraphicPlugins::paletteChanged()
{
    auto p = palette();
    auto windowColor = p.brush(QPalette::Window).color().name();
    auto windowLightColor = p.brush(QPalette::Light).color().name();
    foreach (auto item, graphicItemGroup){
        item->setStyleSheet("#" + item->getGroupId() + "{border:1px solid "+windowLightColor+"; background:"+windowColor+";}");
    }
}
