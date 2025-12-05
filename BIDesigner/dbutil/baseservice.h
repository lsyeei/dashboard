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

#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "basemapper.h"

class QSqlDatabase;
template<typename T>
class BaseService{
public:
    explicit BaseService(QSqlDatabase db);
    ~BaseService();
    T getOne(QVariant id);
    QList<T> list();
    QList<T> list(const QString &where);
    bool deleteBatch(const QString &where);
    bool deleteById(T data);
    bool deleteById(QVariant id);
    bool updateById(T data);
    bool save(T *data);
    BaseMapper<T> *getMapper(){return mapper;}
private:
    BaseMapper<T> *mapper{nullptr};
};

template<typename T>
inline BaseService<T>::BaseService(QSqlDatabase db)
    : mapper(new BaseMapper<T>(db))
{

}

template<typename T>
inline BaseService<T>::~BaseService()
{
    if (mapper) {
        delete mapper;
        mapper = nullptr;
    }
}

template<typename T>
inline T BaseService<T>::getOne(QVariant id)
{
    return mapper->selectById(id);
}

template<typename T>
inline QList<T> BaseService<T>::list()
{
    return mapper->selectList();
}

template<typename T>
inline QList<T> BaseService<T>::list(const QString &where)
{
    return mapper->selectList(where);
}

template<typename T>
inline bool BaseService<T>::deleteBatch(const QString &where)
{
    return mapper->deleteBatch(where);
}

template<typename T>
inline bool BaseService<T>::deleteById(T data)
{
    return mapper->deleteById(data);
}

template<typename T>
inline bool BaseService<T>::deleteById(QVariant id)
{
    return mapper->deleteById(id);
}

template<typename T>
inline bool BaseService<T>::updateById(T data)
{
    return mapper->updateById(data);
}

template<typename T>
inline bool BaseService<T>::save(T *data)
{
    return mapper->insert(data);
}

#endif // BASESERVICE_H
