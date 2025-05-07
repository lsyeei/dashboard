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

#define TABLE_FIELD(field, colName) \
using __type_##field = decltype(field);\
Q_PROPERTY(__type_##field field READ get_##field WRITE set_##field) \
protected:\
    Q_INVOKABLE MAP_FLAG inline QString map_##field(){return #colName;}\
public:\
    Q_INVOKABLE GETTER_FLAG __type_##field get_##field() const {return field;}\
    Q_INVOKABLE SETTER_FLAG void set_##field(const __type_##field &value){if (value != field) field = value;}

class Entity
{
public:
    Entity(){};
    virtual QString getTableName() const = 0;
    virtual QList<QString> getPrimaryKey() const = 0;
    QMap<QString, QString> getFieldMap();
    QString getTest(){return "a";};
    template<typename T>
    T getValue(const QString &field) const;
    template<typename T>
    void setValue(const QString &field, const T &value);
    void setValue(const QString &field, const QVariant &value);
protected:
    virtual const QMetaObject* getMetaInfo() const = 0;
private:
    QMetaMethod getMethod(const QString &methodName) const;
    QMap<QString, QString> fieldMap;
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
                QString colName{""};
                if (metaInfo->method(i).invokeOnGadget(this, qReturnArg(colName))){
                    fieldMap[fieldName] = colName;
                }
            }
        }
    }
    return fieldMap;
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
    method.invokeOnGadget(this, qReturnArg(result));
    return result;
}

template<typename T>
inline void Entity::setValue(const QString &field, const T &value)
{
    auto method = getMethod("set_" + field + "(__type_" + field + ")");
    method.invokeOnGadget(this, value);
}

inline void Entity::setValue(const QString &field, const QVariant &value)
{
    auto metaInfo = getMetaInfo();
    int index = metaInfo->indexOfProperty(field.toLocal8Bit());
    QMetaProperty property = metaInfo->property(index);
    property.writeOnGadget(this, value);
}

#endif // ENTITY_H
