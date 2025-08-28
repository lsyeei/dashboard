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

#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include "qtclasshelpermacros.h"

#include <QScopedPointer>
class SnowFlakePrivate;
class SnowFlake
{
public:
    SnowFlake();
    SnowFlake(long workerId, long datacenterId);
    SnowFlake(long workerId, long datacenterId, long sequence);

    ~SnowFlake();
    /**
     * @brief nextId 获取下一个随机的ID
     * @return
     */
    qint64 nextId();
    /**
     * @brief nextIdString 获取下一个随机的ID
     * @return ID 的16进制字符串
     */
    QString nextIdString();
private:
    SnowFlakePrivate *d_ptr;
    Q_DECLARE_PRIVATE(SnowFlake)
};

#endif // SNOWFLAKE_H
