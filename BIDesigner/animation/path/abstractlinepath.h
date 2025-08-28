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

#ifndef ABSTRACTLINEPATH_H
#define ABSTRACTLINEPATH_H

#include "animation/path/imovepath.h"
#include "ilinepath.h"
#include "namedpoint.h"

class LineSelector;
class LinePathProperty;
class AbstractLinePath : public IMovePath, public ILinePath
{
    Q_OBJECT
public:
    enum PathState{
        // 不可用状态
        DISABLED,
        // 捕获鼠标状态
        CAPTURED,
        // 初始绘制状态
        DRAWING,
        // 绘制完成
        FINISHED
    };
    AbstractLinePath(QGraphicsItem *parent=nullptr);
    ~AbstractLinePath();
    // AbstractZoneItem interface
    LinePathProperty *attribute() const;
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // ICustomGraphic interface
    void setSize(const QSizeF &size) override;

    // ILinePath interface
    virtual QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    QPainterPath startShape() const Q_DECL_OVERRIDE;
    QPainterPath endShape() const Q_DECL_OVERRIDE;
    // IMovePath interface
    QPainterPath path() Q_DECL_OVERRIDE;
    void setMaster(QGraphicsItem *master) Q_DECL_OVERRIDE;
    QGraphicsItem *getMaster() Q_DECL_OVERRIDE;
    // ILinePath interface
    QPainterPath previewPath(QList<QPointF> points, QVariant args) const override;
    void enableEdit(bool flag);
    void enablePreview(bool flag);
    // IMovePath interface
signals:
    void pathChanged() Q_DECL_OVERRIDE;
protected:
    // AbstractItem interface
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;
    void attributeSwitched(int oldIndex, int newIndex) override;
    AbstractSelector *createSelector() override;
    QVariant attr2Variant(const BaseProperty &attr) override;
    void copyProperty(QVariant from, BaseProperty *to) override;
    void updateSelector() override;
    void updateGraphic() override;
    virtual QPainterPath shapePath() const;
    void customUndoAction(QString action, QVariant data, bool isUndo) override;
    BaseProperty *newProperty() override;
    void parseXML(const QString &xml) Q_DECL_OVERRIDE;
    // QGraphicsItem interface
    bool sceneEvent(QEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    /**
     * @brief createPredefinedItem 创建预定义图形
     */
    virtual void createPredefinedItem() = 0;
    /**
     * @brief afterCreateSelector 创建selector后执行
     * @param s 已创建的 selector 指针
     */
    virtual void afterCreateSelector(LineSelector *s)=0;
    /**
     * @brief setSingle 设置为单线段
     * @param pointNumber 组成线段的点的数量，0 表示没有限制
     */
    void setSingle(int pointNumber);
    /**
     * @brief afterInit 图形初始化后触发
     */
    virtual void afterInit();
    /**
     * @brief afterPointMoved 线段上的点移动后处理
     * @param id 发生移动的点的ID
     */
    virtual void afterPointMoved(const QString &id);
    /**
     * @brief afterPointMoveEnd 点移动操作结束后
     */
    virtual void afterPointMoveEnd();
    /**
     * @brief beforeAddPoint插入新点前
     * @param id 在ID前插入
     * @param pos 新点坐标
     */
    virtual void beforeAddPoint(const QString &id, const QPointF &pos);
    /**
     * @brief afterDelPoint 删除点前
     * @param id 要删除点的ID
     */
    virtual void beforeDelPoint(const QString &id);
    virtual QList<NamedPoint> createEditPoint();

protected Q_SLOTS:
    void onPointMoved(const QString &id, const QPointF &pos);
    void onAddPoint(const QString &id, const QPointF &pos);
    void onDelPoint(const QString &id);
    void onPointMoveStart(const QString &id);
    void onPointMoveEnd(const QString &id);

protected:
    // 矩形自身坐标系参考矩形
    QRectF logicRect;
    // true 预置路径，false 自定义路径
    bool predefine{false};
    // 初始化标记，1 捕获鼠标， 2 鼠标移动， 3 初始化结束
    PathState initStatge{DISABLED};

    void syncLogicRect();
private:
    // 单线段标记
    bool singleFlag{false};
    // 点的数量上限，0 没有限制
    int pointUpperLimit{0};
    bool pointMoveFlag{false};
    // 起止点形状
    QPainterPath startType, endType;
    QGraphicsItem *pathOwner;
    bool editable{false};
    bool previewMode{false};
    // 创建起止点形状
    void createStartType(const QPointF &center);
    void createEndType(const QPointF &end, qreal angle);
    /**
     * @brief initEnd 初始化结束
     */
    void initEnd();

    /**
     * @brief drawEndType 绘制终端路径
     * @param painter 画板
     * @param type 终端信息
     */
    void drawEndType(QPainter *painter);
    // 更新图元位置
    void updatePos();
};

#endif // ABSTRACTLINEPATH_H
