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
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "authdef.h"
#include "httpconfig.h"
#include "idatasource.h"
#include "oauth2client.h"
#include "oauth1client.h"
#include "queryconfig.h"
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

class HttpClient :public QObject, public IDataSource
{
    Q_OBJECT
public:
    HttpClient();
    ~HttpClient();

    // IDataSource interface
    bool connect(const QString &args) override;
    void disconnect() override;
    bool isConnected() override;
    QJsonDocument query(const QString &args) override;
    bool update(const QString &args, QJsonDocument data) override;
private Q_SLOTS:
    void onReplyFinished();
    void onReplyError();
    void onRequireAuth(QNetworkReply *reply, QAuthenticator *authenticator);
private:
    QNetworkAccessManager network;
    QHttpHeaders headers;
    QNetworkCookieJar cookies;
    QString baseUrl;
    HttpSetting setting;
    AuthConfig authConfig;
    OAuth2Client *oauth2Client{nullptr};
    OAuth1Client *oauth1Client{nullptr};

    // 授权处理方法
    void applyAPIKeyAuth(const QJsonObject &config, QHttpHeaders &authHeaders, QUrlQuery &urlQuery);
    void applyBearerTokenAuth(const QJsonObject &config, QHttpHeaders &authHeaders);
    void applyJWTAuth(const JWTConfig &config, QHttpHeaders &authHeaders);
    void applyBasicAuth(const QJsonObject &config, QHttpHeaders &authHeaders);
    void handleBasicAuthChallenge(const QJsonObject &config, QAuthenticator *authenticator);
    void handleDigestAuthChallenge(const DigestAuthConfig &config, QAuthenticator *authenticator);
    void handleNTLMChallenge(const NTLMConfig &config, QAuthenticator *authenticator);
    void handleSPNEGOChallenge(const SPNEGOConfig &config, QAuthenticator *authenticator);
    void applyOAuth1Auth(QHttpHeaders &authHeaders, QUrl &urlQuery, const QString &method);
    void applyOAuth2Auth(QHttpHeaders &authHeaders, QUrlQuery &urlQuery);
    QHttpHeaders parseAuth(QUrl &url, QueryMethod method);    
    QHttpHeaders config2Header(const QList<HttpHeaderItem> &config);
    QJsonDocument parseJson(const QByteArray &data);
};

#endif // HTTPCLIENT_H
