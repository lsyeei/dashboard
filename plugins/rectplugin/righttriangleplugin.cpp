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

#include "righttriangleplugin.h"
#include "rectpropertyform.h"
#include "rightttriangleitem.h"
#include "svghelper.h"

RightTrianglePlugin::RightTrianglePlugin() {}
METHOD_DEFINE(RightTrianglePlugin, "直角三角形", "通用", "直角三角形", "绘制直角三角形",
              :/icons/righttriangle.svg, RightTriangleItem, RectPropertyForm)
