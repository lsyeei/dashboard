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
#include "webplugin.h"
#include "rectpropertyform.h"
#include "svghelper.h"
#include "webitem.h"
#include "webpropertyform.h"
#include <QWebEnginePage>

WebPlugin::WebPlugin() {
    // 通过加载QWebEnginePage初始化WebEngine环境，提高后期加载 QWebEngineView 的速度
    page = new QWebEnginePage(this);
    page->load(QUrl("https://www.baidu.com"));
    connect(page, &QWebEnginePage::loadFinished, this, [&]{
        page->deleteLater();
    });
}

WebPlugin::~WebPlugin()
{
    if(page){
        delete page;
        page = nullptr;
    }
}
METHOD_DEFINE(WebPlugin, "网页", "通用", "内嵌网页", "内嵌网页", :/icons/web.svg, WebItem, RectPropertyForm)

QWidget *WebPlugin::propertyWidget()
{
    auto widget =  new RectPropertyForm();
    // widget->addWebProperty();
    widget->addSubWidget(new WebPropertyForm());
    return widget;
}
