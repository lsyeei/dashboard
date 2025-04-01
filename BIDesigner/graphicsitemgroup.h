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

protected:
    // AbstractZoneItem interface
    QPainterPath shapePath() const override;
    void customUndoAction(QString action, QVariant data, bool isUndo) override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    // AbstractItem interface
    void parseXML(const QString &xml) override;
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) Q_DECL_OVERRIDE;

    // AbstractZoneItem interface
protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
private:
    // 外框
    QRectF rect{0,0,0,0};
    // 首次选中，此时调整group的pos及其它图元的pos
    bool firstSelected{true};
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

    void adjustChildItemSize(QRectF rectOffset);
    void adjustChildItemPos(QPointF offset);

    void calcChildItemRatio();
    /**
     * @brief 根据group改变的大小计算子图元应该改变的大小
     * @param item 目标图元
     */
    void adjustSubItemSize(QGraphicsItem * const item);

};

#endif // GRAPHICSITEMGROUP_H
