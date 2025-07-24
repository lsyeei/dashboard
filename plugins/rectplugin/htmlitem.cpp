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

#include "htmlitem.h"
#include "zoneproperty.h"
#include <QTextDocument>

QString HtmlItem::SHAPE_ID = "HTML_TEXT_2024";
HtmlItem::HtmlItem(QGraphicsItem *parent)
    : AbstractTextItem(parent)
{
    QString text = "<div>html code</div>";
    textItem->setPlainText(text);
    textItem->setTextWidth(260);
    textItem->document()->setDefaultStyleSheet("li{margin-left:12px;}");
    attribute()->setData(text);
}

HtmlItem::HtmlItem(const QString &xml, QGraphicsItem *parent)
    : AbstractTextItem(parent)
{
    parseXML(xml);
}

QString HtmlItem::classId() const
{
    return SHAPE_ID;
}

void HtmlItem::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    AbstractTextItem::attributeChanged(oldAttr, newAttr);
    textItem->setHtml(attribute()->getData().toString());
}


QString HtmlItem::toXml() const
{
    return AbstractZoneItem::toXml();
}
