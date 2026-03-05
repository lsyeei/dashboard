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
#include "oauth1client.h"

#include <QRandomGenerator>
#include <type_traits>
#include <QMessageAuthenticationCode>
#include <QCryptographicHash>

OAuth1Client::OAuth1Client(QObject *parent)
    : QObject(parent)
{
}

OAuth1Client::~OAuth1Client()
{
}

void OAuth1Client::setConfig(const Auth1Config &config)
{
    oauth1Config = config;
}

QString OAuth1Client::generateNonce() const
{
    QByteArray randomData;
    randomData.resize(16);
    for (int i = 0; i < 16; ++i) {
        randomData[i] = static_cast<char>(QRandomGenerator::global()->generate());
    }
    return randomData.toBase64().left(16);
}

QString OAuth1Client::generateTimestamp() const
{
    return QString::number(QDateTime::currentSecsSinceEpoch());
}

QString OAuth1Client::percentEncode(const QString &value) const
{
    return QString::fromUtf8(QUrl::toPercentEncoding(value));
}

QString OAuth1Client::normalizeUrl(const QUrl &url) const
{
    QString scheme = url.scheme().toLower();
    QString host = url.host().toLower();
    int port = url.port();

    QString normalizedUrl = scheme + "://" + host;

    if (port > 0) {
        int defaultPort = (scheme == "http") ? 80 : 443;
        if (port != defaultPort) {
            normalizedUrl += ":" + QString::number(port);
        }
    }

    normalizedUrl += url.path(QUrl::FullyEncoded);

    return normalizedUrl;
}

QString OAuth1Client::normalizeParameters(const QMap<QString, QString> &params) const
{
    QStringList encodedParams;

    for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
        QString key = percentEncode(it.key());
        QString value = percentEncode(it.value());
        encodedParams.append(key + "=" + value);
    }

    encodedParams.sort();

    return encodedParams.join("&");
}

QString OAuth1Client::generateBaseString(const QString &httpMethod, const QUrl &url, const QMap<QString, QString> &params) const
{
    QString normalizedMethod = httpMethod.toUpper();
    QString normalizedUrl = normalizeUrl(url);
    QString normalizedParams = normalizeParameters(params);

    return percentEncode(normalizedMethod) + "&" +
           percentEncode(normalizedUrl) + "&" +
           percentEncode(normalizedParams);
}

QString OAuth1Client::generateHMACSHA1Signature(const QString &baseString, const QString &key) const
{
    QByteArray keyBytes = key.toUtf8();
    QByteArray baseStringBytes = baseString.toUtf8();

    QByteArray hmac = QMessageAuthenticationCode::hash(baseStringBytes, keyBytes, QCryptographicHash::Sha1);

    return QString::fromUtf8(hmac.toBase64());
}

void OAuth1Client::applyAuth(QHttpHeaders &headers, QUrl &url, const QString &httpMethod)
{
    QString consumerKey = oauth1Config.getConsumerKey();
    QString consumerSecret = oauth1Config.getConsumerSecret();
    QString token = oauth1Config.getToken();
    QString tokenSecret = oauth1Config.getTokenSecret();
    AuthLocation location = oauth1Config.getLocation();

    // 构建签名密钥
    QString signingKey = percentEncode(consumerSecret) + "&";
    if (!tokenSecret.isEmpty()) {
        signingKey += percentEncode(tokenSecret);
    }

    // 构建OAuth参数
    QString oauthTimestamp = generateTimestamp();
    QString oauthNonce = generateNonce();

    QMap<QString, QString> oauthParams;
    oauthParams["oauth_consumer_key"] = consumerKey;
    oauthParams["oauth_token"] = token;
    oauthParams["oauth_signature_method"] = "HMAC-SHA1";
    oauthParams["oauth_timestamp"] = oauthTimestamp;
    oauthParams["oauth_nonce"] = oauthNonce;
    oauthParams["oauth_version"] = "1.0";

    // 将URL查询参数和OAuth参数合并用于签名
    auto urlQuery = QUrlQuery(url.query());
    QMap<QString, QString> allParams = oauthParams;
    QList<QPair<QString, QString>> queryItems = urlQuery.queryItems();
    foreach (const auto &item, queryItems) {
        allParams[item.first] = item.second;
    }

    // 生成签名
    QString baseString = generateBaseString(httpMethod, url, allParams);
    QString signature = generateHMACSHA1Signature(baseString, signingKey);
    oauthParams["oauth_signature"] = signature;

    // 根据location参数决定将OAuth参数放在请求头还是URL查询中
    if (location == AuthLocation::Header) {
        // 构建OAuth Authorization头
        QStringList headerParts;
        for (auto it = oauthParams.constBegin(); it != oauthParams.constEnd(); ++it) {
            headerParts.append(percentEncode(it.key()) + "=\"" + percentEncode(it.value()) + "\"");
        }
        QString authHeader = "OAuth " + headerParts.join(", ");
        headers.append(QHttpHeaders::WellKnownHeader::Authorization, authHeader.toUtf8());
    } else {
        // 将OAuth参数添加到URL查询中
        for (auto it = oauthParams.constBegin(); it != oauthParams.constEnd(); ++it) {
            urlQuery.addQueryItem(it.key(), it.value());
        }
    }
    url.setQuery(urlQuery);
}
