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

#ifndef LINESELECTOR_H
#define LINESELECTOR_H

#include "curvecontrolparam.h"
#include "namedpoint.h"

#include <QObject>
#include <abstractselector.h>

class LineSelector : public AbstractSelector
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    LineSelector(QList<NamedPoint> points, QGraphicsItem *parent = nullptr);
    ~LineSelector();
    void updatePoints(QList<NamedPoint> points);
    /**
     * @brief createEditPoint 生成可编辑点
     * @param points 可编辑点的集合，其中ID为插入点的ID，pt为编辑点的位置
     */
    void updateEditPoint(const QList<NamedPoint> &points);
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void enableEdit(bool flag);
    /**
     * @brief setPreviewMode 是否启用预览模式
     * @param flag true 启用，false 不启用
     */
    void setPreviewMode(bool flag);
    /**
     * @brief enableCurveAdjuster 启用曲线参数调整
     * @param flag true 启用，false 不启用
     */
    void enableCurveAdjuster(bool flag);
    void setCurveController(const CurveControlParam &left, const CurveControlParam &right);
    /**
     * @brief setCurrentPoint 设置当前处于编辑状态的点
     * @param id 点的ID
     */
    void setCurrentPoint(const QString &id);

Q_SIGNALS:
    void pointMoved(const QString &id, const QPointF &pos);
    void pointMoveStart(const QString &id);
    void pointMoveEnd(const QString &id);
    /**
     * @brief addPoint 添加控制点事件
     * @param id 在id前添加
     * @param pos 相对selector的位置
     */
    void addPoint(const QString &id, const QPointF &pos);
    void delPoint(const QString &id);
    void leftCurveParamChanged(const CurveControlParam &param);
    void rightCurveParamChanged(const CurveControlParam &param);
    // AbstractSelector interface
protected slots:
    void onAdjusterMove(const QPointF &from, const QPointF &to) override;
    void onAdjusterMoveStart() override;
    void onAdjusterMoveEnd() override;
private:
    // 绘制线条的点按照顺序排列的ID集合
    QVector<QString> pointIds;
    QList<NamedPoint> editPoints;
    // true 可通过selecetor增加/删除点，false 不能增加点
    bool editable{false};
    // 正在编辑
    bool editing{false};
    // 触发增删的最小偏移
    const int minEditLen{3};
    // 要合并目标点的ID
    QString mergeId;
    bool previewMode{false};
    // 当前移动的点
    NamedPoint movedAdjustor;
    // 记录控制点移动前的位置
    QPointF startPos{0,0};
    // 曲线控制点调整
    bool curveAdjustable{false};
    const QString lCurve{"left"}, rCurve{"right"};
    CurveControlParam lParam, rParam;
    // 当前调整点的ID
    QString currentAdjusterId{""};
    QPainterPath getParentPath() const;
    /**
     * @brief updateCurveControl 创建或更新曲线控制点
     * @param id 控制点ID
     * @param param 控制点参数
     */
    void updateCurveControl(const QString &id, const CurveControlParam &param);
    void removeCurveControl();
    /**
     * @brief paintCurveControl 绘制曲线调整点的连接线
     * @param painter
     */
    void paintCurveControl(QPainter *painter);
};

#endif // LINESELECTOR_H
