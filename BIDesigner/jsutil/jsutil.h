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
#ifndef JSUTIL_H
#define JSUTIL_H

#include "qjsonvalue.h"
#include "qjsvalue.h"

#include <QPointer>
class JSUtil
{
    JSUtil();
public:
    static JSUtil *instance();
    QJSValue evaluate(const QString &jsCode);
    QJSValue evaluate(const QString &jsFunc, QJSValueList args);

    QJSValue jsonDocToJSValue(const QJsonDocument &doc);
    QJSValue jsonValueToJSValue(const QJsonValue &jsonValue);
    QJSValue jsonObjectToJSValue(const QJsonObject &jsonObject);
    QJSValue jsonArrayToJSValue(const QJsonArray &jsonArray);

    QJsonValue jsValueToJsonValue(const QJSValue &jsValue);
    QJsonObject jsValueToJsonObject(const QJSValue &jsValue);
    QJsonArray jsValueToJsonArray(const QJSValue &jsValue);

    QString JSValueToString(const QJSValue &jsValue);
private:
    QPointer<QJSEngine> engine;
};

#endif // JSUTIL_H
