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
#include "linepropertyform.h"

FormFactory::FormFactory() {
    forms[FormType::LINE] = new LinePropertyForm();
    auto widget = new LinePropertyForm();
    widget->showCornerProperty();
    forms[FormType::CORNER_LINE] = widget;
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
