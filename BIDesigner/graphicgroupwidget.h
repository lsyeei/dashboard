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

#ifndef GRAPHICGROUPWIDGET_H
#define GRAPHICGROUPWIDGET_H

#include "customgraphic/userplugindo.h"
#include <QObject>
#include <QPointer>
#include <QWidget>

class UserPluginManageForm;
class QPushButton;
class QLineEdit;
class QToolButton;
class FlowLayout;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class QHBoxLayout;
class ICustomGraphic;
class IGraphicPlugin;
class GraphicGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicGroupWidget(QString groupName, qint32 index, QWidget *parent = nullptr);
    /**
     * @brief 将插件加入到该组控件中
     * @param plugin 控件对象
     * @return true 加入成功，false 加入失败
     */
    bool addPlugin(IGraphicPlugin *plugin);
    QString getGroupName() const;
    void setGroupName(const QString &name);
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool event(QEvent *event) override;

    QString getWidgetId() const;
    qint32 getUserGroupId() const;
    void setUserGroupId(qint32 id);
    /**
     * @brief setEditable 设置是否允许编辑组
     * @param flag true允许编辑组，false 不允许编辑
     */
    void setEditable(bool flag);
    /**
     * @brief clearGroup 清空图元
     */
    void clearGroup();
    /**
     * @brief removePlugin 删除图元控件
     * @param graphicId 图元对象ID
     * @return true 成功，false 失败
     */
    bool removePlugin(const QString &graphicId);
    /**
     * @brief updatePlugin 更新图元控件
     * @param plugin 图元对象
     */
    void updatePlugin(IGraphicPlugin *plugin);

Q_SIGNALS:
    /**
     * @brief 点击图元
     * @param graphicItem 图元对象
     */
    void graphicItemClicked(const QString &itemId);
    // /**
    //  * @brief removeGroup 通知父控件移除该组
    //  */
    // void removeGroup();
    // /**
    //  * @brief nameChanged 分组名称修改
    //  * @param oldName 原名称
    //  * @param newName 新名称
    //  */
    // void nameChanged(const QString &noldName, const QString &newName);
    // void importGraphic(qint32 userGroupId);
    // void manageGraphic(qint32 userGroupId);

private Q_SLOTS:

    void onTitleclicked();
    void onEditClicked();
    void onDeleteClicked();
    void onImportClicked();
    void onManageClicked();
    void onNameEditEnd();
    void onItemChanged(const UserPluginDO &data);
    void onItemRemoved(const UserPluginDO &data);

private:
    UserPluginManageForm* form{nullptr};
    QString widgetId;
    QVBoxLayout *layout;
    QWidget *titleWidget;
    QHBoxLayout *titleLayout;
    QPointer<QLineEdit> titleEditor;
    QPointer<QPushButton> editBtn;
    QPointer<QMenu> popMenu;
    QPointer<QAction> renameAct;
    QPointer<QAction> delAct;
    QPointer<QAction> importAct;
    QPointer<QAction> manageAct;
    QLabel *icon;
    QLabel *title;
    QWidget *contentWidget;
    FlowLayout *contentLayout;
    // 图元集合，key 图元ID，value 图元控件对象
    QMap<QString, QToolButton *> pluginMap;
    // 代表图元的图表大小
    qint16 iconWidth{32};
    // 是否显示图元名称
    bool showName{false};
    // 图元组名称
    QString groupName;
    // 拖动起点
    QPointF dragStartPosition;
    bool isFolded{false};
    // 用户分组的ID
    qint32 userGroupId{-1};
    /**
     * @brief 根据名称创建ID
     * @param name 名称
     * @param index 序号
     * @return ID
     */
    QString createId(QString name, qint32 index);
    void paletteChanged();
    void itemClicked(QToolButton * button);
    void createEditBtns();
    void showEditBtns(bool showFlag);
};

#endif // GRAPHICGROUPWIDGET_H
