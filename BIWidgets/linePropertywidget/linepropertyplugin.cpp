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

#include "linepropertyplugin.h"
#include "lineproperty.h"
#include "svghelper.h"

#include <QtPlugin>

LinePropertyPlugin::LinePropertyPlugin(QObject *parent)
    : QObject(parent)
{}

void LinePropertyPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LinePropertyPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LinePropertyPlugin::createWidget(QWidget *parent)
{
    return new LineProperty(parent);
}

QString LinePropertyPlugin::name() const
{
    return QLatin1String("LineProperty");
}

QString LinePropertyPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon LinePropertyPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/pen.svg"));
    return QIcon(svg.toPixmap({32,32}));
}

QString LinePropertyPlugin::toolTip() const
{
    return QLatin1String("line property");
}

QString LinePropertyPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LinePropertyPlugin::isContainer() const
{
    return false;
}

QString LinePropertyPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="LineProperty" name="lineProperty">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>239</width>
         <height>68</height>
       </rect>
     </property>
</widget>)");
}

QString LinePropertyPlugin::includeFile() const
{
    return QLatin1String("lineproperty.h");
}
