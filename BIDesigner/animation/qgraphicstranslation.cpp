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

#include "qgraphicstranslation.h"

QGraphicsTranslation::QGraphicsTranslation(QObject *parent)
    : QGraphicsTransform{parent}
{}

QGraphicsTranslation::QGraphicsTranslation(const QPointF &offset, QObject *parent)
    : QGraphicsTransform{parent}
{
    m_dx = offset.x();
    m_dy = offset.y();
}

QGraphicsTranslation::QGraphicsTranslation(qreal dx, qreal dy, QObject *parent)
    : QGraphicsTransform{parent}, m_dx{dx}, m_dy{dy}
{
    
}

qreal QGraphicsTranslation::translateX()
{
    return m_dx;
}

qreal QGraphicsTranslation::translateY()
{
    return m_dy;
}

void QGraphicsTranslation::setTranslate(qreal dx, qreal dy)
{
    m_dx = dx;
    m_dy = dy;
    update();
}

void QGraphicsTranslation::setTranslate(const QPointF &offset)
{
    m_dx = offset.x();
    m_dy = offset.y();
    update();
}

void QGraphicsTranslation::applyTo(QMatrix4x4 *matrix) const
{
    matrix->translate(m_dx, m_dy);
}
