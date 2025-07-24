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
#ifndef TIMEITEM_H
#define TIMEITEM_H

#include <QObject>
#include <abstracttextitem.h>
#include <QTimer>
#include <QPointer>

class TimeItem : public AbstractTextItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit TimeItem(QGraphicsItem *parent = nullptr);
    explicit TimeItem(const QString &xml, QGraphicsItem *parent = nullptr);
    ~TimeItem();
    QString classId() const override;
    // AbstractItem interface
protected:
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;
protected Q_SLOTS:
    void updateTime();
private:
    QScopedPointer<QTimer> timer{new QTimer()};
    QStringList families;

};

#endif // TIMEITEM_H
