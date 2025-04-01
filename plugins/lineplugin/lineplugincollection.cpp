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

#include "bidirectionallineplugin.h"
#include "cubiclineplugin.h"
#include "curvedlineplugin.h"
#include "dashlineplugin.h"
#include "directionallineplugin.h"
#include "dotlineplugin.h"
#include "horizontalelbowplugin.h"
#include "lineplugincollection.h"
#include "polygonlineplugin.h"
#include "solidlineplugin.h"
#include "verticalelbowplugin.h"

LinePluginCollection::LinePluginCollection() {
    pluginList.append(new DashLinePlugin());
    pluginList.append(new DotLinePlugin());
    pluginList.append(new SolidLinePlugin());
    pluginList.append(new DirectionalLinePlugin());
    pluginList.append(new BidirectionalLinePlugin());
    pluginList.append(new PolygonLinePlugin());
    pluginList.append(new CubicLinePlugin());
    pluginList.append(new CurvedLinePlugin());
    pluginList.append(new HorizontalElbowPlugin());
    pluginList.append(new VerticalElbowPlugin());
}

LinePluginCollection::~LinePluginCollection()
{
    for (int i=0; i<pluginList.count(); i++) {
        pluginList.removeAt(i);
    }
}

QList<IGraphicPlugin *> LinePluginCollection::graphicPlugins()
{
    return pluginList;
}
