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
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>

template <typename T>
class BaseMapper{
public:
    explicit BaseMapper(QSqlDatabase *db):database(db){query = QSqlQuery(*db);}
    QList<T> selectList();
    bool execSql(const QString &sql);
private:
    QSqlDatabase *database{nullptr};
    QSqlQuery query;
};

#endif // BASEMAPPER_H

template<typename T>
inline QList<T> BaseMapper<T>::selectList()
{
    QList<T> result;
    T item;
    auto obj = dynamic_cast<Entity*>(&item);
    if (obj == nullptr) {
        return result;
    }
    auto table = obj->getTableName();
    auto map = obj->getFieldMap();
    auto sql = QString("select %1 from %2").arg(map.values().join(','), table);

    auto flag = execSql(sql);
    if (!flag) {
        return result;
    }
    while (query.next()) {
        T data;
        auto temp = dynamic_cast<Entity*>(&data);
        for(auto i=map.cbegin(); i != map.cend(); i++){
            temp->setValue(i.key(),query.value(i.value()));
        }
        result << data;
    }
    return result;
}

template<typename T>
inline bool BaseMapper<T>::execSql(const QString &sql)
{
    if (database == nullptr) {
        return false;
    }
    auto result = query.exec(sql);
    return result;
}
