﻿/**
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

#ifndef ABSTRACTUSERPLUGIN_H
#define ABSTRACTUSERPLUGIN_H

#include "customplugin/userplugindo.h"
#include "igraphicplugin.h"

class GraphicsItemGroup;
class UserImageItem;
class UserSvgItem;
class AbstractUserPlugin : public IGraphicPlugin
{
public:
    AbstractUserPlugin(const QString &groupName, const UserPluginDO &info);

    // IGraphicPlugin interface
public:
    QString id() const override;
    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QIcon icon() const override;
    ICustomGraphic *createItem() override;
    ICustomGraphic *createItem(const QString &xml) override;
    QWidget *propertyWidget() override;
private:
    QString groupName;
    UserPluginDO info;
    GraphicsItemGroup *createGroupGraphics(const QString &xml = nullptr);
    UserImageItem *createImgGraphics(const QString &xml = nullptr);
    UserSvgItem *createSvgGraphics(const QString &xml = nullptr);
};

#endif // ABSTRACTUSERPLUGIN_H
