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
#include "graphiclistform.h"
#include "ui_graphiclistform.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

const static int PointerRole = Qt::UserRole;
const static int IDRole = Qt::UserRole + 1;

GraphicListForm::GraphicListForm(BIGraphicsScene *scene, QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::GraphicListForm)
{
    ui->setupUi(this);
    // 内部控件最大化
    widget()->setWindowState(Qt::WindowMaximized);
    connect(ui->graphicTree, &QTreeWidget::itemSelectionChanged,
            this, &GraphicListForm::onSelectChanged);
    connect(ui->searchBtn, &QToolButton::clicked,
            this, &GraphicListForm::onSearchBtnClicked);
    connect(ui->queryText, &QLineEdit::editingFinished,
            this, &GraphicListForm::onQueryTextEditEnd);
    setScene(scene);
}

GraphicListForm::~GraphicListForm()
{
    delete ui;
}

void GraphicListForm::setScene(BIGraphicsScene *scene)
{
    if (!graphicScene.isNull()) {
        disconnect(graphicScene,&BIGraphicsScene::contentChanged,
                   this, &GraphicListForm::onSceneChanged);
        disconnect(graphicScene, &QGraphicsScene::selectionChanged,
                this, &GraphicListForm::onSelectGraphicItem);
    }
    graphicScene = scene;
    connect(graphicScene, &BIGraphicsScene::contentChanged,
            this, &GraphicListForm::onSceneChanged, Qt::QueuedConnection);
    connect(graphicScene, &QGraphicsScene::selectionChanged,
            this, &GraphicListForm::onSelectGraphicItem, Qt::QueuedConnection);
    // 初始化列表树
    ui->graphicTree->clear();
    itemMap.clear();
}

void GraphicListForm::onSceneChanged(ItemAction action, const QList<QGraphicsItem*> &items)
{
    if (items.isEmpty()) {
        return;
    }
    foreach (auto item, items) {
        if (action == ItemAction::ADD) {
            addItem(item);
        }else if(action == ItemAction::REMOVE) {
            if(auto t= findItem(item)){
                ui->graphicTree->takeTopLevelItem(ui->graphicTree->indexOfTopLevelItem(t));
                delete t;
                itemMap.remove(item);
                break;
            }
        }else if(action == ItemAction::GROUP) {
            auto group = dynamic_cast<QGraphicsItemGroup*>(item);
            if(group == nullptr){
                continue;
            }
            auto treeItem = addItem(group);
            auto childItems = group->childItems();
            foreach (auto c, childItems) {
                auto f = findItem(c);
                if (f) {
                    ui->graphicTree->takeTopLevelItem(ui->graphicTree->indexOfTopLevelItem(f));
                    treeItem->addChild(f);
                }
            }
        }else if(action == ItemAction::UNGROUP) {
            auto group = dynamic_cast<QGraphicsItemGroup*>(item);
            if(group == nullptr){
                continue;
            }
            auto f = findItem(group);
            if (f) {
                while(f->childCount() > 0){
                    ui->graphicTree->insertTopLevelItem(ui->graphicTree->indexOfTopLevelItem(f),f->takeChild(0));
                }
            }
            ui->graphicTree->takeTopLevelItem(ui->graphicTree->indexOfTopLevelItem(f));
            delete f;
            itemMap.remove(item);
        }else if(action == ItemAction::RENAME) {
            auto f = findItem(item);
            if(f){
                f->setText(0, graphicScene->itemName(item));
            }
        }
    }
}

void GraphicListForm::onSelectChanged()
{
    auto treeItem = ui->graphicTree->currentItem();
    if (treeItem == nullptr) {
        return;
    }
    QSignalBlocker sceneBlocker{graphicScene};
    auto item = treeItem->data(0, PointerRole).value<QGraphicsItem*>();
    graphicScene->clearSelection();
    item->setSelected(true);
}

void GraphicListForm::onSelectGraphicItem()
{
    QSignalBlocker treeWidgetBlocker{ui->graphicTree};
    ui->graphicTree->clearSelection();
    auto items = graphicScene->selectedItems();
    foreach (auto item, items) {
        auto treeItem = itemMap[item];
        if (treeItem) {
            treeItem->setSelected(true);
        }
    }
}

void GraphicListForm::onQueryTextEditEnd()
{
    searchIndex = -1;
}

void GraphicListForm::onSearchBtnClicked(bool flag)
{
    Q_UNUSED(flag);
    auto query = ui->queryText->text().trimmed();
    if (query.isEmpty()) {
        return;
    }
    // QTreeWidgetItem *item;
    // if (searchIndex == 0){
    //     item = ui->graphicTree->topLevelItem(0);
    // }else{
    //     item = ui->graphicTree->currentItem();
    //     item = ui->graphicTree->itemBelow(item);
    // }
    // while(item){
    //     auto itemText = item->text(0);
    //     if (itemText.indexOf(query) >= 0){
    //         ui->graphicTree->clearSelection();
    //         item->setSelected(true);
    //         ui->graphicTree->setCurrentItem(item);
    //         ui->graphicTree->scrollToItem(item);
    //         graphicScene->clearSelection();
    //         item->data(0, PointerRole).value<QGraphicsItem*>()->setSelected(true);
    //         searchIndex = 1;
    //         return;
    //     }
    //     item = ui->graphicTree->itemBelow(item);
    // }
    // searchIndex = 0;

    auto items = itemMap.keys();
    for (int i = searchIndex+1; i < items.length(); ++i) {
        searchIndex = i;
        auto itemText = graphicScene->itemName(items[i]);
        if (itemText.indexOf(query) >= 0){
            ui->graphicTree->clearSelection();
            auto treeItem = itemMap[items[i]];
            treeItem->setSelected(true);
            ui->graphicTree->setCurrentItem(treeItem);
            ui->graphicTree->scrollToItem(treeItem);
            graphicScene->clearSelection();
            items[i]->setSelected(true);
            return;
        }
    }
    if (searchIndex >= items.length() - 1) {
        searchIndex = -1;
    }
}

QIcon GraphicListForm::getItemIcon(QGraphicsItem *item, const QSize &size)
{
    QPixmap image{size};//, QImage::Format_ARGB32};
    image.fill(Qt::transparent);
    QPainter painter{&image};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRectF rect{{0,0},size};
    QRectF itemRect = item->sceneBoundingRect();
    auto ratio = itemRect.width() / itemRect.height();
    if (ratio > 1){
        auto imgHeight = size.width()/ratio;
        rect = {0, (size.height() - imgHeight)/2, 1.0*size.width(), imgHeight};
    } else {
        auto imgWidth = size.height()*ratio;
        rect = {(size.width()-imgWidth)/2, 0, imgWidth, 1.0*size.height()};
    }

    BIGraphicsScene tempScene;
    auto data = "<User>" + tempScene.toXml({item}) + "</User>";
    tempScene.setSceneRect(0,0,itemRect.width(),itemRect.height());
    auto items = tempScene.toItems(data);
    tempScene.addItems(items);
    tempScene.render(&painter, rect, itemRect);
    return QIcon{image};
}

QTreeWidgetItem *GraphicListForm::findItem(QGraphicsItem *item)
{
    return itemMap[item];
    // auto treeItems = ui->graphicTree->findItems(graphicScene->itemName(item), Qt::MatchFixedString);
    // if (treeItems.isEmpty()) {
    //     return nullptr;
    // }
    // foreach (auto t, treeItems) {
    //     if (t->data(0,PointerRole).value<QGraphicsItem*>() == item) {
    //         return t;
    //     }
    // }
    // return nullptr;
}

QTreeWidgetItem *GraphicListForm::addItem(QGraphicsItem *item)
{
    auto treeItem = new QTreeWidgetItem();
    treeItem->setText(0, graphicScene->itemName(item));
    treeItem->setIcon(0, getItemIcon(item, {32,32}));
    treeItem->setData(0, PointerRole, QVariant::fromValue(item));
    treeItem->setData(0, IDRole, QVariant::fromValue(graphicScene->getItemId(item)));
    ui->graphicTree->addTopLevelItem(treeItem);
    itemMap[item] = treeItem;

    return treeItem;
}
