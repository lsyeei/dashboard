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
#include "queryconfig.h"

#define EASY_JSON_DEFAULT
#include "easyjson.h"

#include <QJsonArray>
#include <QJsonDocument>

QueryConfig QueryConfig::fromJson(const QString &json)
{
    QueryConfig config;
    if (json.isEmpty()) {
        return config;
    }
    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "json parse error:" << error.errorString()
                   << "。json string：" << json;
        return config;
    }
    auto obj = doc.object();
    config.setMethod(QueryMethod(obj["Method"].toInt(0)));
    config.setUrl(obj["URL"].toString());
    QList<KeyValue> queryParam;
    auto queryArray = obj["QueryParams"].toArray();
    foreach (auto item, queryArray) {
        queryParam << EASYJSON->parseObject<KeyValue>(item.toObject());
    }
    config.setQueryParams(queryParam);
    QList<HttpHeaderItem> headers;
    auto headArray = obj["Headers"].toArray();
    foreach (auto item, headArray) {
        headers << EASYJSON->parseObject<HttpHeaderItem>(item.toObject());
    }
    config.setHeaders(headers);
    config.setBody(EASYJSON->parseObject<HttpBody>(obj["Body"].toObject()));
    return config;
}

QString QueryConfig::toJson()
{
    QJsonObject obj;
    obj.insert("Method", int(method));
    obj.insert("URL", url);
    QJsonArray paramArray;
    foreach (auto item, queryParams) {
        paramArray.append(EASYJSON->toJson(item));
    }
    obj.insert("QueryParams", paramArray);
    QJsonArray headArray;
    foreach (auto item, headers) {
        headArray.append(EASYJSON->toJson(item));
    }
    obj.insert("Headers", headArray);
    obj.insert("Body", EASYJSON->toJson(body));
    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact);
}
