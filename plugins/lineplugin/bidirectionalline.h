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

#ifndef BIDIRECTIONALLINE_H
#define BIDIRECTIONALLINE_H

#include <QObject>
#include "abstractlineitem.h"

class BidirectionalLine : public AbstractLineItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit BidirectionalLine(QGraphicsItem *parent = nullptr);
    explicit BidirectionalLine(const QString &xml,
                               QGraphicsItem *parent = nullptr);
    QString classId() const override;

    // AbstractLineItem interface
protected:
    QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    void createPredefinedItem() Q_DECL_OVERRIDE;
};

#endif // BIDIRECTIONALLINE_H
