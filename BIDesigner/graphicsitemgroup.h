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

#ifndef GRAPHICSITEMGROUP_H
#define GRAPHICSITEMGROUP_H

#define BASE_FOR_GROUP

#include <abstractzoneitem.h>

class GraphicsItemGroup : public AbstractZoneItem
{
    Q_OBJECT
public:
    enum MergeType{None, Unit, Intersect, Subtract, Exclude};
    explicit GraphicsItemGroup(QGraphicsItem *parent = nullptr);
    explicit GraphicsItemGroup(const QString &xml, QGraphicsItem *parent = nullptr);
    // ICustomGraphic interface
    QString classId() const override;
    MergeType getMergeType() const;
    void setMergeType(MergeType newMergeType);
    QString toXml() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    /**
     * @brief isEditing 当前组是否处于编辑状态
     * @return true 编辑中，false 正常状态
     */
    bool isEditing();
    /**
     * @brief notifyEditEnable 发送编辑消息，让组进入编辑状态
     */
    void notifyEditEnable();
    /**
     * @brief notifyEditFinished 通知编辑状态结束
     */
    void notifyEditFinished();
    /**
     * @brief hasChildSelected 处于编辑状态时，判断是否有下级图元处于选中状态
     * @return true 有下级图元处于选中状态，false 没有下级图元处于选中状态
     */
    bool hasChildSelected();
    /**
     * @brief isEditEnd 编辑是否完成
     * @return true 完成，false 未完成
     */
    bool isEditEnd();

protected:
    // AbstractZoneItem interface
    QPainterPath shapePath() const override;
    void customUndoAction(QString action, QVariant data, bool isUndo) override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    // AbstractItem interface
    void parseXML(const QString &xml) override;
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void itemAddEvent(QGraphicsItem* item);
    /**
     * @brief editEnableEvent 通知组合将进入编辑状态
     */
    void editEnableEvent();
    /**
     * @brief editReadyEvent 编辑状态已准备好
     */
    void editReadyEvent();
    /**
     * @brief editFinishEvent 通知组合结束编辑状态
     * @param items 组合包含的图元
     */
    void editFinishEvent(const QList<QGraphicsItem*> &items);
    /**
     * @brief regroupEndEvent 组合编辑结束，并且完成重组的事件
     */
    void regroupEndEvent();
    // AbstractZoneItem interface
protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
    void sceneSelectionChanged();
    /**
     * @brief onItemAdd 新图元加入执行的逻辑
     * @param item 新加入图元
     */
    void onItemAdd(QGraphicsItem* item);
    /**
     * @brief onItemRemove 移除图元执行的逻辑
     * @param item 移除的图元
     */
    void onItemRemove(QGraphicsItem* item);
    void receiveEditEnableEvent();
    void receiveEditFinishEvent(const QList<QGraphicsItem*> &items);
    /**
     * @brief onSubGroupEditReady 接收内部组合进入编辑准备完成消息
     */
    void onSubGroupEditReady();
    /**
     * @brief onSubgroupRegroupEnd 接收内部组合重组完成消息，处理本级组合
     */
    void onSubgroupRegroupEnd();
private:
    // 存放图形比例关系
    QMap<QGraphicsItem *, QVector<qreal>> itemRatios;
    // 合并选项
    MergeType mergeType{None};
    // 合并后的路径
    QPainterPath mergedPath;
    // 合并时的区域大小
    QRectF mergedRect;
    // 是否正在解析xml
    bool isParsing{false};
    // 处于编辑模式的图元
    QList<QGraphicsItem *> editingChilds;
    QList<GraphicsItemGroup*> subGroupList;
    // 编辑模式标记
    bool editFlag{false};
    // 编辑时的外框
    QRectF editRect{0,0,0,0};
    // 收到结束编辑的信号时为 true，编辑结束后置为 false，用于防止多次收到结束编辑信号
    bool endEditSignal{false};

    void adjustChildItemSize(QRectF rectOffset);
    void adjustChildItemPos(QPointF offset);

    void calcChildItemRatio();
    /**
     * @brief 根据group改变的大小计算子图元应该改变的大小
     * @param item 目标图元
     */
    void adjustSubItemSize(QGraphicsItem * const item);
    /**
     * @brief doMerge 合并图元
     * @param type 合并方式
     */
    void doMerge(MergeType type);
    /**
     * @brief editEnabled 开启编辑模式
     * @param item 开启后第一个选中的图元
     * @param childs 进入编辑模式的图元
     */
    void editEnabled(QGraphicsItem *item, const QList<QGraphicsItem*> &childs);
    /**
     * @brief editFinished 编辑结束
     * @param childs 组应包含的图元
     */
    void editFinished(const QList<QGraphicsItem*> &childs);
    /**
     * @brief adjustGroup 调整组的大小及位置
     * @param boundRect 新位置
     */
    void adjustGroup(const QRectF &boundRect);
};

#endif // GRAPHICSITEMGROUP_H
