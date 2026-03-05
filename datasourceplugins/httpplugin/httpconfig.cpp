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
#include "httpconfig.h"
#define EASY_JSON_DEFAULT
#include "easyjson.h"

#include <QJsonArray>
#include <QJsonDocument>

HttpConfig HttpConfig::fromJson(const QString &json)
{
    HttpConfig config;
    QJsonParseError error;
    auto doc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning() << "json parse error:" << error.errorString()
        << "。json string：" << json;
        return config;
    }
    auto obj = doc.object();
    config.setURL(obj["URL"].toString());
    config.setAuthConfig(EASYJSON->parseObject<AuthConfig>(obj["AuthConfig"].toObject()));
    QList<KeyValue> cookies;
    auto cookieArray = obj["Cookies"].toArray();
    foreach (auto item, cookieArray) {
        cookies << EASYJSON->parseObject<KeyValue>(item.toObject());
    }
    config.setCookies(cookies);
    QList<HttpHeaderItem> headers;
    auto headArray = obj["Headers"].toArray();
    foreach (auto item, headArray) {
        headers << EASYJSON->parseObject<HttpHeaderItem>(item.toObject());
    }
    config.setheaders(headers);
    config.setSetting(EASYJSON->parseObject<HttpSetting>(obj["Setting"].toObject()));
    return config;
}

QString HttpConfig::toJson()
{
    QJsonObject obj;
    obj["URL"] = url;
    obj["AuthConfig"] = EASYJSON->toJson(authConfig);
    QJsonArray cookieArray;
    foreach (auto item, cookies) {
        cookieArray.append(EASYJSON->toJson(item));
    }
    obj["Cookies"] = cookieArray;
    QJsonArray headArray;
    foreach (auto item, headers) {
        headArray.append(EASYJSON->toJson(item));
    }
    obj["Headers"] = headArray;
    obj["Setting"] = EASYJSON->toJson(setting);
    QJsonDocument doc(obj);
    return doc.toJson(QJsonDocument::Compact);
}
