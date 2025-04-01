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

#include "fillpropertyplugin.h"
#include "fillproperty.h"
#include "svghelper.h"

#include <QtPlugin>

FillPropertyPlugin::FillPropertyPlugin(QObject *parent)
    : QObject(parent)
{}

void FillPropertyPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool FillPropertyPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *FillPropertyPlugin::createWidget(QWidget *parent)
{
    return new FillProperty(parent);
}

QString FillPropertyPlugin::name() const
{
    return QLatin1String("FillProperty");
}

QString FillPropertyPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon FillPropertyPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/fillcolor.svg"));
    return QIcon(svg.toPixmap({32,32}));
}

QString FillPropertyPlugin::toolTip() const
{
    return QLatin1String("config fill property");
}

QString FillPropertyPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool FillPropertyPlugin::isContainer() const
{
    return false;
}

QString FillPropertyPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="FillProperty" name="fillProperty">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>239</width>
         <height>145</height>
       </rect>
     </property>
</widget>)");
}

QString FillPropertyPlugin::includeFile() const
{
    return QLatin1String("fillproperty.h");
}
