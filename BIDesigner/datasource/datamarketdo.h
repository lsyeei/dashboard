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
#ifndef DATAMARKETDO_H
#define DATAMARKETDO_H
#include "dbutil/entity.h"

#include "datasourcedo.h"

#include <QDateTime>

class DataMarketDO : public Entity{
    Q_GADGET
    TABLE(dataMarket, id)
public:
    DataMarketDO(){
        id = -1;
        dataSourceId = -1;
        uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    }
    void setDataSource(DataSourceDO source){
        dataSource = source;
        dataSourceId = source.get_id();
    }
    DataSourceDO getDataSource(){return dataSource;}
private:
    int id;
    int dataSourceId;
    QString uuid;
    QString dataName;
    QString note;
    QString requestArgs;
    QString processCode;
    int requestPeriod;
    QDateTime createTime;
    QDateTime modifyTime;
    DataSourceDO dataSource;

    TABLE_FIELD(id, id, AUTO)
    TABLE_FIELD(dataSourceId, data_source_id)
    TABLE_FIELD(uuid, uuid)
    TABLE_FIELD(dataName, data_name)
    TABLE_FIELD(note, note)
    TABLE_FIELD(requestArgs, request_args)
    TABLE_FIELD(requestPeriod, request_period)
    TABLE_FIELD(processCode, process_code)
    TABLE_FIELD(createTime, create_time)
    TABLE_FIELD(modifyTime, modify_time)
};

#endif // DATAMARKETDO_H
