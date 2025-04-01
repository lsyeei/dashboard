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

#include "endtypefactory.h"
#include "svgpathdevice.h"

#include <QDir>
#include <QDirIterator>
#include <QGuiApplication>
#include <QIcon>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QScreen>
#include <QSvgRenderer>
#include <svghelper.h>

EndTypeFactory::EndTypeFactory() {
    screenRatio = QGuiApplication::primaryScreen()->devicePixelRatio();
    if (endTypeMap.isEmpty()){
        QString defaultPath = ":/arrows";
        loadEndType(defaultPath);
        // auto arrow = getEndType("arrow", End);
        // QPainterPath p;
        // foreach (auto t, arrow.arrow) {
        //     p.addPath(t);
        // }
        // p.translate(-p.boundingRect() .topLeft());
        // qDebug() << "arrow " << arrow.size << p.boundingRect() << p;
    }
}

QSharedPointer<EndTypeFactory> EndTypeFactory::instance()
{
    static QSharedPointer<EndTypeFactory> instance(new EndTypeFactory());
    return instance;
}

EndType EndTypeFactory::getEndType(const QString &typeId, LineEndType::Category category)
{
    if (!endTypeMap.contains(typeId)) {
        return EndType();
    }
    EndType type = endTypeMap[typeId];
    if (category == LineEndType::Start) {
        QTransform trans;
        QList<PainterPathEx> lines;
        trans.rotate(180, Qt::YAxis);
        trans.translate(-type.size.width(), 0);
        foreach (auto path, type.line) {
            lines.append(trans.map(path));
            lines.last().setPen(path.getPen());
            lines.last().setBrush(path.getBrush());
        }
        type.line = lines;
        QList<PainterPathEx> arrows;
        foreach (auto path, type.arrow) {
            arrows.append(trans.map(path));
            arrows.last().setPen(path.getPen());
            arrows.last().setBrush(path.getBrush());
        }
        type.arrow = arrows;
    }
    return type;
}

void EndTypeFactory::loadEndType(QString path)
{
    QDir dir(path);
    if (!dir.exists()) {
        return;
    }
    QStringList filters;
    filters << "*.svg";
    dir.setNameFilters(filters);
    if(dir.isEmpty()){
        return;
    }
    auto textColor = QGuiApplication::palette().brush(QPalette::Text).color();
    auto fileList = dir.entryList();
    foreach (auto name, fileList) {
        auto id = name.left(name.indexOf("."));
        auto fileName = dir.filePath(name);
        // 替换svg绘图使用的颜色
        SvgHelper helper(fileName);
        helper.setStrokeColor(textColor);
        helper.setFillColor(textColor);
        QSvgRenderer render(helper.getContent());
        if (!render.elementExists("arrow") || !render.elementExists("line")) {
            continue;
        }
        EndType type;
        type.id = id;
        type.fileName = fileName;
        type.size = render.defaultSize();
        auto pathList = extractPath(&render, "line");
        QPainterPath svgPath;
        if (!pathList.isEmpty()) {
            type.line = pathList;
            foreach (auto p, pathList) {
                svgPath.addPath(p);
            }
        }else{
            continue;
        }
        pathList = extractPath(&render, "arrow");
        if (!pathList.isEmpty()) {
            type.arrow = pathList;
            QPainterPath path;
            foreach (auto p, pathList) {
                path.addPath(p);
                svgPath.addPath(p);
            }
            type.arrowSize = path.boundingRect().size();
        }else{
            continue;
        }
        QRectF thumbRect{{0,0}, type.size};
        thumbRect = thumbRect.united(svgPath.boundingRect());
        type.thumb = createThumb(&render, thumbRect);
        endTypeMap[id] = type;
    }
}

QPainterPath EndTypeFactory::flipPath(QPainterPath path)
{
    QTransform trans;
    trans.rotate(180, Qt::YAxis);
    auto width = path.boundingRect().width();
    trans.translate(-width-2, 0);
    return trans.map(path);
}

QPixmap EndTypeFactory::createThumb(QSvgRenderer *render, const QRectF &rect)
{
    render->setAspectRatioMode(Qt::KeepAspectRatio);
    auto size = render->defaultSize();
    if(!rect.isEmpty()){
        size = rect.size().toSize();
    }
    QPixmap pixmap(size * screenRatio);
    pixmap.setDevicePixelRatio(screenRatio);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
    painter.setRenderHint(QPainter::LosslessImageRendering);

    render->setViewBox(QRectF{0, 0, size.width() * screenRatio, size.height() * screenRatio});
    render->render(&painter, QRectF{0, 0, size.width() * screenRatio, size.height() * screenRatio});
    painter.end();
    return pixmap;
}

QList<PainterPathEx> EndTypeFactory::extractPath(QSvgRenderer *render, QString id)
{
    if (!render->elementExists(id)) {
        return QList<PainterPathEx>();
    }
    render->setAspectRatioMode(Qt::KeepAspectRatio);
    auto size = render->defaultSize();
    SvgPathDevice svgPath(size);
    QPainter p(&svgPath);
    render->render(&p, id, QRectF{0, 0, size.width()*1.0, size.height()*1.0});
    p.end();
    return svgPath.getSvgPath();
}

QMap<QString, QIcon> EndTypeFactory::getEndTypeList(LineEndType::Category category)
{
    QMap<QString, QIcon> result;
    QPixmap pixmap;
    for (auto item = endTypeMap.begin(); item != endTypeMap.end(); item ++) {
        pixmap = item->thumb;
        if (category == LineEndType::Start) {
            QTransform trans;
            trans.rotate(180, Qt::YAxis);
            trans.translate(-item->size.width(), 0);
            pixmap = pixmap.transformed(trans);
        }

        result[item.key()] = QIcon(pixmap);
    }
    return result;
}
