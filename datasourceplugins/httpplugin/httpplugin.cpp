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
#include "httpplugin.h"

#include "connectform.h"
#include "httpclient.h"
#include "queryform.h"

const QString HttpPlugin::PLUGIN_ID{"HTTP_DEFAULT"};
HttpPlugin::HttpPlugin() {}

HttpPlugin::~HttpPlugin()
{
}

QString HttpPlugin::id() const
{
    return PLUGIN_ID;
}

QString HttpPlugin::name() const
{
    return tr("HTTP");
}

QString HttpPlugin::toolTip() const
{
    return tr("通过HTTP连接获取数据");
}

IDataSourceWidget *HttpPlugin::connectWidget()
{
    if(!sourceWidget){
        sourceWidget = new ConnectForm();
    }
    return sourceWidget;
}

IDataQueryWidget *HttpPlugin::dataWidget()
{
    if(!queryWidget){
        queryWidget = new QueryForm();
    }
    return queryWidget;
}

IDataSource *HttpPlugin::dataSource()
{
    return new HttpClient();
}
