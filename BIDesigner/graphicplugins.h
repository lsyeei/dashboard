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

#ifndef GRAPHICPLUGINS_H
#define GRAPHICPLUGINS_H

#include <QObject>
#include <QPointer>
#include <QWidget>

class QVBoxLayout;
class QPushButton;
class IGraphicPlugin;
class GraphicPluginGroup;
class ICustomGraphic;
class UserGraphicPlugins;
class GraphicPlugins : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicPlugins(QWidget *parent = nullptr);
    ~GraphicPlugins();

    // QObject interface
    bool event(QEvent *event) override;
    
    IGraphicPlugin *getSelectedPlugin() const;
    /**
     * @brief 通过ID获取图元
     * @param id 图元ID
     * @return 图元对象
     */
    static IGraphicPlugin *getPluginById(const QString id);
    /**
     * @brief 根据图元ID创建图元
     * @param graphicId 图元ID
     * @return 图元对象
     */
    static ICustomGraphic *createGraphic(const QString &graphicId);
    /**
     * @brief 获取全部图元插件
     * @return  图元插件列表
     */
    static QList<IGraphicPlugin *> getAllPlugins();
    /**
     * @brief 根据图元ID创建图元
     * @param graphicId 图元ID
     * @param xmlText包含图元信息的XML
     * @return 图元对象
     */
    static ICustomGraphic *createGraphic(const QString &graphicId, const QString &xmlText);

Q_SIGNALS:
    /**
     * @brief 选中图形元件后发出事件，供其它模块使用
     * @param currentPlugin 当前图元
     */
    void graphicItemChanged(IGraphicPlugin *currentPlugin);

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private Q_SLOTS:
    /**
     * @brief 选中图形元件，处理 GraphicItemGroupWidget 触发的点击事件
     * @param item 元件ID
     */
    void graphicItemSelected(const QString item);
    /**
     * @brief onAddNewGroup 新增图元分组
     */
    void onAddNewGroup();
    void onRemoveGroup();
private:
    // 布局方式
    QVBoxLayout *layout;
    QPointer<QPushButton> addGroupBtn;
    // 所有控件集合，key 控件group与name 生成的唯一ID，value 控件对象
    static QMap<QString, IGraphicPlugin *> pluginMap;
    // 图元控件组控件，key 组控件ID，value widget对象
    QMap<QString, GraphicPluginGroup *> groupWidgetMap;
    // 当前选中的插件
    IGraphicPlugin *selectedPlugin;
    /**
     * @brief 加载图元控件G
     */
    void loadGraphicPlugin();
    /**
     * @brief 加载用户自定义控件
     */
    void loadUserGraphicPlugin();
    /**
     * @brief 将插件安装到程序
     * @param graphicItem 插件对象
     */
    void installPlugin(IGraphicPlugin *graphicItem);
    // QString genItemKey(const QString &group, const QString &name);
    GraphicPluginGroup *createGroupWidget(QString group);
    void paletteChanged();
};

#endif // GRAPHICPLUGINS_H
