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

#include "easyjsonimpl.h"
#include "variantutil.h"

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QColor>
#include <QJsonArray>
#include <QLineF>
#include <QPointF>
#include <QRectF>
#include <QSizeF>
#include <QJsonDocument>

#ifdef EASY_JSON_DEFAULT
EasyJson *EASYJSON = new EasyJsonImpl();
#endif

EasyJsonImpl::EasyJsonImpl() {}

QJsonObject EasyJsonImpl::toJson(const Serializable &obj)
{
    QJsonObject json;
    Serializable *objPtr = const_cast<Serializable*>(&obj);

    const QMetaObject *metaInfo = obj.getMetaInfo();//obj.metaObject();
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = objPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
                QString alias = jsonInfo["alias"];
                QVariant value = objPtr->getValue(jsonInfo["name"]);
                QMetaType type = value.metaType();
                // 对 Serializable 子类递归转换
                if (type.id() > QMetaType::User) {
                    auto valueMeta = type.metaObject();
                    auto classInfo = valueMeta->classInfo(valueMeta->indexOfClassInfo("base"));
                    if (QString("Serializable").compare(classInfo.value()) == 0) {
                        json.insert(alias, toJson(*reinterpret_cast<const Serializable*>(value.constData())));
                        continue;
                    }
                }
                // 转为json对象
                json.insert(alias, VariantUtil::toJsonValue(value));
            }
        }

        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return json;
}

QString EasyJsonImpl::toJsonString(const Serializable &obj)
{
    QJsonObject json = toJson(obj);
    QJsonDocument doc(json);
    return QString(doc.toJson(QJsonDocument::Compact));
}

QVariant EasyJsonImpl::parseObject(QJsonObject json, QMetaType typeName)
{
    const QMetaObject *metaInfo = typeName.metaObject();
    QVariant result(typeName);
    Serializable *obj = reinterpret_cast<Serializable*>(result.data());
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo = obj->invokeMethod<QMap<QString, QString>>(metaInfo, i);

                QMetaProperty fieldType = metaInfo->property(metaInfo->indexOfProperty(jsonInfo["name"].toLocal8Bit()));
                QByteArray fieldName = jsonInfo["name"].toLocal8Bit();
                if (!json.contains(jsonInfo["alias"])){
                    continue;
                }
                QJsonValueRef jsonValue = json[jsonInfo["alias"]];
                // 对 Serializable 子类递归解析
                if (fieldType.metaType().id() > QMetaType::User) {
                    auto valueMeta = fieldType.metaType().metaObject();
                    auto classInfo = valueMeta->classInfo(valueMeta->indexOfClassInfo("base"));
                    if (QString("Serializable").compare(classInfo.value()) == 0) {
                        obj->setValue(fieldName,
                                         parseObject(jsonValue.toObject(), fieldType.metaType()));
                        continue;
                    }
                }
                // 设置字段值
                obj->setValue(fieldName,
                              VariantUtil::fromJsonValue(jsonValue, fieldType.metaType()));
            }
        }
        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return result;
}

QVariant EasyJsonImpl::parseObject(QString json, QMetaType typeName)
{
    if (json.isEmpty()) {
        return QVariant(typeName);
    }
    QJsonDocument doc = QJsonDocument::fromJson(json.toLocal8Bit());
    return parseObject(doc.object(), typeName);
}
