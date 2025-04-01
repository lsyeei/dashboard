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

#ifndef STRAIGHTLINEITEM_H
#define STRAIGHTLINEITEM_H

#include "abstractitem.h"
#include <QObject>

class LineItemProperty;
class StraightLineItem : public AbstractItem
{
    Q_OBJECT
public:
    static QString SHAPE_ID;
    explicit StraightLineItem(QGraphicsItem *parent = nullptr);
    explicit StraightLineItem(const QString &xml,
                              QGraphicsItem *parent = nullptr);
    QString classId() const override;
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // ICustomGraphic interface
    void setSize(const QSizeF &size) override;
    virtual LineItemProperty *attribute() const;
    virtual QPainterPath shapePath() const;

    // AbstractItem interface
protected:
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;
    void attributeSwitched(int oldIndex, int newIndex) override;
    void customUndoAction(QString action, QVariant data, bool isUndo) override;
    AbstractSelector *createSelector() override;
    BaseProperty *newProperty() override;
    QVariant attr2Variant(const BaseProperty &attr) override;
    void copyProperty(QVariant from, BaseProperty *to) override;
    void updateSelector() override;
    void updateGraphic() override;
    // QGraphicsItem interface
    bool sceneEvent(QEvent *event) override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
protected Q_SLOTS:
    void onPointMoved(const QString &id, const QPointF &pos);
private:
    // item 所在矩形大小
    QSizeF itemSize;
    bool initFlag{false};
    bool adjustMove{false};
    /**
     * @brief trans4Line 根据p1与p2直线与X轴的夹角生成一个QTransform
     * @param p2
     * @param p1
     * @return  QTransform 对象
     */
    QTransform trans4Line(QPointF p2, QPointF p1) const;


};

#endif // STRAIGHTLINEITEM_H
