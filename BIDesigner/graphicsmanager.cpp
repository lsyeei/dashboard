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

#include "graphicsmanager.h"
#include "configs.h"
#include "customgraphic/abstractusergraphic.h"
#include "igraphicpluginCollection.h"
#include "igraphicplugin.h"
#include "configmaster.h"
#include <QCoreApplication>
#include <QPluginLoader>
#include <QMessageBox>
#include <QDir>
#include <QtConcurrent>

GraphicsManager::GraphicsManager(QObject *parent) : QObject(parent){}

GraphicsManager::~GraphicsManager()
{
    foreach (auto group, groups) {
        deleteGroup(group);
    }
    groups.clear();
}

GraphicsManager *GraphicsManager::instance()
{
    static GraphicsManager *manager = new GraphicsManager();
    return manager;
}

IGraphicPlugin *GraphicsManager::getPluginById(const QString id)
{
    IGraphicPlugin *result{nullptr};
    foreach (auto group, groups) {
        foreach (auto graphic, group->list) {
            if (graphic->id().compare(id) == 0) {
                result = graphic;
            }
        }
    }
    return result;
}

ICustomGraphic *GraphicsManager::createGraphic(const QString &graphicId)
{
    auto plugin = getPluginById(graphicId);
    if (plugin) {
        return plugin->createItem();
    }
    return nullptr;
}

QList<IGraphicPlugin *> GraphicsManager::getAllPlugins()
{
    QList<IGraphicPlugin *> result;
    foreach (auto group, groups) {
        result << group->list;
    }
    return result;
}

ICustomGraphic *GraphicsManager::createGraphic(const QString &graphicId, const QString &xmlText)
{
    auto plugin = getPluginById(graphicId);
    if (plugin) {
        return plugin->createItem(xmlText);
    }
    return nullptr;
}

bool GraphicsManager::addGroup(int groupId, const QString &groupName)
{
    auto group = groupMaps[groupName];
    if (group){
        return false;
    }
    group = userGroupMaps[groupId];
    if (group){
        return false;
    }
    group = new GraphicGroup{0, groupId, groupName, QList<IGraphicPlugin*>(), GraphicType::USER};
    userGroupMaps[groupId] = group;
    return true;
}

bool GraphicsManager::removeGroup(int groupId)
{
    // 从数据库删除
    auto flag = ConfigMaster::instance()->userPlugin->getMapper()
        ->execSql(QString("delete from userPlugin where group_id=%1;").arg(groupId));
    if(!flag){
        return false;
    }
    flag = ConfigMaster::instance()->userPluginGroup->deleteById(groupId);
    if(!flag){
        return false;
    }
    // 移除缓存
    auto group = userGroupMaps[groupId];
    if (group) {
        groups.removeOne(group);
        userGroupMaps.remove(groupId);
        deleteGroup(group);
        emit groupRemovedEvent(groupId);
        return true;
    }
    return false;
}

bool GraphicsManager::updateGroupName(int groupId, const QString &newName)
{
    auto group = userGroupMaps[groupId];
    if (group) {
        // 更新数据库
        UserPluginGroupDO data;
        data.set_id(groupId);
        data.set_name(newName);
        auto flag = ConfigMaster::instance()->userPluginGroup->updateById(data);
        if (!flag) {
            return false;
        }
        // 更新缓存
        group->groupName = newName;
        return true;
    }
    return false;
}

QList<IGraphicPlugin *> GraphicsManager::importGraphics(int groupId, const QStringList &files)
{
    QList<IGraphicPlugin *> list;
    auto pluginPath = getPluginPath(groupId);
    if (pluginPath.isEmpty()){
        return list;
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
        // 拷贝文件副本保存
        QFile::copy(file, dir.absoluteFilePath(fileName));
        // 存到数据库
        UserPluginDO plugin;
        plugin.set_groupId(groupId);
        plugin.set_name(info.baseName());
        plugin.set_path(pluginPath + fileName);
        plugin.set_type(suffix2Type(suffix));
        plugin.set_thumb(getThumbData(file));
        if(ConfigMaster::instance()->userPlugin->save(&plugin)){
            // 转为图元对象
            list << new AbstractUserGraphic(userGroupMaps[groupId]->groupName, plugin);
        }
    }
    return list;
}

IGraphicPlugin *GraphicsManager::updateGraphic(const UserPluginDO &data)
{
    auto group = userGroupMaps[data.get_groupId()];
    IGraphicPlugin *graphic{nullptr};
    foreach (auto item, group->list) {
        auto pluginId = AbstractUserGraphic::pluginId(data);
        if (item->id().compare(pluginId) == 0) {
            graphic = item;
        }
    }
    if (graphic) {
        if(ConfigMaster::instance()->userPlugin->updateById(data)){
            auto item = dynamic_cast<AbstractUserGraphic*>(graphic);
            item->updatePluginInfo(data);
        }
    }
    return graphic;
}

QString GraphicsManager::removeGraphic(const UserPluginDO &data)
{
    auto group = userGroupMaps[data.get_groupId()];
    IGraphicPlugin *graphic{nullptr};
    foreach (auto item, group->list) {
        auto pluginId = AbstractUserGraphic::pluginId(data);
        if (item->id().compare(pluginId) == 0) {
            graphic = item;
        }
    }
    auto graphicId = graphic->id();
    if (graphic) {
        if (!ConfigMaster::instance()->userPlugin->deleteById(data)){
            return "";
        }
    }
    return graphicId;
}

void GraphicsManager::onPredefGraphicsLoaded()
{
    auto plugins = watcher->future().results();
    int id = 0;
    foreach (auto plugin, plugins){
        auto groupName = plugin->group();
        auto group = groupMaps[groupName];
        if (group == nullptr) {
            // 新建组
            group = new GraphicGroup{0, --id, groupName, QList<IGraphicPlugin*>(), GraphicType::PREDEFINE};
            groups << group;
            groupMaps[groupName] = group;
        }
        group->list << plugin;
    }
    // 删除线程监控
    delete watcher;
    // 加载用户自定义图元
    loadUserGraphics();
    // 加载完成
    isLoaded = true;
    emit loadEndEvent(groups);
}

void GraphicsManager::loadGraphics()
{
    if (isLoaded) {
        return;
    }
    QFuture<IGraphicPlugin*> future = QtConcurrent::run(
        [&](QPromise<IGraphicPlugin*> &promise){
            promise.addResults(loadPredefGraphics());
        });
    watcher = new QFutureWatcher<IGraphicPlugin*>();
    connect(watcher, &QFutureWatcher<IGraphicPlugin*>::finished,
            this, &GraphicsManager::onPredefGraphicsLoaded);
    watcher->setFuture(future);
}

QList<IGraphicPlugin *> GraphicsManager::loadPredefGraphics()
{
    QList<IGraphicPlugin*> result;
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
        QMessageBox::information(nullptr, tr("提示"), tr("未找到插件目录"));
        return result;
    }
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    QFutureSynchronizer<IGraphicPlugin*> sync;
    for (const QString &fileName : entries) {
        sync.addFuture(QtConcurrent::run([=](QPromise<IGraphicPlugin*> &promise){
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            if (!pluginLoader.load()){
                qDebug() << "库加载失败：" << fileName << "; 错误提示：" << pluginLoader.errorString();
                return;
            }
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                auto *pluginCollection = qobject_cast<IGraphicPluginCollection *>(plugin);
                if (pluginCollection){
                    promise.addResults(pluginCollection->graphicPlugins());
                }else{
                    promise.addResult(qobject_cast<IGraphicPlugin *>(plugin));
                }
            }
        }));
    }
    sync.waitForFinished();
    foreach(auto future, sync.futures()){
        result << future.results();
    }
    return result;
}

void GraphicsManager::loadUserGraphics()
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
    foreach (auto userGroup, groupList) {
        auto groupName = userGroup.get_name();
        auto groupId = userGroup.get_id();
        auto group = userGroupMaps[groupId];
        if (group == nullptr) {
            // 新建组
            group = new GraphicGroup{0, groupId, groupName, QList<IGraphicPlugin*>(), GraphicType::USER};
            groups << group;
            userGroupMaps[groupId] = group;
        }
        auto userPlugins = pluginInfoMaps[groupId];
        foreach(auto plugin, userPlugins){
            group->list << new AbstractUserGraphic(groupName, plugin);
        }
    }
}

void GraphicsManager::deleteGroup(GraphicGroup *group)
{
    foreach (auto graphic, group->list) {
        delete graphic;
    }
    delete group;
}

QString GraphicsManager::getPluginPath(qint32 groupId)
{
    // 检查用户控件路径是否存在
    auto pluginPath = QCoreApplication::applicationDirPath() + appConfigs.userPluginPath;
    QDir dir(pluginPath);
    if (!dir.exists()) {
        if(!dir.mkdir(pluginPath)){
            QMessageBox::warning(nullptr, tr("错误"), tr("无法创建路径：") + pluginPath);
            return "";
        }
    }
    // 创建控件组目录
    auto groupName = userGroupMaps[groupId]->groupName;
    auto groupPath = pluginPath + groupName;
    if (!dir.exists(groupPath)) {
        if(!dir.mkdir(groupPath)){
            QMessageBox::warning(nullptr, tr("错误"), tr("无法创建路径：") + groupPath);
            return "";
        }
    }
    return appConfigs.userPluginPath + groupName + "/";
}

UserPluginType GraphicsManager::suffix2Type(const QString &suffix)
{
    auto ext = suffix.toLower();
    if (ext.compare("svg") == 0){
        return UserPluginType::SVG;
    }
    return UserPluginType::IMG;
}

QByteArray GraphicsManager::getThumbData(const QString &file)
{
    QSize size{48,48};
    QPixmap img(file);
    auto thumb = img.scaled(size,Qt::KeepAspectRatio);
    QByteArray array;
    QBuffer buf(&array);
    thumb.save(&buf, "png");
    return array;
}

IGraphicPlugin * GraphicsManager::addGraphic(const UserPluginDO &graphicData, const QString &xmlData)
{
    // 获取缓存的组信息
    auto group = userGroupMaps[graphicData.get_groupId()];
    if (group == nullptr){
        return nullptr;
    }
    auto data = "<User>" + xmlData + "</User>";
    auto pluginPath = getPluginPath(graphicData.get_groupId());
    auto name = graphicData.get_name();
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
    // 存入数据库
    QString path = pluginPath + fileName;
    UserPluginDO plugin(graphicData);
    plugin.set_path(path);
    if(!ConfigMaster::instance()->userPlugin->save(&plugin)){
        file.remove();
        return nullptr;
    }
    // 生成图元
    auto graphic = new AbstractUserGraphic(group->groupName, plugin);
    group->list << graphic;
    return graphic;
}
