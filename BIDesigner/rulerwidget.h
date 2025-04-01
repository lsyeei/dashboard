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

#ifndef RULERWIDGET_H
#define RULERWIDGET_H

#include <QObject>
#include <QWidget>

/**
 * @brief 上下限
 */
struct Bound {
    // 下限
    qint32 lower;
    // 上限
    qint32 upper;
};

class RulerWidget;
/**
 * @brief 顶部尺子，或左侧尺子
 */
class Ruler : public QWidget
{
    Q_OBJECT
public:
    explicit Ruler(RulerWidget *panel, Qt::Orientation orientation);//, QWidget *parent = nullptr);

    void setViewRect(const QRect &newViewRect);
    /**
     * @brief setMarkBound
     * @param bound 刻度值范围
     */
    void setMarkBound(const Bound &bound);
    /**
     * @brief 设置参考线位置
     * @param start 参考线起点
     * @param middle 参考线中间点
     * @param end 参考线终点
     */
    void setTtracePos(qreal start, qreal middle, qreal end);
    /**
     * @brief 设置追踪标记
     * @param flag true 显示参考线，false 不显示参考线
     */
    void setTraceFlag(bool flag);

signals:

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    // 刻度尺控件
    RulerWidget *groupPanel;
    // 尺子方向
    Qt::Orientation orientation{Qt::Horizontal};
    // 视图刻度起始值
    qreal markFrom;
    // 视图刻度最终值
    qreal markTo;
    // 视图区域
    QRect viewRect;
    bool traceFlag{true};
    qreal startPos{0}, middlePos{0}, endPos{0};

    void drawSceneRuler(QPainter *painter);
    void drawHorizontalRuler(QPainter *painter);
    void drawVerticalRuler(QPainter *painter);
    QRect getPaintRect();
    /**
     * @brief 绘制参考线
     * @param painter 画笔
     * @param lines 参考线位置
     */
    void drawTraceLine(QPainter *painter, QList<QLineF> lines);
};
/**
 * @brief 尺子转角
 */
class RulerCorner : public QWidget
{
    Q_OBJECT
public:
    explicit RulerCorner(RulerWidget *panel);//, QWidget *parent = nullptr);

signals:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    // 刻度尺控件
    RulerWidget *groupPanel;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

/**
 * @brief 刻度尺控件
 */
class RulerWidget : public QObject
{
    Q_OBJECT
    friend class ruler;
    friend class RulerCorner;
public:
    explicit RulerWidget(QWidget *parent = nullptr);
    ~RulerWidget();
    void resize(const QSize &size);
    void update();

    /**
     * @brief 是否显示标尺
     * @param show true 显示，false 不显示
     */
    void show(bool show);

    qint16 getScaleWidth() const;
    RulerWidget * setScaleWidth(qint16 newScaleWidth);

    QColor getBackgroundColor() const;
    RulerWidget * setBackgroundColor(const QColor &newBackgroundColor);

    QColor getForegroundColor() const;
    RulerWidget * setForegroundColor(const QColor &newForegroundColor);

    qint16 getScaleStep() const;
    RulerWidget * setScaleStep(qint16 newScaleStep);

    QColor getFontColor() const;
    RulerWidget * setFontColor(const QColor &newFontColor);

    qint16 getFontSize() const;
    RulerWidget * setFontSize(qint16 newFontSize);

    /**
     * @brief 设置标尺视口大小
     * @param rect 视口位置
     */
    RulerWidget * setViewRect(const QRect &rect);

    /**
     * @brief setMarkBound
     * @param hBound 水平刻度值
     * @param vBound 垂直刻度值
     */
    RulerWidget * setMarkBound(const Bound &hBound, const Bound &vBound);

    void setTraceFlag(bool flag);

    void setTraceZone(const QRectF &zone);

signals:
private:
    // 标尺
    QScopedPointer<Ruler> topRuler;
    QScopedPointer<Ruler> leftRuler;
    QScopedPointer<RulerCorner> corner;
    // 标尺宽度
    qint16 scaleWidth{15};
    // 背景颜色
    QColor backgroundColor{qRgb(41,37,47)};
    // 前景色
    QColor foregroundColor{qRgba(50,50,50,100)};
    // 标尺步进距离
    qint16 scaleStep{10};
    // 字体颜色
    QColor fontColor{qRgb(163,163,164)};
    // 字体大小
    qint16 fontSize{10};
};

#endif // RULERWIDGET_H
