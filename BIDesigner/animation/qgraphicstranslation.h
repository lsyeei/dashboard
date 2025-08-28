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

#ifndef QGRAPHICSTRANSLATION_H
#define QGRAPHICSTRANSLATION_H

#include <QGraphicsTransform>

class QGraphicsTranslation : public QGraphicsTransform
{
    Q_OBJECT
public:
    explicit QGraphicsTranslation(QObject *parent = nullptr);
    QGraphicsTranslation(const QPointF &offset, QObject *parent = nullptr);
    QGraphicsTranslation(qreal dx, qreal dy, QObject *parent = nullptr);
    qreal translateX();
    qreal translateY();
    void setTranslate(qreal dx, qreal dy);
    void setTranslate(const QPointF &offset);
    // QGraphicsTransform interface
    void applyTo(QMatrix4x4 *matrix) const override;
private:
    qreal m_dx{0};
    qreal m_dy{0};

};

#endif // QGRAPHICSTRANSLATION_H
