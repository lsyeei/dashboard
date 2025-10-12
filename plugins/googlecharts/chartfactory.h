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

#include "abstractgooglechart.h"
#include "chartobject.h"

#include <QList>
#include <QString>
#ifndef CHARTFACTORY_H
#define CHARTFACTORY_H

class ChartFactory
{
    ChartFactory();
public:
    static QString chartClassId(const QString &chartType);
    static ChartFactory *instance();
    QList<ChartObject> chartObjects();
    AbstractGoogleChart *create(const ChartObject &obj);
    QWidget *propertyWidget();
private:
    QList<ChartObject> charts;
    QWidget *widget{nullptr};
    void initCharts();
};

#endif // CHARTFACTORY_H
