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

#ifndef IDATASOURCE_H
#define IDATASOURCE_H
#include <QString>

class QJsonDocument;
class IDataSource{
public:
    virtual ~IDataSource() = default;
    virtual bool connect(const QString &args) = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() = 0;
    /**
     * @brief query 查询方法，根据制定参数查询数据
     * @param args 查询参数
     * @return 查询结果，以JSON字符串方式返回
     */
    virtual QJsonDocument query(const QString &args) = 0;
    /**
     * @brief update 更新数据
     * @param args 更新参数
     * @param data  需要更新的数据及其值组成的JSON字符串
     * @return true 成功，false 失败
     */
    virtual bool update(const QString &args, QJsonDocument data) = 0;
};

#endif // IDATASOURCE_H
