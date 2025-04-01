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

#ifndef LINEPATH_H
#define LINEPATH_H

#include "abstractlinepath.h"

class LinePath : public AbstractLinePath
{
    Q_OBJECT

public:
    static QString PATH_ID;
    explicit LinePath(QGraphicsItem *parent = nullptr);
    explicit LinePath(const QString &xml, QGraphicsItem *parent = nullptr);
    QString classId() const override;

    // AbstractLinePath interface
protected:
    QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    void createPredefinedItem() Q_DECL_OVERRIDE;
    void afterCreateSelector(LineSelector *s) Q_DECL_OVERRIDE;
};

#endif // LINEPATH_H
