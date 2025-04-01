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

#include "gradientcolorpickerplugin.h"
#include "gradientcolorpicker.h"
#include "svghelper.h"
#include <QtPlugin>

GradientColorPickerPlugin::GradientColorPickerPlugin(QObject *parent)
    : QObject(parent)
{}

void GradientColorPickerPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool GradientColorPickerPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *GradientColorPickerPlugin::createWidget(QWidget *parent)
{
    return new GradientColorPicker(parent);
}

QString GradientColorPickerPlugin::name() const
{
    return QLatin1String("GradientColorPicker");
}

QString GradientColorPickerPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon GradientColorPickerPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/gradient.svg"));
    return QIcon(svg.toPixmap({32,32}));
}

QString GradientColorPickerPlugin::toolTip() const
{
    return QLatin1String("gradient color picker");
}

QString GradientColorPickerPlugin::whatsThis() const
{
    return QLatin1String("a gradient color picker");
}

bool GradientColorPickerPlugin::isContainer() const
{
    return false;
}

QString GradientColorPickerPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="GradientColorPicker" name="gradientColorPicker">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>152</width>
         <height>257</height>
       </rect>
    </property>
</widget>)");
}

QString GradientColorPickerPlugin::includeFile() const
{
    return QLatin1String("gradientcolorpicker.h");
}
