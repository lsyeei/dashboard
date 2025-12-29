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
#ifndef DRIVERDESCRIPTION_H
#define DRIVERDESCRIPTION_H


#include "serializable.h"
class DriverDescription : public Serializable{
    Q_GADGET
    SERIALIZE(DriverDescription)
public:
    DriverDescription(QString name, QString dbms,
                      QString note, QList<QString> options)
        :name(name), dbms(dbms),note(note),options(options){}
private:
    // 驱动名
    QString name;
    // 对应的数据库管理系统
    QString dbms;
    // 注释
    QString note;
    // 可用的连接选项
    QList<QString> options;

    JSONFIELD(name, Name)
    JSONFIELD(dbms, Dbms)
    JSONFIELD(note, Note)
    JSONFIELD(options, Options)
};
static QList<QString> mysqlOptions{"CLIENT_COMPRESS","CLIENT_FOUND_ROWS",
    "CLIENT_IGNORE_SPACE","CLIENT_NO_SCHEMA","CLIENT_INTERACTIVE",
    "MYSQL_OPT_PROTOCOL","UNIX_SOCKET","MYSQL_SHARED_MEMORY_BASE_NAME",
    "MYSQL_OPT_RECONNECT","MYSQL_OPT_CONNECT_TIMEOUT","MYSQL_OPT_READ_TIMEOUT",
    "MYSQL_OPT_WRITE_TIMEOUT","MYSQL_OPT_LOCAL_INFILE","MYSQL_OPT_SSL_MODE",
    "MYSQL_OPT_TLS_VERSION","MYSQL_OPT_SSL_CRL","MYSQL_OPT_SSL_CRLPATH"};
static QList<QString> sqlliteOptions{"QSQLITE_BUSY_TIMEOUT","QSQLITE_USE_QT_VFS",
    "QSQLITE_OPEN_READONLY","QSQLITE_OPEN_URI","QSQLITE_ENABLE_SHARED_CACHE",
    "QSQLITE_ENABLE_REGEXP","QSQLITE_NO_USE_EXTENDED_RESULT_CODES",
    "QSQLITE_ENABLE_NON_ASCII_CASE_FOLDING","QSQLITE_OPEN_NOFOLLOW"};
static QList<QString> psqlOptions{};
static QList<QString> ociOptions{"OCI_ATTR_PREFETCH_ROWS","OCI_ATTR_PREFETCH_MEMORY",
    "OCI_AUTH_MODE"};
static QList<QString> odbcOptions{"SQL_ATTR_ACCESS_MODE","SQL_ATTR_LOGIN_TIMEOUT",
    "SQL_ATTR_CONNECTION_TIMEOUT","SQL_ATTR_CURRENT_CATALOG","SQL_ATTR_METADATA_ID",
    "SQL_ATTR_PACKET_SIZE","SQL_ATTR_TRACEFILE","SQL_ATTR_TRACE",
    "SQL_ATTR_CONNECTION_POOLING","SQL_ATTR_ODBC_VERSION"};
static QList<QString> ibaseOptions{"ISC_DPB_SQL_ROLE_NAME"};
static QList<QString> mimerOptions{};
static QList<QString> db2Options{"SQL_ATTR_ACCESS_MODE","SQL_ATTR_LOGIN_TIMEOUT"};
static QList<DriverDescription> drivers{
    {"QMYSQL","MySql","MySql",mysqlOptions},
    {"MARIADB","MariaDB","MySQL or MariaDB (version 5.6 and above)",mysqlOptions},
    {"QPSQL","PostgreSQL","PostgreSQL (versions 7.3 and above)",psqlOptions},
    {"QSQLITE","SQLite","SQLite version 3",sqlliteOptions},
    {"QOCI","Oracle","Oracle Call Interface Driver (version 12.1 and above)",ociOptions},
    {"QODBC","ODBC","Microsoft SQL Server and other ODBC-compliant databases",odbcOptions},
    {"QIBASE","Borland InterBase / Firebird","Borland InterBase / Firebird",ibaseOptions},
    {"QMIMER","Mimer SQL","Mimer SQL (version 11 and above)",mimerOptions},
    {"QDB2","IBM DB2","IBM DB2 (version 7.1 and above)",db2Options}
};
#endif // DRIVERDESCRIPTION_H
