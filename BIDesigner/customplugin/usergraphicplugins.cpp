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
#include <QLayout>
#include <configmaster.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QCoreApplication>
#include "configs.h"

UserGraphicPlugins::UserGraphicPlugins(QWidget *parent) : parentWidget(parent) {
    layout = parent->layout();
}

UserGraphicPlugins::~UserGraphicPlugins()
{
    auto widgets = groupWidgetMap.keys();
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

bool UserGraphicPlugins::load()
{
    // 读取插件组信息
    auto groupList = ConfigMaster::instance()->userPluginGroup->list();
    // 读取插件信息
    auto pluginList = ConfigMaster::instance()->userPlugin->list();
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
        auto widget = createGroupWidget(groupName);
        widget->setUserGroupId(groupId);
        groupWidgetMap[widget] = groupId;
        installPlugins(pluginInfoMaps[groupId], widget);
    }

    return true;
}

bool UserGraphicPlugins::addNewGroup(const QString &groupName)
{
    UserPluginGroupDO group;
    group.set_name(groupName);
    auto flag = ConfigMaster::instance()->userPluginGroup->save(&group);
    if (flag) {
        auto widget = createGroupWidget(groupName);
        widget->setUserGroupId(group.get_id());
        groupWidgetMap[widget] = group.get_id();
        return true;
    }
    return false;
}

QList<GraphicPluginGroup*> UserGraphicPlugins::groupWidgets()
{
    return groupWidgetMap.keys();
}

IGraphicPlugin *UserGraphicPlugins::getPluginById(const QString &pluginId) const
{
    return pluginMap[pluginId];
}

QList<IGraphicPlugin *> UserGraphicPlugins::plugins() const
{
    return pluginMap.values();
}

GraphicPluginGroup *UserGraphicPlugins::createGroupWidget(const QString &group)
{
    GraphicPluginGroup *groupWidget = new GraphicPluginGroup(group, minIdex + groupWidgetMap.count(), parentWidget);
    groupWidget->setEditable(true);
    layout->addWidget(groupWidget);
    connect(groupWidget, SIGNAL(graphicItemClicked(QString)),
            this, SLOT(onGraphicItemSelected(QString)));
    connect(groupWidget, SIGNAL(removeGroup()), this, SLOT(onRemoveGroup()));
    connect(groupWidget, SIGNAL(nameChanged(QString,QString)),
            this, SLOT(onGroupNameChanged(QString,QString)));
    connect(groupWidget, SIGNAL(importGraphic(qint32)),
            this, SLOT(onImportUserGraphics(qint32)));
    return groupWidget;
}

UserPluginType UserGraphicPlugins::suffix2Type(const QString &suffix)
{
    auto ext = suffix.toLower();
    if (ext.compare("svg") == 0){
        return UserPluginType::SVG;
    }
    return UserPluginType::IMG;
}

QByteArray UserGraphicPlugins::getThumbData(const QString &file)
{
    QSize size{48,48};
    QPixmap img(file);
    auto thumb = img.scaled(size,Qt::KeepAspectRatio);
    QByteArray array;
    QBuffer buf(&array);
    thumb.save(&buf, "png");
    return array;
}

void UserGraphicPlugins::installPlugins(QList<UserPluginDO> plugins, GraphicPluginGroup *widget)
{
    foreach (auto plugin, plugins) {
        IGraphicPlugin *graphic = new AbstractUserPlugin(widget->getGroupName(), plugin);
        auto id = graphic->id();
        if (pluginMap[id]) {
            delete graphic;
            continue;
        }
        pluginMap[id] = graphic;
        widget->addPlugin(graphic);
    }
}

void UserGraphicPlugins::onGraphicItemSelected(QString itemId)
{
    auto plugin = pluginMap[itemId];
    if (plugin)
        emit graphicItemChanged(plugin);
}

void UserGraphicPlugins::onRemoveGroup()
{
    auto obj = sender();
    auto group = dynamic_cast<GraphicPluginGroup *>(obj);
    if (group == nullptr) {
        return;
    }
    auto id = groupWidgetMap[group];
    auto flag = ConfigMaster::instance()->userPluginGroup->deleteById(id);
    if(flag){
        delete group;
        groupWidgetMap.remove(group);
    }
}

void UserGraphicPlugins::onGroupNameChanged(const QString &oldName, const QString &newName)
{
    auto obj = sender();
    auto group = dynamic_cast<GraphicPluginGroup *>(obj);
    if (group == nullptr) {
        return;
    }
    auto id = groupWidgetMap[group];
    UserPluginGroupDO data;
    data.set_id(id);
    data.set_name(newName);
    auto flag = ConfigMaster::instance()->userPluginGroup->updateById(data);
    if (!flag) {
        group->setGroupName(oldName);
    }
}

void UserGraphicPlugins::onImportUserGraphics(qint32 groupId)
{
    auto files = QFileDialog::getOpenFileNames(parentWidget, tr("导入图元"), QDir::currentPath(),
                                               "Images (*.svg *.png *.jpg *.bmp *.gif *.jpeg)");
    if (files.isEmpty()) {
        return;
    }
    // 检查用户控件路径是否存在
    auto pluginPath = QCoreApplication::applicationDirPath() + appConfigs.userPluginPath;
    QDir dir(pluginPath);
    if (!dir.exists()) {
        if(!dir.mkdir(pluginPath)){
            QMessageBox::warning(parentWidget, tr("错误"), tr("无法创建路径：") + pluginPath);
            return;
        }
    }
    // 创建控件组目录
    auto obj = sender();
    auto groupWidget = dynamic_cast<GraphicPluginGroup*>(obj);
    if (groupWidget == nullptr) {
        return;
    }
    auto groupName = groupWidget->getGroupName();
    auto groupPath = pluginPath + groupName;
    if (!dir.exists(groupPath)) {
        if(!dir.mkdir(groupPath)){
            QMessageBox::warning(parentWidget, tr("错误"), tr("无法创建路径：") + groupPath);
            return;
        }
    }
    // 拷贝文件到插件目录,生成缩略图，存到配置文件
    QFileInfo info;
    auto relativePath = appConfigs.userPluginPath + groupName + "/";
    foreach(auto file, files){
        info.setFile(file);
        auto fileName = info.fileName();
        auto suffix = info.suffix();
        if (dir.exists(groupPath + "/" + fileName)) {
            continue;
        }
        QFile::copy(file, groupPath + "/" + fileName);
        UserPluginDO plugin;
        plugin.set_groupId(groupId);
        plugin.set_name(info.baseName());
        plugin.set_path(relativePath + fileName);
        plugin.set_type(suffix2Type(suffix));
        plugin.set_thumb(getThumbData(file));
        ConfigMaster::instance()->userPlugin->save(&plugin);
    }
    // 加载新导入的图元控件
    auto plugins = ConfigMaster::instance()->userPlugin->list();
    installPlugins(plugins, groupWidget);
}
