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

#ifndef ABSTRACTLINEITEM_H
#define ABSTRACTLINEITEM_H

#include <QObject>
#include "abstractitem.h"
#include "endtypefactory.h"
#include "ilinepath.h"
#include "linebaseproperty.h"
#include "lineselector.h"

class QTimeLine;
class AbstractLineItem : public AbstractItem, public ILinePath
{
    Q_OBJECT
    // Q_PROPERTY(qreal width READ width WRITE setWidth FINAL)
    // Q_PROPERTY(qreal height READ height WRITE setHeight FINAL)
    // Q_PROPERTY(QSizeF size READ size WRITE setSize FINAL)
    // Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
public:
    enum LineState{
        // 不可用状态
        DISABLED,
        // 捕获鼠标状态
        CAPTURED,
        // 绘制状态
        DRAWING,
        // 绘制完成
        FINISHED
    };
    explicit AbstractLineItem(QGraphicsItem *parent = nullptr);
    ~AbstractLineItem();

    // AbstractZoneItem interface
    LineBaseProperty *attribute() const;
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    QSizeF size();
    // ICustomGraphic interface
    void setSize(const QSizeF &size) override;

    // ILinePath interface
    virtual QPainterPath linePath(QList<QPointF> points) const Q_DECL_OVERRIDE;
    QPainterPath startShape() const Q_DECL_OVERRIDE;
    QPainterPath endShape() const Q_DECL_OVERRIDE;

    // qreal width() const;
    // virtual void setWidth(qreal newWidth);

    // qreal height() const;
    // virtual void setHeight(qreal newHeight);

    // QColor color() const;
    // virtual void setColor(const QColor &newColor);

    // ILinePath interface
    QPainterPath previewPath(QList<QPointF> points, QVariant args) const override;
    /**
     * @brief enableEdit 开启编辑（增加、删除）功能
     * @param flag true 开启， false 关闭
     */
    void enableEdit(bool flag);
    /**
     * @brief enablePreview 开启预览模式，开启后移动控制点时有预览
     * @param flag true 开启，false 关闭
     */
    void enablePreview(bool flag);

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
     * @brief linePath 绘制点组成的路径
     * @param points 组成线的点
     * @return 路径
     */
    // virtual QPainterPath linePath(QList<QPointF> points) const = 0;
    /**
     * @brief createPredefinedItem 创建预定义图形
     */
    virtual void createPredefinedItem() = 0;
    /**
     * @brief afterCreateSelector 创建selector后执行
     * @param s 已创建的 selector 指针
     */
    virtual void afterCreateSelector(LineSelector *s);
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
    virtual void afterPointMoveEnd(const QString &id);
    /**
     * @brief beforeAddPoint插入新点前
     * @param id 在ID前插入
     * @param pos 新点坐标
     */
    virtual void beforeAddPoint(const QString &id, const QPointF &pos);
    virtual void afterAddPoint(const QString &id);
    /**
     * @brief afterDelPoint 删除点前
     * @param id 要删除点的ID
     */
    virtual void beforeDelPoint(const QString &id);
    /**
     * @brief calcEndRotation 绘制端点图形旋转角度
     * @param points 组成线段点的集合
     * @param type 要计算的端点
     */
    virtual qreal calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const;
    /**
     * @brief getEndTypePath 计算终端图形的轮廓和连接点
     * @param type 终端数据
     * @return 轮廓和连接点
     */
    QPair<QPainterPath, QPointF> getEndTypePath(LineEndType type) const;
    void syncLogicRect();
    /**
     * @brief dragPoint 初始化绘制过程中，按下鼠标左键并移动时触发该方法
     * @param pt 拖动的点
     * @param pos  鼠标在scene坐标系内的位置
     */
    virtual void dragPoint(const NamedPoint &pt, const QPointF &pos);
    /**
     * @brief createEditPoint 生成可编辑的点
     * @return 点的集合， ID为插入位置点的ID，pt为可编辑点的坐标
     */
    virtual QList<NamedPoint> createEditPoint();

protected Q_SLOTS:
    /**
     * @brief onPointMoved 处理控制点移动
     * @param id 当前移动的控制点
     * @param pos scene坐标系内的坐标
     */
    void onPointMoved(const QString &id, const QPointF &pos);
    void onAddPoint(const QString &id, const QPointF &pos);
    void onDelPoint(const QString &id);
    void onPointMoveStart(const QString &id);
    void onPointMoveEnd(const QString &id);
    void onAnimateFrameChanged(int value);

protected:
    // 矩形自身坐标系参考矩形
    QRectF logicRect;
    // 初始化标记，1 捕获鼠标， 2 鼠标移动， 3 初始化结束
    LineState initStatge{DISABLED};
    // 端点路径
    QPainterPath startPath;
    QPainterPath endPath;
    //连接点
    QPointF startJointPt;
    QPointF endJointPt;

private:
    // 单线段标记
    bool singleFlag{false};
    // 点的数量上限，0 没有限制
    int pointUpperLimit{0};
    // 动画
    QTimeLine *timeLine{nullptr};
    int frameCount{25};
    // flow animation 偏移
    qreal dashOffset{0};
    bool pointMoveFlag{false};
    // 是否允许编辑，默认关闭
    bool editable{false};
    // 是否开启预览模式，默认关闭
    bool previewMode{false};
    /**
     * @brief initEnd 初始化结束
     */
    void initEnd();

    /**
     * @brief drawEndType 绘制终端路径
     * @param painter 画板
     * @param type 终端信息
     */
    void drawEndType(QPainter *painter, LineEndType type);
    // 更新图元位置
    void updatePos();
};

#endif // ABSTRACTLINEITEM_H
