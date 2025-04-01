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

#include "colorpickerwidget.h"
#include "colorpicker.h"
#include "svghelper.h"

#include <QtPlugin>

ColorPickerWidget::ColorPickerWidget(QObject *parent)
    : QObject(parent)
{}

void ColorPickerWidget::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ColorPickerWidget::isInitialized() const
{
    return m_initialized;
}

QWidget *ColorPickerWidget::createWidget(QWidget *parent)
{
    return new ColorPicker(parent);
}

QString ColorPickerWidget::name() const
{
    return QLatin1String("ColorPicker");
}

QString ColorPickerWidget::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon ColorPickerWidget::icon() const
{
    SvgHelper svg(QLatin1String(":/icons/dropper.svg"));
    return QIcon(svg.toPixmap({32,32}));
}

QString ColorPickerWidget::toolTip() const
{
    return QLatin1String("color picker");
}

QString ColorPickerWidget::whatsThis() const
{
    return QLatin1String("");
}

bool ColorPickerWidget::isContainer() const
{
    return false;
}

QString ColorPickerWidget::domXml() const
{
    return QLatin1String(R"(<widget class="ColorPicker" name="colorPicker">
    <property name="geometry">
       <rect>
         <x>0</x>
         <y>0</y>
         <width>50</width>
         <height>24</height>
       </rect>
     </property>
</widget>)");
}

QString ColorPickerWidget::includeFile() const
{
    return QLatin1String("colorpicker.h");
}
