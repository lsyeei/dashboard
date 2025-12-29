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
#ifndef GRAPHICLISTFORM_H
#define GRAPHICLISTFORM_H

#include "bigraphicsscene.h"
#include <QPointer>

namespace Ui {
class GraphicListForm;
}
class QTreeWidgetItem;

class GraphicListForm : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicListForm(BIGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicListForm();
    /**
     * @brief setScene 设置关联的场景控件
     * @param scene 场景指针
     */
    void setScene(BIGraphicsScene *scene);
protected Q_SLOTS:
    void onSceneChanged(ItemAction action, const QList<QGraphicsItem*> &items);
    void onSelectChanged();
    void onSelectGraphicItem();
    void onQueryTextEditEnd();
    void onSearchBtnClicked(bool flag);
private:
    Ui::GraphicListForm *ui;
    // 关联的场景
    QPointer<BIGraphicsScene> graphicScene;
    // 图元与树结构映射
    QHash<QGraphicsItem*,QTreeWidgetItem*> itemMap;
    int searchIndex{-1};
    /**
     * @brief getItemIcon 获取图元缩略图
     * @param item 图元
     * @param size 缩略图大小
     * @return 图标
     */
    QIcon getItemIcon(QGraphicsItem *item, const QSize &size);
    /**
     * @brief findItem 查找图元在 tree widget 中的位置
     * @param item
     * @return 查找结果
     */
    QTreeWidgetItem *findItem(QGraphicsItem *item);
    /**
     * @brief addItem 添加图元
     * @param item 图元
     * @return 新建的 TreeWidgetItem
     */
    QTreeWidgetItem *addItem(QGraphicsItem *item);
};

#endif // GRAPHICLISTFORM_H
