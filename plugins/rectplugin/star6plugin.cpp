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

#include "star6plugin.h"
#include "rectpropertyform.h"
#include "star6item.h"
#include "svghelper.h"

Star6Plugin::Star6Plugin() {}
METHOD_DEFINE(Star6Plugin, "六角星", "通用", "六角星", "绘制六角星",
              :/icons/star6.svg, Star6Item, RectPropertyForm)
