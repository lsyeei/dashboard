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
#pragma once
#ifndef ABSTRACTZONEITEM_H
#define ABSTRACTZONEITEM_H

#include "abstractitem.h"

class ZoneProperty;
class AbstractZoneItem : public AbstractItem
{
    Q_OBJECT
    // Q_PROPERTY(qreal width READ width WRITE setWidth FINAL)
    // Q_PROPERTY(qreal height READ height WRITE setHeight FINAL)
    // Q_PROPERTY(QSizeF size READ size WRITE setSize FINAL)
    // Q_PROPERTY(Qt::BrushStyle brushStyle READ brushStyle WRITE setBrushStyle FINAL)
    // Q_PROPERTY(QColor color READ color WRITE setColor FINAL)

public:
    AbstractZoneItem(QGraphicsItem *parent = nullptr, bool init = true);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    QSizeF size();
    // ICustomGraphic interface
    void setSize(const QSizeF &size) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QList<CustomMetadata> metadataList() Q_DECL_OVERRIDE;
    void setCustomData(const QString &name, const QString &value) Q_DECL_OVERRIDE;
    QString getCustomData(const QString &name) Q_DECL_OVERRIDE;

    using AbstractItem::attribute;
    ZoneProperty *attribute() const;

    // qreal width() const;
    virtual void setWidth(qreal newWidth);

    // qreal height() const;
    virtual void setHeight(qreal newHeight);

    // QColor color() const;
    virtual void setColor(const QColor &newColor);

    // Qt::BrushStyle brushStyle() const;
    // void setBrushStyle(Qt::BrushStyle newBrushStyle);

protected slots:
    virtual void sizeChanged(QRectF offsetValue);
    virtual void cornerChanged(qreal newValue);
    virtual void rotateChanged(qreal offsetValue);
    virtual void adjustStart(AbstractSelector::AdjustType type);
    virtual void adjustEnd(AbstractSelector::AdjustType type);

protected:
    // 矩形自身坐标系参考矩形
    QRectF logicRect;
    // 缩放后矩形框原点偏移的距离
    QPointF centerOffset;
    /**
     * @brief 生成该图形的绘制路径
     * @return 绘制路径
     */
    virtual QPainterPath shapePath() const = 0;
    // AbstractItem interface
    void customUndoAction(QString action, QVariant data, bool isUndo) override;
    AbstractSelector *createSelector() override;
    void updateSelector() override;
    void updateGraphic() override;
    BaseProperty *newProperty() override;
    QVariant attr2Variant(const BaseProperty &attr) override;
    void copyProperty(QVariant from, BaseProperty *to) override;
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;
    void attributeSwitched(int oldIndex, int newIndex) override;
    void parseXML(const QString &xml) Q_DECL_OVERRIDE;

    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    /**
     * @brief updateItem 更新图像、选择框、属性面板
     */
    void updateItem();

private:
    void syncLogicRect();
};

#endif // ABSTRACTZONEITEM_H
