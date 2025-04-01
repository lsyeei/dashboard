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

#ifndef HTMLITEM_H
#define HTMLITEM_H

#include <QObject>
#include <abstracttextitem.h>

class HtmlItem : public AbstractTextItem
{
    Q_OBJECT
public:
    static QString SHAPE_ID;
    explicit HtmlItem(QGraphicsItem *parent = nullptr);
    explicit HtmlItem(const QString &xml, QGraphicsItem *parent = nullptr);
    QString classId() const override;
    // ICustomGraphic interface
    QString toXml() const override;


    // AbstractItem interface
protected:
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;

};

#endif // HTMLITEM_H
