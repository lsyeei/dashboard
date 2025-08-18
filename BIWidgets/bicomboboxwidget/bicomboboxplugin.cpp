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

#include "bicomboboxplugin.h"
#include "bicombobox.h"
#include "svghelper.h"

#include <QtPlugin>

BIComboBoxPlugin::BIComboBoxPlugin(QObject *parent)
    : QObject(parent)
{}

void BIComboBoxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool BIComboBoxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *BIComboBoxPlugin::createWidget(QWidget *parent)
{
    return new BIComboBox(parent);
}

QString BIComboBoxPlugin::name() const
{
    return QLatin1String("BIComboBox");
}

QString BIComboBoxPlugin::group() const
{
    return QLatin1String("BI Designer Widgets");
}

QIcon BIComboBoxPlugin::icon() const
{
    SvgHelper svg(QLatin1String(":/combobox.svg"));
    return QIcon(svg.toPixmap({32,32}));
}

QString BIComboBoxPlugin::toolTip() const
{
    return QLatin1String("editable comboBox");
}

QString BIComboBoxPlugin::whatsThis() const
{
    return QLatin1String("editable comboBox width add and remmove button");
}

bool BIComboBoxPlugin::isContainer() const
{
    return false;
}

QString BIComboBoxPlugin::domXml() const
{
    return QLatin1String(R"(<widget class="BIComboBox" name="bIComboBox">
            </widget>)");
}

QString BIComboBoxPlugin::includeFile() const
{
    return QLatin1String("bicombobox.h");
}
