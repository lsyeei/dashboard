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

#ifndef RECTITEM_H
#define RECTITEM_H

#include "abstractzoneitem.h"
class RectItem : public AbstractZoneItem
{
    Q_OBJECT
    // Q_INTERFACES(QGraphicsItem)
public:
    static QString SHAPE_ID;
    explicit RectItem(QGraphicsItem *parent = nullptr);
    explicit RectItem(const QString &xml, QGraphicsItem *parent = nullptr);

    // ICustomGraphic interface
    QString classId() const override;
// Q_SIGNALS:
//     void stateChanged() override;
//     void undoEvent(const QString &text, QVariant undoData, QVariant redoData) override;
protected:
    Q_DISABLE_COPY(RectItem)
    // AbstractZoneItem interface
    QPainterPath shapePath() const override;
};

#endif // RECTITEM_H
