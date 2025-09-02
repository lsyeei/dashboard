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
#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <QObject>
#include <QFutureWatcher>
#include <QHash>
#include "customgraphic/userplugintype.h"
#include "customgraphic/userplugindo.h"
class IGraphicPlugin;
class ICustomGraphic;

enum class GraphicType{
    // 预定义
    PREDEFINE,
    // 用户
    USER
};
struct GraphicGroup{
    // 排序
    int order;
    // 组ID
    int groupId;
    // 组名
    QString groupName;
    // 相同组的图元列表
    QList<IGraphicPlugin*> list;
    // 是否可以修改
    GraphicType type{GraphicType::PREDEFINE};
};
class GraphicsManager : public QObject
{
    Q_OBJECT
    GraphicsManager(QObject *parent = nullptr);
    ~GraphicsManager();
public:
    static GraphicsManager *instance();
    /**
     * @brief loadGraphics 加载图元
     */
    void loadGraphics();
    bool loaded(){return isLoaded;}
    // 删除拷贝构造函数和赋值运算符
    GraphicsManager(const GraphicsManager&) = delete;
    GraphicsManager& operator=(const GraphicsManager&) = delete;
    /**
     * @brief 通过ID获取图元
     * @param id 图元ID
     * @return 图元对象
     */
    IGraphicPlugin *getPluginById(const QString id);
    /**
     * @brief 根据图元ID创建图元
     * @param graphicId 图元ID
     * @return 图元对象
     */
    ICustomGraphic *createGraphic(const QString &graphicId);
    /**
     * @brief 获取全部图元插件
     * @return  图元插件列表
     */
    QList<IGraphicPlugin *> getAllPlugins();
    /**
     * @brief 根据图元ID创建图元
     * @param graphicId 图元ID
     * @param xmlText包含图元信息的XML
     * @return 图元对象
     */
    ICustomGraphic *createGraphic(const QString &graphicId, const QString &xmlText);
    /**
     * @brief addGroup 添加一个用户组
     * @param groupId 组ID
     * @param groupName 组名称
     * @return true 成功，false 失败
     */
    bool addGroup(int groupId, const QString &groupName);
    /**
     * @brief removeGroup 删除用户组
     * @param groupId 组ID
     * @return true 成功，false 失败
     */
    bool removeGroup(int groupId);
    /**
     * @brief updateGroupName 更新用户组名称
     * @param groupId 组ID
     * @param newName 新组名
     * @return true 成功，false 失败
     */
    bool updateGroupName(int groupId, const QString &newName);
    /**
     * @brief importGraphics 从文件导入图元到指定用户组
     * @param groupId 组ID
     * @param files 文件列表
     * @return 图元对象
     */
    QList<IGraphicPlugin*> importGraphics(int groupId, const QStringList &files);
    /**
     * @brief updateGraphic 更新用户图元数据
     * @param data 图元数据，含图元数据ID
     * @return 图元对象
     */
    IGraphicPlugin* updateGraphic(const UserPluginDO &data);
    /**
     * @brief removeGraphic 删除
     * @param data 图元数据，含图元数据ID
     * @return 图元对象ID
     */
    QString removeGraphic(const UserPluginDO &data);
    /**
     * @brief addGraphic 添加用户图元
     * @param graphicData 图元数据
     * @param xmlData 图元对应的文件数据
     * @return 图元对象
     */
    IGraphicPlugin *addGraphic(const UserPluginDO &graphicData, const QString &xmlData);
Q_SIGNALS:
    void loadEndEvent(QList<GraphicGroup*> groups);
    /**
     * @brief removeGroup 移除组消息
     * @param groupId 组ID
     */
    void groupRemovedEvent(int groupId);
protected Q_SLOTS:
    void onPredefGraphicsLoaded();
private:
    bool isLoaded{false};
    QFutureWatcher<IGraphicPlugin*> *watcher;
    // 全部图元组信息
    QList<GraphicGroup*> groups;
    QHash<QString, GraphicGroup*> groupMaps;
    QHash<int, GraphicGroup*> userGroupMaps;

    QList<IGraphicPlugin*> loadPredefGraphics();
    void loadUserGraphics();
    /**
     * @brief deleteGroup 清理组所占用的内存
     * @param group 组数据指针
     */
    void deleteGroup(GraphicGroup *group);
    /**
     * @brief getPluginPath 获取自定义图元的存储路径
     * @param groupId 自定义图元组ID
     * @return 存储路径
     */
    QString getPluginPath(qint32 groupId);
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
};

#endif // GRAPHICSMANAGER_H
