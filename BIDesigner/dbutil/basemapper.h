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
#ifndef BASEMAPPER_H
#define BASEMAPPER_H

#include "entity.h"
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>

template <typename T>
class BaseMapper{
public:
    explicit BaseMapper(QSqlDatabase db);
    T selectById(QVariant id);
    bool deleteById(const T &data);
    bool deleteById(QVariant id);
    bool updateById(const T &data);
    QList<T> selectList();
    QList<T> selectList(const QString &where);
    bool insert(T *data);
    bool execSql(const QString &sql, bool autoCommit = true);
private:
    QSqlDatabase database;
    QSqlQuery query;
    QString table;
    QList<QString> pkList;
    QMap<QString,QString> fieldMap;

    bool isValid();
    bool isPrimaryKey(const QString col);
    bool selectById(QVariant id, T *data);
};


template<typename T>
inline BaseMapper<T>::BaseMapper(QSqlDatabase db)
    :database(db)
{
    query = QSqlQuery(db);
    T item;
    auto obj = dynamic_cast<Entity*>(&item);
    if (obj == nullptr) {
        return;
    }
    table = obj->getTableName();
    pkList = obj->getPrimaryKey();
    fieldMap = obj->getFieldMap();
}

template<typename T>
inline T BaseMapper<T>::selectById(QVariant id)
{
    T data;
    selectById(id, &data);
    return data;
}

template<typename T>
inline bool BaseMapper<T>::deleteById(const T &data)
{
    if(!isValid()){
        return false;
    }
    auto obj = dynamic_cast<const Entity*>(&data);
    QString sql = QString("delete from %1 where ").arg(table);
    for(int i = 0; i< pkList.count(); i++){
        if (i > 0) {
            sql += " and ";
        }
        sql += pkList[i] + "=" + obj->getValueByColName(pkList[i]).toString();
    }
    return execSql(sql);
}

template<typename T>
inline bool BaseMapper<T>::deleteById(QVariant id)
{
    if(!isValid()){
        return false;
    }
    QString sql = QString("delete from %1 where %2=%3")
                      .arg(table, pkList[0], id.toString());
    return execSql(sql);
}

template<typename T>
inline bool BaseMapper<T>::updateById(const T &data)
{
    if(!isValid()){
        return false;
    }
    auto obj = dynamic_cast<const Entity*>(&data);
    QString values{""};
    for (auto item=fieldMap.cbegin(); item!=fieldMap.cend(); item++) {
        if (isPrimaryKey(item.value())) {
            continue;
        }
        if (item.value().compare("create_time") == 0) {
            continue;
        }
        if (item.value().compare("modify_time") == 0) {
            values += values.isEmpty()?"":",";
            values += "modify_time=datetime('now', 'localtime')";
            continue;
        }
        auto value = obj->getValueByColName(item.value());
        if (!value.isValid() || value.isNull()) {
            continue;
        }
        switch (value.typeId()) {
        case QMetaType::QString:
            if (value.toString().isEmpty()) {
                break;
            }
            values += (values.isEmpty()?"":",") + item.value() + "=";
            values += "'" + value.toString() + "'";
            break;            
        case QMetaType::QByteArray:
            values += values.isEmpty()?"thumb=X'":",thumb=X'";
            values += QString(value.toByteArray().toHex(0)) + "'";
            break;
        default:
            if (value.toString().isEmpty()) {
                break;
            }
            values += (values.isEmpty()?"":",") + item.value() + "=";
            values += value.toString();
            break;
        }
    }
    QString where{""};
    for(int i = 0; i< pkList.count(); i++){
        if (i > 0) {
            where += " and ";
        }
        where += pkList[i] + "=" + obj->getValueByColName(pkList[i]).toString();
    }
    QString sql = QString("update %1 set %2 where %3").arg(table, values, where);
    return execSql(sql);
}

template<typename T>
inline QList<T> BaseMapper<T>::selectList()
{
    return selectList("");
}

template<typename T>
inline QList<T> BaseMapper<T>::selectList(const QString &where)
{
    QList<T> result;
    if (!isValid()) {
        return result;
    }
    auto cols = fieldMap.values();
    auto sql = QString("select %1 from %2").arg(cols.join(','), table);
    if (!where.isEmpty()) {
        sql += " where " + where;
    }

    auto flag = execSql(sql, false);
    if (!flag) {
        return result;
    }
    while (query.next()) {
        T data;
        auto temp = dynamic_cast<Entity*>(&data);
        for(auto i=fieldMap.cbegin(); i != fieldMap.cend(); i++){
            temp->setValue(i.key(),query.value(i.value()));
        }
        result << data;
    }
    return result;
}

template<typename T>
inline bool BaseMapper<T>::insert(T *data)
{
    if (!isValid()) {
        return false;
    }
    auto obj = dynamic_cast<Entity*>(data);
    QString cols{""}, values{""};
    for (auto item=fieldMap.cbegin(); item!=fieldMap.cend(); item++) {
        if (isPrimaryKey(item.value()) &&
            obj->getColPropery(item.value()).compare("AUTO") == 0) {
            continue;
        }
        if (item.value().compare("modify_time") == 0 ||
            item.value().compare("create_time") == 0) {
            cols += cols.isEmpty()?"":",";
            cols += item.value();
            values += values.isEmpty()?"":",";
            values += "datetime('now', 'localtime')";
            continue;
        }

        auto value = obj->getValueByColName(item.value());
        if (!value.isValid() || value.isNull()) {
            continue;
        }
        switch (value.typeId()) {
        case QMetaType::QString:
            if (value.toString().isEmpty()) {
                break;
            }
            cols += cols.isEmpty()?"":",";
            cols += item.value();
            values += values.isEmpty()?"":",";
            values += "'" + value.toString() + "'";
            break;
        case QMetaType::QByteArray:
            cols += cols.isEmpty()?"":",";
            cols += item.value();
            values += values.isEmpty()?"X'":",X'";
            values += QString(value.toByteArray().toHex(0)) + "'";
            break;
        default:
            cols += cols.isEmpty()?"":",";
            cols += item.value();
            values += values.isEmpty()?"":",";
            values += value.toString();
            break;
        }
    }
    QString sql = QString("insert into %1(%2) values(%3)").arg(table, cols, values);
    auto result = execSql(sql, false);
    if (result) {
        auto id = query.lastInsertId();
        // obj->setValueByColName(pkList[0], id);
        selectById(id, data);
        database.commit();
    } else {
        database.rollback();
    }

    return result;
}

template<typename T>
inline bool BaseMapper<T>::execSql(const QString &sql, bool autoCommit)
{
    if (!database.isValid() || !database.isOpen()) {
        return false;
    }
    auto result = query.exec(sql);
    if (autoCommit) {
        if (result) {
            database.commit();
        }else{
            database.rollback();
        }
    }

    return result;
}

template<typename T>
inline bool BaseMapper<T>::isValid()
{
    return database.isValid() && database.isOpen() &&
           !table.isEmpty() && !pkList.isEmpty() && !fieldMap.isEmpty();
}

template<typename T>
inline bool BaseMapper<T>::isPrimaryKey(const QString col)
{
    foreach (auto item, pkList) {
        if (item.compare(col) == 0) {
            return true;
        }
    }
    return false;
}

template<typename T>
inline bool BaseMapper<T>::selectById(QVariant id, T *data)
{
    if(!isValid()){
        return false;
    }
    QString sql = QString("select * from %1 where %2=%3").arg(table, pkList[0], id.toString());

    if (!execSql(sql, false)) {
        return false;
    }
    auto obj = dynamic_cast<Entity*>(data);
    query.first();
    for(auto i=fieldMap.cbegin(); i != fieldMap.cend(); i++){
        obj->setValue(i.key(),query.value(i.value()));
    }
    return true;
}

#endif // BASEMAPPER_H
