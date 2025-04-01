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

#ifndef SOLIDLINE_H
#define SOLIDLINE_H

#include <QObject>
#include "abstractlineitem.h"

class SolidLine : public AbstractLineItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit SolidLine(QGraphicsItem *parent = nullptr);
    explicit SolidLine(const QString &xml, QGraphicsItem *parent = nullptr);
    QString classId() const override;

protected:
    // AbstractLineItem interface
    void createPredefinedItem() override;
    QPainterPath linePath(QList<QPointF> points) const override;
};

#endif // SOLIDLINE_H
