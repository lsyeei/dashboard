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
#include "bigraphicsscene.h"
#include "customplugin/abstractuserplugin.h"
#include "customplugin/userplugindo.h"
#include "customplugin/userplugingroupdo.h"
#include "customplugin/userpluginmanageform.h"
#include "graphicplugingroup.h"
#include <QIcon>
#include <QLayout>
#include <configmaster.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QCoreApplication>
#include <QGraphicsItem>
#include <QPainter>
#include "configs.h"
#include "graphicsitemgroup.h"
#include "icustomgraphic.h"
#include "userplugingroupdialog.h"

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

bool UserGraphicPlugins::reloadGroup(qint32 groupId)
{
    GraphicPluginGroup *groupWidget = getGroupWidget(groupId);
    if (groupWidget == nullptr) {
        return false;
    }
    // 清空原有控件
    groupWidget->clearGroup();
    // 重新加载控件
    auto plugins = ConfigMaster::instance()->userPlugin->list(QString("group_id=").arg(groupId));
    installPlugins(plugins, groupWidget);
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

void UserGraphicPlugins::saveToLib(QList<QGraphicsItem *> items)
{
    auto dlg = new UserPluginGroupDialog(parentWidget);
    connect(dlg, &UserPluginGroupDialog::addNewGroup,
            this, [&](const QString name){addNewGroup(name);});
    dlg->exec();
    auto id = dlg->getGroupId();
    delete dlg;
    if (id < 0) {
        return;
    }
    // 生成插件信息
    QList<UserPluginDO> plugins;
    foreach (auto item, items) {
        plugins << savePlugin(id, item);
    }
    // 安装插件
    installPlugins(plugins, getGroupWidget(id));
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
    connect(groupWidget, SIGNAL(manageGraphic(qint32)),
            this, SLOT(onManageUserGraphics(qint32)));
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

GraphicPluginGroup *UserGraphicPlugins::getGroupWidget(qint32 groupId)
{
    GraphicPluginGroup *groupWidget{nullptr};
    for (auto item = groupWidgetMap.begin(); item != groupWidgetMap.end(); item++) {
        if (item.value() == groupId) {
            groupWidget = item.key();
            break;
        }
    }
    return groupWidget;
}

UserPluginDO UserGraphicPlugins::savePlugin(int groupId, QGraphicsItem *item)
{
    auto graphic = dynamic_cast<ICustomGraphic*>(item);
    auto biScene = dynamic_cast<BIGraphicsScene*>(item->scene());
    auto data = "<User>" + biScene->toXml({item}) + "</User>";
    auto pluginPath = getPluginPath(groupId);
    auto name = biScene->itemName(item);
    // 存入文件
    auto fileName = name + ".g";
    QDir dir(QCoreApplication::applicationDirPath() + pluginPath);
    if (dir.exists(dir.absoluteFilePath(fileName))) {
        name += QString("-%1").arg(QDateTime::currentSecsSinceEpoch());
        fileName = name + ".g";
    }
    QFile file(dir.absoluteFilePath(fileName));
    file.open(QIODeviceBase::WriteOnly);
    file.write(data.toLocal8Bit());
    file.close();
    // 获取缩略图
    auto thumb = graphicsItemThumb(graphic);
    // 存入数据库
    QString path = pluginPath + fileName;
    UserPluginType type{UserPluginType::GROUP};
    if (typeid(*item) != typeid(GraphicsItemGroup)) {
        type = UserPluginType::SYSTEM;
    }

    UserPluginDO plugin;
    plugin.set_groupId(groupId);
    plugin.set_name(name);
    plugin.set_thumb(thumb);
    plugin.set_path(path);
    plugin.set_type(type);
    if(!ConfigMaster::instance()->userPlugin->save(&plugin)){
        file.remove();
    }
    return plugin;
}

QByteArray UserGraphicPlugins::graphicsItemThumb(ICustomGraphic *item)
{
    QSize size{48,48};
    QImage image{size, QImage::Format_ARGB32};
    image.fill(Qt::transparent);
    QPainter painter{&image};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRectF rect{{0,0},size};
    QRectF itemRect = item->sceneBoundingRect();
    auto ratio = itemRect.width() / itemRect.height();
    if (ratio > 1){
        auto imgHeight = size.width()/ratio;
        rect = {0, (size.height() - imgHeight)/2, 1.0*size.width(), imgHeight};
    } else {
        auto imgWidth = size.height()*ratio;
        rect = {(size.width()-imgWidth)/2, 0, imgWidth, 1.0*size.height()};
    }

    BIGraphicsScene tempScene;
    auto data = "<User>" + tempScene.toXml({item}) + "</User>";
    tempScene.setSceneRect(0,0,itemRect.width(),itemRect.height());
    auto items = tempScene.toItems(data);
    tempScene.addItems(items);
    tempScene.render(&painter, rect, itemRect);

    QByteArray array;
    QBuffer buf(&array);
    image.save(&buf, "png");
    return array;
}

QString UserGraphicPlugins::getPluginPath(qint32 groupId)
{
    // 检查用户控件路径是否存在
    auto pluginPath = QCoreApplication::applicationDirPath() + appConfigs.userPluginPath;
    QDir dir(pluginPath);
    if (!dir.exists()) {
        if(!dir.mkdir(pluginPath)){
            QMessageBox::warning(parentWidget, tr("错误"), tr("无法创建路径：") + pluginPath);
            return "";
        }
    }
    // 创建控件组目录
    auto groupWidget = getGroupWidget(groupId);
    if (groupWidget == nullptr) {
        return "";
    }
    auto groupName = groupWidget->getGroupName();
    auto groupPath = pluginPath + groupName;
    if (!dir.exists(groupPath)) {
        if(!dir.mkdir(groupPath)){
            QMessageBox::warning(parentWidget, tr("错误"), tr("无法创建路径：") + groupPath);
            return "";
        }
    }
    return appConfigs.userPluginPath + groupName + "/";
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
    auto pluginPath = getPluginPath(groupId);
    if (pluginPath.isEmpty()){
        return;
    }
    QDir dir(QCoreApplication::applicationDirPath() + pluginPath);
    // 拷贝文件到插件目录,生成缩略图，存到配置文件
    QFileInfo info;
    foreach(auto file, files){
        info.setFile(file);
        auto fileName = info.fileName();
        auto suffix = info.suffix();
        if (dir.exists(dir.absoluteFilePath(fileName))) {
            continue;
        }
        QFile::copy(file, dir.absoluteFilePath(fileName));
        UserPluginDO plugin;
        plugin.set_groupId(groupId);
        plugin.set_name(info.baseName());
        plugin.set_path(pluginPath + fileName);
        plugin.set_type(suffix2Type(suffix));
        plugin.set_thumb(getThumbData(file));
        ConfigMaster::instance()->userPlugin->save(&plugin);
    }
    // 加载新导入的图元控件
    auto plugins = ConfigMaster::instance()->userPlugin->list(QString("group_id=%1").arg(groupId));
    installPlugins(plugins, getGroupWidget(groupId));
}

void UserGraphicPlugins::onManageUserGraphics(qint32 groupId)
{
    if (form == nullptr) {
        form = new UserPluginManageForm(groupId, parentWidget);
        connect(form, &UserPluginManageForm::importEvent,
                this, &UserGraphicPlugins::onImportUserGraphics);
        connect(form, &UserPluginManageForm::dataChanged,
                this, &UserGraphicPlugins::onPluginChanged);
        connect(form, &UserPluginManageForm::remove,
                this, &UserGraphicPlugins::onPluginRemoved);
    }else{
        form->setGroup(groupId);
    }

    form->show();
}

void UserGraphicPlugins::onPluginChanged(const UserPluginDO &data)
{
    auto id = AbstractUserPlugin::pluginId(data);
    auto obj = pluginMap[id];
    if (obj) {
        auto plugin = dynamic_cast<AbstractUserPlugin*>(obj);
        if (plugin) {
            if(!ConfigMaster::instance()->userPlugin->updateById(data)){
                return;
            }
            plugin->updatePluginInfo(data);
            auto widget = getGroupWidget(data.get_groupId());
            if (widget) {
                widget->updatePlugin(plugin);
            }
        }
    }
}

void UserGraphicPlugins::onPluginRemoved(const UserPluginDO &data)
{
    auto id = AbstractUserPlugin::pluginId(data);
    auto obj = pluginMap[id];
    if (obj) {
        auto plugin = dynamic_cast<AbstractUserPlugin*>(obj);
        if (plugin) {
            if (!ConfigMaster::instance()->userPlugin->deleteById(data)){
                return;
            }
            // 删除文件
            auto filePath = QCoreApplication::applicationDirPath() + data.get_path();
            QFile::remove(filePath);
            // 从控件组中移除
            auto widget = getGroupWidget(data.get_groupId());
            if (widget) {
                widget->removePlugin(plugin);
            }
        }
        delete obj;
        pluginMap.remove(id);
    }
}
