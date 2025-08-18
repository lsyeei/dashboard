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

#ifndef IGRAPHICPLUGIN_H
#define IGRAPHICPLUGIN_H

#include <QObject>

class QString;
class QIcon;
class ICustomGraphic;
class IGraphicPlugin
{
public:
    virtual ~IGraphicPlugin() = default;
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual QString group() const = 0;
    virtual QString toolTip() const = 0;
    virtual QString whatsThis() const = 0;
    virtual QIcon icon() const = 0;

    /**
     * @brief 新建一个控件
     * @return 控件对象
     */
    virtual ICustomGraphic *createItem() = 0;
    /**
     * @brief 从XML文件创建控件
     * @param xml 包含控件信息的XML
     * @return 控件对象
     */
    virtual ICustomGraphic *createItem(const QString &xml) = 0;
    /**
     * @brief 属性控件
     * @return 属性控件
     */
    virtual QWidget *propertyWidget() = 0;

};

#define IGraphicPlugin_iid "cn.devhome.BIDEsigner.IGraphicPlugin"
Q_DECLARE_INTERFACE(IGraphicPlugin, IGraphicPlugin_iid)

#endif // IGRAPHICPLUGIN_H
