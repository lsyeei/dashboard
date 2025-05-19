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
#include "predefgraphicplugins.h"
#include "graphicplugingroup.h"
#include "igraphicplugin.h"
#include "igraphicpluginCollection.h"
#include "qlayout.h"
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QPluginLoader>
#include <QWidget>

PredefGraphicPlugins::PredefGraphicPlugins(QWidget *parent) : parentWidget(parent){
    layout = parent->layout();
}

PredefGraphicPlugins::~PredefGraphicPlugins()
{
    auto widgets = groupWidgetMap.values();
    foreach (auto item, widgets) {
        delete item;
    }
    groupWidgetMap.clear();
    auto plugins = pluginMap.values();
    foreach (auto item, plugins) {
        delete item;
    }
    pluginMap.clear();
}

bool PredefGraphicPlugins::load()
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
        QMessageBox::information(parentWidget, tr("提示"), tr("未找到插件目录"));
        return false;
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
    return true;
}

QList<GraphicPluginGroup *> PredefGraphicPlugins::groupWidgets()
{
    return groupWidgetMap.values();
}

IGraphicPlugin *PredefGraphicPlugins::getPluginById(const QString &pluginId) const
{
    return pluginMap[pluginId];
}

QList<IGraphicPlugin *> PredefGraphicPlugins::plugins() const
{
    return pluginMap.values();
}

void PredefGraphicPlugins::onGraphicItemSelected(QString itemId)
{
    auto plugin = pluginMap[itemId];
    if (plugin)
        emit graphicItemChanged(plugin);
}

void PredefGraphicPlugins::installPlugin(IGraphicPlugin *graphicItem)
{
    QString groupName = graphicItem->group();
    GraphicPluginGroup *groupWidget{nullptr};
    // 如果该组已存在，加入该组，否则新建一组并加入
    foreach (auto widget, groupWidgetMap) {
        if (widget->getGroupName().compare(groupName) == 0) {
            groupWidget = widget;
        }
    }
    if (groupWidget == nullptr){
        groupWidget = createGroupWidget(groupName);
    }
    // 将图元加入控件组
    if (groupWidget->addPlugin(graphicItem)) {
        QString id = graphicItem->id();
        pluginMap[id] = graphicItem;
    }
}

GraphicPluginGroup *PredefGraphicPlugins::createGroupWidget(QString group)
{
    GraphicPluginGroup *groupWidget = new GraphicPluginGroup(group, groupWidgetMap.count(), parentWidget);
    layout->addWidget(groupWidget);
    groupWidgetMap[groupWidget->getGroupId()] = groupWidget;
    connect(groupWidget, SIGNAL(graphicItemClicked(QString)),
            this, SLOT(onGraphicItemSelected(QString)));

    return groupWidget;
}
