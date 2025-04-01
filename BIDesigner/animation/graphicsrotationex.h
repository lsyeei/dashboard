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

#ifndef GRAPHICSROTATIONEX_H
#define GRAPHICSROTATIONEX_H

#include <QGraphicsRotation>

class GraphicsRotationX: public QGraphicsRotation
{
    Q_OBJECT
public:
    GraphicsRotationX(qreal angle, QObject *parent = nullptr)
        : QGraphicsRotation{parent}{
        setAngle(angle);
        setAxis(Qt::XAxis);
    }
};

class GraphicsRotationY: public QGraphicsRotation
{
    Q_OBJECT
public:
    GraphicsRotationY(qreal angle, QObject *parent = nullptr)
        : QGraphicsRotation{parent}{
        setAngle(angle);
        setAxis(Qt::YAxis);
    }
};

class GraphicsRotationZ: public QGraphicsRotation
{
    Q_OBJECT
public:
    GraphicsRotationZ(qreal angle, QObject *parent = nullptr)
        : QGraphicsRotation{parent}{
        setAngle(angle);
        setAxis(Qt::ZAxis);
    }
};
#endif // GRAPHICSROTATIONEX_H
