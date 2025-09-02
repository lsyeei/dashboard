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

#ifndef GRAPHICPROPERTYFORM_H
#define GRAPHICPROPERTYFORM_H

#include "graphicsmanager.h"

#include <QWidget>

class BIGraphicsView;
class QGraphicsItem;
namespace Ui {
class GraphicProperty;
}

class GraphicPropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicPropertyForm(QWidget *parent = nullptr);
    ~GraphicPropertyForm();

    bool setGraphicItem(QGraphicsItem *item);

    void setView(BIGraphicsView *newView);
public Q_SLOTS:
    void onGraphicPluginLoaded(QList<GraphicGroup*> groups);
private slots:
    void graphicItemNameChanged();
private:
    Ui::GraphicProperty *ui;
    BIGraphicsView *view;
    // 关联的图元
    QGraphicsItem *graphicItem{nullptr};
    // 属性面板集合，key 属性面板ID，value 属性面板指针
    QHash<QString, QWidget*> widgets;
    // 当前显示的属性面板
    QWidget *current{nullptr};
};

#endif // GRAPHICPROPERTYFORM_H
