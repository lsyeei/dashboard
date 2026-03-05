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
#ifndef OAUTH1CLIENT_H
#define OAUTH1CLIENT_H

#include <QNetworkAccessManager>
#include <QHttpHeaders>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDateTime>
#include <QCryptographicHash>
#include <QByteArray>
#include <QUrl>
#include "auth1config.h"
#include <QObject>

/**
 * @brief OAuth1客户端类，负责OAuth1授权流程和签名计算
 */
class OAuth1Client : public QObject
{
    Q_OBJECT
public:
    explicit OAuth1Client(QObject *parent = nullptr);
    ~OAuth1Client();

    /**
     * @brief 设置OAuth1配置
     * @param config OAuth1配置对象
     */
    void setConfig(const Auth1Config &config);

    /**
     * @brief 应用OAuth1授权到请求头或URL参数
     * @param headers 请求头
     * @param url 完整的请求URL
     * @param httpMethod HTTP方法（GET、POST等）
     */
    void applyAuth(QHttpHeaders &headers, QUrl &url,  const QString &httpMethod);

private:
    Auth1Config oauth1Config;

    /**
     * @brief 生成随机nonce
     * @return nonce字符串
     */
    QString generateNonce() const;

    /**
     * @brief 生成时间戳
     * @return 时间戳字符串
     */
    QString generateTimestamp() const;

    /**
     * @brief 生成HMAC-SHA1签名
     * @param baseString 基础字符串
     * @param key 签名密钥
     * @return Base64编码的签名
     */
    QString generateHMACSHA1Signature(const QString &baseString, const QString &key) const;

    /**
     * @brief 生成基础字符串
     * @param httpMethod HTTP方法
     * @param url 请求URL
     * @param params 参数
     * @return 基础字符串
     */
    QString generateBaseString(const QString &httpMethod, const QUrl &url, const QMap<QString, QString> &params) const;

    /**
     * @brief 对参数进行编码和排序
     * @param params 参数map
     * @return 编码并排序后的参数字符串
     */
    QString normalizeParameters(const QMap<QString, QString> &params) const;

    /**
     * @brief 对URL进行编码
     * @param url URL
     * @return 编码后的URL
     */
    QString normalizeUrl(const QUrl &url) const;

    /**
     * @brief 百分比编码
     * @param value 待编码的字符串
     * @return 编码后的字符串
     */
    QString percentEncode(const QString &value) const;
};

#endif // OAUTH1CLIENT_H
