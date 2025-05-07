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
#ifndef USERGRAPHICPLUGINS_H
#define USERGRAPHICPLUGINS_H

#include <QMap>
#include <QObject>
#include "igraphicplugin.h"

class QLayout;
class GraphicPluginGroup;
class UserGraphicPlugins : public QObject/*,  public IGraphicPlugin*/
{
    Q_OBJECT
public:
    UserGraphicPlugins(QWidget *parent);
    QMap<QString, GraphicPluginGroup *> load();

    // // IGraphicPlugin interface
    // QString id() const override;
    // QString name() const override;
    // QString group() const override;
    // QString toolTip() const override;
    // QString whatsThis() const override;
    // QIcon icon() const override;
    // ICustomGraphic *createItem() override;
    // ICustomGraphic *createItem(const QString &xml) override;
    // QWidget *propertyWidget() override;

Q_SIGNALS:
    void graphicItemChanged(IGraphicPlugin *plugin);
protected Q_SLOTS:
    void graphicItemSelected(QString itemId);
private:
    QWidget *parent;
    QLayout *layout;
    // 用户自定义控件索引的最小值
    static const int minIdex{1000};
    // 所有控件集合，key 控件group与name 生成的唯一ID，value 控件对象
    static QMap<QString, GraphicPluginGroup *> groupWidgetMap;
    // 用户自定义插件集合
    QMap<QString, IGraphicPlugin *> pluginMap;
    // 当前选中的插件
    IGraphicPlugin *selectedPlugin;

    void createGroupWidget(QString group);
};

#endif // USERGRAPHICPLUGINS_H
