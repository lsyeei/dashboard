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

#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QObject>
#include <abstractzoneitem.h>

class CircleItem : public AbstractZoneItem
{
    Q_OBJECT
    Q_PROPERTY(int radius READ radius WRITE setRadius FINAL)
public:
    static QString SHAPE_ID;
    explicit CircleItem(QGraphicsItem *parent = nullptr);
    explicit CircleItem(const QString &xml, QGraphicsItem *parent = nullptr);

    // ICustomGraphic interface
    QString classId() const override;

    // AbstractZoneItem interface
    int radius() const;
    void setRadius(int newRadius);

protected:
    QPainterPath shapePath() const override;
};

#endif // CIRCLEITEM_H
