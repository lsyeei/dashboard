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
#include "abstractuserplugin.h"
#include "grouppropertyform.h"
#include "usersvgitem.h"
#include <QBuffer>
#include <QIcon>
#include "customplugin/userimageitem.h"
#include "graphicsitemgroup.h"
#include "icustomgraphic.h"

AbstractUserPlugin::AbstractUserPlugin(const QString &groupName, const UserPluginDO &info)
    : groupName(groupName), info(info) {}


QString AbstractUserPlugin::id() const
{
    return QString("%1-%2-%3").arg(groupName).arg(info.get_name()).arg(info.get_id());
}

QString AbstractUserPlugin::name() const
{
    return info.get_name();
}

QString AbstractUserPlugin::group() const
{
    return groupName;
}

QString AbstractUserPlugin::toolTip() const
{
    return info.get_name();
}

QString AbstractUserPlugin::whatsThis() const
{
    return info.get_note();
}

QIcon AbstractUserPlugin::icon() const
{
    QPixmap pixmap;
    pixmap.loadFromData(info.get_thumb());
    return QIcon(pixmap);
}

ICustomGraphic *AbstractUserPlugin::createItem()
{
    return createItem("");
}

ICustomGraphic *AbstractUserPlugin::createItem(const QString &xml)
{    
    switch(info.get_type()){
    case UserPluginType::SVG:
        return createSvgGraphics(xml);
        break;
    case UserPluginType::IMG:
        return createImgGraphics(xml);
        break;
    case UserPluginType::GROUP:
        return createGroupGraphics(xml);
        break;
    }
    return nullptr;
}

QWidget *AbstractUserPlugin::propertyWidget()
{
    switch(info.get_type()){
    case UserPluginType::SVG:
        // return createSvgGraphics(xml);
        break;
    case UserPluginType::IMG:
        // return createImgGraphics(xml);
        break;
    case UserPluginType::GROUP:
        return new GroupPropertyForm();
        break;
    }
    return nullptr;
}

GraphicsItemGroup *AbstractUserPlugin::createGroupGraphics(const QString &xml)
{
    if (!xml.isEmpty()) {
        return new GraphicsItemGroup(xml);
    }

    // 读取文件
    QString content;
    QFile file(info.get_path());
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    stream >> content;
    file.close();
    return new GraphicsItemGroup(content);
}

UserSvgItem *AbstractUserPlugin::createSvgGraphics(const QString &xml)
{
    UserSvgItem *graphic;
    if (!xml.isEmpty()) {
        graphic = new UserSvgItem(xml);
    }else{
        graphic = new UserSvgItem(id(), info.get_path());
    }
    return graphic;
}

UserImageItem *AbstractUserPlugin::createImgGraphics(const QString &xml)
{
    UserImageItem *graphic;
    if (!xml.isEmpty()) {
        graphic = new UserImageItem(xml);
    }else{
        graphic = new UserImageItem(id(), info.get_path());
    }
    return graphic;
}
