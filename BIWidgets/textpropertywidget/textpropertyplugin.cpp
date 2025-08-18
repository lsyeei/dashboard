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

#include "textpropertyplugin.h"
#include "svghelper.h"
#include "textproperty.h"

#include <QtPlugin>

TextPropertyPlugin::TextPropertyPlugin(QObject *parent)
    : QObject(parent)
{}

void TextPropertyPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool TextPropertyPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *TextPropertyPlugin::createWidget(QWidget *parent)
{
    return new TextProperty(parent);
}

QString TextPropertyPlugin::name() const
{
    return QLatin1String("TextProperty");
}

QString TextPropertyPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon TextPropertyPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/text.svg"));
    QWidget widget;
    auto textColor = widget.palette().brush(QPalette::Text).color();
    svg.setFillColor(textColor);
    svg.setStrokeColor(textColor);
    return QIcon(svg.toPixmap({32,32}));
}

QString TextPropertyPlugin::toolTip() const
{
    return QLatin1String("text property");
}

QString TextPropertyPlugin::whatsThis() const
{
    return QLatin1String("set text font and paragraph");
}

bool TextPropertyPlugin::isContainer() const
{
    return false;
}

QString TextPropertyPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="TextProperty" name="textProperty">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>239</width>
         <height>355</height>
       </rect>
     </property>
</widget>)");
}

QString TextPropertyPlugin::includeFile() const
{
    return QLatin1String("textproperty.h");
}
