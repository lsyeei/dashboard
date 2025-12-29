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
#ifndef ENTITY_H
#define ENTITY_H

#include <QMap>
#include <QMetaObject>
#include <QMetaMethod>
#include <QString>
#include <QObject>
#include <QList>
#include "qobjectdefs.h"
#include "serializable.h"

#ifndef Q_MOC_RUN
// define the tag text as empty, so the compiler doesn't see it
#  define MAP_FLAG
#  define GETTER_FLAG
#  define SETTER_FLAG
#endif

#define TABLE(tableName, ...) \
Q_CLASSINFO("base", "Entity") \
public:\
    QString getTableName() const override {return #tableName;}\
    QList<QString> getPrimaryKey() const override{\
        QString param(#__VA_ARGS__);\
        if(param.isEmpty()) return {"id"};\
        return param.split(',');\
    }\
protected:\
    inline const QMetaObject* getMetaInfo() const override{ \
        return &staticMetaObject; \
    }

#define TABLE_FIELD_4(field, colName, encodeFunc, decodeFunc)\
using __type_##field = decltype(field);\
Q_PROPERTY(__type_##field field READ get_##field WRITE set_##field) \
protected:\
    Q_INVOKABLE MAP_FLAG inline QList<QString> map_##field(){return {#colName, "ENCRYPT"};}\
public:\
    Q_INVOKABLE GETTER_FLAG __type_##field get_##field() const {return field;}\
    Q_INVOKABLE SETTER_FLAG void set_##field(const __type_##field &value){if (value != field) field = value;}\
private:\
    Q_INVOKABLE GETTER_FLAG __type_##field get_encrypt_##field() const {return encodeFunc(field);}\
    Q_INVOKABLE SETTER_FLAG void set_encrypt_##field(const __type_##field &value){auto v=decodeFunc(value);if (v != field) field = v;}

#define TABLE_FIELD_3(field, colName, attribute) TABLE_FIELD_2(field, colName, attribute)

#define TABLE_FIELD_2(field, colName, ...) \
using __type_##field = decltype(field);\
Q_PROPERTY(__type_##field field READ get_##field WRITE set_##field) \
protected:\
    Q_INVOKABLE MAP_FLAG inline QList<QString> map_##field(){return {#colName, #__VA_ARGS__};}\
public:\
    Q_INVOKABLE GETTER_FLAG __type_##field get_##field() const {return field;}\
    Q_INVOKABLE SETTER_FLAG void set_##field(const __type_##field &value){if (value != field) field = value;}

#define TABLE_FIELD_1 static_assert(false, "TABLE_FIELD minmum requires 2 arguments");
#define TABLE_FIELD(...) QT_OVERLOADED_MACRO(TABLE_FIELD, __VA_ARGS__)

class Entity:public Serializable
{
public:
    Entity(){};
    virtual QString getTableName() const = 0;
    virtual QList<QString> getPrimaryKey() const = 0;
    /**
     * @brief getFieldMap class field 到 table colum 的映射
     * @return key 为 class field，value 为 table colum
     */
    QMap<QString, QString> getFieldMap();
    QVariant getValueByColName(const QString &colName) const;
    void setValueByColName(const QString &colName, const QVariant &value);
    QString getColPropery(const QString &colName);
    template<typename T>
    T getValue(const QString &field) const;
    template<typename T>
    void setValue(const QString &field, const T &value);
    // void setValue(const QString &field, const QVariant &value);

protected:
    virtual const QMetaObject* getMetaInfo() const = 0;
private:
    QMetaMethod getMethod(const QString &methodName) const;
    // key:class field, value:table field
    QMap<QString, QString> fieldMap;
    // key:table field, value:table field property
    QMap<QString, QString> colProperty;
};

inline QMap<QString, QString> Entity::getFieldMap()
{
    if (fieldMap.isEmpty()) {
        auto metaInfo = getMetaInfo();
        int count = metaInfo->methodCount();
        for(int i=0; i< count; i++){
            QString tag(metaInfo->method(i).tag());
            if (tag.compare("MAP_FLAG") == 0){
                auto name = metaInfo->method(i).name();
                auto fieldName = name.split('_')[1];
                QList<QString> attr;
                if (metaInfo->method(i).invokeOnGadget(this, qReturnArg(attr))){
                    fieldMap[fieldName] = attr[0];
                    if (attr.count() > 1) {
                        colProperty[attr[0]] = attr[1];
                    }else{
                        colProperty[attr[0]] = "";
                    }
                }
            }
        }
    }
    return fieldMap;
}

inline QVariant Entity::getValueByColName(const QString &colName) const
{
    QString field{""};
    if (fieldMap.isEmpty()) {
        const_cast<Entity*>(this)->getFieldMap();
    }
    for(auto item = fieldMap.cbegin(); item != fieldMap.cend(); item++){
        if (item.value().compare(colName) == 0) {
            field = item.key();
            break;
        }
    }
    if (field.isEmpty()) {
        return QVariant();
    }
    auto property = const_cast<Entity*>(this)->getColPropery(colName);
    QString methodName{"get_%1()"};
    if (!property.isEmpty() && property.compare("ENCRYPT")==0) {
        methodName = "get_encrypt_%1()";qDebug() << __FUNCTION__ << field << methodName;
    }
    auto method = getMethod(methodName.arg(field));
    auto rtnType = method.returnMetaType();
    auto result = QVariant::fromMetaType(rtnType);
    QGenericReturnArgument arg(result.typeName(), result.data());
    method.invokeOnGadget(const_cast<Entity*>(this), arg);
    return result;
}

inline void Entity::setValueByColName(const QString &colName, const QVariant &value)
{
    QString field{""};
    if (fieldMap.isEmpty()) {
        const_cast<Entity*>(this)->getFieldMap();
    }
    for(auto item = fieldMap.cbegin(); item != fieldMap.cend(); item++){
        if (item.value().compare(colName) == 0) {
            field = item.key();
            break;
        }
    }
    if (field.isEmpty()) {
        return;
    }
    // 获取set方法
    auto property = const_cast<Entity*>(this)->getColPropery(colName);
    QString methodName{"set_%1(__type_%1)"};
    if (!property.isEmpty() && property.compare("ENCRYPT")==0) {
        methodName = "set_encrypt_%1(__type_%1)";
    }
    // 转换类型
    auto metaInfo = getMetaInfo();
    auto fieldMeta = metaInfo->property(metaInfo->indexOfProperty(field.toLocal8Bit()));
    auto fieldValue = QVariant::fromMetaType(fieldMeta.metaType());
    if (fieldMeta.typeId() != value.typeId()) {
        // qDebug() << __FUNCTION__ << colName << ":convert type " << value.typeName() << " to" << fieldMeta.typeName();
        if(!QMetaType::canConvert(value.metaType(), fieldMeta.metaType())){
            qWarning() << __FUNCTION__ << colName << ":can not convert "
                       << value.typeName() << " to" << fieldMeta.typeName();
            return;
        }
        if(!QMetaType::convert(value.metaType(), value.data(),
                                fieldMeta.metaType(),fieldValue.data())){
            qWarning() << __FUNCTION__ << colName << ": convert failed, from"
                       << fieldMeta.typeName() << " to" << value.typeName();
            return;
        }
    }else{
        fieldValue = value;
    }
    // 调用set方法
    auto method = getMethod(methodName.arg(field));
    QGenericArgument arg(fieldValue.typeName(), fieldValue.data());
    auto rtn = method.invokeOnGadget(const_cast<Entity*>(this), arg);
    if (!rtn) {
        qWarning() << __FUNCTION__ << field << method.name() << "invoke error";
    }
}

inline QString Entity::getColPropery(const QString &colName)
{
    if (colProperty.isEmpty()) {
        this->getFieldMap();
    }
    return colProperty[colName];
}

inline QMetaMethod Entity::getMethod(const QString &methodName) const
{
    auto meta = getMetaInfo();
    auto index = meta->indexOfMethod(methodName.toLocal8Bit());
    return meta->method(index);
}

template<typename T>
inline T Entity::getValue(const QString &field) const
{
    auto method = getMethod("get_" + field + "()");
    T result;
    method.invokeOnGadget(const_cast<Entity*>(this), qReturnArg(result));
    return result;
}

template<typename T>
inline void Entity::setValue(const QString &field, const T &value)
{
    auto method = getMethod("set_" + field + "(__type_" + field + ")");
    method.invokeOnGadget(this, value);
}

// inline void Entity::setValue(const QString &field, const QVariant &value)
// {qDebug() << __FUNCTION__;
//     auto metaInfo = getMetaInfo();
//     int index = metaInfo->indexOfProperty(field.toLocal8Bit());
//     QMetaProperty property = metaInfo->property(index);
//     property.writeOnGadget(this, value);
// }

#endif // ENTITY_H
