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
#include "qtextcursor.h"
#include "zoneproperty.h"

#include <QFontDatabase>

QString TimeItem::SHAPE_ID = "TIME_2024";

TimeItem::TimeItem(QGraphicsItem *parent) : AbstractTextItem(parent)
{    
    int lcdFontId = QFontDatabase::addApplicationFont("://font/lcdNumber.TTF");
    if (lcdFontId == -1) {
        qDebug() << "字体加载失败！";
    }else{
        families = QFontDatabase::applicationFontFamilies(lcdFontId);
    }

    TimeProperty property;
    property.setFormat("hh:mm:ss");
    property.setIsLcd(false);
    property.setFont(textItem->font());
    property.setForeground(textItem->defaultTextColor());
    property.setTime(QDateTime::currentDateTime().toString(property.getFormat()));
    attribute()->setData(QVariant::fromValue(property));
    updateTime();
    connect(timer.data(), SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->setInterval(1000);
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
    auto attr = attribute();
    auto data = attr->getData();
    if (data.isNull()) {
        return;
    }
    auto property = data.value<TimeProperty>();
    QString format = property.getFormat();
    auto txt = property.getTime();
    if (property.getIsAuto()) {
        auto locale = QLocale::system();
        auto time = QDateTime::currentDateTime();
        txt = locale.toString(time, format);
    }
    textItem->setPlainText(txt);

    auto font = property.getFont();
    if (property.getIsLcd()) {
        if (!families.isEmpty()) {
            QStringList familyList;
            familyList << families << font.families();
            font.setFamilies(familyList);
        }
    }
    textItem->setFont(font);
    textItem->setDefaultTextColor(property.getForeground());
    auto cursor = textItem->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(property.getAlignment());
    cursor.beginEditBlock();
    cursor.mergeBlockFormat(blockFormat);
    cursor.endEditBlock();
}

void TimeItem::propertyChanged(const TimeProperty &property)
{
    if (property.getIsAuto()) {
        timer->stop();
        updateTime();
        timer->start();
    }else{
        if (timer->isActive()) {
            timer->stop();
        }
        updateTime();
    }
}

void TimeItem::updateAttribute(BaseProperty *attr)
{
    AbstractTextItem::updateAttribute(attr);
    auto property = dynamic_cast<ZoneProperty*>(attr);
    auto data = property->getData();
    if (!data.isNull()) {
        propertyChanged(data.value<TimeProperty>());
    }
}

void TimeItem::attributeSwitched(int oldIndex, int newIndex)
{
    AbstractTextItem::attributeSwitched(oldIndex, newIndex);
    auto data = attribute()->getData();
    if (data.isNull()) {
        return;
    }
    textItem->setTextWidth(attribute()->getWidth());
    propertyChanged(data.value<TimeProperty>());
}

QString TimeItem::toXml() const
{
    return AbstractZoneItem::toXml();
}

void TimeItem::parseXML(const QString &xml)
{
    AbstractZoneItem::parseXML(xml);
    auto data = attribute()->getData();
    if (data.isNull()) {
        return;
    }
    textItem->setTextWidth(attribute()->getWidth());
    propertyChanged(data.value<TimeProperty>());
}
