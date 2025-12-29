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
#include "connectarg.h"
#include "database.h"
#include "queryarg.h"
#include "QtSql/qsqlerror.h"

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/QSqlRecord>

#include <QJsonArray>
#include <QJsonDocument>
#include <variantutil.h>


Database::Database() {}

Database::Database(const QString &connectArgs)
{
    doConnect(connectArgs);
}

Database::~Database()
{
    doDisconnect();
}

bool Database::connect(const QString &args)
{
    return doConnect(args);
}

void Database::disconnect()
{
    doDisconnect();
}

bool Database::isConnected()
{
    return !connectionName.isEmpty();
}

QJsonDocument Database::query(const QString &args)
{
    QJsonDocument result;
    if (connectionName.isEmpty()) {
        qWarning() << "database not connected";
        return result;
    }
    auto queryArg = QueryArg::fromJson(args);
    if (queryArg.getAction() != Action::Select) {
        return result;
    }
    QString sql = queryArg.getSQL();
    auto db = QSqlDatabase::database(connectionName, true);
    QSqlQuery query{db};
    if (query.exec(sql)){
        auto record = query.record();
        auto count = record.count();
        QJsonArray rows;
        while(query.next()){
            QJsonObject obj;
            for (int col=0;col<count;++col){
                obj.insert(record.fieldName(col), query.value(col).toJsonValue());
            }
            rows.append(obj);
        }
        if (rows.count() > 1) {
            result.setArray(rows);
        }else if(rows.count() == 1){
            result.setObject(rows.first().toObject());
        }
    }else{
        qWarning() << __FUNCTION__ << "error happend:" << query.lastError().text();
    }
    return result;
}

bool Database::update(const QString &args, QJsonDocument data)
{
    return false;
    if(data.isEmpty()){
        return false;
    }
    if (connectionName.isEmpty()) {
        qWarning() << "database not connected";
        return false;
    }
    auto queryArg = QueryArg::fromJson(args);
    QString sql = queryArg.getSQL();
    if(queryArg.getAction() != Action::Update){
        return false;
    }

    auto db = QSqlDatabase::database(connectionName, true);
    QSqlQuery query{db};
    auto result = query.exec(sql);
    if (!result){
        qWarning() << __FUNCTION__ << "error happend:" << query.lastError().text();
    }
    return result;
}

QString Database::getConnectionName() const
{
    return connectionName;
}

QList<QString> Database::tables()
{
    auto db = QSqlDatabase::database(connectionName, true);
    return db.tables();
}

QList<QSqlField> Database::tableFields(const QString &tableName)
{
    QList<QSqlField> fields;
    auto db = QSqlDatabase::database(connectionName, true);
    auto record = db.record(tableName);
    auto count = record.count();
    for (int i = 0; i < count; ++i) {
        fields << record.field(i);
    }
    return fields;
}

bool Database::doConnect(const QString &args)
{
    if (args.isEmpty()) {
        return false;
    }
    auto connectArg = ConnectArg::fromJson(args);
    auto driver = connectArg.getDriver();
    auto dbName = connectArg.getDatabaseName();
    auto host = connectArg.getHost();
    if (driver.isEmpty() || dbName.isEmpty()) {
        return false;
    }
    QSqlDatabase db = QSqlDatabase::addDatabase(driver);
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(connectArg.getUserName());
    db.setPassword(connectArg.getPassword());
    int port = connectArg.getPort();
    if(port > 0){
        db.setPort(port);
    }
    auto options = connectArg.getOptions();
    if (!options.isEmpty()) {
        db.setConnectOptions(options);
    }
    if (!db.open()){
        qWarning() << "database " << dbName << "opened error:"
                   << db.lastError().text();
    }
    connectionName = db.connectionName();
    return true;
}

void Database::doDisconnect()
{
    auto db = QSqlDatabase::database(connectionName);
    if (db.isValid()) {
        db.close();
        QSqlDatabase::removeDatabase(connectionName);
    }
}



