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

#ifndef DIAMONDITEM_H
#define DIAMONDITEM_H

#include <QObject>
#include <abstractzoneitem.h>

class DiamondItem : public AbstractZoneItem
{
    Q_OBJECT
public:
    static QString SHAPE_ID;
    explicit DiamondItem(QGraphicsItem *parent = nullptr);
    explicit DiamondItem(const QString &xml, QGraphicsItem *parent = nullptr);

    // ICustomGraphic interface
    QString classId() const override;

    // AbstractZoneItem interface
protected:
    QPainterPath shapePath() const override;

};

#endif // DIAMONDITEM_H
