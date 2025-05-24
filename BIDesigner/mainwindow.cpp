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

#include "animation/path/imovepath.h"
#include "filetemplate.h"
#include "bigraphicsscene.h"
#include "graphicplugins.h"
#include "mainwindow.h"
#include "graphicpropertyform.h"
#include "svghelper.h"
#include "ui_mainwindow.h"
#include "projectpropertyform.h"
#include "pageproperty.h"
#include <QDir>
#include <QPluginLoader>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QShortcut>
#include <QtConcurrent>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QPluginLoader>
#include <ExportDialog.h>
#include "igraphicplugin.h"
#include "icustomgraphic.h"
#include "graphicsitemgroup.h"
#include "xmlHelper.h"
#include "animation/animationform.h"
#include "animation/animationfactory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 修改滚动区域背景
    ui->scrollArea->setBackgroundRole(QPalette::Base);
    setCentralWidget(ui->centralwidget);
    // 加载图元控件
    graphicPluginWidget = new GraphicPlugins(ui->graphicItems);
    ui->graphicItems->layout()->setAlignment(Qt::AlignTop);
    ui->graphicItems->layout()->addWidget(graphicPluginWidget);
    // 设置场景
    setScene();
    // 配置工具栏
    initToolBar();
    // 配置状态栏
    initStatusBar();
    // 加载图元属性窗口
    initGraphicsWidget();
    // 项目属性
    initProjectPropertyForm();
    // 动画属性
    initAnimateForm();
    // 初始化右键菜单
    initPopMenu();
    ui->graphicsView->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteCanged();
    }
    return QMainWindow::event(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->graphicsView && event->type() == QEvent::ContextMenu) {
        auto e = dynamic_cast<QContextMenuEvent*>(event);
        onViewMenuEvent(e);
        event->accept();
        return true;
    }
    return QObject::eventFilter(watched, event);
}

void MainWindow::initStatusBar()
{
    // 鼠标位置信息
    mouseInfo = new QLabel(ui->statusBar);
    mouseInfo->setMargin(2);
    mouseInfo->setText("x , y");
    ui->statusBar->addWidget(mouseInfo);
    // 缩放信息
    scaleInfo = new QLabel(ui->statusBar);
    ui->statusBar->addWidget(scaleInfo);
    graphicsViewZoomed(100);
    // 背景网格
    ui->showViewGrid->blockSignals(true);
    ui->showViewGrid->setChecked(true);
    ui->showViewGrid->blockSignals(false);
    ui->showViewRefLine->blockSignals(true);
    ui->showViewRefLine->setChecked(true);
    ui->showViewRefLine->blockSignals(false);
    ui->showViewRuler->blockSignals(true);
    ui->showViewRuler->setChecked(true);
    ui->showViewRuler->blockSignals(false);
}


QPushButton *MainWindow::createDropdownBtn(const QString &title, int width)
{
    QIcon menuIcon(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal));
    QPushButton *btn = new QPushButton(menuIcon, title, ui->toolBar);
    btn->setIconSize({18,18});
    btn->setFlat(true);
    btn->setLayoutDirection(Qt::RightToLeft);
    auto menuSize = btn->sizePolicy();
    menuSize.setVerticalPolicy(QSizePolicy::Expanding);
    btn->setSizePolicy(menuSize);
    btn->setMinimumWidth(width);

    return btn;
}

void MainWindow::enableAlignAction(bool flag)
{
    ui->alignTop->setEnabled(flag);
    ui->alignBottom->setEnabled(flag);
    ui->alignLeft->setEnabled(flag);
    ui->alignRight->setEnabled(flag);
    ui->alignVertical->setEnabled(flag);
    ui->alignHorizon->setEnabled(flag);
}

void MainWindow::enableDistributeAction(bool flag)
{
    ui->distributeHorizon->setEnabled(flag);
    ui->distributeVertical->setEnabled(flag);
}

void MainWindow::enableLayerAction(bool flag)
{
    ui->toBack->setEnabled(flag);
    ui->toFront->setEnabled(flag);
    ui->toTop->setEnabled(flag);
    ui->toBottom->setEnabled(flag);
}

void MainWindow::parseProjectXml(const QString &xml)
{
    QXmlStreamReader reader(xml);
    typedef XmlTemplate::projectTemplate project;
    while(!reader.atEnd()){
        reader.readNextStartElement();
        if (reader.hasError()) {
            QMessageBox::information(this, tr("提示"), QString(tr("解析project错误。%1" )).arg(reader.errorString()));
            break;
        }
        auto name= reader.name();
        if (name.compare(project::projectName) == 0) {
            projectProperty.setName(reader.readElementText());
        } else if (name.compare(project::author) == 0) {
            projectProperty.setAuthor(reader.readElementText());
        } else if (name.compare(project::createTime) == 0) {
            projectProperty.setCreateTime(QDateTime::fromString(reader.readElementText()));
        } else if (name.compare(project::modifyTime) == 0) {
            projectProperty.setModifyTime(QDateTime::fromString(reader.readElementText()));
        }
    }
    projectWidget->initProjectData(projectProperty);
}

void MainWindow::parsePageXml(const QString &xml)
{
    QXmlStreamReader reader(xml);
    while(!reader.atEnd()){
       reader.readNext();
        if (reader.hasError()) {
            QMessageBox::information(this, tr("提示"), QString(tr("解析board错误。%1" )).arg(reader.errorString()));
            break;
        }
        if (reader.isCDATA()){
            auto data = reader.text();
            QByteArray array =  QByteArray::fromHex(data.toLocal8Bit());
            QDataStream stream(&array, QIODeviceBase::ReadOnly);
            PageProperty page;
            stream >> page;
            ui->graphicsView->setPageProperty(page);
            projectWidget->initPageData(page);
        }
    }
}

void MainWindow::paletteCanged()
{
    // 修改图标
    ui->group->setIcon(QIcon{SvgHelper{QString{":/icons/icons/group.svg"}}
                    .toPixmap(ui->group->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->ungroup->setIcon(QIcon{SvgHelper{QString{":/icons/icons/ungroup.svg"}}
                    .toPixmap(ui->ungroup->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->toFront->setIcon(QIcon{SvgHelper{QString{":/icons/icons/bring-to-upper.svg"}}
                    .toPixmap(ui->toFront->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->toBack->setIcon(QIcon{SvgHelper{QString{":/icons/icons/bring-to-downer.svg"}}
                    .toPixmap(ui->toBack->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->toTop->setIcon(QIcon{SvgHelper{QString{":/icons/icons/bring-to-top.svg"}}
                    .toPixmap(ui->toTop->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->toBottom->setIcon(QIcon{SvgHelper{QString{":/icons/icons/bring-to-bottom.svg"}}
                    .toPixmap(ui->toBottom->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignLeft->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-left.svg"}}
                    .toPixmap(ui->alignLeft->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignRight->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-right.svg"}}
                    .toPixmap(ui->alignRight->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignTop->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-up.svg"}}
                    .toPixmap(ui->alignTop->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignBottom->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-down.svg"}}
                    .toPixmap(ui->alignBottom->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignHorizon->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-midle.svg"}}
                    .toPixmap(ui->alignHorizon->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->alignVertical->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Aligne-vertical-midl.svg"}}
                    .toPixmap(ui->alignVertical->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->distributeHorizon->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Distribute-midle.svg"}}
                    .toPixmap(ui->distributeHorizon->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->distributeVertical->setIcon(QIcon{SvgHelper{QString{":/icons/icons/Distribute-vertical .svg"}}
                    .toPixmap(ui->distributeVertical->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->doPreview->setIcon(QIcon{SvgHelper{QString{":/icons/icons/preview.svg"}}
                    .toPixmap(ui->doPreview->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->flipVertical->setIcon(QIcon{SvgHelper{QString{":/icons/icons/flip_vertical.svg"}}
                    .toPixmap(ui->flipVertical->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});
    ui->flipHorizontal->setIcon(QIcon{SvgHelper{QString{":/icons/icons/flip_horizontal.svg"}}
                    .toPixmap(ui->flipHorizontal->isEnabled()?SvgHelper::Normal:SvgHelper::Disabled)});

    menuBtn->setIcon(QIcon(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal)));
    zoomBtn->setIcon(QIcon(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal)));
}

void MainWindow::initPopMenu()
{
    graphicMenu = new QMenu(ui->graphicsView);
    graphicMenu->addAction(ui->redo);
    graphicMenu->addAction(ui->undo);
    graphicMenu->addSeparator();
    graphicMenu->addAction(ui->doCopy);
    graphicMenu->addAction(ui->doCut);
    graphicMenu->addAction(ui->doPast);
    graphicMenu->addAction(ui->doDelete);
    graphicMenu->addSeparator();
    graphicMenu->addAction(ui->doSelectAll);
    graphicMenu->addAction(ui->doUnselectAll);
    graphicMenu->addSeparator();
    auto groupMenu = graphicMenu->addMenu(ui->group->icon(),tr("组合"));
    groupMenu->addAction(ui->group);
    groupMenu->addAction(ui->ungroup);
    auto alignMenu = graphicMenu->addMenu(ui->alignLeft->icon(),tr("对齐"));
    alignMenu->addAction(ui->alignLeft);
    alignMenu->addAction(ui->alignRight);
    alignMenu->addAction(ui->alignHorizon);
    alignMenu->addAction(ui->alignTop);
    alignMenu->addAction(ui->alignBottom);
    alignMenu->addAction(ui->alignVertical);
    alignMenu->addSeparator();
    alignMenu->addAction(ui->distributeHorizon);
    alignMenu->addAction(ui->distributeVertical);
    auto distMenu = graphicMenu->addMenu(ui->toTop->icon(), tr("排列"));
    distMenu->addAction(ui->toTop);
    distMenu->addAction(ui->toBottom);
    distMenu->addAction(ui->toFront);
    distMenu->addAction(ui->toBack);
    graphicMenu->addAction(ui->doExport);
    graphicMenu->addAction(ui->saveToLib);

    viewMenu = new QMenu(ui->graphicsView);
    viewMenu->addAction(ui->doPast);
    viewMenu->addSeparator();
    viewMenu->addAction(ui->redo);
    viewMenu->addAction(ui->undo);
    viewMenu->addSeparator();
    viewMenu->addAction(ui->doSelectAll);
    viewMenu->addAction(ui->doUnselectAll);
    viewMenu->addSeparator();
    viewMenu->addAction(ui->zoomin);
    viewMenu->addAction(ui->zoomout);
    viewMenu->addAction(ui->zoomFitWindow);
    viewMenu->addAction(ui->zoomFitWidth);
    viewMenu->addSeparator();
    viewMenu->addAction(ui->showViewGrid);
    viewMenu->addAction(ui->showViewRefLine);
    viewMenu->addAction(ui->showViewRuler);
}

void MainWindow::initToolBar()
{

    // 添加菜单按钮
    menuBtn = createDropdownBtn(tr("Dashboard"), 100);
    ui->toolBar->insertWidget(ui->doSave, menuBtn);
    connect(menuBtn, SIGNAL(pressed()), this, SLOT(menuPopup()));
    // 添加视图缩放菜单
    zoomBtn = createDropdownBtn("100%", 50);
    ui->toolBar->insertWidget(ui->zoomin, zoomBtn);
    connect(zoomBtn, SIGNAL(pressed()), this, SLOT(zoomMenuPopup()));
    // 创建菜单
    initMenu();
    // 关联事件
    setMenuEvent();
    // 设置工具栏状态
    ui->group->setEnabled(false);
    ui->ungroup->setEnabled(false);
    enableAlignAction(false);
    enableDistributeAction(false);
    enableLayerAction(false);

    paletteCanged();
}

void MainWindow::initMenu()
{
    ui->menuBar->setVisible(false);
    auto menuChildrens = ui->menuBar->findChildren<QMenu *>(Qt::FindDirectChildrenOnly);
    menu = new QMenu(ui->toolBar);
    foreach (auto subMenu, menuChildrens) {
        menu->addMenu(subMenu);
    }
    // 视图缩放菜单
    zoomMenu = new QMenu(tr("缩放"),ui->toolBar);
    zoomMenu->addAction(ui->zoom25);
    zoomMenu->addAction(ui->zoom50);
    zoomMenu->addAction(ui->zoom75);
    zoomMenu->addAction(ui->zoom100);
    zoomMenu->addAction(ui->zoom125);
    zoomMenu->addAction(ui->zoom150);
    zoomMenu->addAction(ui->zoom200);
    zoomMenu->addAction(ui->zoom300);
    zoomMenu->addAction(ui->zoom400);
    zoomMenu->addSeparator();
    zoomMenu->addAction(ui->zoomFitWindow);
    zoomMenu->addAction(ui->zoomFitWidth);
    zoomMenu->addSeparator();
    zoomMenu->addAction(ui->zoomDefine);
}

void MainWindow::setMenuEvent()
{
    // 退出
    connect(ui->doExit, SIGNAL(triggered(bool)), this, SLOT(doExit()));
    // 打开保存
    connect(ui->doOpen, SIGNAL(triggered(bool)), this, SLOT(doOpen()));
    connect(ui->doSave, SIGNAL(triggered(bool)), this, SLOT(doSave()));
    connect(ui->doExport, SIGNAL(triggered(bool)), this, SLOT(doExport()));
    // 编辑
    connect(ui->doCopy, SIGNAL(triggered(bool)), ui->graphicsView, SLOT(doCopy()));
    connect(ui->doCut, SIGNAL(triggered(bool)), ui->graphicsView, SLOT(doCut()));
    connect(ui->doPast, SIGNAL(triggered(bool)), ui->graphicsView, SLOT(doPast()));
    connect(ui->doDelete, SIGNAL(triggered(bool)), ui->graphicsView, SLOT(doDelete()));
    // 前后次序设置
    connect(ui->toFront, SIGNAL(triggered(bool)), this, SLOT(doZOrder()));
    connect(ui->toBack, SIGNAL(triggered(bool)), this, SLOT(doZOrder()));
    connect(ui->toTop, SIGNAL(triggered(bool)), this, SLOT(doZOrder()));
    connect(ui->toBottom, SIGNAL(triggered(bool)), this, SLOT(doZOrder()));
    // 组合
    connect(ui->group, SIGNAL(triggered(bool)), this, SLOT(doGroup()));
    connect(ui->ungroup, SIGNAL(triggered(bool)), this, SLOT(doUngroup()));
    // 翻转
    connect(ui->flipHorizontal, SIGNAL(triggered(bool)), this, SLOT(doFlip()));
    connect(ui->flipVertical, SIGNAL(triggered(bool)), this, SLOT(doFlip()));
    // 对齐
    connect(ui->alignLeft, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    connect(ui->alignRight, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    connect(ui->alignTop, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    connect(ui->alignBottom, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    connect(ui->alignHorizon, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    connect(ui->alignVertical, SIGNAL(triggered(bool)), this, SLOT(doAlign()));
    // 分布
    connect(ui->distributeHorizon, SIGNAL(triggered(bool)), this, SLOT(doDistribute()));
    connect(ui->distributeVertical, SIGNAL(triggered(bool)), this, SLOT(doDistribute()));
    // 选择
    connect(ui->doSelectAll, SIGNAL(triggered(bool)), this, SLOT(doSelect()));
    connect(ui->doUnselectAll, SIGNAL(triggered(bool)), this, SLOT(doSelect()));
    // 撤销
    connect(ui->undo, SIGNAL(triggered(bool)), this, SLOT(undo()));
    connect(ui->redo, SIGNAL(triggered(bool)), this, SLOT(redo()));
    // 视图
    connect(ui->showViewGrid, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));
    connect(ui->showViewRuler, SIGNAL(toggled(bool)), this, SLOT(showRuler(bool)));
    connect(ui->showViewRefLine, SIGNAL(toggled(bool)), this, SLOT(showRefLine(bool)));
    connect(ui->zoomin, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoomout, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom25, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom50, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom75, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom100, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom125, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom150, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom200, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom300, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoom400, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoomFitWindow, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoomFitWidth, SIGNAL(triggered(bool)), this, SLOT(doZoom()));
    connect(ui->zoomDefine, SIGNAL(triggered(bool)), this, SLOT(doZoom()));

    connect(ui->doAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    connect(ui->saveToLib, SIGNAL(triggered(bool)), this, SLOT(saveToLib()));
}

void MainWindow::initGraphicsWidget()
{
    propertyWidget = new GraphicPropertyForm();
    propertyWidget->setView(ui->graphicsView);
}

void MainWindow::initProjectPropertyForm()
{
    projectWidget = new ProjectPropertyForm();
    projectWidget->initProjectData(projectProperty);
    auto page = ui->graphicsView->getPageProperty();
    page.setWidth(scene->sceneRect().width());
    page.setHeight(scene->sceneRect().height());
    ui->graphicsView->setPageProperty(page);
    projectWidget->initPageData(page);
    ui->scrollArea->setWidget(projectWidget);
    ui->propertyWidget->setTabText(0, tr("项目"));
    ui->propertyWidget->setCurrentIndex(0);
    connect(projectWidget, SIGNAL(projectPropertyEvent(ProjectProperty)),
            this, SLOT(projectPropertyChanged(ProjectProperty)));
    connect(projectWidget, SIGNAL(pagePropertyEvent(PageProperty)),
            this, SLOT(pagePropertyChanged(PageProperty)));
    connect(projectWidget, SIGNAL(rulerStateEvent(bool)),
            this, SLOT(showRuler(bool)));
    connect(projectWidget, SIGNAL(refLineStateEvent(bool)),
            this, SLOT(showRefLine(bool)));
}

void MainWindow::initAnimateForm()
{
    animationForm = new AnimationForm();
    connect(animationForm, SIGNAL(playEvent(bool)), this, SLOT(onAnimatePlay(bool)));
    auto index = ui->propertyWidget->addTab(animationForm, tr("动画"));
    ui->propertyWidget->setTabVisible(index, false);
    // animationForm->setDisabled(true);
    AnimationFactory::instance()->bindScene(scene);
}

void MainWindow::setScene()
{
    scene = new BIGraphicsScene(this);

    ui->graphicsView->setScene(scene);

    QRect rect = ui->graphicsView->rect();
    scene->setSceneRect(0,0, rect.width(),rect.height());
    // ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    connect(ui->graphicsView, SIGNAL(mouseMove(QMouseEvent*)),
            this, SLOT(graphicsViewMouseMove(QMouseEvent*)));
    connect(ui->graphicsView, SIGNAL(zoomEvent(qint16)),
            this, SLOT(graphicsViewZoomed(qint16)));
    connect(graphicPluginWidget, SIGNAL(graphicItemChanged(IGraphicPlugin*)),
            ui->graphicsView, SLOT(graphicItemChangedHandler(IGraphicPlugin*)));
    // 监听图元选中状态，同步切换属性设置页面
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()), Qt::QueuedConnection);
    connect(this, SIGNAL(singleSelectEvent(QGraphicsItem*)),
            this, SLOT(oneGraphSelected(QGraphicsItem*)), Qt::QueuedConnection);
    connect(this, SIGNAL(noSelectEvent()), this, SLOT(noGraphSelected()), Qt::QueuedConnection);
    connect(this, SIGNAL(multiSelectEvent()), this, SLOT(multiGraphSelected()), Qt::QueuedConnection);

    ui->graphicsView->setMouseTracking(true);

}

void MainWindow::onSceneSelectionChanged()
{
    auto f = QtConcurrent::run([&]{
        // 选中的图元
        auto selectedItems = scene->selectedItems();
        if (!selectedItems.isEmpty()){
            if (selectedItems.count() > 1) {
                // 有多个选中的图元，属性窗口禁用
                selectedItems.removeIf([&](auto item){return scene->isHide(item);});
                if (selectedItems.count() == 1) {
                    emit(singleSelectEvent(selectedItems.first()));
                }else{
                    emit(multiSelectEvent());
                }
            } else {
                emit(singleSelectEvent(selectedItems.first()));
            }
        } else {
            // 没有选中的图元
            emit(noSelectEvent());
        }
    });
}

void MainWindow::oneGraphSelected(QGraphicsItem *item)
{
    if (scene->isHide(item)) {
        auto pathItem = dynamic_cast<IMovePath*>(item);
        if (pathItem == nullptr) {
            return;
        }
        // 切换到主图元属性
        item = pathItem->getMaster();
    }
    propertyWidget->setDisabled(false);
    if (ui->scrollArea->widget() != propertyWidget) {
        ui->scrollArea->takeWidget();
        ui->scrollArea->setWidget(propertyWidget);
    }
    auto result = propertyWidget->setGraphicItem(item);
    if (result) {
        ui->propertyWidget->setTabText(0, tr("样式"));
    }
    // 启动动画
    ui->propertyWidget->setTabVisible(ui->propertyWidget->indexOf(animationForm),
                                      true);
    animationForm->setGraphicItem(dynamic_cast<ICustomGraphic*>(item));
    // 启/禁用组合
    if (typeid(*item) == typeid(GraphicsItemGroup)) {
        ui->group->setDisabled(true);
        ui->ungroup->setEnabled(true);
    } else {
        ui->group->setDisabled(true);
        ui->ungroup->setDisabled(true);
    }
    enableAlignAction(false);
    enableDistributeAction(false);
    enableLayerAction(true);
}

void MainWindow::noGraphSelected()
{
    if (playFlag) {
        return;
    }
    if (ui->scrollArea->widget() != projectWidget) {
        ui->propertyWidget->setCurrentIndex(0);
        ui->propertyWidget->setTabText(0, tr("项目"));
        ui->scrollArea->takeWidget();
        ui->scrollArea->setWidget(projectWidget);
    }

    ui->group->setDisabled(true);
    ui->ungroup->setDisabled(true);
    enableAlignAction(false);
    enableDistributeAction(false);
    enableLayerAction(false);
    // 禁用动画
    ui->propertyWidget->setTabVisible(ui->propertyWidget->indexOf(animationForm),
                                      false);
}

void MainWindow::multiGraphSelected()
{
    // 有多个图元被选中
    ui->group->setEnabled(true);
    ui->ungroup->setDisabled(true);
    enableAlignAction(true);
    enableDistributeAction(true);
    enableLayerAction(true);
    // 禁用属性
    propertyWidget->setDisabled(true);
    // 禁用动画
    ui->propertyWidget->setTabVisible(ui->propertyWidget->indexOf(animationForm),
                                      false);
}

void MainWindow::graphicsViewMouseMove(QMouseEvent *event)
{
    // 监控 graphics View 鼠标移动事件
    QPointF pos = ui->graphicsView->mapToScene(event->pos());
    mouseInfo->setText(QString(" x = %1 , y = %2").arg(pos.x()).arg(pos.y()));
}

void MainWindow::graphicsViewZoomed(qint16 zoom)
{
    QString text = QString(" %1 % ").arg(zoom);
    scaleInfo->setText(tr(" 缩放：") + text);
    zoomBtn->setText(text);
}

void MainWindow::on_action_animate_triggered()
{
    auto items = scene->selectedItems();
    if (items.empty()) {
        return;
    }
    QString attr = "textColor";
    QTransform trans;
    angle += 30;
    angle = fmodf(angle, 360);
    trans.rotate(angle, Qt::YAxis);qDebug() << angle << items.first()->transform();
    items.first()->setTransform(trans, false);
    // qDebug() << "属性： " << item->property(attr.toLocal8Bit());
    //          << "state=" << item->property("state")
    //          << item->property("stateSet");
    // item->setProperty("state", 1);
    // qDebug() << "new state=" << item->property("state");
    // if (animation == nullptr) {
    //     animation = new QPropertyAnimation(item, attr.toLocal8Bit(), ui->graphicsView);
    // }

    // animation->setTargetObject(item);
    // animation->setPropertyName(attr.toLocal8Bit());
    // animation->setDuration(2000);
    // animation->setStartValue(QColor{Qt::white});//(QPointF{10,60});//(10);//
    // animation->setEndValue(QColor{Qt::red});//(QPointF{90,160});//(120);//
    // animation->setLoopCount(3);
    // animation->start();

    // delete animation;
    // CustomGraphicItemInterface *item = dynamic_cast<CustomGraphicItemInterface *>(items.at(0));
    // QString data = item->toXml();
    // qDebug() << data;
}

void MainWindow::menuPopup()
{
    auto menuPos = menuBtn->pos();
    auto toolHeight = menuBtn->height();
    auto toolWidth = menuBtn->width();
    menuPos.setY(toolHeight + menuPos.y());
    menuPos.setX(menuPos.x() + toolWidth - menu->width());

    menu->popup(ui->toolBar->mapToGlobal(menuPos));
}

void MainWindow::zoomMenuPopup()
{
    auto menuPos = zoomBtn->pos();
    auto toolHeight = zoomBtn->height();
    auto toolWidth = zoomBtn->width();
    menuPos.setY(toolHeight + menuPos.y());
    menuPos.setX(menuPos.x() + toolWidth - menu->width());

    zoomMenu->popup(ui->toolBar->mapToGlobal(menuPos));
}


void MainWindow::doExit()
{
    QApplication::exit(0);
}


void MainWindow::doSave()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), QDir::currentPath(), QString(tr("BI文件%1")).arg("(*.bi)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("提示"), tr("打开文件错误，请重新保存。"));
        return;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(XmlTemplate::root);

    xmlWriter.writeStartElement(XmlTemplate::project);
    {
        typedef XmlTemplate::projectTemplate project;
        xmlWriter.writeTextElement(project::projectName, projectProperty.getName().toUtf8());
        xmlWriter.writeTextElement(project::author, projectProperty.getAuthor().toUtf8());
        xmlWriter.writeTextElement(project::createTime, projectProperty.getCreateTime().toString());
        xmlWriter.writeTextElement(project::modifyTime, projectProperty.getModifyTime().toString());
    }
    xmlWriter.writeEndElement();


    xmlWriter.writeStartElement(XmlTemplate::board);
    {
        auto page = ui->graphicsView->getPageProperty();
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << page;
        xmlWriter.writeCDATA(data.toHex());
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::shapes);
    xmlWriter.writeCharacters("");
    xmlWriter.device()->write(ui->graphicsView->toXml().toUtf8());
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::animates);
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(XmlTemplate::dataSource);
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();

    QMessageBox::information(this, tr("提示"), tr("文件保存成功"));
}


void MainWindow::doOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开"), QDir::currentPath(), tr("BI文件(*.bi)"));
    if (fileName.isEmpty()) {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("提示"), QString(tr("打开文件错误。%1" )).arg(file.errorString()));
        return;
    }

    QXmlStreamReader reader(&file);
    while(!reader.atEnd()){
        auto type = reader.readNext();
        if (reader.hasError()) {
            QMessageBox::information(this, tr("提示"), QString(tr("文件读取错误。%1" )).arg(reader.errorString()));
            break;
        }
        if (type == QXmlStreamReader::StartDocument){

        } else if (type == QXmlStreamReader::StartElement){
            auto startName = reader.name();
            if (startName.compare(XmlTemplate::project) == 0){
                parseProjectXml(XmlHelper::rawText(&reader, false));
            } else if (startName.compare(XmlTemplate::board) == 0){
                parsePageXml(XmlHelper::rawText(&reader, false));
            } else if (startName.compare(XmlTemplate::shapes) == 0){
                ui->graphicsView->loadFromXml(XmlHelper::rawText(&reader, false));
            } else if (startName.compare(XmlTemplate::animates) == 0){
                AnimationFactory::instance()->parseXml(XmlHelper::rawText(&reader, false));
            } else if (startName.compare(XmlTemplate::dataSource) == 0){
                // qDebug() << reader.name() << XmlHelper::rawText(&reader, false);
            }
        }
    }
    file.close();
}

void MainWindow::doExport()
{
    ExportDialog dlg(this);
    dlg.setImageSize(ui->graphicsView->sceneRect().size().toSize(),
                     ui->graphicsView->selectSize());
    bool flag{false};
    if(dlg.exec()==QDialog::Accepted){
        if (dlg.fileType().compare("svg")==0){
            flag = ui->graphicsView->exportToSvg(dlg.selectedScope(),
                                                 dlg.fileName(), dlg.imageSize());
        }else{
            flag = ui->graphicsView->exportToImage(dlg.selectedScope(),
                                                   dlg.fileName(),
                                                   dlg.imageSize(),
                                                   dlg.color(),
                                                   dlg.quality());
        }
        if (flag) {
            QMessageBox::information(this, tr("提示"), QString(tr("导出成功，保存路径：%1")).arg(dlg.fileName()));
        }else{
            QMessageBox::warning(this, tr("提示"), tr("导出失败！"));
        }
    }
}

void MainWindow::doGroup()
{
    ui->graphicsView->createGroup();
}


void MainWindow::doUngroup()
{
    ui->graphicsView->destroyGroup();
}

void MainWindow::doFlip()
{
    auto action = sender();
    auto actionName = action->objectName();
    ui->graphicsView->flipGraphic(actionName);
}

void MainWindow::doZOrder()
{
    auto action = sender();
    auto actionName = action->objectName();
    ui->graphicsView->setGraphicZOrder(actionName);
}

void MainWindow::doAlign()
{
    ui->graphicsView->setGraphicAlign(sender()->objectName());
}

void MainWindow::doDistribute()
{
    ui->graphicsView->setGraphicDistribute(sender()->objectName());
}

void MainWindow::doSelect()
{
    auto action = sender()->objectName();
    if (action.compare("doSelectAll") == 0) {
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier);
        QCoreApplication::sendEvent(ui->graphicsView, &keyPress);
        QKeyEvent keyRelease(QEvent::KeyRelease, Qt::Key_A, Qt::ControlModifier);
        QCoreApplication::sendEvent(ui->graphicsView, &keyRelease);
    }else{
        QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_A, Qt::ControlModifier | Qt::ShiftModifier);
        QCoreApplication::sendEvent(ui->graphicsView, &keyPress);
        QKeyEvent keyRelease(QEvent::KeyRelease, Qt::Key_A, Qt::ControlModifier | Qt::ShiftModifier);
        QCoreApplication::sendEvent(ui->graphicsView, &keyRelease);
    }
}

void MainWindow::undo()
{
    ui->graphicsView->undo();
}

void MainWindow::redo()
{
    ui->graphicsView->redo();
}

void MainWindow::doZoom()
{
    auto action = sender()->objectName();
    qreal ratio = 1;
    if (action.compare("zoomin") == 0) {
        ratio =ui->graphicsView->zoomByStep(1);
    } else if(action.compare("zoomout") == 0) {
        ratio =ui->graphicsView->zoomByStep(-1);
    } else if(action.compare("zoom25") == 0) {
        ratio =ui->graphicsView->zoomByValue(0.25);
    } else if(action.compare("zoom50") == 0) {
        ratio =ui->graphicsView->zoomByValue(0.5);
    } else if(action.compare("zoom75") == 0) {
        ratio =ui->graphicsView->zoomByValue(0.75);
    } else if(action.compare("zoom100") == 0) {
        ratio =ui->graphicsView->zoomByValue(1);
    } else if(action.compare("zoom125") == 0) {
        ratio =ui->graphicsView->zoomByValue(1.25);
    } else if(action.compare("zoom150") == 0) {
        ratio =ui->graphicsView->zoomByValue(1.5);
    } else if(action.compare("zoom200") == 0) {
        ratio =ui->graphicsView->zoomByValue(2);
    } else if(action.compare("zoom300") == 0) {
        ratio =ui->graphicsView->zoomByValue(3);
    } else if(action.compare("zoom400") == 0) {
        ratio =ui->graphicsView->zoomByValue(4);
    } else if(action.compare("zoomFitWindow") == 0) {
        ratio =ui->graphicsView->zoomByType(BIGraphicsView::FITWINDOW);
    } else if(action.compare("zoomFitWidth") == 0) {
        ratio =ui->graphicsView->zoomByType(BIGraphicsView::FITWIDTH);
    } else if(action.compare("zoomDefine") == 0) {
        // ui->graphicsView->zoomView(-1);
    }
    zoomBtn->setText(QString::asprintf("%d%", qRound(ratio * 100)));
    scaleInfo->setText(tr(" 缩放：") + zoomBtn->text());
}

void MainWindow::showRuler(bool flag)
{
    ui->graphicsView->setShowScale(flag);
    if (sender() != projectWidget) {
        projectWidget->showRuler(flag);
    }else{
        ui->showViewRuler->setChecked(flag);
    }
}

void MainWindow::showGrid(bool flag)
{
    if (sender() != projectWidget) {
        projectWidget->showGrid(flag);
    }else{
        ui->showViewGrid->setChecked(flag);
    }
    ui->graphicsView->setShowGrid(flag);
}

void MainWindow::showRefLine(bool flag)
{
    if (sender() != projectWidget) {
        projectWidget->showRefLine(flag);
    }else{
        ui->showViewRefLine->setChecked(flag);
    }
    ui->graphicsView->setShowRefLine(flag);
}

void MainWindow::projectPropertyChanged(const ProjectProperty &project)
{
    projectProperty = project;
}

void MainWindow::pagePropertyChanged(const PageProperty &page)
{
    ui->graphicsView->setPageProperty(page);
    QSignalBlocker blocker(ui->showViewGrid);
    ui->showViewGrid->setCheckable(page.getShowLine());
}

void MainWindow::onAnimatePlay(bool flag)
{
    playFlag = flag;
}

void MainWindow::showAbout()
{
    QMessageBox msg{QMessageBox::Information, "关于",
                    "Compelling Data Designer V0.1 \r\n\r\n"
                    "项目地址：https://github.com/lsyeei/dashboard/ \r\n\r\n"
                    "作者：李世颖\r\n\r\n"
                    "Email：lsyeei@163.com\r\n\r\n"};
    msg.setWindowModality(Qt::ApplicationModal);
    msg.exec();
}

void MainWindow::saveToLib()
{
    auto items = scene->selectedItems();
    if (items.isEmpty()) {
        return;
    }
    if(graphicPluginWidget){
        graphicPluginWidget->saveToLib(items);
    }
}

void MainWindow::onViewMenuEvent(QContextMenuEvent *event)
{
    QPoint viewPt = ui->graphicsView->viewport()->mapFromGlobal(event->globalPos());
    auto item = scene->itemAt(ui->graphicsView->mapToScene(viewPt),
                              ui->graphicsView->transform());
    if (item) {
        item->setSelected(true);
        graphicMenu->popup(event->globalPos());
    }else{
        viewMenu->popup(event->globalPos());
    }
}
