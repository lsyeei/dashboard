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
#include "usersvgitem.h"
#include "svgpathdevice.h"
#include "zoneproperty.h"

#include <QSvgRenderer>

UserSvgItem::UserSvgItem(const QString &classId, const QString &svgPath, QGraphicsItem *parent)
    :AbstractZoneItem(parent), id(classId) {
    // 读取 SVG 文件
    QFile f(svgPath);
    if (!f.exists()) {
        return;
    }
    f.open(QFile::ReadOnly);
    auto array = f.readAll();
    f.close();
    QVariantList data;
    data << id << array;

    auto attr = attribute();
    attr->setData(data);

    auto pen = attr->getPen();
    pen.setStyle(Qt::NoPen);
    attr->setPen(pen);

    render = new QSvgRenderer(array);
    auto view = render->viewBoxF();
    setSize({60.0,60.0*view.height()/view.width()});
    attr->setExtraP1(view.width());
    attr->setExtraP2(view.height());

    initOrgPath();
}


UserSvgItem::UserSvgItem(const QString &xml, QGraphicsItem *parent)
    :AbstractZoneItem(parent)
{
    parseXML(xml);
}

QString UserSvgItem::classId() const
{
    return id;
}

void UserSvgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();

    auto attr = attribute();
    auto pen = attr->getPen();
    if(!pen.noPen()){
        auto arcSize = 0;
        if (attr->getRound()) {
            arcSize = attr->getArcSize();
        }
        painter->setPen(pen.getPen());
        painter->drawRoundedRect(logicRect, arcSize, arcSize);
        painter->setClipping(true);
        QPainterPath path;
        auto offset = pen.getWidth()/2;
        path.addRoundedRect(logicRect.adjusted(offset,offset,-offset,-offset), arcSize, arcSize);
        painter->setClipPath(path);
    }
    if (render) {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::TextAntialiasing);
        painter->setRenderHint(QPainter::VerticalSubpixelPositioning);
        render->render(painter, logicRect);
    }
    painter->restore();
}


QPainterPath UserSvgItem::shapePath() const
{
    auto rect = logicRect;
    auto view = render->viewBoxF();
    QTransform trans;
    trans.translate(rect.x(),rect.y());
    trans.scale(rect.width()/view.width(), rect.height()/view.height());
    auto shape = trans.map(orgPath);
    auto attr = attribute();
    auto pen = attr->getPen();
    if(!pen.noPen()){
        auto arcSize = 0;
        if (attr->getRound()) {
            arcSize = attr->getArcSize();
        }
        shape.addRoundedRect(logicRect,arcSize,arcSize);
    }
    return shape;
}

void UserSvgItem::parseXML(const QString &xml)
{
    AbstractZoneItem::parseXML(xml);
    auto attr = attribute();
    auto data = attr->getData();
    QList<QVariant> list;
    if (data.isValid()) {
        list = data.toList();
    }
    if (list.count() > 0) {
        id = list[0].toString();
    }
    if (list.count() > 1) {
        render = new QSvgRenderer(list[1].toByteArray());
        initOrgPath();
    }
}

void UserSvgItem::initOrgPath()
{
    auto rect = logicRect;
    SvgPathDevice device(rect.size().toSize());
    QPainter painter(&device);
    render->render(&painter, rect);
    auto list = device.getSvgPath();
    foreach (auto item, list) {
        orgPath.addPath(item);
    }
}
