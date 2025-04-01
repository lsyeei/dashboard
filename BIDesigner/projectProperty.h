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

#ifndef PROJECTPROPERTY_H
#define PROJECTPROPERTY_H

#include "serializable.h"

class ProjectProperty : public Serializable
{
    Q_GADGET
    SERIALIZE(ProjectProperty)
public:
    explicit ProjectProperty() : Serializable() {};
    ~ProjectProperty(){};
private:
    QString name{"new Project"};
    QString author{"anonymous"};
    QDateTime createTime;
    QDateTime modifyTime;

    JSONFIELD(name, Name)
    JSONFIELD(author, Author)
    JSONFIELD(createTime, CreateTime)
    JSONFIELD(modifyTime, ModifyTime)
};

#endif // PROJECTPROPERTY_H
