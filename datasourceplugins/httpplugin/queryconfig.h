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
#ifndef QUERYCONFIG_H
#define QUERYCONFIG_H

#include "httpbody.h"
#include "httpheader.h"
#include "keyvalue.h"
#include "serializable.h"

enum class QueryMethod{GET, POST, PUT, DELETE, PATCH};
class QueryConfig : public Serializable
{
    Q_GADGET
    SERIALIZE(QueryConfig)
public:
    QueryConfig(){}
    static QList<QPair<QString, QueryMethod>> queryMethodList(){
        return {{"GET", QueryMethod::GET}, {"POST", QueryMethod::POST}};
    }
    static QueryConfig fromJson(const QString &json);
    QString toJson();
private:
    // 请求方法
    QueryMethod method;
    // 请求地址
    QString url;
    // 请求参数配置
    QList<KeyValue> queryParams;
    // http header 配置
    QList<HttpHeaderItem> headers;
    // body 内容
    HttpBody body;

    JSONFIELD(method, Method)
    JSONFIELD(url, Url)
    JSONFIELD(queryParams, QueryParams)
    JSONFIELD(headers, Headers)
    JSONFIELD(body, Body)
};

#endif // QUERYCONFIG_H
