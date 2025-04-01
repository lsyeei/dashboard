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

#include "pathimage.h"
#include "qdebug.h"
#include "qscreen.h"

#include <QGuiApplication>
#include <QPainter>

PathImage::PathImage(const QSize &size) : m_size(size)
{
    screenRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
}

PathImage::PathImage(const QSize &size, const TintedPath &path) : PathImage(size)
{
    m_pathList << path;
}

QSize PathImage::size() const
{
    return m_size;
}

void PathImage::addPath(const TintedPath &path)
{
    insertPath("", path);
}

void PathImage::insertPath(const QString &beforeIndex, const TintedPath &path)
{
    if (beforeIndex.isEmpty()) {
        m_pathList << path;
        return;
    }
    m_pathList.insert(std::find_if(m_pathList.begin(), m_pathList.end(),
                                   [=](TintedPath item){
                                    return item.id.compare(beforeIndex) == 0;
                                    })
                      , path);
}

bool PathImage::removePath(const QString &index)
{
    auto item = std::find_if(m_pathList.begin(), m_pathList.end(),
                 [=](TintedPath item){
                     return item.id.compare(index) == 0;
    });
    if (item == m_pathList.end()) {
        return false;
    }
    m_pathList.remove(std::distance(m_pathList.begin(),item));
    return true;
}

QPixmap PathImage::toPixMap(qreal angle, const QSize &size)
{
    auto imgSize = size;
    if (size.isEmpty()) {
        imgSize = m_size;
    }
    // 创建位图,根据屏幕缩放比例调整图形大小
    QPixmap pixmap(imgSize*screenRatio);
    pixmap.fill(Qt::transparent);
    pixmap.setDevicePixelRatio(screenRatio);
    // 设置坐标系
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
    painter.setRenderHint(QPainter::LosslessImageRendering);
    painter.setViewport({{0,0}, imgSize});
    painter.setWindow({{-m_size.width()/2, -m_size.height()/2},m_size});

    // 旋转
    painter.rotate(angle);
    // 绘制
    foreach (auto item, m_pathList) {
        painter.fillPath(item.path, item.brush);
        painter.strokePath(item.path, item.pen);
    }

    painter.end();
    return pixmap;
}
