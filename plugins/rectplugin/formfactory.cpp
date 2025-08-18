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
#include "formfactory.h"
#include <QLayout>
#include "htmlpropertyform.h"
#include "rectpropertyform.h"
#include "textpropertyform.h"
#include "timepropertyform.h"
#include "webpropertyform.h"

FormFactory::FormFactory() {
    forms[FormType::RECT] = new RectPropertyForm();
    auto widget = new RectPropertyForm();
    widget->hideRound();
    forms[FormType::SHARP_RECT] = widget;
    widget = new RectPropertyForm();
    widget->addSubWidget(new TextPropertyForm());
    forms[FormType::TEXT] = widget;
    widget = new RectPropertyForm();
    widget->addSubWidget(new HtmlPropertyForm());
    forms[FormType::HTML] = widget;
    widget = new RectPropertyForm();
    widget->addSubWidget(new TimePropertyForm());
    forms[FormType::TIME] = widget;
    widget = new RectPropertyForm();
    widget->addSubWidget(new WebPropertyForm());
    forms[FormType::WEB] = widget;
}

FormFactory::~FormFactory()
{
    auto item=forms.cbegin();
    while(item != forms.cend()) {
        auto widget = item.value();
        item++;
        if (widget->parentWidget()) {
            continue;
        }
        delete widget;
    }
    forms.clear();
}

FormFactory *FormFactory::instance()
{
    static FormFactory *factory = new FormFactory();
    return factory;
}

QWidget *FormFactory::widget(FormType type)
{
    return forms[type];
}
