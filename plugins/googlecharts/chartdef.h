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
#ifndef CHARTDEF_H
#define CHARTDEF_H

#include "chartobject.h"

#include <QList>
namespace ChartDefine {
    QList<ChartObject> list{
{"ColumnChart","柱形图",":/icons/histogram.svg", R"(
[
  ['', 'Germany', 'USA', 'Brazil', 'Canada', 'France', 'RU'],
  ['', 700, 300, 400, 500, 600, 800]
])",R"(
{
  "title": "Countries"
})","https://developers.google.cn/chart/interactive/docs/gallery/columnchart?hl=zh-cn"},

{"BarChart","条形图",":/icons/barchart.svg", R"(
[
  ['Galaxy', 'Distance', 'Brightness'],
  ['Canis Major Dwarf', 8000, 23.3],
  ['Sagittarius Dwarf', 24000, 4.5],
  ['Ursa Major II Dwarf', 30000, 14.3],
  ['Lg. Magellanic Cloud', 50000, 0.9],
  ['Bootes I', 60000, 13.1]
])",R"(
{
  "chart": {
    "title": "Nearby galaxies",
    "subtitle": "distance on the left, brightness on the right"
  },
  "bars": "horizontal",
  "series": {
    "0": { "axis": "distance" },
    "1": { "axis": "brightness" }
  },
  "axes": {
    "x": {
      "distance": {"label": "parsecs"},
      "brightness": {"side": "top", "label": "apparent magnitude"}
    }
  }
})","https://developers.google.cn/chart/interactive/docs/gallery/barchart?hl=zh-cn"},

// {"Histogram","直方图",":/icons/histogram.svg", R"(
// [
//   ['Quarks', 'Leptons', 'Gauge Bosons', 'Scalar Bosons'],
//   [2/3, -1, 0, 0],
//   [2/3, -1, 0, null],
//   [2/3, -1, 0, null],
//   [-1/3, 0, 1, null],
//   [-1/3, 0, -1, null],
//   [-1/3, 0, null, null],
//   [-1/3, 0, null, null]
// ])",R"(
// {
//   "title": "Charges of subatomic particles",
//   "legend": { "position": "top", "maxLines": 2 },
//   "colors": ["#5C3292", "#1A8763", "#871B47", "#999999"],
//   "interpolateNulls": false
// })","https://developers.google.cn/chart/interactive/docs/gallery/histogram?hl=zh-cn"},

{"LineChart","折线图",":/icons/linechart.svg",R"(
[
  ['Year', 'Sales', 'Expenses'],
  ['2004',  1000,      400],
  ['2005',  1170,      460],
  ['2006',  660,       1120],
  ['2007',  1030,      540]
])",R"(
{
  "title": "Company Performance",
  "curveType": "function",
  "legend": { "position": "bottom" }
})","https://developers.google.cn/chart/interactive/docs/gallery/linechart?hl=zh-cn"},

{"PieChart","饼图",":/icons/piechart.svg",R"(
[
  ['Task', 'Hours per Day'],
  ['Work',     11],
  ['Eat',      2],
  ['Commute',  2],
  ['Watch TV', 2],
  ['Sleep',    7]
])",R"(
{
  "title": "My Daily Activities",
  "is3D": true
})","https://developers.google.cn/chart/interactive/docs/gallery/piechart?hl=zh-cn"},

{"AreaChart","面积图",":/icons/areachart.svg", R"(
[
  ['Year', 'Sales', 'Expenses'],
  ['2013',  1000,      400],
  ['2014',  1170,      460],
  ['2015',  660,       1120],
  ['2016',  1030,      540]
])", R"(
{
  "title": "Company Performance",
  "hAxis": {"title": "Year",  "titleTextStyle": {"color": "#333"}},
  "vAxis": {"minValue": 0}
})","https://developers.google.cn/chart/interactive/docs/gallery/areachart?hl=zh-cn"},

{"SteppedAreaChart","阶梯面积图",":/icons/steppedareachart.svg", R"(
[
  ['Director (Year)',  'Rotten Tomatoes', 'IMDB'],
  ['Alfred Hitchcock (1935)', 8.4,         7.9],
  ['Ralph Thomas (1959)',     6.9,         6.5],
  ['Don Sharp (1978)',        6.5,         6.4],
  ['James Hawes (2008)',      4.4,         6.2]
])",R"(
{
  "title": "The decline of \'The 39 Steps\'",
  "vAxis": {"title": "Accumulated Rating"},
  "isStacked": true
})","https://developers.google.cn/chart/interactive/docs/gallery/steppedareachart?hl=zh-cn"},

{"CandlestickChart","K线图",":/icons/candlestickchart.svg",R"(
[
  ['', '', '', '', ''],
  ['Mon', 20, 28, 38, 45],
  ['Tue', 31, 38, 55, 66],
  ['Wed', 50, 55, 77, 80],
  ['Thu', 77, 77, 66, 50],
  ['Fri', 68, 66, 22, 15]
])",R"(
{
  "legend":"none"
})","https://developers.google.cn/chart/interactive/docs/gallery/candlestickchart?hl=zh-cn"},

{"ScatterChart","散点图",":/icons/scatterchart.svg", R"(
[
  ['Age', 'Weight'],
  [ 8,      12],
  [ 4,      5.5],
  [ 11,     14],
  [ 4,      5],
  [ 3,      3.5],
  [ 6.5,    7]
])",R"(
{
  "title": "Age vs. Weight comparison",
  "hAxis": {"title": "Age", "minValue": 0, "maxValue": 15},
  "vAxis": {"title": "Weight", "minValue": 0, "maxValue": 15},
  "legend": "none"
})","https://developers.google.cn/chart/interactive/docs/gallery/scatterchart?hl=zh-cn"},

{"BubbleChart","气泡图",":/icons/bubblechart.svg", R"(
[
  ['ID', 'Life Expectancy', 'Fertility Rate', 'Region',     'Population'],
  ['CAN',    74.66,              3.67,      'North America',  33739900],
  ['DEU',    79.84,              1.26,      'Europe',         81902307],
  ['DNK',    78.6,               1.84,      'Europe',         5523095],
  ['EGY',    72.73,              2.78,      'Middle East',    59716203]
])",R"(
{
  "title": "Fertility rate vs life expectancy in selected countries (2010). X=Life Expectancy, Y=Fertility, Bubble size=Population, Bubble color=Region",
  "hAxis": {"title": "Life Expectancy"},
  "vAxis": {"title": "Fertility Rate"},
  "bubble": {"textStyle": {"fontSize": 11}}
})","https://developers.google.cn/chart/interactive/docs/gallery/bubblechart?hl=zh-cn"},

{"ComboChart","组合图",":/icons/combochart.svg",R"(
[
  ['Month', 'Bolivia', 'Ecuador', 'Madagascar', 'Papua New Guinea', 'Rwanda', 'Average'],
  ['2004/05',  165,      938,         522,             998,           450,      614.6],
  ['2005/06',  135,      1120,        599,             1268,          288,      682],
  ['2006/07',  157,      1167,        587,             807,           397,      623],
  ['2007/08',  139,      1110,        615,             968,           215,      609.4],
  ['2008/09',  136,      691,         629,             1026,          366,      569.6]
])",R"(
{
  "title" : "Monthly Coffee Production by Country",
  "vAxis": {"title": "Cups"},
  "hAxis": {"title": "Month"},
  "seriesType": "bars",
  "series": {"5": {"type": "line"}}
})","https://developers.google.cn/chart/interactive/docs/gallery/combochart?hl=zh-cn"},

{"Gauge","仪表盘",":/icons/gauge.svg",R"(
[
  ['Label', 'Value'],
  ['CPU', 55]
])",R"(
{
  "width": 400, "height": 120,
  "redFrom": 90, "redTo": 100,
  "yellowFrom":75, "yellowTo": 90,
  "minorTicks": 5
})","https://developers.google.cn/chart/interactive/docs/gallery/gauge?hl=zh-cn"},

{"Table","表格",":/icons/table.svg",R"(
[
  ['name', 'Salary', 'Full Time Employee'],
  ['Mike',  {v: 10000, f: '$10,000'}, true],
  ['Jim',   {v:8000,   f: '$8,000'},  false],
  ['Alice', {v: 12500, f: '$12,500'}, true],
  ['Bob',   {v: 7000,  f: '$7,000'},  true]
])",R"(
{
  "showRowNumber": true,
  "width": "100%",
  "height": "100%"
})","https://developers.google.cn/chart/interactive/docs/gallery/table?hl=zh-cn"},
    };
}

#endif // CHARTDEF_H
