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

#ifndef PATHIMAGE_H
#define PATHIMAGE_H

#include <QBrush>
#include <QPainterPath>
#include <QPen>


struct TintedPath{
    QString id;
    QPainterPath path;
    QPen pen;
    QBrush brush;
};

class PathImage
{
public:
    PathImage(const QSize &size = {64,64});
    PathImage(const QSize &size, const TintedPath &path);
    QSize size() const;
    void addPath(const TintedPath &path);
    void insertPath(const QString &beforeIndex, const TintedPath &path);
    bool removePath(const QString &index);
    QPixmap toPixMap(qreal angle = 0, const QSize &size = QSize{});
private:
    qreal screenRatio;
    // 图像大小
    QSize m_size;
    // 路径集合
    QList<TintedPath> m_pathList;
};

#endif // PATHIMAGE_H
