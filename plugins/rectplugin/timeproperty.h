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
#ifndef TIMEPROPERTY_H
#define TIMEPROPERTY_H
#include "serializable.h"

class TimeProperty : public Serializable{

    Q_GADGET
    SERIALIZE(TimeProperty)
public:
    TimeProperty(){}
    ~TimeProperty(){}
private:
    QString time;
    QString format{"hh:mm"};
    // 自动刷新
    bool isAuto{false};
    // LCD 样式
    bool isLCD{false};
    // 对齐
    Qt::AlignmentFlag alignment{Qt::AlignCenter};
    QFont font;
    QColor foreground{Qt::white};
    QColor background{Qt::white};

    JSONFIELD(time, Time)
    JSONFIELD(format, Format)
    JSONFIELD(isAuto, IsAuto)
    JSONFIELD(isLCD, IsLcd)
    JSONFIELD(alignment, Alignment)
    JSONFIELD(font, Font)
    JSONFIELD(foreground, Foreground)
    JSONFIELD(background, Background)
};

Q_DECLARE_METATYPE(TimeProperty)
#endif // TIMEPROPERTY_H
