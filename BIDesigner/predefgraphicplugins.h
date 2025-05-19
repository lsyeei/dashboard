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
#ifndef PREDEFGRAPHICPLUGINS_H
#define PREDEFGRAPHICPLUGINS_H

#include <QMap>
#include <QObject>

class QLayout;
class IGraphicPlugin;
class GraphicPluginGroup;
class PredefGraphicPlugins : public QObject
{
    Q_OBJECT
public:
    PredefGraphicPlugins(QWidget *parent);
    ~PredefGraphicPlugins();
    bool load();
    QList<GraphicPluginGroup*> groupWidgets();
    IGraphicPlugin *getPluginById(const QString &pluginId) const;
    QList<IGraphicPlugin *> plugins() const;

Q_SIGNALS:
    void graphicItemChanged(IGraphicPlugin *plugin);
protected Q_SLOTS:
    void onGraphicItemSelected(QString itemId);
private:
    QWidget *parentWidget{nullptr};
    QLayout *layout{nullptr};
    // 所有控件集合，key 控件group与name 生成的唯一ID，value 控件对象
    QMap<QString, IGraphicPlugin *> pluginMap;
    // 图元控件组控件，key 组控件ID，value widget对象
    QMap<QString, GraphicPluginGroup *> groupWidgetMap;

    /**
     * @brief 将插件安装到程序
     * @param graphicItem 插件对象
     */
    void installPlugin(IGraphicPlugin *graphicItem);
    // QString genItemKey(const QString &group, const QString &name);
    GraphicPluginGroup *createGroupWidget(QString group);
};

#endif // PREDEFGRAPHICPLUGINS_H
