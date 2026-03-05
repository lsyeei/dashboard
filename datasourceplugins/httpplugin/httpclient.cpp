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
#include "oauth2client.h"
#include "oauth1client.h"
#include "auth1config.h"
#include <QEventLoop>
#include <QHttp1Configuration>
#include <QHttp2Configuration>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QNetworkCookie>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QAuthenticator>
#include <QDateTime>
#include <QRandomGenerator>
#include <QTimer>

HttpClient::HttpClient()
{
}

HttpClient::~HttpClient()
{
    if (oauth2Client) {
        delete oauth2Client;
        oauth2Client = nullptr;
    }
    if (oauth1Client) {
        delete oauth1Client;
        oauth1Client = nullptr;
    }
}

QHttpHeaders HttpClient::config2Header(const QList<HttpHeaderItem> &config) {
    QHttpHeaders httpHeader;
    foreach (auto item, config) {
        if (item.getType() == HeaderItemType::Known) {
            httpHeader.append(item.getKey().value<QHttpHeaders::WellKnownHeader>(),
                           item.getValue());
        } else {
            httpHeader.append(item.getKey().toString(), item.getValue());
        }
    }
    return httpHeader;
}

bool HttpClient::connect(const QString &args) {
    auto httpConfig = HttpConfig::fromJson(args);
    baseUrl = httpConfig.getURL();
    setting = httpConfig.getSetting();
    // 设置HTTP头
    headers = config2Header(httpConfig.getheaders());
    // 设置cookie
    auto cookieConfig = httpConfig.getCookies();
    foreach (auto item, cookieConfig) {
        headers.append(QHttpHeaders::WellKnownHeader::Cookie, item.getValue());
        QNetworkCookie cookie;
        cookie.setName(item.getKey().toUtf8());
        cookie.setValue(item.getValue().toUtf8());
        cookies.insertCookie(cookie);
    }
    // http 权限认证
    authConfig = httpConfig.getAuthConfig();

    // 如果是OAuth2，初始化OAuth2Client
    if (authConfig.getMethod() == AuthMethod::OAuth2) {
        oauth2Client = new OAuth2Client(this);
        Auth2Config oauth2Config = authConfig.getConfig().value<Auth2Config>();
        oauth2Client->setConfig(oauth2Config);
    }
    // 如果是OAuth1，初始化OAuth1Client
    if (authConfig.getMethod() == AuthMethod::OAuth1) {
        oauth1Client = new OAuth1Client(this);
        Auth1Config oauth1Config = authConfig.getConfig().value<Auth1Config>();
        oauth1Client->setConfig(oauth1Config);
    }
    // 预热 SSL 连接（连接到实际目标服务器）
    if (baseUrl.startsWith("https://")) {
        QUrl url(baseUrl);
        QSslSocket sslSocket;
        sslSocket.connectToHostEncrypted(url.host(), 443);

        // 等待 SSL 握手完成（设置 5 秒超时）
        if (sslSocket.waitForEncrypted(5000)) {
            sslSocket.abort();
        }
    }
    return true;
}

void HttpClient::disconnect()
{
}

bool HttpClient::isConnected()
{
    return true;
}

QHttpHeaders HttpClient::parseAuth(QUrl &url, QueryMethod method)
{
    QHttpHeaders authHeaders;
    auto urlQuery = QUrlQuery(url.query());
    switch (authConfig.getMethod()) {
    case AuthMethod::APIKey:
        applyAPIKeyAuth(authConfig.getConfig().toJsonObject(), authHeaders, urlQuery);
        url.setQuery(urlQuery);
        break;
    case AuthMethod::BearToken:
        applyBearerTokenAuth(authConfig.getConfig().toJsonObject(), authHeaders);
        break;
    case AuthMethod::JWT:
        applyJWTAuth(authConfig.getConfig().value<JWTConfig>(), authHeaders);
        break;
    case AuthMethod::BasicAuth:
        applyBasicAuth(authConfig.getConfig().toJsonObject(), authHeaders);
        break;
    case AuthMethod::OAuth1:
        // OAuth1 需要完整的URL和HTTP方法来生成签名
        {
            QString methodName = (method == QueryMethod::GET) ? "GET" : "POST";
            applyOAuth1Auth(authHeaders, url, methodName);
        }
        break;
    case AuthMethod::OAuth2:
        applyOAuth2Auth(authHeaders, urlQuery);
        url.setQuery(urlQuery);
        break;
    case AuthMethod::NoAuth:
    default:
        break;
    }

    return authHeaders;
}

QJsonDocument HttpClient::parseJson(const QByteArray &data)
{
    QJsonDocument result;
    QJsonParseError parseError;
    result = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        QJsonObject obj;
        obj["value"] = QString::fromUtf8(data);
        result.setObject(obj);
    }
    return result;
}

QJsonDocument HttpClient::query(const QString &args)
{
    auto queryConfig = QueryConfig::fromJson(args);
    QUrl url;
    url.setUrl(baseUrl + queryConfig.getUrl());
    // 处理 query param
    QUrlQuery urlQuery;
    auto params = queryConfig.getQueryParams();
    foreach (auto item, params) {
        urlQuery.addQueryItem(item.getKey(), item.getValue());
    }
    url.setQuery(urlQuery);

    // 处理授权配置
    auto authHeaders = parseAuth(url, queryConfig.getMethod());

    // 处理 query 中配置的 header
    auto queryHeader = config2Header(queryConfig.getHeaders());

    // 处理 Body
    QByteArray data;
    auto body = queryConfig.getBody();
    if (!body.isEmpty()) {
        queryHeader.append(QHttpHeaders::WellKnownHeader::ContentType, body.getContentType());
        data = body.getContent().toUtf8();
    }

    QNetworkRequest request;
    // HTTP 连接配置
    network.setRedirectPolicy(QNetworkRequest::RedirectPolicy(setting.getRedirectPolicy()));
    network.setTransferTimeout(setting.getTimeout());
    if (setting.getVersion() == HttpVersion::V1) {
        request.setHttp1Configuration(QHttp1Configuration());
    } else if (setting.getVersion() == HttpVersion::V2) {
        request.setHttp2Configuration(QHttp2Configuration());
    }
    request.setUrl(url);
    network.setCookieJar(&cookies);
    auto headerList = headers.toListOfPairs();
    headerList << authHeaders.toListOfPairs() << queryHeader.toListOfPairs();
    request.setHeaders(QHttpHeaders::fromListOfPairs(headerList));
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

    // 创建事件循环用于等待异步请求完成
    QEventLoop eventLoop;

    // 连接事件，请求完成时退出事件循环
    QObject::connect(reply, &QNetworkReply::finished,
            &eventLoop, &QEventLoop::quit);
    QObject::connect(reply, &QNetworkReply::errorOccurred,
            &eventLoop, &QEventLoop::quit);
    QObject::connect(&network, &QNetworkAccessManager::authenticationRequired,
                     this, &HttpClient::onRequireAuth);

    // 阻塞等待请求完成
    eventLoop.exec();

    QJsonDocument result;
    // 读取响应数据
    if (reply->error() == QNetworkReply::NoError) {
        result = parseJson(reply->readAll());
    } else {
        qWarning() << "HTTP request error:" << reply->errorString();
        qWarning() << "request info: url=" << request.url()
                    << "; headers:" << request.headers();
        if (reply->isReadable()) {
            result = parseJson(reply->readAll());
        }else{
            result.setObject({{"error", reply->errorString()},
                              {"HTTP Status", reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()}});
        }
    }

    reply->deleteLater();

    return result;
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

void HttpClient::onRequireAuth(QNetworkReply *reply, QAuthenticator *authenticator)
{
    if (authenticator == nullptr) {
        return;
    }

    auto authConfigObj = authConfig.getConfig().toJsonObject();

    switch (authConfig.getMethod()) {
    case AuthMethod::BasicAuth:
        handleBasicAuthChallenge(authConfigObj, authenticator);
        break;
    case AuthMethod::DigestAuth:
        handleDigestAuthChallenge(authConfig.getConfig().value<DigestAuthConfig>(), authenticator);
        break;
    case AuthMethod::NTLM:
        handleNTLMChallenge(authConfig.getConfig().value<NTLMConfig>(), authenticator);
        break;
    case AuthMethod::SPNEGO:
        handleSPNEGOChallenge(authConfig.getConfig().value<SPNEGOConfig>(), authenticator);
        break;
    default:
        break;
    }
}

void HttpClient::applyAPIKeyAuth(const QJsonObject &config, QHttpHeaders &authHeaders, QUrlQuery &urlQuery)
{
    QString location = config["location"].toString();
    QString key = config["key"].toString();
    QString value = config["value"].toString();
    if (location == "Header") {
        authHeaders.append(key.toUtf8(), value.toUtf8());
    } else if (location == "Query") {
        urlQuery.addQueryItem(key, value);
    }
}

void HttpClient::applyBearerTokenAuth(const QJsonObject &config, QHttpHeaders &authHeaders)
{
    QString token = config["token"].toString();
    authHeaders.append(QHttpHeaders::WellKnownHeader::Authorization,
                      QString("Bearer %1").arg(token).toUtf8());
}

void HttpClient::applyJWTAuth(const JWTConfig &config, QHttpHeaders &authHeaders)
{
    QString token = config.getToken();
    AuthLocation location = config.getLocation();
    QString headerPrefix = config.getHeaderPrefix();

    if (token.isEmpty()) {
        qWarning() << "JWT token is empty";
        return;
    }

    if (location == AuthLocation::Header) {
        authHeaders.append(QHttpHeaders::WellKnownHeader::Authorization,
                          QString("%1 %2").arg(headerPrefix, token).toUtf8());
    } else {
        // Query 参数方式（目前不支持，因为需要 URL）
        qWarning() << "JWT Query parameter location not yet supported";
    }
}

void HttpClient::applyBasicAuth(const QJsonObject &config, QHttpHeaders &authHeaders)
{
    QString userName = config["userName"].toString();
    QString password = config["password"].toString();
    QString credential = userName + ":" + password;
    QByteArray base64Credential = credential.toUtf8().toBase64();
    authHeaders.append(QHttpHeaders::WellKnownHeader::Authorization,
                      QString("Basic %1").arg(QString::fromUtf8(base64Credential)).toUtf8());
}

void HttpClient::handleBasicAuthChallenge(const QJsonObject &config, QAuthenticator *authenticator)
{
    QString userName = config["userName"].toString();
    QString password = config["password"].toString();
    QString realm = config["realm"].toString();
    QString spn = config["spn"].toString();
    if (!userName.isEmpty() && !password.isEmpty()) {
        authenticator->setUser(userName);
        authenticator->setPassword(password);
    }
    if (!realm.isEmpty()) {
        authenticator->setOption("realm", realm);
    }
    if (!spn.isEmpty()) {
        authenticator->setOption("spn", spn);
    }
}

void HttpClient::handleDigestAuthChallenge(const DigestAuthConfig &config, QAuthenticator *authenticator)
{
    QString userName = config.getUserName();
    QString password = config.getPassword();
    QString realm = config.getRealm();
    if (!userName.isEmpty() && !password.isEmpty()) {
        authenticator->setUser(userName);
        authenticator->setPassword(password);
    }
    if (!realm.isEmpty()) {
        authenticator->setOption("realm", realm);
    }
}

void HttpClient::handleNTLMChallenge(const NTLMConfig &config, QAuthenticator *authenticator)
{
    QString userName = config.getUserName();
    QString password = config.getPassword();
    QString realm = config.getRealm();
    QString spn = config.getSpn();
    if (!userName.isEmpty() && !password.isEmpty()) {
        authenticator->setUser(userName);
        authenticator->setPassword(password);
    }
    if (!realm.isEmpty()) {
        authenticator->setOption("realm", realm);
    }
    if (!spn.isEmpty()) {
        authenticator->setOption("spn", spn);
    }
}

void HttpClient::handleSPNEGOChallenge(const SPNEGOConfig &config, QAuthenticator *authenticator)
{
    QString userName = config.getUserName();
    QString password = config.getPassword();
    QString spn = config.getSpn();
    if (!userName.isEmpty() && !password.isEmpty()) {
        authenticator->setUser(userName);
        authenticator->setPassword(password);
    }
    if (!spn.isEmpty()) {
        authenticator->setOption("spn", spn);
    }
}

void HttpClient::applyOAuth1Auth(QHttpHeaders &authHeaders, QUrl &url, const QString &method)
{
    // 使用OAuth1Client处理授权
    if (oauth1Client) {
        oauth1Client->applyAuth(authHeaders, url, method);
    }
}

void HttpClient::applyOAuth2Auth(QHttpHeaders &authHeaders, QUrlQuery &urlQuery)
{
    // 设置OAuth2配置已在connect()中完成，直接应用授权
    if (oauth2Client) {
        oauth2Client->applyAuth(authHeaders, urlQuery);
    }
}
