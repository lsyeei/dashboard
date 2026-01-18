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
    // if (graphicScene && scene != graphicScene) {
    //     disconnect(graphicScene, &BIGraphicsScene::contentChanged,
    //                this, &DataActionManager::onSceneEvent);
    // }
    graphicScene = scene;
    // connect(scene, &BIGraphicsScene::contentChanged,
    //         this, &DataActionManager::onSceneEvent);
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
    // 启动定时器
    for (auto it = periodMap.begin(); it != periodMap.end(); ++ it){
        auto timerId = startTimer(std::chrono::seconds(it.key()), Qt::PreciseTimer);
        timerMap[timerId] = it.value();
    }
    // 注册事件
    connect(this, &DataActionManager::dataQueryEndEvent,
            this, &DataActionManager::onDataQueryEnd, Qt::QueuedConnection);
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

void DataActionManager::addDataAction(DataAction action)
{
    auto graphicId = action.getGraphicId();
    if (graphicId.isEmpty() || action.getDataId().isEmpty()) {
        return;
    }
    auto actMap = actionMap[graphicId];
    actMap[action.getDataId()] = action;
    actionMap[graphicId] = actMap;
}

void DataActionManager::updateDataAction(DataAction action)
{
    auto graphicId = action.getGraphicId();
    if (graphicId.isEmpty() || action.getDataId().isEmpty()) {
        return;
    }
    auto actMap = actionMap[graphicId];
    actMap[action.getDataId()] = action;
    actionMap[graphicId] = actMap;
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

void DataActionManager::testDataAction(DataAction action)
{
    if (action.getDataId().isEmpty()) {
        return;
    }
    auto data = action.getData();
    // 异步请求
    auto future = QtConcurrent::run<QJsonValue>([&](QPromise<QJsonValue> &result){
        result.addResult(queryData(data));});
    QFutureWatcher<QJsonValue> watcher;
    // 等待结果并执行动作
    connect(&watcher, &QFutureWatcher<QJsonValue>::finished, this, [&]{
        auto value = watcher.result();
        onDataQueryEnd(action, value);
    });
    watcher.setFuture(future);
}

void DataActionManager::onDataQueryEnd(DataAction action, QJsonValue value)
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
        QThreadPool::globalInstance()->start([&]{
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
    auto source = data.getDataSource();
    // 获取数据源插件
    auto pluginID = source.get_sourcePluginId();
    auto plugin = DataSourcePluginManager::instance()->getPluginById(pluginID);
    // 获取数据源并连接
    auto dataSource = plugin->dataSource();
    dataSource->connect(source.get_sourceArgs());
    if (dataSource->isConnected()){
        // 请求数据
        auto result = dataSource->query(data.get_requestArgs());
        // 执行处理代码
        auto code = data.get_processCode();
        if (!code.isEmpty()) {
            auto value = JSUtil::instance()->jsonDocToJSValue(result);
            auto rtn = JSUtil::instance()->evaluate(code,{value});
            return JSUtil::instance()->jsValueToJsonValue(rtn);
        }
    }
    return QJsonValue();
}

void DataActionManager::mergeDataSource()
{
    dataSourceMap.clear();
    dataMarketMap.clear();
    foreach (auto item, actionMap) {
        foreach (auto act, item) {
            auto data = act.getData();
            dataMarketMap[data.get_uuid()] = data;
            auto source = data.getDataSource();
            dataSourceMap[source.get_uuid()] = source;
        }
    }
}
