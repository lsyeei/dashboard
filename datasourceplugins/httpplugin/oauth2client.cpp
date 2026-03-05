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
#include "oauth2client.h"
#include "auth2config.h"

OAuth2Client::OAuth2Client(QObject *parent)
    : QObject(parent)
    , tokenExpireTime(0)
{
}

OAuth2Client::~OAuth2Client()
{
}

void OAuth2Client::setConfig(const Auth2Config &config)
{
    oauth2Config = config;
}

bool OAuth2Client::isTokenValid() const
{
    if (cachedAccessToken.isEmpty()) {
        return false;
    }
    // 提前5分钟判断过期，避免临界时间问题
    qint64 currentTime = QDateTime::currentSecsSinceEpoch();
    return tokenExpireTime > (currentTime + 300);
}

bool OAuth2Client::refreshToken()
{
    AuthModel authModel = oauth2Config.getAuthModel();

    switch (authModel) {
    case AuthModel::Credentials_Password:
        return requestTokenWithPassword();
    case AuthModel::Credentials_Client:
        return requestTokenWithClientCredentials();
    case AuthModel::Code:
    case AuthModel::Code_PKCE:
    case AuthModel::Implicit:
    default:
        qWarning() << "OAuth2 authModel not supported for automatic token refresh:" << static_cast<int>(authModel);
        qWarning() << "Please use UI to obtain token manually or implement custom auth flow";
        return false;
    }
}

QString OAuth2Client::getAccessToken() const
{
    return cachedAccessToken;
}

QString OAuth2Client::getIdToken() const
{
    return cachedIdToken;
}

void OAuth2Client::applyAuth(QHttpHeaders &headers, QUrlQuery &urlQuery)
{
    // 检查token是否有效，如无效则刷新
    if (!isTokenValid()) {
        if (!refreshToken()) {
            qWarning() << "Failed to refresh OAuth2 token";
            return;
        }
    }

    // 使用缓存的token
    AuthLocation location = oauth2Config.getLocation();
    TokenType tokenType = oauth2Config.getTokenType();
    QString token = (tokenType == TokenType::Access) ? cachedAccessToken : cachedIdToken;

    if (location == AuthLocation::Header) {
        // Header 方式
        headers.append(QHttpHeaders::WellKnownHeader::Authorization,
                      QString("Bearer %1").arg(token).toUtf8());
    } else {
        // Query 参数方式
        urlQuery.addQueryItem("access_token", cachedAccessToken);
    }
}

bool OAuth2Client::requestTokenWithPassword()
{
    QString accessTokenUrl = oauth2Config.getAccessTokenUrl();
    QString clientId = oauth2Config.getClientId();
    QString clientSecret = oauth2Config.getClientSecret();
    QString userName = oauth2Config.getUserName();
    QString password = oauth2Config.getPassword();

    if (accessTokenUrl.isEmpty() || clientId.isEmpty() || userName.isEmpty() || password.isEmpty()) {
        qWarning() << "OAuth2 Password Credentials mode: incomplete configuration";
        return false;
    }

    QNetworkRequest tokenRequest;
    tokenRequest.setUrl(QUrl(accessTokenUrl));
    tokenRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray tokenData = QString("grant_type=password&username=%1&password=%2&client_id=%3")
                          .arg(userName).arg(password).arg(clientId).toUtf8();
    if (!clientSecret.isEmpty()) {
        tokenData += QString("&client_secret=%1").arg(clientSecret).toUtf8();
    }

    QNetworkReply *tokenReply = network.post(tokenRequest, tokenData);

    QEventLoop tokenLoop;
    QObject::connect(tokenReply, &QNetworkReply::finished, &tokenLoop, &QEventLoop::quit);
    tokenLoop.exec();

    bool success = false;
    if (tokenReply->error() == QNetworkReply::NoError) {
        QByteArray response = tokenReply->readAll();
        QJsonParseError parseError;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error == QJsonParseError::NoError) {
            QJsonObject tokenResponse = jsonResponse.object();
            cachedAccessToken = tokenResponse.value("access_token").toString();
            cachedIdToken = tokenResponse.value("id_token").toString();
            int expiresIn = tokenResponse.value("expires_in").toInt();

            if (!cachedAccessToken.isEmpty()) {
                tokenExpireTime = QDateTime::currentSecsSinceEpoch() + expiresIn - 300;
                success = true;
            } else {
                qWarning() << "OAuth2 token response missing access_token";
            }
        } else {
            qWarning() << "OAuth2 token response parse error:" << parseError.errorString();
        }
    } else {
        qWarning() << "OAuth2 token request error:" << tokenReply->errorString();
    }

    tokenReply->deleteLater();
    return success;
}

bool OAuth2Client::requestTokenWithClientCredentials()
{
    QString accessTokenUrl = oauth2Config.getAccessTokenUrl();
    QString clientId = oauth2Config.getClientId();
    QString clientSecret = oauth2Config.getClientSecret();

    if (accessTokenUrl.isEmpty() || clientId.isEmpty()) {
        qWarning() << "OAuth2 Client Credentials mode: incomplete configuration";
        return false;
    }

    QNetworkRequest tokenRequest;
    tokenRequest.setUrl(QUrl(accessTokenUrl));
    tokenRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray tokenData = QString("grant_type=client_credentials&client_id=%1")
                          .arg(clientId).toUtf8();
    if (!clientSecret.isEmpty()) {
        tokenData += QString("&client_secret=%1").arg(clientSecret).toUtf8();
    }

    QNetworkReply *tokenReply = network.post(tokenRequest, tokenData);

    QEventLoop tokenLoop;
    QObject::connect(tokenReply, &QNetworkReply::finished, &tokenLoop, &QEventLoop::quit);
    tokenLoop.exec();

    bool success = false;
    if (tokenReply->error() == QNetworkReply::NoError) {
        QByteArray response = tokenReply->readAll();
        QJsonParseError parseError;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response, &parseError);
        if (parseError.error == QJsonParseError::NoError) {
            QJsonObject tokenResponse = jsonResponse.object();
            cachedAccessToken = tokenResponse.value("access_token").toString();
            cachedIdToken = tokenResponse.value("id_token").toString();
            int expiresIn = tokenResponse.value("expires_in").toInt();

            if (!cachedAccessToken.isEmpty()) {
                tokenExpireTime = QDateTime::currentSecsSinceEpoch() + expiresIn - 300;
                success = true;
            } else {
                qWarning() << "OAuth2 token response missing access_token";
            }
        } else {
            qWarning() << "OAuth2 token response parse error:" << parseError.errorString();
        }
    } else {
        qWarning() << "OAuth2 token request error:" << tokenReply->errorString();
    }

    tokenReply->deleteLater();
    return success;
}
