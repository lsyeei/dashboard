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
#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include "baseservice.h"
#include <QSqlDriver>
 #include <QSqlError>

class TransactionManager {
public:
    TransactionManager();
    ~TransactionManager();
    template <typename T>
    bool addService(BaseService<T> *service);
    bool beginTransaction();
    bool commit();
    bool rollback();
    bool isInTransaction() const;

private:
    QSet<QString> dbConnName;
    QSet<AbstractMapper*> mapperSet;
    bool inTransaction{false};

    void restore();
};
#endif // TRANSACTIONMANAGER_H

inline TransactionManager::TransactionManager(){}

inline TransactionManager::~TransactionManager(){
    dbConnName.clear();
    mapperSet.clear();
}

template <typename T>
inline bool TransactionManager::addService(BaseService<T> *service){
    if (inTransaction) {
        return false;
    }
    auto mapper = service->getMapper();
    if (!mapper || mapper->isBatchMode()){
        return false;
    }
    auto connName = mapper->databaseConnectionName();
    auto dataBase = QSqlDatabase::database(connName);
    if (!dataBase.driver()->hasFeature(QSqlDriver::Transactions)){
        return false;
    }
    mapperSet.insert(mapper);
    dbConnName.insert(connName);
    return true;
}

inline bool TransactionManager::beginTransaction() {
    if (inTransaction) {
        return false;
    }
    bool errorFlag{false};
    // mapper 进入批量模式
    QList<AbstractMapper*> doneMapper;
    foreach (auto mapper, mapperSet) {
        if(!mapper->startBatchMode()){
            errorFlag = true;
            break;
        }
        doneMapper << mapper;
    }
    if (errorFlag) {
        foreach (auto mapper, doneMapper) {
            mapper->endBatchMode();
        }
        return false;
    }
    // 开启事务
    QList<QSqlDatabase> doneDB;
    foreach (auto connName, dbConnName) {
        auto db = QSqlDatabase::database(connName);
        if (!db.transaction()){
            errorFlag = true;
            break;
        }
        doneDB << db;
    }
    if (errorFlag) {
        foreach (auto db, doneDB) {
            db.commit();
        }
        doneDB.clear();
        return false;
    }
    // 开启事务完成
    inTransaction = true;
    return true;
}

inline bool TransactionManager::commit() {
    if (!inTransaction) {
        return false;
    }
    bool errorFlag{false};
    foreach (auto connName, dbConnName) {
        auto db = QSqlDatabase::database(connName);
        if (!db.commit()){
            errorFlag = true;
            qWarning() << "事务提交失败！"  << db.lastError().text();
        }
    }
    restore();
    return !errorFlag;
}

inline bool TransactionManager::rollback() {
    if (!inTransaction) {
        return false;
    }
    bool errorFlag{false};
    foreach (auto connName, dbConnName) {
        auto db = QSqlDatabase::database(connName);
        if (!db.rollback()){
            errorFlag = true;
            qWarning() << "事务回滚失败！"  << db.lastError().text();
        }
    }
    restore();
    return !errorFlag;
}

inline bool TransactionManager::isInTransaction() const {
    return inTransaction;
}

inline void TransactionManager::restore(){
    foreach (auto mapper, mapperSet) {
        mapper->endBatchMode();
    }
    inTransaction = false;
}
