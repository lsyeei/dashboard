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

#include "svghelper.h"
#include "svghelperprivate.h"
#include <QFile>
#include <QSvgRenderer>
#include <QRegularExpression>
#include <QDomElement>
#include <QDebug>
#include <QtWidgets/QWidget>

SvgHelperPrivate::SvgHelperPrivate(SvgHelper *parent): q_ptr(parent)
{}

SvgHelperPrivate::~SvgHelperPrivate()
{}

QString SvgHelperPrivate::getProperty(const QString &nodeName, const QString property) const
{
    QDomNode dom = svgDoc.namedItem(nodeName);
    QString value = dom.toElement().attribute(property);
    if (!value.isEmpty()){
        return value;
    }
    QDomNamedNodeMap attrs = dom.attributes();
    QDomNode node = attrs.namedItem("style");
    if(node.isNull()){
        return "";
    }
    QString style = node.nodeValue();
    QRegularExpression reg(property + ":\\s*(\\d+)\\w*;?");
    QRegularExpressionMatch matched = reg.match(style);

    if (!matched.hasMatch()) {
        return "";
    }
    return matched.captured(1);
}

SvgHelper::SvgHelper():d_ptr(new SvgHelperPrivate(this))
{}

SvgHelper::SvgHelper(const QString &filePath):d_ptr(new SvgHelperPrivate(this))
{
    Q_D(SvgHelper);
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    d->svgDoc.setContent(data);
}

SvgHelper::SvgHelper(const QByteArray &content):d_ptr(new SvgHelperPrivate(this))
{
    Q_D(SvgHelper);

    d->svgDoc.setContent(content);
}

SvgHelper::~SvgHelper()
{}

qint16 SvgHelper::width() const
{
    Q_D(const SvgHelper);
    QString height = d->getProperty("svg", "width");
    return height.toInt();
}

void SvgHelper::setWidth(qint16 width)
{
    Q_D(SvgHelper);
    d->setProperty({{"width", QString(width)}});
}

qint16 SvgHelper::height() const
{
    Q_D(const SvgHelper);
    QString height = d->getProperty("svg", "height");
    return height.toInt();
}

void SvgHelper::setHeight(qint16 height)
{
    Q_D(SvgHelper);
    d->setProperty({{"height", QString(height)}});
}

QSize SvgHelper::size() const
{
    return {width(), height()};
}

void SvgHelper::setSize(QSize size)
{
    Q_D(SvgHelper);
    d->setProperty({{"height", QString::number(size.height())},
                 {"width", QString::number(size.width())}});
}

void SvgHelper::setFillColor(QColor color)
{
    Q_D(SvgHelper);
    d->setProperty({{"fill", color.name(QColor::HexRgb)}});
}

void SvgHelper::setStrokeColor(QColor color)
{
    Q_D(SvgHelper);
    d->setProperty({{"stroke", color.name(QColor::HexRgb)}});
}

void SvgHelper::setStrokeWidth(qint16 width)
{
    Q_D(SvgHelper);
    d->setProperty({{"stroke-width", QString(width)}});
}

void SvgHelper::render(QPainter *painter, const QRectF &bounds)
{
    Q_D(SvgHelper);
    if(d->svgDoc.isNull()){
        return;
    }
    QSvgRenderer render(d->svgDoc.toByteArray());
    render.render(painter, bounds);
}

QByteArray SvgHelper::getContent() const
{
    Q_D(const SvgHelper);
    if(d->svgDoc.isNull()){
        return QByteArray();
    }
    return d->svgDoc.toByteArray();
}

QPixmap SvgHelper::toPixmap(ColorGroup group) const
{
    return toPixmap(QSize(), group);
}

QPixmap SvgHelper::toPixmap(const QSize &size, ColorGroup group) const
{
    Q_D(const SvgHelper);
    if(d->svgDoc.isNull()){
        return QPixmap(size);
    }
    if (group > None) {
        QPalette::ColorGroup g = QPalette::Normal;
        if (group == Normal) {
            g = QPalette::Normal;
        }else if(group == Disabled){
            g = QPalette::Disabled;
        }else if(group == Active){
            g = QPalette::Active;
        }else if(group == Inactive){
            g = QPalette::Inactive;
        }
        QWidget widget;
        auto color = widget.palette().brush(g, QPalette::Text).color();
        auto item = const_cast<SvgHelper*>(this);
        item->setStrokeColor(color);
        item->setFillColor(color);
    }
    QSvgRenderer render(d->svgDoc.toByteArray());
    QSize imgSize = size;
    if (!size.isValid()) {
        imgSize = render.viewBoxF().size().toSize();
    }
    QPixmap pixmap(imgSize);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    render.render(&painter, {{0,0}, size});
    painter.end();
    return pixmap;
}

void SvgHelperPrivate::setProperty(QMap<QString, QString> property)
{
    QDomNode root = svgDoc.namedItem("svg");
    for(auto iter = property.begin(); iter != property.end(); iter++){
        QString key = iter.key();
        if (key == "width" || key == "height"){
            // 整幅图属性
            setNodeProperty(root, key, iter.value(), 1);
        } else {
            // 各个绘制单元属性
            QDomNodeList childs = root.childNodes();
            for (int i = 0; i < childs.count(); i++)
            {
                if (!childs.at(i).isElement())
                {
                    continue;
                }
                setNodeProperty(childs.at(i).toElement(), key, iter.value(), -1);
            }
        }
    }
}

void SvgHelperPrivate::setNodeProperty(const QDomNode &dom, const QString property, const QString value, qint16 deep)
{
    if (dom.isNull()) {
        return;
    }
    QDomNamedNodeMap attrs = dom.attributes();
    QDomNode node = attrs.namedItem(property);
    if (node.isNull()){
        node = attrs.namedItem("style");
        if(!node.isNull()){
            QString style = node.nodeValue();
            QRegularExpression reg(property + ":\\s*\\d+\\w*;?");
            if (style.indexOf(reg) == -1) {
                dom.toElement().setAttribute(property, value);
            }else{
                style = style.replace(QRegularExpression(property + ":\\s*\\d+(\\w*;?)"), property + ":" + value + "\\1");
                node.setNodeValue(style);
            }
        }else{
            dom.toElement().setAttribute(property, value);
        }
    } else {
        if(node.nodeValue().trimmed().compare("none", Qt::CaseInsensitive) != 0){
            node.setNodeValue(value);
        }
    }
    if (deep == 1){
        return;
    }
    deep --;
    // 递归替换属性
    for (int i = 0; i < dom.childNodes().count(); i++)
    {
        QDomNode child = dom.childNodes().at(i);
        if (!child.isElement())
        {
            continue;
        }
        setNodeProperty(child, property, value, deep);
    }
}
