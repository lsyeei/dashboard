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
#ifndef HTTPCONFIG_H
#define HTTPCONFIG_H

#include "authdef.h"
#include "keyvalue.h"
#include "serializable.h"
#include "httpheader.h"

// http 版本
enum class HttpVersion{V1, V2};

/**
 * @brief The HttpSetting class
 * HTTP 连接设置
 */
class HttpSetting : public Serializable
{
    Q_GADGET
    SERIALIZE(HttpSetting)
public:
    HttpSetting(){version = HttpVersion::V2;timeout=500;redirectPolicy=-1;}
    static QList<QPair<QString,HttpVersion>> versionList(){
        return {{"version 1.x", HttpVersion::V1}, {"version 2.x", HttpVersion::V2}};
    }
private:
    // http 版本
    HttpVersion version;
    // 连接超时
    qint32 timeout;
    // 重定向策略
    qint32 redirectPolicy;

    JSONFIELD(version, Version)
    JSONFIELD(timeout, Timeout)
    JSONFIELD(redirectPolicy, RedirectPolicy)
};

/**
 * @brief The HttpConfig class
 * HTTP 数据源连接配置
 */
class HttpConfig : public Serializable
{
    Q_GADGET
    SERIALIZE(HttpConfig)
public:
    HttpConfig(){}
    static HttpConfig fromJson(const QString &json);
    QString toJson();
private:
    // http 地址
    QString url;
    // 授权配置
    AuthConfig authConfig;
    // cookie 配置
    QList<KeyValue> cookies;
    // http header 配置
    QList<HttpHeaderItem> headers;
    // http 其它设置
    HttpSetting setting;

    JSONFIELD(url, URL)
    JSONFIELD(authConfig, AuthConfig)
    JSONFIELD(cookies, Cookies)
    JSONFIELD(headers, headers)
    JSONFIELD(setting, Setting)
};

#endif // HTTPCONFIG_H
