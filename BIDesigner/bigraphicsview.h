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

#ifndef BIGRAPHICSVIEW_H
#define BIGRAPHICSVIEW_H

#include "pageproperty.h"
#include "rulerwidget.h"

#include <QGraphicsView>
#include <QObject>
#include <QUndoStack>

class QXmlStreamWriter;
class QXmlStreamReader;
class GraphicPlugins;
class IGraphicPlugin;
class ICustomGraphic;
class BIGraphicsView : public QGraphicsView
{
    Q_OBJECT
    enum UndoAction{ADD, DEL, MOVE, GROUP, UNGROUP};
public:
    enum ZoomType{FITWINDOW, FITWIDTH};
    BIGraphicsView(QWidget *parent = nullptr);
    BIGraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~BIGraphicsView();

    // QObject interface
    bool event(QEvent *event) override;
    /**
     * @brief 用XML编码保存视图中的图形
     * @return xml 格式字符串
     */
    QString toXml();
    /**
     * @brief 从XML加载图形
     * @param xml xml文本
     */
    void loadFromXml(const QString &xml);

    void createGroup();
    void destroyGroup();
    /**
     * @brief flipGraphic 翻转当前选中的图元
     * @param actionName 命令名称
     */
    void flipGraphic(const QString &actionName);
    /**
     * @brief 设置选中图元的前后位置
     * @param action 命令名
     */
    void setGraphicZOrder(QString action);
    /**
     * @brief 设置图对齐
     * @param action 命令名称
     */
    void setGraphicAlign(QString action);
    /**
     * @brief 设置图分布
     * @param action 命令名称
     */
    void setGraphicDistribute(QString action);
    /**
     * @brief 全选/反选所有图元
     * @param flag true 全选，false 全不选
     */
    void selectAll(bool flag);
    /**
     * @brief 撤销操作
     */
    void undo();
    /**
     * @brief 重做操作
     */
    void redo();
    /**
     * @brief 缩放视图
     * @param step 步进
     * @return 当前缩放比例
     */
    qreal zoomByStep(qreal step);
    qreal zoomByValue(qreal value);
    qreal zoomByType(ZoomType type);
    /**
     * @brief 修改当前选中图元名称
     * @param name 名称
     */
    void modifyItemName(QString name);
    PageProperty getPageProperty() const;
    void setPageProperty(const PageProperty &newPageProperty);
    void setShowGrid(bool flag);
    void setShowScale(bool newShowScale);

    void setShowRefLine(bool flag);

    void setCurrentScale(qreal value);
    QSize selectSize();
    bool exportToImage(bool selectedScope, const QString &fileName, const QSize &size, const QColor &bgcolor, int quality);
    bool exportToSvg(bool selectedScope, const QString &fileName, const QSize &size);
    void setDragMode(QGraphicsView::DragMode mode);

Q_SIGNALS:
    void mouseMove(QMouseEvent *event);
    void zoomEvent(qint16 zoom);
public Q_SLOTS:
    void doCopy();
    void doCut();
    void doPast();
    void doDelete();
protected:
    // QWidget interface
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    // QGraphicsView interface
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[],
                   const QStyleOptionGraphicsItem options[]) override;
    void paintEvent(QPaintEvent *event) override;
    void scrollContentsBy(int dx, int dy) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
protected Q_SLOTS:
    /**
     * @brief 处理选择图元改变事件
     * @param graphicItem 当前使用的图元
     */
    void graphicItemChangedHandler(IGraphicPlugin *graphicItem);
    // UndoObject interface
    void undoEventProcessor(const QString &text, QVariant oldData, QVariant newData);
private:
    // 标尺
    QScopedPointer<RulerWidget> ruler;
    // 背景颜色
    QColor baseColor{qRgb(41,37,47)};
    // 背景颜色
    QColor backgroundColor{qRgb(24,20,29)};
    // 前景色
    QColor foregroundColor{qRgba(150,150,150,200)};
    // 显示标尺
    bool showScale{true};
    // 比例尺
    qreal currentScale{1};
    // 标尺宽度
    qint16 scaleWidth{15};
    // 标尺步进距离
    qint16 scaleStep{10};
    // 字体颜色
    QColor fontColor{qRgb(163,163,164)};
    // 字体大小
    qint16 fontSize{10};
    // 放大的最大比例
    qreal maxZoom{10};
    // 缩小的最小比例
    qreal minZoom{0.1};
    // 当前按下的键值
    QSet<int> pressKey;
    // scene 区域的margin
    qint16 contentMargin{50};
    // 鼠标位置
    QPointF mousePos;
    // 键盘移动步进
    qreal moveStep{1};
    // 图元插件面板
    // GraphicPluginWidget * graphicPluginWidget;
    // 当前选择的图元
    IGraphicPlugin *currentGraphicItem;
    // 撤销命令栈
    QUndoStack undoStack;
    // 选中图元移动前的位置
    QHash<QGraphicsItem *, QPointF> itemsPos,dragItemPos;
    bool isDrag{false};
    // 页面属性
    PageProperty pageProperty;
    Qt::PenStyle lastPenStyle{Qt::DashLine};
    // 显示参考线
    bool showRefLine{true};
    // 通过拖放方式创建
    bool createByDrop{false};
    // 图元区域选择
    bool rubberBanding{false};
    QRect rubberBandRect;
    bool extendSelection{false};
    QPointF mousePressScenePoint, lastMouseMoveScenePoint, lastRubberbandScenePoint;
    QPoint mousePressViewPoint;
    
    /**
     * @brief 初始化刻度尺等
     */
    void init();
    void updateRuler(const QSize &size);
    /**
     * @brief 执行缩放
     */
    void doZoom();
    /**
     * @brief 使用currentGraphicItem绘制新图元
     * @param point 图元位置
     */
    void createGraphicsItem(const QPointF &point);
    /**
     * @brief 生成可撤销命令
     * @param action 当前动作
     * @param items 涉及的图元列表
     */
    void genUndoCommand(UndoAction action, QList<QGraphicsItem*> items);
    /**
     * @brief 记录图元当前位置
     * @param items 图元列表
     * @return 图元与位置的列表
     */
    QHash<QGraphicsItem *, QPointF> getItemsPos(QList<QGraphicsItem*> items);
    QRegion rubberBandRegion(const QWidget *widget, const QRect &rect) const;

};
#endif // BIGRAPHICSVIEW_H
