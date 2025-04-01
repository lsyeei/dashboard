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

#ifndef RECTSELECTOR_H
#define RECTSELECTOR_H

#include "abstractselector.h"

class RectSelector : public AbstractSelector
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    RectSelector() = delete;
    /**
     * @brief 带参构造函数
     * @param rect 被控制图行的边界
     * @param rectBorder 超出被控制矩形的部分，比如：矩形框的边框。使用该参数可以防止大小改变时刷新区域偏小导致的残影
     * @param parent 一般指被控图形
     */
    explicit RectSelector(const QRectF &rect, qreal rectBorder, QGraphicsItem *parent = nullptr);
    /**
     * @brief 带参构造函数
     * @param rect 被控制图像的边界（不含边框）
     * @param parent 被控图形
     */
    explicit RectSelector(const QRectF &rect, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updateRect(const QRectF &newRect);
    void setRadius(const qreal newRadius);
    void showCornerAdjuster(bool show);
    /**
     * @brief 设置保持比例
     * @param flag true 保持比例，false 不保持比例
     * @return true 成功，false 失败
     */
    bool keepRatio(bool flag);
    /**
     * @brief 设置被控矩形的边框
     * @param border 边框大小
     */
    void setRectBorder(qreal border);

Q_SIGNALS:
    void rectSizeChanged(QRectF value);
    void rectCornerChanged(qreal value);
    void rectRotateChanged(qreal value);

    // AbstractSelector interface
protected slots:
    void onAdjusterMove(const QPointF &from, const QPointF &to) override;
private:
    // 选择框大小
    QRectF rect;
    // 被控矩形边框
    qreal parentBorder{0};
    // 边框
    qint8 borderWidth{1};
    QString borderColor{"#06a"};
    // 被控矩形的圆角
    bool hasCorner{false};
    qreal radius{0};
    // 偏移量累计器，当每次大小变化不足1时先累计，大于1后再调整图形
    QPointF sizeOffsetTotal{0,0};
    qreal ratio{0};


    /**
     * @brief 获取被控图像得旋转角度
     * @return  旋转角度
     */
    qreal parentRotation();
    /**
     * @brief syncTransfrom 同步父节点的transform
     */
    void syncTransfrom() override;
    /**
     * @brief 创建控制点
     */
    void createAdjuster();
    /**
     * @brief 初始化控制点
     */
    void initAdjuster();
    /**
     * @brief 更新控制点
     */
    void updateCorner();
    /**
     * @brief 计算调整的大小
     * @param obj 调整点
     * @param from 鼠标在父节点坐标系下移动的起始位置
     * @param to 鼠标在父节点坐标系下移动的终止位置
     */
    void calcSize(AdjustPoint *obj, const QPointF &from, const QPointF &to);
    /**
     * @brief 重新计算大小的偏移量
     * @param offset 初始偏移量
     * @return 调整后的偏移量
     */
    QRectF recalcSize(QRectF offset);
    /**
     * @brief 计算圆角调整大小
     * @param from 鼠标在父节点坐标系下移动的起始位置
     * @param to 鼠标在父节点坐标系下移动的终止位置
     */
    void calcCorner(const QPointF &from, const QPointF &to);
    /**
     * @brief 计算旋转的角度
     * @param from 鼠标在父节点坐标系下移动的起始位置
     * @param to 鼠标在父节点坐标系下移动的终止位置
     */
    void calacRotation(const QPointF &from, const QPointF &to);
};

#endif // RECTSELECTOR_H
