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

#include <QHash>
#include <QString>
#ifndef FORMFACTORY_H
#define FORMFACTORY_H

class QWidget;
enum class FormType{
    RECT,SHARP_RECT,TEXT,HTML,TIME,WEB
};
/**
 * @brief The FormFactory class 单例模式
 */
class FormFactory
{
    FormFactory();
public:
    ~FormFactory();
    static FormFactory *instance();
    QWidget* widget(FormType type);
private:
    // key form类型, value QWidget 指针
    QHash<FormType, QWidget*> forms;
};

#endif // FORMFACTORY_H
