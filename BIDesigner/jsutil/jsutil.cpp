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
#include "jsutil.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
 #include <QJSValueIterator>
#include <QJSEngine>
#include <QJsonDocument>

JSUtil::JSUtil() {
    engine = new QJSEngine();
}

JSUtil *JSUtil::instance()
{
    static JSUtil *instance = new JSUtil();
    return instance;
}

QJSValue JSUtil::evaluate(const QString &jsCode)
{
    QJSEngine js;
    return js.evaluate(jsCode);
}

QJSValue JSUtil::evaluate(const QString &jsFunc, QJSValueList args)
{
    auto func = engine->evaluate(jsFunc);
    // 检查是否出错
    if (func.isError()) {
        return func;
    }
    // 执行js方法，处理结果
    QJSValue result = func.call(args);
    return func.call(args);
}

QJSValue JSUtil::jsonDocToJSValue(const QJsonDocument &doc)
{
    if (doc.isObject()) {
        return jsonObjectToJSValue(doc.object());
    }else if(doc.isArray()){
        return jsonArrayToJSValue(doc.array());
    }else{
        return QString::fromUtf8(doc.toJson());
    }
}

QJSValue JSUtil::jsonValueToJSValue(const QJsonValue &jsonValue)
{
    return engine->toScriptValue(jsonValue);
    // if (jsonValue.isObject()) {
    //     // 如果是对象，递归转换
    //     return jsonObjectToJSValue(jsonValue.toObject());
    // } else if (jsonValue.isArray()) {
    //     // 如果是数组，递归转换
    //     return jsonArrayToJSValue(jsonValue.toArray());
    // } else if (jsonValue.isDouble()) {
    //     // 注意：JSON中的数字都是double，可根据需要转为int
    //     QJsonValue::Type type = jsonValue.type();
    //     // 判断是否为整数
    //     double d = jsonValue.toDouble();
    //     if (type == QJsonValue::Type::Double && std::floor(d) == d) {
    //         // 可以转为整数，但注意JS中所有数字都是双精度
    //         return QJSValue((int)d);
    //     }
    //     return QJSValue(d);
    // } else if (jsonValue.isString()) {
    //     return QJSValue(jsonValue.toString());
    // } else if (jsonValue.isBool()) {
    //     return QJSValue(jsonValue.toBool());
    // } else if (jsonValue.isNull()) {
    //     return QJSValue(QJSValue::NullValue);
    // } else {
    //     // Undefined
    //     return QJSValue(QJSValue::UndefinedValue);
    // }
}

QJSValue JSUtil::jsonObjectToJSValue(const QJsonObject &jsonObject)
{
    return engine->toScriptValue(jsonObject);
    // QJSValue jsObject = engine->newObject();
    // for (auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it) {
    //     // 为对象的每个键设置转换后的值
    //     jsObject.setProperty(it.key(), jsonValueToJSValue(it.value()));
    // }
    // return jsObject;
}

QJSValue JSUtil::jsonArrayToJSValue(const QJsonArray &jsonArray)
{
    return engine->toScriptValue(jsonArray);
    // QJSValue jsArray = engine->newArray(jsonArray.size());
    // for (int i = 0; i < jsonArray.size(); ++i) {
    //     // 为数组的每个索引设置转换后的值
    //     jsArray.setProperty(i, jsonValueToJSValue(jsonArray.at(i)));
    // }
    // return jsArray;
}

QJsonValue JSUtil::jsValueToJsonValue(const QJSValue &jsValue)
{
    return engine->fromScriptValue<QJsonValue>(jsValue);
//     if (jsValue.isObject()) {
//         // 如果是对象，递归转换
//         return jsValueToJsonObject(jsValue);
//     } else if (jsValue.isArray()) {
//         // 如果是数组，递归转换
//         return jsValueToJsonArray(jsValue);
//     } else if (jsValue.isNumber()) {
//         auto d = jsValue.toNumber();
//         // 判断是否为整数
//         if (qFloor(d) == d) {
//             // 可以转为整数，但注意JS中所有数字都是双精度
//             return QJsonValue((int)d);
//         }
//         return QJsonValue(d);
//     } else if (jsValue.isBool()) {
//         return QJsonValue(jsValue.toBool());
//     } else if (jsValue.isDate()) {
//         return QJsonValue::fromVariant(jsValue.toDateTime());
//     } else if (jsValue.isString() || jsValue.isUrl() || jsValue.isRegExp() ||
//                jsValue.isCallable() || jsValue.isError()) {
//         return QJsonValue(jsValue.toString());
//     } else if (jsValue.isNull()) {
//         return QJsonValue(QJsonValue::Null);
//     } else {
//         // Undefined
//         return QJsonValue(QJsonValue::Undefined);
//     }
}

QJsonObject JSUtil::jsValueToJsonObject(const QJSValue &jsonValue)
{
    QJsonObject obj;
    QJSValueIterator it(jsonValue);
    while (it.hasNext()) {
        it.next();qDebug() << __FUNCTION__ << it.name();
        obj[it.name()] = jsValueToJsonValue(it.value());
    }
    return obj;
}

QJsonArray JSUtil::jsValueToJsonArray(const QJSValue &jsValue)
{
    QJsonArray array;
    const int length = jsValue.property("length").toInt();
    for (int i = 0; i < length; ++i) {
        array.append(jsValueToJsonValue(jsValue.property(i)));
    }
    return array;
}

QString JSUtil::JSValueToString(const QJSValue &jsValue)
{
    QJsonDocument doc;
    auto obj = jsValueToJsonValue(jsValue);
    if (obj.isArray()) {
        doc.setArray(obj.toArray());
    }else if(obj.isObject()){
        doc.setObject(obj.toObject());
    }else if(obj.isString()){
        return obj.toString();
    }else if(obj.isBool()){
        return obj.toBool(true)?"true":"false";
    }else if(obj.isDouble()){
        return QString{"%1"}.arg(obj.toDouble());
    }else if(obj.isNull()){
        return "null";
    }else if(obj.isUndefined()){
        return "undefined";
    }
    return doc.toJson();
}
