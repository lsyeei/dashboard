﻿/**
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

#include "pospropertyplugin.h"
#include "posproperty.h"
#include "svghelper.h"

#include <QtPlugin>

PosPropertyPlugin::PosPropertyPlugin(QObject *parent)
    : QObject(parent)
{}

void PosPropertyPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PosPropertyPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PosPropertyPlugin::createWidget(QWidget *parent)
{
    return new PosProperty(parent);
}

QString PosPropertyPlugin::name() const
{
    return QLatin1String("PosProperty");
}

QString PosPropertyPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon PosPropertyPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/OneAXIS.svg"));
    QWidget widget;
    auto textColor = widget.palette().brush(QPalette::Text).color();
    svg.setFillColor(textColor);
    svg.setStrokeColor(textColor);
    return QIcon(svg.toPixmap({32,32}));
}

QString PosPropertyPlugin::toolTip() const
{
    return QLatin1String("position property");
}

QString PosPropertyPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool PosPropertyPlugin::isContainer() const
{
    return false;
}

QString PosPropertyPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="PosProperty" name="posProperty">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>220</width>
         <height>120</height>
       </rect>
     </property>
</widget>)");
}

QString PosPropertyPlugin::includeFile() const
{
    return QLatin1String("posproperty.h");
}
