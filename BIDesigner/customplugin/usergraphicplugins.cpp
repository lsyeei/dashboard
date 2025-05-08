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
#include "usergraphicplugins.h"
#include "customplugin/abstractuserplugin.h"
#include "customplugin/userplugindo.h"
#include "customplugin/userplugingroupdo.h"
#include "graphicplugingroup.h"

#include <QIcon>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <configs.h>
#include <QLayout>

#include "dbutil/basemapper.h"

QMap<QString, GraphicPluginGroup *> UserGraphicPlugins::groupWidgetMap = QMap<QString, GraphicPluginGroup *>();

UserGraphicPlugins::UserGraphicPlugins(QWidget *parent) : parent(parent) {}

QMap<QString, GraphicPluginGroup *> UserGraphicPlugins::load()
{
    QMap<QString, GraphicPluginGroup *> widgets;
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(appConfigs.dbName);
    if(!db.isValid()){
        return widgets;
    }
    if (!db.open(appConfigs.dbUser, appConfigs.dbPwd)){
        qWarning() << "配置文件:" << appConfigs.dbName << "打开失败！";
        return widgets;
    }
    // 读取插件组信息
    BaseMapper<UserPluginGroupDO> groupMapper(&db);
    auto groupList = groupMapper.selectList();
    // 读取插件信息
    BaseMapper<UserPluginDO> pluginMapper(&db);
    auto pluginList = pluginMapper.selectList();
    QMap<int, QList<UserPluginDO>> pluginInfoMaps = [=](){
        QMap<int, QList<UserPluginDO>> result;
        foreach (auto item, pluginList) {
            result[item.get_groupId()] << item;
        }
        return result;
    }();
    // 按组创建
    foreach (auto group, groupList) {
        auto groupId = group.get_id();
        auto groupName = group.get_name();
        createGroupWidget(groupName);
        auto widget = groupWidgetMap[groupName];
        auto plugins = pluginInfoMaps[groupId];
        foreach (auto plugin, plugins) {
            IGraphicPlugin *graphic = new AbstractUserPlugin(groupName, plugin);
            pluginMap[graphic->id()] = graphic;
            widget->addPlugin(graphic);
        }
    }

    db.close();
    return widgets;
}

void UserGraphicPlugins::createGroupWidget(QString group)
{
    GraphicPluginGroup *groupWidget = new GraphicPluginGroup(group, minIdex + groupWidgetMap.count(), parent);
    layout->addWidget(groupWidget);
    groupWidgetMap[group] = groupWidget;
    connect(groupWidget, SIGNAL(graphicItemClicked(QString)),
            this, SLOT(graphicItemSelected(QString)));
}

void UserGraphicPlugins::graphicItemSelected(QString itemId)
{
    auto plugin = pluginMap[itemId];
    if (plugin)
        emit graphicItemChanged(plugin);
}
