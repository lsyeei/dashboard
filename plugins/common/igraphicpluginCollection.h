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

#ifndef IGRAPHICPLUGINCOLLECTION_H
#define IGRAPHICPLUGINCOLLECTION_H

#include "igraphicplugin.h"
class IGraphicPluginCollection
{
public:
    virtual ~IGraphicPluginCollection() = default;
    virtual QList<IGraphicPlugin*> graphicPlugins() = 0;
};

#define IGraphicPluginCollection_iid "cn.devhome.BIDEsigner.IGraphicPluginCollection"
Q_DECLARE_INTERFACE(IGraphicPluginCollection, IGraphicPluginCollection_iid)

#endif // IGRAPHICPLUGINCOLLECTION_H
