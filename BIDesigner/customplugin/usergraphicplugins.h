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

#include <QHash>
#include <QMap>
#include <QObject>
#include "customplugin/userplugintype.h"
#include "igraphicplugin.h"

class UserPluginManageForm;
class UserPluginDO;
class QLayout;
class GraphicPluginGroup;
class UserGraphicPlugins : public QObject
{
    Q_OBJECT
public:
    UserGraphicPlugins(QWidget *parent);
    ~UserGraphicPlugins();
    bool load();
    bool reloadGroup(qint32 groupId);
    bool addNewGroup(const QString &groupName);
    QList<GraphicPluginGroup*> groupWidgets();
    IGraphicPlugin *getPluginById(const QString &pluginId) const;
    QList<IGraphicPlugin *> plugins() const;

Q_SIGNALS:
    void graphicItemChanged(IGraphicPlugin *plugin);
protected Q_SLOTS:
    void onGraphicItemSelected(QString itemId);
    void onRemoveGroup();
    void onGroupNameChanged(const QString &oldName, const QString &newName);
    void onImportUserGraphics(qint32 groupId);
    void onManageUserGraphics(qint32 groupId);
    void onPluginChanged(const UserPluginDO &data);
    void onPluginRemoved(const UserPluginDO &data);

private:
    QWidget *parentWidget{nullptr};
    QLayout *layout{nullptr};
    // 用户自定义控件索引的最小值
    const int minIdex{1000};
    // 所有控件集合，key 控件group与name 生成的唯一ID，value 控件对象
    QHash<GraphicPluginGroup *, qint32> groupWidgetMap;
    // 用户自定义插件集合
    QMap<QString, IGraphicPlugin *> pluginMap;
    UserPluginManageForm* form{nullptr};
    // 当前选中的插件
    // IGraphicPlugin *selectedPlugin;
    GraphicPluginGroup *createGroupWidget(const QString &group);
    /**
     * @brief suffix2Type 根据文件后缀确定插件类型
     * @param suffix 后缀名
     * @return 插件类型
     */
    UserPluginType suffix2Type(const QString &suffix);
    /**
     * @brief getThumbData 根据文件生成缩略图
     * @param file 全路径文件
     * @return 缩略图数据
     */
    QByteArray getThumbData(const QString &file);
    /**
     * @brief installPlugins 安装图元
     * @param plugins 图元信息
     * @param widget 图元组窗口
     */
    void installPlugins(QList<UserPluginDO> plugins, GraphicPluginGroup *widget);
    /**
     * @brief getGroupWidget 获取指定组的控件
     * @param groupId 组ID
     * @return 控件对象
     */
    GraphicPluginGroup *getGroupWidget(qint32 groupId);
};

#endif // USERGRAPHICPLUGINS_H
