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

#include "serializable.h"
Serializable::Serializable()
{
    QUuid uid = QUuid::createUuid();
    id = uid.toString(QUuid::WithoutBraces);
}

Serializable::~Serializable()
{}

bool Serializable::isSubClass(QMetaType type)
{
    auto meta = type.metaObject();
    int infoIndex = meta->indexOfClassInfo("base");
    bool isSubClass = false;
    if (infoIndex >= 0) {
        auto base = meta->classInfo(infoIndex).value();
        if (QString("Serializable").compare(base) == 0) {
            isSubClass = true;
        }
    }
    return isSubClass;
}

void Serializable::copy(const Serializable &from, Serializable &to)
{
    auto fromMeta = from.getMetaInfo();
    auto toMeta = to.getMetaInfo();
    if (QString(fromMeta->className()).compare(
            toMeta->className()) != 0){
        return;
    }
    do{
        int count = fromMeta->methodCount();
        for(int i=0; i< count; i++){
            if (QString(fromMeta->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = invokeMethod<QMap<QString, QString>>(fromMeta, i);
                QVariant value = const_cast<Serializable&>(from).getValue(jsonInfo["name"]);
                to.setValue(jsonInfo["name"], value);
            }
        }
        fromMeta = fromMeta->superClass();
    }while(fromMeta != nullptr);
}

void Serializable::copy(const Serializable &from){
    auto f = const_cast<Serializable*>(&from);
    Serializable *t = this;
    auto fromMeta = f->getMetaInfo();
    auto toMeta = t->getMetaInfo();
    if (QString(fromMeta->className()).compare(
            toMeta->className()) != 0){
        return;
    }
    do{
        int count = fromMeta->methodCount();
        QMap<QString, QMetaMethod> methodMap;
        for(int i=0; i< count; i++){
            methodMap[fromMeta->method(i).name()] = fromMeta->method(i);
        }
        for(int i=0; i< count; i++){
            if (QString(fromMeta->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = invokeMethod<QMap<QString, QString>>(fromMeta, i);
                QVariant value = const_cast<Serializable&>(from).getValue(jsonInfo["name"]);
                setValue(jsonInfo["name"], value);
            }
        }
        fromMeta = fromMeta->superClass();
    }while(fromMeta != nullptr);
}

QString Serializable::hashCode()
{
    return id;
}

bool Serializable::equals(Serializable &obj)
{
    if (hashCode() != obj.hashCode()) {
        return false;
    }
    auto metaInfo = getMetaInfo();
    if (QString(metaInfo->className()).compare(
            obj.getMetaInfo()->className()) != 0){
        return false;
    }
    if (toString() != obj.toString()){
        return false;
    }
    return true;
}

bool Serializable::operator==(Serializable &obj)
{
    return equals(obj);
}

QString Serializable::toString()
{
    QString fieldStr;
    QTextStream stream(&fieldStr);
    const QMetaObject *metaInfo = getMetaInfo();
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = invokeMethod<QMap<QString, QString>>(metaInfo, i);
                QVariant value = getValue(jsonInfo["name"]);
                bool isObject = Serializable::isSubClass(value.metaType());
                QString str;
                if (isObject) {
                    // Serializable子类递归转为字符串
                    str = reinterpret_cast<Serializable*>(
                              const_cast<void*>(value.constData())
                              )->toString();
                } else {
                    // 普通QVariant，通过工具类转换
                    str = VariantUtil::toString(value);
                }
                stream << jsonInfo["name"] << ":"
                       << (isObject?"{":"")
                       << str
                       << (isObject?"}":"")
                       << ";";
            }
        }

        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return fieldStr;
}

void Serializable::setValue(QString fieldName, QVariant value)
{
    const QMetaObject *metaInfo = getMetaInfo();
    int index = metaInfo->indexOfProperty(fieldName.toLocal8Bit());
    QMetaProperty field = metaInfo->property(index);

    QObject *objPtr = reinterpret_cast<QObject*>(this);
    field.write(objPtr, value);
}

QVariant Serializable::getValue(QString fieldName)
{
    const QMetaObject *metaInfo = getMetaInfo();
    int index = metaInfo->indexOfProperty(fieldName.toLocal8Bit().constData());
    QMetaProperty field = metaInfo->property(index);
    QObject *objPtr = reinterpret_cast<QObject*>(this);
    return field.read(objPtr);
}

template<typename T>
T Serializable::invokeMethod(const QMetaObject *metaInfo, int index){
    T result;
    void** voidPtr = new void*();
    *voidPtr = reinterpret_cast<void *>(&result);
    metaInfo->static_metacall(QMetaObject::InvokeMetaMethod, index, voidPtr);
    delete voidPtr;
    return result;
}

QDataStream &operator<<(QDataStream &stream, const Serializable &data){
    Serializable *dataPtr = const_cast<Serializable *>(&data);
    const QMetaObject *metaInfo = data.getMetaInfo();
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
                QVariant value = dataPtr->getValue(jsonInfo["name"]);
                QMetaProperty fieldType = metaInfo->property(metaInfo->indexOfProperty(jsonInfo["name"].toLocal8Bit()));
                if (fieldType.metaType().id() == QMetaType::QVariant){
                    stream << value.metaType().id();
                }
                stream << value;
            }
        }
        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Serializable &data){
    Serializable *dataPtr = const_cast<Serializable *>(&data);
    const QMetaObject *metaInfo = data.getMetaInfo();
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
                QMetaProperty fieldType = metaInfo->property(metaInfo->indexOfProperty(jsonInfo["name"].toLocal8Bit()));
                QMetaType fieldMeta = fieldType.metaType();
                if (fieldMeta.id() == QMetaType::QVariant) {
                    int typeId = 0;
                    stream >> typeId;
                    fieldMeta = QMetaType(typeId);
                }
                QVariant value(fieldMeta);
                stream >> value;
                dataPtr->setValue(jsonInfo["name"], value);
            }
        }
        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return stream;
}

QDebug operator<<(QDebug dbg, const Serializable &data){
    Serializable *dataPtr = const_cast<Serializable *>(&data);
    const QMetaObject *metaInfo = data.getMetaInfo();
    auto reg = QRegularExpression("QVariant\\([^,]+, (.+)\\)$");
    do{
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            if (QString(metaInfo->method(i).tag()).compare("JSON_FLAG") == 0){
                QMap<QString, QString> jsonInfo;
                jsonInfo = dataPtr->invokeMethod<QMap<QString, QString>>(metaInfo, i);
                QVariant value = dataPtr->getValue(jsonInfo["name"]);
                QString str = dbg.toString(value);
                str = str.replace(reg, "\\1");
                dbg << jsonInfo["alias"] << ":"
                    << str << "; ";
            }
        }
        metaInfo = metaInfo->superClass();
    }while(metaInfo != nullptr);
    return dbg;
}
