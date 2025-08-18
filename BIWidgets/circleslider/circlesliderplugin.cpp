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

#include "circlesliderplugin.h"
#include "circleslider.h"
#include "svghelper.h"

#include <QtPlugin>

CircleSliderPlugin::CircleSliderPlugin(QObject *parent)
    : QObject(parent)
{}

void CircleSliderPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool CircleSliderPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *CircleSliderPlugin::createWidget(QWidget *parent)
{
    return new CircleSlider(parent);
}

QString CircleSliderPlugin::name() const
{
    return QLatin1String("CircleSlider");
}

QString CircleSliderPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon CircleSliderPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/circle.svg"));
    QWidget widget;
    auto textColor = widget.palette().brush(QPalette::Text).color();
    svg.setFillColor(textColor);
    svg.setStrokeColor(textColor);
    return QIcon(svg.toPixmap({32,32}));
}

QString CircleSliderPlugin::toolTip() const
{
    return QLatin1String("circle slider");
}

QString CircleSliderPlugin::whatsThis() const
{
    return QLatin1String("slider with a circle shape, the value will auto circled");
}

bool CircleSliderPlugin::isContainer() const
{
    return false;
}

QString CircleSliderPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="CircleSlider" name="circleSlider">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>30</width>
         <height>30</height>
       </rect>
     </property>
</widget>)");
}

QString CircleSliderPlugin::includeFile() const
{
    return QLatin1String("circleslider.h");
}
