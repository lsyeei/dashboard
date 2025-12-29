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
#ifndef DATASOURCEMANAGER_H
#define DATASOURCEMANAGER_H

#include <QFutureWatcher>
#include <QObject>

class IDataSourcePlugin;
class IDataSource;
class DataSourceManager:public QObject
{
    Q_OBJECT
    DataSourceManager(QObject *parent = nullptr);
    ~DataSourceManager();
public:
    static DataSourceManager *instance();
    /**
     * @brief loadGraphics 加载图元
     * @return true 成功，false 失败
     */
    void loadDataSource();
    bool loaded(){return isLoaded;}
    // 删除拷贝构造函数和赋值运算符
    DataSourceManager(const DataSourceManager&) = delete;
    DataSourceManager& operator=(const DataSourceManager&) = delete;
    /**
     * @brief 通过ID获取数据源插件
     * @param id 数据源ID
     * @return 数据源插件
     */
    IDataSourcePlugin *getPluginById(const QString id);
    /**
     * @brief 根据插件ID创建数据源
     * @param dataSourceId 数据源插件ID
     * @return 数据源对象
     */
    IDataSource *createDataSource(const QString &pluginId);
    /**
     * @brief 获取全部根据插件插件
     * @return  根据插件插件列表
     */
    QList<IDataSourcePlugin *> getAllPlugins();
protected Q_SLOTS:
    void onPluginLoadEnd();
private:
    // 插件列表
    QList<IDataSourcePlugin*> pluginList;
    bool isLoaded{false};
    QFutureWatcher<IDataSourcePlugin*> *watcher;

    QList<IDataSourcePlugin*> loadPlugins();
};

#endif // DATASOURCEMANAGER_H
