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
#ifndef USERPLUGINDO_H
#define USERPLUGINDO_H

#include "dbutil/entity.h"
#include "userplugintype.h"
#include <QDateTime>

class UserPluginDO : public Entity{
    Q_GADGET
    TABLE(userPlugin, id)
public:
    UserPluginDO(){}
private:
    int id;
    int groupId;
    QString name;
    QString note;
    UserPluginType type;
    QString path;
    QByteArray thumb;
    QDateTime createTime;
    QDateTime modifyTime;

    TABLE_FIELD(id, id)
    TABLE_FIELD(groupId, group_id)
    TABLE_FIELD(name, name)
    TABLE_FIELD(note, note)
    TABLE_FIELD(type, type)
    TABLE_FIELD(path, path)
    TABLE_FIELD(thumb, thumb)
    TABLE_FIELD(createTime, create_time)
    TABLE_FIELD(modifyTime, modify_time)
};

#endif // USERPLUGINDO_H
