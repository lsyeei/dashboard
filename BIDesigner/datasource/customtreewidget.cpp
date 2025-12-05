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
#include "customtreewidget.h"

CustomTreeWidget::CustomTreeWidget(QWidget *parent):QTreeWidget(parent){
    // 启用拖放模式（控件内部移动）
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::InternalMove);
};

void CustomTreeWidget::dropEvent(QDropEvent *event)
{

    // 在放下操作发生前，先获取当前选中的项（即被拖动的源节点）
    QTreeWidgetItem *draggedItem = currentItem();
    if (!draggedItem) {
        // 如果意外没有源节点，调用基类方法或直接返回
        QTreeWidget::dropEvent(event);
        return;
    }

    // 获取源节点的原父节点
    auto *originalParent = draggedItem->parent();
    // 如果 originalParent 为空，表示源节点原先是顶级节点
    // 顶级节点可以理解为属于 invisibleRootItem[citation:10]
    // if (!originalParent) {
    //     originalParent = this->invisibleRootItem();
    // }

    // 获取放下事件发生位置的目标项（新位置的父节点或兄弟节点）
    // QTreeWidgetItem *targetItem = this->itemAt(event->pos());
    // QTreeWidgetItem *newParent = nullptr;
    // bool isOnItem = (targetItem != nullptr);

    // if (isOnItem) {
    //     // 如果放在了某个项上，这个项就是新的父节点
    //     newParent = targetItem;
    // } else {
    //     // 如果放到了空白区域，新父节点就是虚拟根节点（即成为顶级节点）
    //     newParent = this->invisibleRootItem();
    // }
    // 必须调用基类的 dropEvent，让 Qt 完成默认的移动操作
    QTreeWidget::dropEvent(event);

    // 拖放完成后，可以再次验证节点的新位置（可选）
    QTreeWidgetItem *actualNewParent = draggedItem->parent();
    // if (!actualNewParent) {
    //     actualNewParent = this->invisibleRootItem();
    // }
    emit itemDroped(draggedItem, originalParent, actualNewParent);
}
