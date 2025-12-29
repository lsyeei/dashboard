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

#ifndef DATABASEPLUGIN_H
#define DATABASEPLUGIN_H
#include <QObject>
#include "idatasourceplugin.h"

class DatabasePlugin:public QObject, public IDataSourcePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cn.devhome.BIDEsigner.IDataSourcePlugin")
    Q_INTERFACES(IDataSourcePlugin)
public:
    DatabasePlugin();
    const static QString PLUGIN_ID;
    // IDataSourcePlugin interface
    QString id() const override;
    QString name() const override;
    QString toolTip() const override;
    IDataSourceWidget *connectWidget() override;
    IDataQueryWidget *dataWidget() override;
    IDataSource *dataSource() override;
};

#endif // DATABASEPLUGIN_H
