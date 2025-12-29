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

#ifndef IDATASOURCEPLUGIN_H
#define IDATASOURCEPLUGIN_H

#include "QtWidgets/qwidget.h"
#include "idatasource.h"

class IDataSourceWidget : public QWidget
{
public:
    IDataSourceWidget(QWidget *parent = nullptr) : QWidget(parent){}
    virtual QString getArgs() = 0;
    virtual void setArgs(const QString &args) = 0;
};
class IDataQueryWidget : public IDataSourceWidget
{
public:
    IDataQueryWidget(QWidget *parent = nullptr) : IDataSourceWidget(parent){}
    virtual void setDataSource(const QString &dataSourceArgs) = 0;
};

class IDataSourcePlugin{
public:
    virtual ~IDataSourcePlugin() = default;
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString toolTip() const = 0;
    virtual IDataSourceWidget *connectWidget() = 0;
    virtual IDataQueryWidget *dataWidget() = 0;
    virtual IDataSource* dataSource() = 0;
};

#define IDataSourcePlugin_iid "cn.devhome.BIDEsigner.IDataSopurcePlugin"
Q_DECLARE_INTERFACE(IDataSourcePlugin, IDataSourcePlugin_iid)

#endif // IDATASOURCEPLUGIN_H
