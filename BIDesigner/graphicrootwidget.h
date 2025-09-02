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

#ifndef GRAPHICROOTWIDGET_H
#define GRAPHICROOTWIDGET_H

#include "customgraphic/userpluginmanageform.h"
#include "graphicsmanager.h"
#include <QObject>
#include <QPointer>
#include <QWidget>

class QScrollArea;
class QGraphicsItem;
class QVBoxLayout;
class QPushButton;
class IGraphicPlugin;
class GraphicGroupWidget;
class ICustomGraphic;
class UserGraphics;
class PredefGraphics;
class GraphicRootWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicRootWidget(QWidget *parent = nullptr);
    ~GraphicRootWidget();

    // QObject interface
    bool event(QEvent *event) override;
    
    IGraphicPlugin *getSelectedPlugin() const;

    /**
     * @brief createGraphicGroup 创建图元组
     * @param group 组信息
     */
    void createGraphicGroup(const GraphicGroup &group);

    /**
     * @brief selectGroup 选择或新建组
     * @return 组ID
     */
    int selectGroup();
    /**
     * @brief addGraphic 添加图元
     * @param groupId 组ID
     * @param graphic 图元
     */
    void addGraphic(int groupId, IGraphicPlugin *graphic);

Q_SIGNALS:
    /**
     * @brief 选中图形元件后发出事件，供其它模块使用
     * @param currentPlugin 当前图元
     */
    void graphicItemChanged(IGraphicPlugin *currentPlugin);

public Q_SLOTS:
    /**
     * @brief onGraphicPluginLoaded 图元插件加载完毕后生成插件
     */
    void onGraphicPluginLoaded(QList<GraphicGroup*> groups);

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private Q_SLOTS:
    void onGraphicItemSelected(QString itemId);
    // void onLoadEnd();
    /**
     * @brief onAddNewGroup 新增图元分组
     */
    void onAddNewGroup();
    /**
     * @brief onRemoveGroup 移除组控件
     * @param groupId 组ID
     */
    void onRemoveGroup(int groupId);
private:
    // 布局方式
    QVBoxLayout *layout;
    QPointer<QPushButton> addGroupBtn;
    QWidget *groupPanel;
    QScrollArea *scroll;
    // 当前选中的插件
    IGraphicPlugin *selectedPlugin;
    // 图元控件组控件，key 组ID，value widget对象
    QMap<int, GraphicGroupWidget *> groupWidgetMap;
    UserPluginManageForm* form{nullptr};

    void paletteChanged();
    /**
     * @brief createGroupWidget 创建组控件
     * @param groupId 组ID
     * @param groupName 组名称
     * @param type 组类型
     * @return 控件指针
     */
    GraphicGroupWidget *createGroupWidget(int groupId, const QString &groupName, GraphicType type);
    bool addNewGroup(const QString &groupName);
};

#endif // GRAPHICROOTWIDGET_H
