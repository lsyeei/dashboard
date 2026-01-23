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
#include "dataactionmanager.h"
#include "datacontrolform.h"
#include "datasource/datasourcepluginmanager.h"
#include "jsutil/jsutil.h"
#include "xmlHelper.h"
#include <QTimerEvent>
#include <QXmlStreamReader>
#include <filetemplate.h>
#include <QtConcurrent>
#include "idatasourceplugin.h"
#include "idatasource.h"
#include "bigraphicsscene.h"

DataActionManager::DataActionManager() {
}

DataActionManager::~DataActionManager()
{
    foreach (auto item, actionMap) {
        item.clear();
    }
    actionMap.clear();
    dataSourceMap.clear();
    dataMarketMap.clear();
}

DataActionManager *DataActionManager::instance()
{
    static auto *manager = new DataActionManager();
    return manager;
}

void DataActionManager::setGraphicsScene(BIGraphicsScene *scene)
{
    graphicScene = scene;
}

QString DataActionManager::toXml()
{
    // 合并数据源及数据信息
    mergeDataSource();
    // 生成 XML
    QString data;
    QScopedPointer<QXmlStreamWriter> xml(new QXmlStreamWriter(&data));

    typedef XmlTemplate::dataSourceTemplate dataSource;
    xml->writeStartElement(dataSource::configList);
    auto configs = dataSourceMap.values();
    XmlHelper::writeCDATA(xml.data(), configs);
    xml->writeEndElement();

    xml->writeStartElement(dataSource::dataList);
    auto dataSets = dataMarketMap.values();
    XmlHelper::writeCDATA(xml.data(), dataSets);
    xml->writeEndElement();

    xml->writeStartElement(dataSource::actionList);
    typedef dataSource::actionTemplate actions;
    typedef actions::graphicActionTemplate actionDetail;
    auto item = actionMap.begin();
    while(item != actionMap.end()){
        if (graphicScene->getItemById(item.key()) == nullptr){
            // 已经删除的图元不导出
            continue;
        }
        xml->writeStartElement(actions::graphicAction);
        xml->writeTextElement(actionDetail::graphicId,item.key());
        xml->writeStartElement(actionDetail::actions);
        auto actions = item.value().values();
        XmlHelper::writeCDATA(xml.data(), actions);
        xml->writeEndElement();
        xml->writeEndElement();
        item ++;
    }
    xml->writeEndElement();
    return data;
}

void DataActionManager::parseXml(const QString &xml)
{
    qRegisterMetaType<NamedId>("NamedId");
    typedef XmlTemplate::dataSourceTemplate dataSource;
    typedef dataSource::actionTemplate actions;
    typedef actions::graphicActionTemplate actionDetail;
    QXmlStreamReader reader(xml);
    while(!reader.atEnd()){
        auto flag = reader.readNextStartElement();
        if (reader.hasError()) {
            QMessageBox::information(nullptr, tr("提示"),
                                     QString(tr("解析数据源错误。%1" ))
                                         .arg(reader.errorString()));
            break;
        }
        if (!flag){
            continue;
        }
        if (reader.name().compare(dataSource::configList) == 0)
        {
            auto sourceList = XmlHelper::CDATA2List<DataSourceDO>(&reader);
            for (int i=0; i < sourceList.count(); ++i) {
                dataSourceMap[sourceList[i].get_uuid()] = sourceList[i];
            }
        }
        if (reader.name().compare(dataSource::dataList) == 0)
        {
            auto dataList = XmlHelper::CDATA2List<DataMarketDO>(&reader);
            for (int i=0; i < dataList.count(); ++i) {
                dataMarketMap[dataList[i].get_uuid()] = dataList[i];
            }
        }
        if (reader.name().compare(dataSource::actionList) == 0) {
            while(true){
                auto type = reader.readNext();
                if (type != QXmlStreamReader::StartElement ||
                    reader.name().compare(actions::graphicAction) != 0){
                    break;
                }
                QString id = "";
                type = reader.readNext();
                if (type == QXmlStreamReader::StartElement &&
                    reader.name().compare(actionDetail::graphicId) == 0) {
                    id = reader.readElementText();
                }
                reader.readNextStartElement();
                if (reader.name().compare(actionDetail::actions) == 0) {
                    auto actionList = XmlHelper::CDATA2List<DataAction>(&reader);
                    if (id.isEmpty()) {
                        break;
                    }
                    // 完善信息
                    QMap<QString, DataAction> actMap;
                    for (int i=0; i < actionList.count(); ++i) {
                        auto& item = actionList[i];
                        auto& source = dataSourceMap[item.getSourceId()];
                        auto& data = dataMarketMap[item.getDataId()];
                        data.setDataSource(source);
                        item.setData(data);
                        actMap[item.getDataId()] = item;
                    }
                    actionMap[id] = actMap;
                }
            }
        }
    }
    // 将解析的数据整合到本地数据，供数据编辑使用
    emit loadProjectData(projectName, dataMarketMap.values());
}

void DataActionManager::run()
{
    if (graphicScene == nullptr) {
        qWarning() << __FUNCTION__ << "DataActionManager need a pointer of graphic scene";
        return;
    }
    // 按照索引分类数据与动作
    QMap<int, QList<DataMarketDO>> periodMap;
    foreach (auto item, actionMap){
        foreach (auto action, item) {
            // 以数据请求周期为索引分类数据
            auto data = action.getData();
            auto period = data.get_requestPeriod();
            auto periodList = periodMap[period];
            periodList.append(data);
            // 以数据为索引进行分类
            auto list = actionIndexBydata[action.getDataId()];
            list << action;
        }
    }
    // 计算数据源中数据的数量
    foreach (auto item, dataMarketMap) {
        auto sourceId = item.getDataSource().get_uuid();
        if (dataCounter.contains(sourceId)) {
            dataCounter[sourceId] = dataCounter[sourceId] + 1;
        }else{
            dataCounter[sourceId] = 1;
        }
    }

    // 启动定时器
    for (auto it = periodMap.begin(); it != periodMap.end(); ++ it){
        auto timerId = startTimer(std::chrono::seconds(it.key()), Qt::PreciseTimer);
        timerMap[timerId] = it.value();
    }
    // 注册事件
    connect(this, &DataActionManager::dataQueryEndEvent,
            this, &DataActionManager::onDataQueryEnd, Qt::QueuedConnection);
}

void DataActionManager::stop()
{
    // 停止所有计数器
    for (auto item = timerMap.begin(); item != timerMap.end(); ++ item) {
        killTimer(item.key());
    }
    // 停止所有数据连接线程
    foreach (auto item, threadPoolMap) {
        item->clear();
    }
}

QList<DataAction> DataActionManager::getGraphicDataActions(const QString &graphicId)
{
    if (!actionMap.contains(graphicId)) {
        return QList<DataAction>();
    }
    auto actMap = actionMap[graphicId];
    if (actMap.isEmpty()) {
        return QList<DataAction>();
    }
    return actMap.values();
}

DataAction DataActionManager::getDataAction(const QString &graphicId, const QString &dataId)
{
    if (graphicId.isEmpty() || dataId.isEmpty() || !actionMap.contains(graphicId)) {
        return DataAction();
    }
    auto actMap = actionMap[graphicId];
    if (actMap.isEmpty() || !actMap.contains(dataId)) {
        return DataAction();
    }
    return actMap[dataId];
}

void DataActionManager::saveActionData(DataAction action)
{
    auto sourceId = action.getSourceId();
    if (!sourceId.isEmpty()){
        if (!dataSourceMap.contains(sourceId)){
            dataSourceMap[sourceId] = action.getDataSource();
        }
        auto dataId = action.getDataId();
        if (!dataMarketMap.contains(dataId)) {
            dataMarketMap[dataId] = action.getData();
        }
    }
}

void DataActionManager::addDataAction(DataAction action)
{
    auto graphicId = action.getGraphicId();
    if (graphicId.isEmpty() || action.getDataId().isEmpty()) {
        return;
    }
    auto actMap = actionMap[graphicId];
    actMap[action.getDataId()] = action;
    actionMap[graphicId] = actMap;
    saveActionData(action);
}

void DataActionManager::updateDataAction(DataAction action)
{
    auto graphicId = action.getGraphicId();
    if (graphicId.isEmpty() || action.getDataId().isEmpty()) {
        return;
    }
    auto& actMap = actionMap[graphicId];
    actMap[action.getDataId()] = action;
    // actionMap[graphicId] = actMap;
    saveActionData(action);
}

void DataActionManager::removeDataAction(DataAction action)
{
    auto graphicId = action.getGraphicId();
    removeDataAction(graphicId, action.getDataId());
}

void DataActionManager::removeDataAction(const QString &graphicId, const QString &dataId)
{
    if (graphicId.isEmpty() || dataId.isEmpty() || !actionMap.contains(graphicId)) {
        return;
    }
    auto actMap = actionMap[graphicId];
    if (actMap.isEmpty()) {
        return;
    }
    actMap.remove(dataId);
}

void DataActionManager::testDataAction(const DataAction &action)
{
    if (action.getDataId().isEmpty()) {
        return;
    }
    DataMarketDO data;
    auto dataId = action.getDataId();
    if (dataMarketMap.contains(dataId)) {
        data = dataMarketMap[dataId];
    }else{
        data = action.getData();
    }
    // 异步请求
    auto future = QtConcurrent::run<QVariantPair>(
        [&](QPromise<QVariantPair> &result, DataMarketDO dataMarket){
            if (threadData.hasLocalData()){
            // 清空存储的连接，防止连接混用
            threadData.setLocalData(nullptr);
        }
        auto value = queryData(dataMarket);
        result.addResult({QVariant::fromValue(action), QVariant::fromValue(value)});
    }, data);
    // 等待结果并执行动作
    connect(&testWatcher, &QFutureWatcher<QVariantPair>::finished,
            this, &DataActionManager::onTestQueryEnd, Qt::SingleShotConnection);
    testWatcher.setFuture(future);
}

bool DataActionManager::copy(const QString &fromGraphicId, const QString &toGraphicId)
{
    if (fromGraphicId.isEmpty() || toGraphicId.isEmpty()){
        return false;
    }
    if (!actionMap.contains(fromGraphicId)){
        return true;
    }
    auto fromActionMap = actionMap[fromGraphicId];
    auto& toActionMap = actionMap[toGraphicId];
    foreach (auto act, fromActionMap) {
        if (toActionMap.contains(act.getDataId())) {
            continue;
        }
        act.setGraphicId(toGraphicId);
        toActionMap[act.getDataId()] = act;
    }
    return true;
}

void DataActionManager::onDataSourceChanged(DataSourceDO source)
{
    auto sourceId = source.get_uuid();
    if (dataSourceMap.contains(sourceId)){
        dataSourceMap[sourceId] = source;
    }
}

void DataActionManager::onDataChanged(DataMarketDO data)
{
    auto dataId = data.get_uuid();
    if (dataMarketMap.contains(dataId)) {
        dataMarketMap[dataId] = data;
    }
}

void DataActionManager::onDataQueryEnd(const DataAction &action, QJsonValue value)
{
    // 获取图元
    auto graphicID = action.getGraphicId();
    // 查找图元
    if (graphicScene == nullptr) {
        return;
    }
    auto graphic = graphicScene->getItemById(graphicID);
    if (graphic == nullptr) {
        qWarning() << __FUNCTION__ << "graphic id:" << graphicID << " is not a exist";
        return;
    }
    // 执行动作
    auto act = action.getAction();
    auto absAction = AbstractAction::fromVariant(&act);
    absAction->triggerAction(value.toVariant(), graphic);
    emit actionTestEnd(absAction->tracerInfo());
}

void DataActionManager::onTestQueryEnd()
{
    auto data = testWatcher.result();
    auto action = data.first.value<DataAction>();
    auto value = data.second.value<QJsonValue>();
    onDataQueryEnd(action, value);
}

// 不处理图元删除事件，删除的图元可能通过撤销操作恢复
// void DataActionManager::onSceneEvent(ItemAction action, QList<QGraphicsItem *> items)
// {
//     if (action != ItemAction::REMOVE) {
//         return;
//     }
//     // 只处理删除图元事件
//     foreach (auto item, items) {
//         actionMap.remove(graphicScene->getItemId(item));
//     }
// }

void DataActionManager::timerEvent(QTimerEvent *event)
{
    auto dataList = timerMap[event->timerId()];
    if (dataList.isEmpty()){
        return;
    }
    foreach (auto data, dataList) {
        auto sourceId = data.getDataSource().get_uuid();
        // 检查该数据源是否已有连接的线程
        if (!threadPoolMap.contains(sourceId)) {
            // 分配数据连接线程池
            auto pool = new QThreadPool();
            threadPoolMap[sourceId] = pool;
            int threadCount{1};
            auto dataCount = dataCounter[sourceId];
            auto total = dataMarketMap.count();
            threadCount = QThread::idealThreadCount() * dataCount / total;
            if (threadCount < 1) {
                threadCount = 1;
            }
            pool->setMaxThreadCount(threadCount);
        }

        auto future = QtConcurrent::run(threadPoolMap[sourceId],/*);
        QThreadPool::globalInstance()->start(*/[&]{
            // 请求数据
            auto value = queryData(data);
            if (value.isNull() || value.isUndefined()){
                return;
            }
            // 执行数据逻辑
            auto actionList = actionIndexBydata[data.get_uuid()];
            foreach (auto item, actionList) {
                // 数据逻辑涉及UI，需要在主线程中执行，此处只发出消息
                emit dataQueryEndEvent(item, value);
            }
        });
    }
}

QJsonValue DataActionManager::queryData(DataMarketDO data)
{
    QJsonValue jsValue;
    auto dataId = data.get_uuid();
    auto localData = dataMarketMap[dataId];
    IDataSource* dataSource{nullptr};
    if (threadData.hasLocalData()){
        dataSource = threadData.localData();
    }else{
        auto source = localData.getDataSource();
        // 获取数据源插件
        auto pluginID = source.get_sourcePluginId();
        auto plugin = DataSourcePluginManager::instance()->getPluginById(pluginID);
        // 获取数据源并连接
        dataSource = plugin->dataSource();
        dataSource->connect(source.get_sourceArgs());
        threadData.setLocalData(dataSource);
    }
    if (dataSource->isConnected()){
        // 请求数据
        auto result = dataSource->query(localData.get_requestArgs());
        // 执行处理代码
        auto code = localData.get_processCode();
        if (!code.isEmpty()) {
            auto value = JSUtil::instance()->jsonDocToJSValue(result);
            auto rtn = JSUtil::instance()->evaluate(code,{value});
            jsValue = JSUtil::instance()->jsValueToJsonValue(rtn);
        }
    }
    return jsValue;
}

void DataActionManager::mergeDataSource()
{
    QList<QString> sourceIdList;
    QList<QString> dataIdList;
    foreach (auto item, actionMap) {
        dataIdList << item.keys();
    }
    // 清理不用的data
    for (auto item = dataMarketMap.begin(); item != dataMarketMap.end();) {
        if (!dataIdList.contains(item.key())) {
            item = dataMarketMap.erase(item);
        }else{
            sourceIdList.append(item->getDataSource().get_uuid());
            ++item;
        }
    }
    // 清理不用的source
    for (auto item = dataSourceMap.begin(); item != dataSourceMap.end(); ) {
        if (!sourceIdList.contains(item.key())) {
            item = dataSourceMap.erase(item);
        }else{
            ++item;
        }
    }
}
