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

#ifndef BIGRAPHICSSCENE_H
#define BIGRAPHICSSCENE_H

#include "brushproperty.h"
#include "igraphicsscene.h"
#include "penproperty.h"
#include "undoobject.h"

#include <QGraphicsScene>

enum class OrderAction{NONE, UP, DOWN, TOP, BOTTOM};
enum class AlignAction{NONE, LEFT, RIGHT, TOP, BOTTOM, HORIZON, VERTICAL};
enum class DistributeAction{NONE, HORIZON, VERTICAL};

class SnowFlake;
class GraphicsItemGroup;
class BIGraphicsScene : public IGraphicsScene, public UndoObject
{
    Q_OBJECT
public:
    explicit BIGraphicsScene(QObject *parent = nullptr);
    ~BIGraphicsScene();
    void refreshBackground(QGraphicsView *view, QPainter *painter);
    // 图元数据保留位置
    static int itemIdIndex;
    static int itemNameIndex;
    static int itemHideFlag;
    static int itemGroupFlag;
    /**
     * @brief 解析XML转换为 QGraphicsItem
     * @param xmlText XML文本
     * @return  QGraphicsItem列表
     */
    static QList<QGraphicsItem *> toItems(const QString &xmlText);
    /**
     * @brief 用XML编码保存场景中的全部图形
     * @return xml 格式字符串
     */
    QString toXml();
    /**
     * @brief  用XML编码保存场景中的指定图形
     * @param items 指定要存储的图元
     * @return
     */
    QString toXml(QList<QGraphicsItem *> items);
    /**
     * @brief 添加图元并设置为可选择、移动
     * @param item 要加入scene 的图元指针
     */
    void addEditableItem(QGraphicsItem *item);
    /**
     * @brief 批量添加图元
     * @param items 图元列表
     */
    void addItems(QList<QGraphicsItem *> items);
    /**
     * @brief 取消组合
     * @param group 要取消的图元
     */
    void ungroup(QGraphicsItemGroup *group);
    /**
     * @brief group 组合
     * @param group 原组对象
     * @param items 组成员列表
     */
    void group(QGraphicsItemGroup *group, const QList<QGraphicsItem *> &items);
    /**
     * @brief flipItem 翻转当前选中对象
     * @param orientation 方向
     */
    void flipItem(Qt::Orientation orientation);
    /**
     * @brief 设置选中图元的 zorder
     * @param action zorder 调整的偏动作
     */
    void setSelectedItemZOrder(OrderAction action);
    /**
     * @brief 对齐图元
     * @param action 对齐方式
     */
    void setItemsAlign(AlignAction action);
    /**
     * @brief 图元等距分布
     * @param action 分布方式
     */
    void distributeItems(DistributeAction action);
    /**
     * @brief 全选/反选所有图元
     * @param flag true 全选，false 全不选
     */
    void selectAll(bool flag);
    /**
     * @brief 拷贝选中的图元
     */
    void copyItems();
    /**
     * @brief cutItems 剪切选中的图元
     */
    void cutItems();
    /**
     * @brief 粘贴剪贴板中的图元
     * @param pos 粘贴的中心位置
     * @return 粘贴的图元列表
     */
    QList<QGraphicsItem *> pastItems(QPointF pos);

    /**
     * @brief 移动图元
     * @param items 需要移动的图元
     * @param offset 移动距离
     */
    void moveItems(QList<QGraphicsItem*> items, const QPointF offset);
    /**
     * @brief 删除图元
     * @param items 图元集合
     */
    void deleteItems(QList<QGraphicsItem *> items);

    // UndoObject interface
    void undo(QVariant undoData) override;
    void redo(QVariant redoData) override;
    /**
     * @brief 设置图元名称
     * @param item 图元对象
     * @param name 图元名称
     */
    void setItemName(QGraphicsItem *item, QString name);
    /**
     * @brief itemName 获取图元名称
     * @param item 图元对象
     * @return 图元名称
     */
    QString itemName(QGraphicsItem *item);
    /**
     * @brief setItemId 设置图元ID
     * @param item 图元对象
     * @param id ID值
     */
    void setItemId(QGraphicsItem *item, const QString &id) override;
    /**
     * @brief getItemId 获取图元ID
     * @param item 图元对象
     * @return  图元ID
     */
    QString getItemId(QGraphicsItem *item) override;
    /**
     * @brief getItemById 根据ID查找图元
     * @param id 图元ID
     * @return 图元对象
     */
    QGraphicsItem *getItemById(const QString &id) override;
    /**
     * @brief  对指定的图元进行排序
     * @param itemList 图元列表
     * @param order 顺序
     * @return 已排序图元
     */
    QList<QGraphicsItem *> sortItems(QList<QGraphicsItem *> itemList, Qt::SortOrder order);

    void setPainter(const BrushProperty &brush, const PenProperty &pen);
    /**
     * @brief 计算多个图元的组合边界
     * @param items 图元列表
     * @return 组合边界
     */
    QPainterPath getUnitBound(QList<QGraphicsItem *> items);
    /**
     * @brief 隐藏图元
     * @param item 图元对象
     */
    void hideItem(QGraphicsItem *item);
    /**
     * @brief isHide 判断图元是否隐藏
     * @param item 图元对象
     * @return true 隐藏图元，false 不隐藏
     */
    bool isHide(QGraphicsItem *item);
    void setSelectionArea(const QPainterPath &path,
                          Qt::ItemSelectionOperation selectionOperation,
                          Qt::ItemSelectionMode mode,
                          const QTransform &deviceTransform);

signals:
    void undoEvent(const QString &text, QVariant undoData, QVariant redoData) override;

    // QGraphicsScene interface
protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    // 网格步长
    qint16 gridStep{10};
    // 放大最大倍数
    const qreal maxZoom{10};
    // 缩小最小倍数
    const qreal minZoom{0.1};
    // 绘制背景刷
    BrushProperty brushProperty;
    PenProperty penProperty;
    // ID 生成器
    SnowFlake *idGenerator;

    /**
     * @brief 绘制网格
     * @param painter
     * @param rect 绘图区域
     */
    void drawSceneGrid(QPainter *painter, const QRectF &rect);

    /**
     * @brief 计算视图中的rect
     * @param rect
     */
    QRectF getMapRect(const QRectF &rect);
    /**
     * @brief 更新图元
     * @param item 图元指针
     */
    void updateItem(QGraphicsItem *item);

    void doCommand(QVariant undoData);
};

#endif // BIGRAPHICSSCENE_H
