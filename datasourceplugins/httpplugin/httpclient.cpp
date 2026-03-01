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
#include "httpclient.h"
#include "httpconfig.h"
#include "queryconfig.h"
#include <QHttp1Configuration>
#include <QHttp2Configuration>
#include <QJsonDocument>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QUrlQuery>

HttpClient::HttpClient() {}


bool HttpClient::connect(const QString &args)
{
    auto httpConfig = HttpConfig::fromJson(args);
    baseUrl = httpConfig.getURL();
    // 设置HTTP头
    auto headerConfig = httpConfig.getheaders();
    foreach(auto item, headerConfig){
        if(item.getType() == HeaderItemType::Known){
            headers.append(item.getKey().value<QHttpHeaders::WellKnownHeader>(), item.getValue());
        }else{
            headers.append(item.getKey().toString(), item.getValue());
        }
    }
    // 设置cookie
    auto cookieConfig = httpConfig.getCookies();
    foreach (auto item, cookieConfig) {
        headers.append(QHttpHeaders::WellKnownHeader::Cookie, item.getValue());
        QNetworkCookie cookie;
        cookie.setName(item.getKey().toUtf8());
        cookie.setValue(item.getValue().toUtf8());
        cookies.insertCookie(cookie);
    }
    // HTTP 连接配置
    auto setting = httpConfig.getSetting();
    network.setRedirectPolicy(QNetworkRequest::RedirectPolicy(setting.getRedirectPolicy()));
    network.setTransferTimeout(setting.getTimeout());
    if (setting.getVersion() == HttpVersion::V1) {
        request.setHttp1Configuration(QHttp1Configuration());
    } else if (setting.getVersion() == HttpVersion::V2) {
        request.setHttp2Configuration(QHttp2Configuration());
    }
    // http 权限认证
    authConfig = httpConfig.getAuthConfig();
    return true;
}

void HttpClient::disconnect()
{
}

bool HttpClient::isConnected()
{
    return true;
}

QJsonDocument HttpClient::query(const QString &args)
{
    auto queryConfig = QueryConfig::fromJson(args);
    QUrl url;
    url.setUrl(baseUrl + queryConfig.getUrl());

    // 处理 param
    QUrlQuery urlQuery;
    auto params = queryConfig.getQueryParams();
    foreach (auto item, params) {
        urlQuery.addQueryItem(item.getKey(), item.getValue());
    }
    url.setQuery(urlQuery);

    // 处理 header
    auto headerConfig = queryConfig.getHeaders();
    foreach(auto item, headerConfig){
        if(item.getType() == HeaderItemType::Known){
            headers.append(item.getKey().value<QHttpHeaders::WellKnownHeader>(),
                           item.getValue());
        }else{
            headers.append(item.getKey().toString(), item.getValue());
        }
    }

    // 处理 Body
    QByteArray data;
    auto body = queryConfig.getBody();
    headers.append(QHttpHeaders::WellKnownHeader::ContentType, body.getContentType());
    data = body.getContent().toUtf8();

    request.setUrl(url);
    network.setCookieJar(&cookies);
    request.setHeaders(headers);
    // 发送请求
    QNetworkReply *reply{nullptr};
    if (queryConfig.getMethod() == QueryMethod::GET) {
        reply = network.get(request, data);
    } else if (queryConfig.getMethod() == QueryMethod::POST) {
        reply = network.post(request, data);
    }
    if (reply == nullptr) {
        return QJsonDocument();
    }
    // 连接事件
    QObject::connect(reply, &QNetworkReply::finished,
            this, &HttpClient::onReplyFinished, Qt::QueuedConnection);
    QObject::connect(reply, &QNetworkReply::errorOccurred,
            this, &HttpClient::onReplyError, Qt::QueuedConnection);
    QObject::connect(&network, &QNetworkAccessManager::authenticationRequired,
                     this, &HttpClient::onRequireAuth, Qt::QueuedConnection);

    return QJsonDocument();
}

bool HttpClient::update(const QString &args, QJsonDocument data)
{
    return true;
}

void HttpClient::onReplyFinished()
{

}

void HttpClient::onReplyError()
{

}

void HttpClient::onRequireAuth(QNetworkReply *reply, QAuthenticator *authenticato)
{

}
