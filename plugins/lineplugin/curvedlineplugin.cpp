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

#include "curvedlineplugin.h"
#include "curvedline.h"
#include "linepropertyform.h"
#include "svghelper.h"

CurvedLinePlugin::CurvedLinePlugin() {}
METHOD_DEFINE(CurvedLinePlugin, "曲线", "线条", "绘制曲线", "绘制曲线", :/icons/curvedLine.svg, CurvedLine, LinePropertyForm)
