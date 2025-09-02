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
#include "abstractusergraphic.h"
#include "bigraphicsscene.h"
#include "graphicrootwidget.h"
#include "grouppropertyform.h"
#include "userpluginpropertyform.h"
#include "usersvgitem.h"
#include <QBuffer>
#include <QIcon>
#include <filetemplate.h>
#include "customgraphic/userimageitem.h"
#include "graphicsitemgroup.h"
#include "icustomgraphic.h"

AbstractUserGraphic::AbstractUserGraphic(const QString &groupName, const UserPluginDO &info)
    : groupName(groupName), info(info) {}

void AbstractUserGraphic::updatePluginInfo(const UserPluginDO &data)
{
    info = data;
}

QString AbstractUserGraphic::pluginId(const UserPluginDO &data)
{
    return QString("__user-%2-%3").arg(data.get_groupId()).arg(data.get_id());
}

QString AbstractUserGraphic::id() const
{
    return pluginId(info);
}

QString AbstractUserGraphic::name() const
{
    return info.get_name();
}

QString AbstractUserGraphic::group() const
{
    return groupName;
}

QString AbstractUserGraphic::toolTip() const
{
    if(info.get_note().isEmpty()){
        return info.get_name();
    }
    return info.get_note();
}

QString AbstractUserGraphic::whatsThis() const
{
    return info.get_note();
}

QIcon AbstractUserGraphic::icon() const
{
    QPixmap pixmap;
    pixmap.loadFromData(info.get_thumb());
    return QIcon(pixmap);
}

ICustomGraphic *AbstractUserGraphic::createItem()
{
    return createItem("");
}

ICustomGraphic *AbstractUserGraphic::createItem(const QString &xml)
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
    case UserPluginType::SYSTEM:
        return createSystemGraphics(xml);
        break;
    }
    return nullptr;
}

QWidget *AbstractUserGraphic::propertyWidget()
{
    switch(info.get_type()){
    case UserPluginType::SVG:
        return new UserPluginPropertyForm();
        break;
    case UserPluginType::IMG:
        return new UserPluginPropertyForm();
        break;
    case UserPluginType::GROUP:
        return new GroupPropertyForm();
        break;
    case UserPluginType::SYSTEM:
        return getSystemPropertyForm();
        break;
    }
    return nullptr;
}

GraphicsItemGroup *AbstractUserGraphic::createGroupGraphics(const QString &xml)
{
    if (!xml.isEmpty()) {
        return new GraphicsItemGroup(xml);
    }

    // 读取文件
    QString content = fileContent();
    return new GraphicsItemGroup(content);
}

UserSvgItem *AbstractUserGraphic::createSvgGraphics(const QString &xml)
{
    UserSvgItem *graphic;
    if (!xml.isEmpty()) {
        graphic = new UserSvgItem(xml);
    }else{
        graphic = new UserSvgItem(id(), appPath() + info.get_path());
    }
    return graphic;
}

ICustomGraphic *AbstractUserGraphic::createSystemGraphics(const QString &xml)
{
    // 读取文件
    QString content = fileContent();
    if (!xml.isEmpty()) {
        content = xml;
    }
    auto items = BIGraphicsScene::toItems(content);
    if (!items.isEmpty()) {
        return dynamic_cast<ICustomGraphic *>(items[0]);
    }
    return nullptr;
}

QString AbstractUserGraphic::appPath()
{
    return QCoreApplication::applicationDirPath();
}

QWidget *AbstractUserGraphic::getSystemPropertyForm()
{
    auto graphic = createSystemGraphics(fileContent());
    if (graphic == nullptr) {
        return nullptr;
    }

    auto id = graphic->classId();
    delete graphic;
    if (id.isEmpty()) {
        return nullptr;
    }
    auto plugin = GraphicsManager::instance()->getPluginById(id);
    if (plugin) {
        return plugin->propertyWidget();
    }
    return nullptr;
}

QString AbstractUserGraphic::fileContent()
{
    QString content;
    QFile file(QCoreApplication::applicationDirPath() + info.get_path());
    file.open(QFile::ReadOnly);
    content = QString::fromLocal8Bit(file.readAll());
    file.close();
    return content;
}

UserImageItem *AbstractUserGraphic::createImgGraphics(const QString &xml)
{
    UserImageItem *graphic;
    if (!xml.isEmpty()) {
        graphic = new UserImageItem(xml);
    }else{
        graphic = new UserImageItem(id(), appPath() + info.get_path());
    }
    return graphic;
}
