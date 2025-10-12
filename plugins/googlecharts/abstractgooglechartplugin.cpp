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

#include "abstractgooglechart.h"
#include "abstractgooglechartplugin.h"
#include "chartfactory.h"
#include "svghelper.h"


AbstractGoogleChartPlugin::AbstractGoogleChartPlugin(const ChartObject &obj):chart(obj) {}

QString AbstractGoogleChartPlugin ::id() const {
    return ChartFactory::chartClassId(chart.type);
}

QString AbstractGoogleChartPlugin ::name() const { return chart.name; }

QString AbstractGoogleChartPlugin ::group() const { return tr(u8"谷歌图表"); }

QString AbstractGoogleChartPlugin ::toolTip() const { return chart.name; }

QString AbstractGoogleChartPlugin ::whatsThis() const {
    QString  whate{tr(u8"谷歌图表-")};
    return whate + chart.name;
}

QIcon AbstractGoogleChartPlugin ::icon() const {
    return QIcon(SvgHelper(chart.icon).toPixmap(SvgHelper ::Normal));
}

ICustomGraphic *AbstractGoogleChartPlugin ::createItem() {
    return ChartFactory::instance()->create(chart);
}

ICustomGraphic *AbstractGoogleChartPlugin ::createItem(const QString &xml) {
    return new AbstractGoogleChart(xml);
}

QWidget *AbstractGoogleChartPlugin::propertyWidget()
{
    return ChartFactory::instance()->propertyWidget();
}
