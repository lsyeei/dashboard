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

#include "circleplugin.h"
#include "diamondplugin.h"
#include "hexagonplugin.h"
#include "obtusetriangleplugin.h"
#include "octagonplugin.h"
#include "parallelogramplugin.h"
#include "pentagonplugin.h"
#include "pieplugin.h"
#include "quadrangleplugin.h"
#include "rectplugin.h"
#include "rectplugincollection.h"
#include "righttrapezoidplugin.h"
#include "righttriangleplugin.h"
#include "sectorplugin.h"
#include "star4plugin.h"
#include "star5plugin.h"
#include "star6plugin.h"
#include "star8plugin.h"
#include "trapeziumplugin.h"
#include "triangleplugin.h"
#include "textplugin.h"
#include "htmlitemplugin.h"

RectPluginCollection::RectPluginCollection()
{
    pluginList.append(new TextPlugin());
    pluginList.append(new HtmlItemPlugin());
    pluginList.append(new Rectplugin());
    pluginList.append(new CirclePlugin());
    pluginList.append(new ParallelogramPlugin());
    pluginList.append(new DiamondPlugin());
    pluginList.append(new TrapeziumPlugin());
    pluginList.append(new RightTrapezoidPlugin());
    pluginList.append(new QuadranglePlugin());
    pluginList.append(new TrianglePlugin());
    pluginList.append(new RightTrianglePlugin());
    pluginList.append(new ObtuseTrianglePlugin());
    pluginList.append(new Star4Plugin());
    pluginList.append(new Star5Plugin());
    pluginList.append(new Star6Plugin());
    pluginList.append(new Star8Plugin());
    pluginList.append(new PentagonPlugin());
    pluginList.append(new HexagonPlugin());
    pluginList.append(new OctagonPlugin());
    pluginList.append(new PiePlugin());
    pluginList.append(new SectorPlugin());
}

RectPluginCollection::~RectPluginCollection()
{
    for (int i=0; i<pluginList.count(); i++) {
        pluginList.removeAt(i);
    }
}

QList<IGraphicPlugin *> RectPluginCollection::graphicPlugins()
{
    return pluginList;
}
