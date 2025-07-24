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
#include "timeitem.h"
#include "timeproperty.h"
#include "zoneproperty.h"

#include <QFontDatabase>

QString TimeItem::SHAPE_ID = "TIME_2024";

TimeItem::TimeItem(QGraphicsItem *parent) : AbstractTextItem(parent)
{
    TimeProperty property;
    property.setFormat("HH:mm:ss");
    property.setIsLcd(false);
    property.setFont(textItem->font());
    property.setForeground(textItem->defaultTextColor());
    attribute()->setData(QVariant::fromValue(property));
    updateTime();
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->setInterval(1000);
    timer->start();

    int lcdFontId = QFontDatabase::addApplicationFont("://font/lcdNumber.TTF");
    if (lcdFontId == -1) {
        qDebug() << "字体加载失败！";
    }else{
        families = QFontDatabase::applicationFontFamilies(lcdFontId);
    }
}

TimeItem::TimeItem(const QString &xml, QGraphicsItem *parent) : TimeItem(parent)
{
    parseXML(xml);
}

TimeItem::~TimeItem()
{
    timer->stop();
}

QString TimeItem::classId() const
{
    return SHAPE_ID;
}

void TimeItem::updateTime()
{
    QString format{"H:mm:ss"};
    auto attr = attribute();
    auto data = attr->getData();
    if (!data.isNull()) {
        auto property = data.value<TimeProperty>();
        if (!property.getFormat().isEmpty()) {
            format = property.getFormat();
        }
        auto font = property.getFont();
        if (property.getIsLcd()) {
            if (!families.isEmpty()) {
                font.setFamilies(families);
            }
        }
        textItem->setFont(font);
        textItem->setDefaultTextColor(property.getForeground());
    }
    auto time = QTime::currentTime();
    auto txt = time.toString(format);
    textItem->setPlainText(txt);
}
void TimeItem::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    AbstractTextItem::attributeChanged(oldAttr, newAttr);
    timer->stop();
    updateTime();
    timer->start();
}
