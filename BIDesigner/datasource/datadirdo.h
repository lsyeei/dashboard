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

#ifndef DATADIRDO_H
#define DATADIRDO_H
#include "datasourcedo.h"

#include <dbutil/entity.h>
#include <QDateTime>

class DataDirDO : public Entity{
    Q_GADGET
    TABLE(dataDir, id)
public:
    DataDirDO(){
        id = -1;
        groupId = GROUP_ID;
    }
    static const int GROUP_ID{0};
    DataSourceDO getDataSource() const {return dataSource;}
    void setDataSource(DataSourceDO source){dataSource = source;}
    QString getParentName(){return parentName;}
    void setParentName(const QString &name){parentName = name;}
    bool isEmpty(){return id <= -1 && name.isEmpty();}
private:
    int id;
    int parentId;
    QString name;
    int groupId;
    QByteArray data;
    QByteArray property;
    QDateTime createTime;
    QDateTime modifyTime;
    // 关联的数据源
    DataSourceDO dataSource;
    // 父目录名
    QString parentName;

    TABLE_FIELD(id, id, AUTO)
    TABLE_FIELD(parentId, parent_id)
    TABLE_FIELD(name, name)
    TABLE_FIELD(groupId, group_id)
    TABLE_FIELD(data, value)
    TABLE_FIELD(property, property)
    TABLE_FIELD(createTime, create_time)
    TABLE_FIELD(modifyTime, modify_time)
};

#endif // DATADIRDO_H
