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

#include "configmaster.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <configs.h>
#include <customgraphic/userplugingroupdo.h>

Configs appConfigs = Configs();
const QString ConfigMaster::connName{"masterConn"};
ConfigMaster *ConfigMaster::master{nullptr};

ConfigMaster::ConfigMaster() {
    connectDB();
    // if(db == nullptr){
    //     return;
    // }
    userPluginGroup = new UserPluginGroupService(QSqlDatabase::database(connName));
    userPlugin = new UserPluginService(QSqlDatabase::database(connName));
}

ConfigMaster *ConfigMaster::instance()
{
    if(master){
        return master;
    }
    master = new ConfigMaster();
    return master;
}

#define DELETE(ptr) \
if (ptr) {\
    delete ptr;\
    ptr = nullptr;\
}

ConfigMaster::~ConfigMaster()
{
    DELETE(userPluginGroup)
    DELETE(userPlugin)
    if (query) {
        query->finish();
        delete query;
        query = nullptr;
    }
    // if (db) {
    //     if(db->isOpen()){
    //         db->commit();
    //         db->close();
    //     }
    //     delete db;
    //     db = nullptr;
    // }
}

void ConfigMaster::connectDB()
{
    auto currentPath = QCoreApplication::applicationDirPath();
    QDir path(currentPath + appConfigs.path);
    if (!path.exists()) {
        path.mkdir(currentPath + appConfigs.path,
                   QFileDevice::ReadOwner|QFileDevice::WriteOwner);
    }
    bool initDb{false};
    if (!path.exists(currentPath + appConfigs.path + appConfigs.dbName)) {
        initDb = true;
    }
    // 连接数据库
    auto db = QSqlDatabase::addDatabase("QSQLITE", connName);
    db.setDatabaseName(currentPath + appConfigs.path + appConfigs.dbName);
    if(!db.isValid()){
        qWarning() << "无法使用sqlite数据库，缺少驱动";
        return;
    }
    query = new QSqlQuery(db);

    if(initDb){
        // 创建数据库文件
        if (!db.open()){
            qWarning() << "配置文件:" << appConfigs.dbName << "创建失败！";
            return;
        }
        // 设置用户密码
        initDbPwd(query);
        // 创建表
        createTables(query);
    }else if (!db.open(appConfigs.dbUser, appConfigs.dbPwd)){
        qWarning() << "配置文件:" << appConfigs.dbName << "打开失败！";
        return;
    }
    if (!checkTables(query)) {
        // 创建表
        createTables(query);
    }
}

bool ConfigMaster::checkTables(QSqlQuery *query)
{
    query->exec("SELECT COUNT(name) as num FROM sqlite_master WHERE type = 'table';");
    auto size = query->size();
    if (size <= 0) {
        return false;
    }
    auto num = query->value("num");
    if (num.toInt() > 1) {
        return true;
    }
    return false;
}

void ConfigMaster::initDbPwd(QSqlQuery *query)
{
    Q_UNUSED(query)
    // query->exec(QString("ATTACH DATABASE '%1' AS encrypted KEY '%2';").arg(appConfigs.dbName, appConfigs.dbPwd));
    // query->exec("SELECT sqlcipher_export('encrypted');");
    // query->exec("DETACH DATABASE encrypted;");
}

void ConfigMaster::createTables(QSqlQuery *query)
{
    auto file = QCoreApplication::applicationDirPath() + appConfigs.path + appConfigs.initSql;
    QFile f(file);
    if (!f.exists()) {
        qWarning() << "缺失配置初始化文件:" << file;
        return;
    }
    f.open(QFile::ReadOnly);
    QTextStream stream(&f);
    auto content = stream.readAll();
    if (content.isEmpty()){
        return;
    }
    auto list = content.split(");");
    foreach (auto item, list) {
        auto sql = item.trimmed();
        if (sql.isEmpty() || sql.length() < 15) {
            continue;
        }
        query->exec(sql +");");
    }

}
