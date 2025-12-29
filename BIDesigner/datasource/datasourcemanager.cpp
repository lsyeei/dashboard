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
#include "datasourcemanager.h"
#include "idatasourceplugin.h"
 #include <QtConcurrent>
#include <QCoreApplication>
#include <QDir>
#include <QFutureSynchronizer>
#include <QMessageBox>
#include <QPluginLoader>

DataSourceManager::DataSourceManager(QObject *parent) : QObject(parent){}

DataSourceManager::~DataSourceManager()
{
    foreach (auto item, pluginList) {
        delete item;
    }
    pluginList.clear();
}

DataSourceManager *DataSourceManager::instance()
{
    static DataSourceManager *manager = new DataSourceManager();
    return manager;
}

void DataSourceManager::loadDataSource()
{
    if (isLoaded) {
        return;
    }
    QFuture<IDataSourcePlugin*> future = QtConcurrent::run(
        [&](QPromise<IDataSourcePlugin*> &promise){
            promise.addResults(loadPlugins());
        });
    watcher = new QFutureWatcher<IDataSourcePlugin*>();
    connect(watcher, &QFutureWatcher<IDataSourcePlugin*>::finished,
            this, &DataSourceManager::onPluginLoadEnd);
    watcher->setFuture(future);
}

IDataSourcePlugin *DataSourceManager::getPluginById(const QString id)
{
    foreach (auto plugin, pluginList) {
        if(plugin->id().compare(id) == 0){
            return plugin;
        }
    }
    return nullptr;
}

IDataSource *DataSourceManager::createDataSource(const QString &pluginId)
{
    auto plugin = getPluginById(pluginId);
    if (plugin) {
        return plugin->dataSource();
    }
    return nullptr;
}

QList<IDataSourcePlugin *> DataSourceManager::getAllPlugins()
{
    return pluginList;
}

void DataSourceManager::onPluginLoadEnd()
{
    pluginList = watcher->future().results();
    delete watcher;
    isLoaded = true;
}

QList<IDataSourcePlugin *> DataSourceManager::loadPlugins()
{
    QList<IDataSourcePlugin *> result;
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
    if (!pluginsDir.cd("dataplugins")){
        QMessageBox::information(nullptr, tr("提示"), tr("未找到数据插件目录"));
        return result;
    }
    const QStringList entries = pluginsDir.entryList(QDir::Files);

    QFutureSynchronizer<IDataSourcePlugin*> sync;
    for (const QString &fileName : entries) {
        sync.addFuture(QtConcurrent::run([=](QPromise<IDataSourcePlugin*> &promise){
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            if (!pluginLoader.load()){
                qDebug() << "库加载失败：" << fileName << "; 错误提示：" << pluginLoader.errorString();
                return;
            }
            QObject *plugin = pluginLoader.instance();
            if (plugin) {
                promise.addResult(qobject_cast<IDataSourcePlugin *>(plugin));
            }
        }));
    }
    sync.waitForFinished();
    foreach(auto future, sync.futures()){
        result << future.results();
    }
    return result;
}
