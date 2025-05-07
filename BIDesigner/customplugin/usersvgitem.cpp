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
    QByteArray array;
    QFile f(svgPath);
    if (!f.exists()) {
        return;
    }
    f.open(QFile::ReadOnly);
    QDataStream stream(&f);
    stream >> array;
    f.close();
    QList<QVariant> data;
    data << id << array;

    auto attr = attribute();
    attr->setData(data);

    render = new QSvgRenderer(array);
    // loadPath(array);
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

    if (render) {
        painter->save();

        auto attr = attribute();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::TextAntialiasing);
        painter->setRenderHint(QPainter::VerticalSubpixelPositioning);

        auto rect = attr->getLogicRect();
        auto view = render->viewBoxF();
        SvgPathDevice device(rect.size().toSize());
        painter->setWindow(rect.toRect());
        painter->setViewport(view.toRect());
        painter->rotate(attr->getRotate());
        render->render(painter);

        painter->restore();
    }
}


QPainterPath UserSvgItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto rect = attr->getLogicRect();
    auto view = render->viewBoxF();
    SvgPathDevice device(rect.size().toSize());
    QPainter painter(&device);
    painter.setWindow(rect.toRect());
    painter.setViewport(view.toRect());
    painter.rotate(attr->getRotate());
    render->render(&painter);
    auto list = device.getSvgPath();
    foreach (auto item, list) {
        path.addPath(item);
    }
    return path;
}

// void UserSvgItem::loadPath(QByteArray content)
// {
//     render = new QSvgRenderer(content);
//     auto rect = attribute()->getLogicRect();
//     render->setViewBox(rect);
//     SvgPathDevice device(rect.size().toSize());
//     QPainter painter(&device);
//     render->render(&painter);
//     auto list = device.getSvgPath();
//     foreach (auto item, list) {
//         path.addPath(item);
//     }
// }


void UserSvgItem::parseXML(const QString &xml)
{
    AbstractZoneItem::parseXML(xml);
    auto data = attribute()->getData();
    QList<QVariant> list;
    if (data.isValid()) {
        list = data.toList();
    }
    if (list.count() > 0) {
        id = list[0].toString();
    }
    if (list.count() > 1) {
        render = new QSvgRenderer(list[1].toByteArray());
    }
}
