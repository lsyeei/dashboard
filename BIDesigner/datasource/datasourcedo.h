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
#ifndef DATASOURCEDO_H
#define DATASOURCEDO_H
#include "dbutil/entity.h"

#include <QDateTime>

class DataSourceDO : public Entity{
    Q_GADGET
    TABLE(dataSource, id)
public:
    DataSourceDO(){
        id = -1;
        dataDirId = -1;
    }

    bool isEmpty(){return id <= -1 && sourcePluginId.isEmpty();}
private:
    int id;
    int dataDirId;
    QString sourcePluginId;
    QString sourceArgs;
    QDateTime createTime;
    QDateTime modifyTime;

    QString encodeArgs(const QString &arg) const
    {
        auto base64 = arg.toUtf8().toBase64();
        return QString::fromUtf8(base64);
    }
    QString decodeArgs(const QString &arg) const
    {
        auto hex = arg.toUtf8();
        auto base64 = QByteArray::fromBase64Encoding(hex).decoded;
        return QString::fromUtf8(base64);
    }

    TABLE_FIELD(id, id, AUTO)
    TABLE_FIELD(dataDirId, data_dir_id)
    TABLE_FIELD(sourcePluginId, source_plugin_id)
    TABLE_FIELD(sourceArgs, source_args, encodeArgs, decodeArgs)
    TABLE_FIELD(createTime, create_time)
    TABLE_FIELD(modifyTime, modify_time)
};

#endif // DATASOURCEDO_H
