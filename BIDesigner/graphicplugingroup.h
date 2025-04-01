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

#ifndef GRAPHICPLUGINGROUP_H
#define GRAPHICPLUGINGROUP_H

#include <QObject>
#include <QWidget>

class FlowLayout;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class QHBoxLayout;
class ICustomGraphic;
class IGraphicPlugin;
class GraphicPluginGroup : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicPluginGroup(QString groupName, qint32 index, QWidget *parent = nullptr);
    /**
     * @brief 将插件加入到该组控件中
     * @param plugin 控件对象
     * @return true 加入成功，false 加入失败
     */
    bool addPlugin(IGraphicPlugin *plugin);
    QString getGroupName() const;
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;
    bool event(QEvent *event) override;

    QString getGroupId() const;

Q_SIGNALS:
    /**
     * @brief 点击图元
     * @param graphicItem 图元对象
     */
    void graphicItemClicked(const QString &itemName);
private Q_SLOTS:
    void itemClicked(QToolButton * button);
    void onTitleclicked();

private:
    QString widgetId;
    QVBoxLayout *layout;
    QWidget *titleWidget;
    QHBoxLayout *titleLayout;
    QLabel *icon;
    QLabel *title;
    QWidget *contentWidget;
    FlowLayout *contentLayout;
    // 图元集合，key 图元ID，value 图元控件对象
    QMap<QString, QToolButton *> itemWidgetMap;
    // 代表图元的图表大小
    qint16 iconWidth{32};
    // 是否显示图元名称
    bool showName{false};
    // 图元组名称
    QString groupName;
    // 拖动起点
    QPointF dragStartPosition;
    bool isFolded{false};
    /**
     * @brief 根据名称创建ID
     * @param name 名称
     * @param index 序号
     * @return ID
     */
    QString createId(QString name, qint32 index);
    void paletteChanged();
};

#endif // GRAPHICPLUGINGROUP_H
