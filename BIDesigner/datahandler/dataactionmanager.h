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
 *
 * 数据及其动作的统一管理，主要作用：
 * 1. 管理所有与图元相关联的数据；
 * 2. 负责数据的序列化与反序列化；
 * 3. 统一请求数据并根据结果执行相应动作；
 * 4. 统一管理画布中使用的数据源；
 */
#ifndef DATAACTIONMANAGER_H
#define DATAACTIONMANAGER_H

#include "bigraphicsscene.h"
#include "datasource/datamarketdo.h"
#include "datasource/datasourcedo.h"
#include "dataaction.h"
#include <QThreadPool>
#include <QThreadStorage>
#include <QFutureWatcher>

class IDataSource;
class DataActionManager : public QObject
{
    Q_OBJECT
    DataActionManager();
public:
    ~DataActionManager();
    static DataActionManager* instance();
    void setGraphicsScene(BIGraphicsScene *scene);
    QString toXml();
    void parseXml(const QString &xml);
    /**
     * @brief run 启动数据请求任务并执行对应的动作
     */
    void run();
    void stop();
    /**
     * @brief getGraphicDataActions 获取图元配置的数据
     * @param graphicId 图元ID
     * @return 数据列表
     */
    QList<DataAction> getGraphicDataActions(const QString &graphicId);
    /**
     * @brief getDataAction 获取指定的数据动作
     * @param graphicId 图元ID
     * @param dataId 数据ID
     * @return 数据对象
     */
    DataAction getDataAction(const QString &graphicId, const QString &dataId);
    /**
     * @brief addDataAction 添加数据动作
     * @param action 数据动作
     */
    void addDataAction(DataAction action);
    void updateDataAction(DataAction action);
    void removeDataAction(DataAction action);
    void removeDataAction(const QString &graphicId, const QString &dataId);
    /**
     * @brief testDataAction 测试数据动作
     * @param action 数据动作
     */
    void testDataAction(const DataAction &action);
    void setProjectName(const QString &name){projectName = name;}
Q_SIGNALS:
    void dataQueryEndEvent(DataAction action, QJsonValue value);
    void loadProjectData(const QString &projectName, QList<DataMarketDO> dataList);
    void actionTestEnd(const QString &testInfo);
public Q_SLOTS:
    void onDataSourceChanged(DataSourceDO source);
    void onDataChanged(DataMarketDO data);

protected Q_SLOTS:
    void onDataQueryEnd(const DataAction &action, QJsonValue value);
    // void onSceneEvent(ItemAction action, QList<QGraphicsItem*> items);
    void onTestQueryEnd();
    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
private:
    // 管理图元的场景
    BIGraphicsScene *graphicScene{nullptr};
    // 动作，key 图元ID， value 关联的数据及动作信息(key 数据UUID， value 动作)
    QMap<QString, QMap<QString, DataAction>> actionMap;

    // 仅当 mergeDataSource 或 parseXml 执行后才清除无用数据
    // 数据源，key 数据源UUID， value 数据源描述
    QMap<QString, DataSourceDO> dataSourceMap;
    // 仅当 mergeDataSource 或 parseXml 执行后才清除无用数据
    // 数据，key 数据UUID， value 数据描述
    QMap<QString, DataMarketDO> dataMarketMap;
    // key 数据UUID，value 动作列表。用于数据请求后查找动作，在run方法中初始化
    QMap<QString, QList<DataAction>> actionIndexBydata;
    // key 定时器ID， value 定时器到期后需求请求的数据列表
    QMap<int, QList<DataMarketDO>> timerMap;
    QString projectName{""};
    // key 数据源UUID， value 连接该数据源的连接池
    QMap<QString, QThreadPool*> threadPoolMap;
    // 使用线程数据存储数据连接，保证没=每个线程一个连接
    QThreadStorage<IDataSource *> threadData;
    // key 数据源 ID， value 该数据源下数据的数量
    QMap<QString, int> dataCounter;
    // 监控返回的测试数据
    QFutureWatcher<QVariantPair> testWatcher;

    /**
     * @brief queryData 请求数据
     * @param data 数据对象
     * @return 请求结果
     */
    QJsonValue queryData(DataMarketDO data);
    /**
     * @brief mergeDataSource 汇总 actionMap 中的数据源信息与数据信息，去除重复信息
     */
    void mergeDataSource();
    void saveActionData(DataAction action);
};

#endif // DATAACTIONMANAGER_H
