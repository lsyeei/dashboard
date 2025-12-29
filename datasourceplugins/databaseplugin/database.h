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
#ifndef DATABASE_H
#define DATABASE_H

#include "idatasource.h"
#include <QSqlField>

class Database : public IDataSource
{
public:
    Database();
    Database(const QString &connectArgs);
    ~Database();

    // IDataSource interface
    bool connect(const QString &args) override;
    void disconnect() override;
    bool isConnected() override;
    QJsonDocument query(const QString &args) override;
    bool update(const QString &args, QJsonDocument data) override;
    QString getConnectionName() const;
    QList<QString> tables();
    QList<QSqlField> tableFields(const QString &tableName);
private:
    QString connectionName;
    bool doConnect(const QString &args);
    void doDisconnect();
};

#endif // DATABASE_H
