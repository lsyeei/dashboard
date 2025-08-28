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

#pragma once
#ifndef PROPERTYHELPER_H
#define PROPERTYHELPER_H
#include <QObject>
/*
 * 自动生成类的成员变量以及对应的属性, 主要有是三种
    1.AUTO_PROPERTY： 包含了该变量的所有属性，读/写/改变信号
    2.READONLY_PROPERTY: 仅读，没有写方法和信号
    3.READ_PROPERTY: 仅读，但是包含了属性改变信号
 *
 * fieldType: 变量类型，如 int, QString, std::string
 * fieldName: 变量名字
 *
*/
#define AUTO_PROPERTY(fieldType, fieldName) \
Q_PROPERTY(fieldType fieldName READ get##fieldName WRITE set##fieldName NOTIFY fieldName##Changed ) \
    public: \
    inline fieldType get##fieldName() const { return fieldName; } \
    inline void set##fieldName(const fieldType& value) { \
        if (fieldName == value)  return; \
        fieldName = value; \
        emit fieldName##Changed(value); \
    } \
    Q_SIGNAL void fieldName##Changed(const fieldType &value);\
    private: \
    fieldType fieldName; \

#define READONLY_PROPERTY(fieldType, fieldName) \
Q_PROPERTY(fieldType fieldName READ get##fieldName CONSTANT ) \
    public: \
    inline fieldType get##fieldName() const { return fieldName; } \
    private: \
    fieldType fieldName;

#define READ_PROPERTY(fieldType, fieldName) \
Q_PROPERTY(fieldType fieldName READ get##fieldName NOTIFY fieldName##Changed) \
    public: \
    inline fieldType get##fieldName() const { return fieldName; } \
    Q_SIGNAL void fieldName##Changed(const fieldType &value);\
    private: \
    fieldType fieldName;

#define STREAM_OUT \
template<typename T> \
friend QDataStream &operator<<(QDataStream &stream, const T &data) \
{ \
    const QMetaObject *metaInfo = data.metaObject(); \
    QString exclude{"objectName"}; \
    for(int i = 0; i < metaInfo->propertyCount(); i++) \
    { \
        auto fieldName = metaInfo->property(i).name(); \
        if (exclude.compare(fieldName) == 0){ \
            continue; \
        } \
        stream << data.property(fieldName); \
    } \
    return stream; \
}

#define STREAM_IN \
template<class T> \
friend QDataStream &operator>>(QDataStream &stream, T &data) \
{ \
    const QMetaObject *metaInfo = data.metaObject(); \
    QString exclude{"objectName"};\
    for(int i = 0; i < metaInfo->propertyCount(); i++)\
    {\
        QString fieldName = metaInfo->property(i).name();\
        if (exclude.compare(fieldName) == 0){\
            continue;\
        }\
        QMetaType fieldType = metaInfo->property(i).metaType();\
        QVariant value(fieldType);\
        stream >> value;\
        data.setProperty(fieldName.toLocal8Bit().data(), value);\
    }\
    return stream;\
}

#define DEBUG_OUT \
template<class T> \
friend QDebug operator<<(QDebug dbg, const T &data) \
{ \
    const QMetaObject *metaInfo = data.metaObject(); \
    QString exclude{"objectName"};\
    for(int i = 0; i < metaInfo->propertyCount(); i++)\
    {\
        auto fieldName = metaInfo->property(i).name();\
        if (exclude.compare(fieldName) == 0){\
            continue;\
        }\
        dbg << fieldName << ":" << data.property(fieldName);\
    }\
    return dbg;\
}

#endif // PROPERTYHELPER_H
