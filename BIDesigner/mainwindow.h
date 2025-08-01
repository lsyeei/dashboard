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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "projectpropertyform.h"
#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE

class QLabel;
class QPushButton;
class GraphicPropertyForm;
class ProjectPropertyForm;
class AnimationForm;
class QPropertyAnimation;
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class BIGraphicsScene;
class GraphicPlugins;
class QGraphicsItem;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    BIGraphicsScene *scene;
    // QObject interface
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

Q_SIGNALS:
    void singleSelectEvent(QGraphicsItem *item);
    void noSelectEvent();
    void multiSelectEvent();
private slots:
    // void colorChanged(QColor oldcolor,QColor newcolor);
    // 图元切换时同步切换属性窗口
    void onSceneSelectionChanged();
    void oneGraphSelected(QGraphicsItem *item);
    void noGraphSelected();
    void multiGraphSelected();

    void graphicsViewMouseMove(QMouseEvent *event);
    void graphicsViewZoomed(qint16 zoom);

    void on_action_animate_triggered();
    void menuPopup();
    void zoomMenuPopup();

    void doExit();
    void doSave();
    void doOpen();
    void doExport();
    void doGroup();
    void doUngroup();
    void doFlip();
    void doZOrder();
    void doAlign();
    void doDistribute();
    void doSelect();
    void undo();
    void redo();
    void doZoom();
    void showRuler(bool flag);
    void showGrid(bool flag);
    void showRefLine(bool flag);

    void projectPropertyChanged(const ProjectProperty &project);
    void pagePropertyChanged(const PageProperty &page);
    void onAnimatePlay(bool flag);
    void showAbout();
    void saveToLib();

private:
    Ui::MainWindow *ui;
    // 图元属性窗口
    GraphicPropertyForm *propertyWidget{nullptr};
    QMenu *menu{nullptr};
    QMenu *zoomMenu{nullptr};
    QPushButton *menuBtn{nullptr};
    QPushButton *zoomBtn{nullptr};
    ProjectPropertyForm *projectWidget{nullptr};
    // 控件所在 widget
    GraphicPlugins * graphicPluginWidget{nullptr};
    // 状态栏控件
    QLabel *mouseInfo{nullptr};
    QLabel *scaleInfo{nullptr};
    QPropertyAnimation *animation{nullptr};
    ProjectProperty projectProperty;
    // 动画
    AnimationForm *animationForm{nullptr};
    bool playFlag{false};
    qreal angle{0};
    // 右键菜单
    QPointer<QMenu> graphicMenu;
    QPointer<QMenu> viewMenu;
    // void drawShape();
    void setScene();
    void initStatusBar();
    /**
     * @brief 创建带下拉指示的按钮
     * @param title按钮标题
     * @param width 按钮宽度
     * @return 按钮对象指针
     */
    QPushButton *createDropdownBtn(const QString &title, int width);
    void initToolBar();
    void initMenu();
    void setMenuEvent();
    void initGraphicsWidget();

    void initProjectPropertyForm();
    void initAnimateForm();
    void enableAlignAction(bool flag);
    void enableDistributeAction(bool flag);
    void enableLayerAction(bool flag);
    /**
     * @brief 解析 xml 中的project信息
     * @param xml xml文本
     */
    void parseProjectXml(const QString &xml);
    /**
     * @brief 解析 xml 中的project信息
     * @param xml xml文本
     */
    void parsePageXml(const QString &xml);
    /**
     * @brief paletteCanged 系统主题改变
     */
    void paletteCanged();
    /**
     * @brief initPopMenu 初始化右键菜单
     */
    void initPopMenu();
    void onViewMenuEvent(QContextMenuEvent *event);
    void loadPlugin();
};
#endif // MAINWINDOW_H
