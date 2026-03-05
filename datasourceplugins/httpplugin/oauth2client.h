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
#ifndef OAUTH2CLIENT_H
#define OAUTH2CLIENT_H

#include <QNetworkAccessManager>
#include <QHttpHeaders>
#include <QJsonObject>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDateTime>
#include <QObject>
#include "auth2config.h"

/**
 * @brief OAuth2客户端类，负责OAuth2授权流程和token管理
 */
class OAuth2Client : public QObject
{
    Q_OBJECT
public:
    explicit OAuth2Client(QObject *parent = nullptr);
    ~OAuth2Client();

    /**
     * @brief 设置OAuth2配置
     * @param config OAuth2配置对象
     */
    void setConfig(const Auth2Config &config);

    /**
     * @brief 检查token是否有效
     * @return true表示有效，false表示无效或不存在
     */
    bool isTokenValid() const;

    /**
     * @brief 刷新access token
     * @return true表示刷新成功，false表示刷新失败
     */
    bool refreshToken();

    /**
     * @brief 获取access token
     * @return access token字符串
     */
    QString getAccessToken() const;

    /**
     * @brief 获取ID token
     * @return ID token字符串
     */
    QString getIdToken() const;

    /**
     * @brief 应用OAuth2授权到请求头或URL参数
     * @param headers 请求头
     * @param urlQuery URL查询参数
     */
    void applyAuth(QHttpHeaders &headers, QUrlQuery &urlQuery);

private:
    Auth2Config oauth2Config;
    QString cachedAccessToken;
    QString cachedIdToken;
    qint64 tokenExpireTime;
    QNetworkAccessManager network;

    /**
     * @brief 使用密码模式获取token
     * @return true表示成功，false表示失败
     */
    bool requestTokenWithPassword();

    /**
     * @brief 使用客户端凭证模式获取token
     * @return true表示成功，false表示失败
     */
    bool requestTokenWithClientCredentials();
};

#endif // OAUTH2CLIENT_H
