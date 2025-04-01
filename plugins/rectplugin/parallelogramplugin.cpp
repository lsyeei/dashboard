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

#include "parallelogramplugin.h"
#include "parallelogramitem.h"
#include "rectpropertyform.h"
#include "svghelper.h"

ParallelogramPlugin::ParallelogramPlugin() {}
METHOD_DEFINE(ParallelogramPlugin, "平行四边形", "通用", "平行四边形", "绘制平行四边形", :/icons/parallelogram.svg, ParallelogramItem, RectPropertyForm)
