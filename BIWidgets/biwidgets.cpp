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

#include "biwidgets.h"
#include "bicomboboxplugin.h"
#include "circlesliderplugin.h"
#include "colorpickerwidget.h"
#include "fillpropertyplugin.h"
#include "gradientcolorpickerplugin.h"
#include "textpropertyplugin.h"
#include <pospropertyplugin.h>
#include <linepropertyplugin.h>

BIWidgets::BIWidgets(QObject *parent) : QObject(parent)
{
    widgets.append(new ColorPickerWidget(this));
    widgets.append(new LinePropertyPlugin(this));
    widgets.append(new FillPropertyPlugin(this));
    widgets.append(new PosPropertyPlugin(this));
    widgets.append(new BIComboBoxPlugin(this));
    widgets.append(new TextPropertyPlugin(this));
    widgets.append(new CircleSliderPlugin(this));
    widgets.append(new GradientColorPickerPlugin(this));
}

QList<QDesignerCustomWidgetInterface *> BIWidgets::customWidgets() const
{
    return widgets;
}
