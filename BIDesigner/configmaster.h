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
#ifndef CONFIGMASTER_H
#define CONFIGMASTER_H

#include <QPointer>
#include <QSqlDatabase>
#include "customgraphic/userplugingroupservice.h"
#include "customgraphic/userpluginservice.h"

/**
 * @brief The ConfigMaster class
 * 此类用于管理 config 文件，负责读写
 */
class ConfigMaster
{
    ConfigMaster();
public:
    static ConfigMaster *instance();
    ~ConfigMaster();
    UserPluginGroupService *userPluginGroup;
    UserPluginService *userPlugin;
private:
    static ConfigMaster *master;
    // QSqlDatabase *db{nullptr};
    QSqlQuery *query{nullptr};
    /**
     * @brief connectDB 检查配置文件是否存在，如果不存在初始化一个配置文件
     */
    void connectDB();
    bool checkTables(QSqlQuery *query);
    /**
     * @brief initDbPwd 初始化数据库用户密码
     * @param query query 指针
     */
    void initDbPwd(QSqlQuery *query);
    /**
     * @brief createTables 创建数据表并初始化
     * @param query query指针
     */
    void createTables(QSqlQuery *query);
};

#endif // CONFIGMASTER_H
