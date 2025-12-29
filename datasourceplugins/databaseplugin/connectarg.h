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

#ifndef CONNECTARG_H
#define CONNECTARG_H
#include <serializable.h>

class ConnectArg : public Serializable {
    Q_GADGET
    SERIALIZE(ConnectArg)
public:
    ConnectArg();
    static ConnectArg fromJson(const QString &json);
    QString toJson();
private:
    QString driver;
    QString host;
    QString databaseName;
    QString userName;
    QString password;
    int port;
    QString options;

    JSONFIELD(driver, Driver)
    JSONFIELD(host, Host)
    JSONFIELD(databaseName, DatabaseName)
    JSONFIELD(userName, UserName)
    JSONFIELD(password, Password)
    JSONFIELD(port, Port)
    JSONFIELD(options, Options)
};

#endif // CONNECTARG_H
