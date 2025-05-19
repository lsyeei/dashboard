/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bigraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action;
    QAction *action_animate;
    QAction *doSave;
    QAction *undo;
    QAction *redo;
    QAction *group;
    QAction *ungroup;
    QAction *zoomin;
    QAction *zoomout;
    QAction *toFront;
    QAction *toBack;
    QAction *toTop;
    QAction *toBottom;
    QAction *alignLeft;
    QAction *alignRight;
    QAction *alignTop;
    QAction *alignBottom;
    QAction *alignHorizon;
    QAction *alignVertical;
    QAction *distributeHorizon;
    QAction *distributeVertical;
    QAction *doExit;
    QAction *doCreate;
    QAction *doOpen;
    QAction *doExport;
    QAction *doCut;
    QAction *doCopy;
    QAction *doPast;
    QAction *doSelectAll;
    QAction *doUnselectAll;
    QAction *showViewGrid;
    QAction *showViewRefLine;
    QAction *showViewRuler;
    QAction *doPreview;
    QAction *doAbout;
    QAction *zoom25;
    QAction *zoom50;
    QAction *zoom75;
    QAction *zoom100;
    QAction *zoom125;
    QAction *zoom150;
    QAction *zoom200;
    QAction *zoom300;
    QAction *zoom400;
    QAction *zoomFitWindow;
    QAction *zoomFitWidth;
    QAction *zoomDefine;
    QAction *flipHorizontal;
    QAction *flipVertical;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *graphicItems;
    QVBoxLayout *verticalLayout_4;
    BIGraphicsView *graphicsView;
    QTabWidget *propertyWidget;
    QWidget *property;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *graphicProperty;
    QVBoxLayout *verticalLayout_3;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *layerMenu;
    QMenu *helpMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1038, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setBaseSize(QSize(92, 44));
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        MainWindow->setFont(font);
        action = new QAction(MainWindow);
        action->setObjectName("action");
        action->setVisible(false);
        action->setMenuRole(QAction::MenuRole::NoRole);
        action_animate = new QAction(MainWindow);
        action_animate->setObjectName("action_animate");
        action_animate->setEnabled(false);
        action_animate->setVisible(false);
        action_animate->setMenuRole(QAction::MenuRole::NoRole);
        doSave = new QAction(MainWindow);
        doSave->setObjectName("doSave");
        QIcon icon;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::DocumentSave)) {
            icon = QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave);
        } else {
            icon.addFile(QString::fromUtf8(":/icons/icons/save.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        doSave->setIcon(icon);
        doSave->setMenuRole(QAction::MenuRole::NoRole);
        undo = new QAction(MainWindow);
        undo->setObjectName("undo");
        QIcon icon1;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditUndo)) {
            icon1 = QIcon::fromTheme(QIcon::ThemeIcon::EditUndo);
        } else {
            icon1.addFile(QString::fromUtf8(":/icons/icons/Undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        undo->setIcon(icon1);
        undo->setMenuRole(QAction::MenuRole::NoRole);
        redo = new QAction(MainWindow);
        redo->setObjectName("redo");
        QIcon icon2;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::EditRedo)) {
            icon2 = QIcon::fromTheme(QIcon::ThemeIcon::EditRedo);
        } else {
            icon2.addFile(QString::fromUtf8(":/icons/icons/Redo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        redo->setIcon(icon2);
        redo->setMenuRole(QAction::MenuRole::NoRole);
        group = new QAction(MainWindow);
        group->setObjectName("group");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/group.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        group->setIcon(icon3);
        group->setMenuRole(QAction::MenuRole::NoRole);
        ungroup = new QAction(MainWindow);
        ungroup->setObjectName("ungroup");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/ungroup.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ungroup->setIcon(icon4);
        ungroup->setMenuRole(QAction::MenuRole::NoRole);
        zoomin = new QAction(MainWindow);
        zoomin->setObjectName("zoomin");
        QIcon icon5;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::ZoomIn)) {
            icon5 = QIcon::fromTheme(QIcon::ThemeIcon::ZoomIn);
        } else {
            icon5.addFile(QString::fromUtf8(":/icons/icons/zoom in.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        zoomin->setIcon(icon5);
        zoomin->setMenuRole(QAction::MenuRole::NoRole);
        zoomout = new QAction(MainWindow);
        zoomout->setObjectName("zoomout");
        QIcon icon6;
        if (QIcon::hasThemeIcon(QIcon::ThemeIcon::ZoomOut)) {
            icon6 = QIcon::fromTheme(QIcon::ThemeIcon::ZoomOut);
        } else {
            icon6.addFile(QString::fromUtf8(":/icons/icons/zoom out.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        }
        zoomout->setIcon(icon6);
        zoomout->setMenuRole(QAction::MenuRole::NoRole);
        toFront = new QAction(MainWindow);
        toFront->setObjectName("toFront");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icons/bring-to-downer.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toFront->setIcon(icon7);
        toFront->setMenuRole(QAction::MenuRole::NoRole);
        toBack = new QAction(MainWindow);
        toBack->setObjectName("toBack");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icons/bring-to-upper.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toBack->setIcon(icon8);
        toBack->setMenuRole(QAction::MenuRole::NoRole);
        toTop = new QAction(MainWindow);
        toTop->setObjectName("toTop");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icons/bring-to-top.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toTop->setIcon(icon9);
        toTop->setMenuRole(QAction::MenuRole::NoRole);
        toBottom = new QAction(MainWindow);
        toBottom->setObjectName("toBottom");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icons/bring-to-bottom.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        toBottom->setIcon(icon10);
        toBottom->setMenuRole(QAction::MenuRole::NoRole);
        alignLeft = new QAction(MainWindow);
        alignLeft->setObjectName("alignLeft");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icons/Aligne-left.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignLeft->setIcon(icon11);
        alignLeft->setMenuRole(QAction::MenuRole::NoRole);
        alignRight = new QAction(MainWindow);
        alignRight->setObjectName("alignRight");
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icons/Aligne-right.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignRight->setIcon(icon12);
        alignRight->setMenuRole(QAction::MenuRole::NoRole);
        alignTop = new QAction(MainWindow);
        alignTop->setObjectName("alignTop");
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/icons/Aligne-up.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignTop->setIcon(icon13);
        alignTop->setMenuRole(QAction::MenuRole::NoRole);
        alignBottom = new QAction(MainWindow);
        alignBottom->setObjectName("alignBottom");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/icons/Aligne-down.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignBottom->setIcon(icon14);
        alignBottom->setMenuRole(QAction::MenuRole::NoRole);
        alignHorizon = new QAction(MainWindow);
        alignHorizon->setObjectName("alignHorizon");
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/icons/Aligne-vertical-midl.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignHorizon->setIcon(icon15);
        alignHorizon->setMenuRole(QAction::MenuRole::NoRole);
        alignVertical = new QAction(MainWindow);
        alignVertical->setObjectName("alignVertical");
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/icons/Aligne-midle.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignVertical->setIcon(icon16);
        alignVertical->setMenuRole(QAction::MenuRole::NoRole);
        distributeHorizon = new QAction(MainWindow);
        distributeHorizon->setObjectName("distributeHorizon");
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icons/icons/Distribute-vertical .svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        distributeHorizon->setIcon(icon17);
        distributeHorizon->setMenuRole(QAction::MenuRole::NoRole);
        distributeVertical = new QAction(MainWindow);
        distributeVertical->setObjectName("distributeVertical");
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icons/icons/Distribute-midle.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        distributeVertical->setIcon(icon18);
        distributeVertical->setMenuRole(QAction::MenuRole::NoRole);
        doExit = new QAction(MainWindow);
        doExit->setObjectName("doExit");
        QIcon icon19(QIcon::fromTheme(QString::fromUtf8("application-exit")));
        doExit->setIcon(icon19);
        doExit->setMenuRole(QAction::MenuRole::QuitRole);
        doCreate = new QAction(MainWindow);
        doCreate->setObjectName("doCreate");
        QIcon icon20(QIcon::fromTheme(QString::fromUtf8("document-new")));
        doCreate->setIcon(icon20);
        doOpen = new QAction(MainWindow);
        doOpen->setObjectName("doOpen");
        QIcon icon21(QIcon::fromTheme(QString::fromUtf8("document-open")));
        doOpen->setIcon(icon21);
        doExport = new QAction(MainWindow);
        doExport->setObjectName("doExport");
        doCut = new QAction(MainWindow);
        doCut->setObjectName("doCut");
        doCopy = new QAction(MainWindow);
        doCopy->setObjectName("doCopy");
        doPast = new QAction(MainWindow);
        doPast->setObjectName("doPast");
        doSelectAll = new QAction(MainWindow);
        doSelectAll->setObjectName("doSelectAll");
        doUnselectAll = new QAction(MainWindow);
        doUnselectAll->setObjectName("doUnselectAll");
        showViewGrid = new QAction(MainWindow);
        showViewGrid->setObjectName("showViewGrid");
        showViewGrid->setCheckable(true);
        showViewRefLine = new QAction(MainWindow);
        showViewRefLine->setObjectName("showViewRefLine");
        showViewRefLine->setCheckable(true);
        showViewRuler = new QAction(MainWindow);
        showViewRuler->setObjectName("showViewRuler");
        showViewRuler->setCheckable(true);
        doPreview = new QAction(MainWindow);
        doPreview->setObjectName("doPreview");
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/icons/icons/preview.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        doPreview->setIcon(icon22);
        doPreview->setMenuRole(QAction::MenuRole::NoRole);
        doAbout = new QAction(MainWindow);
        doAbout->setObjectName("doAbout");
        QIcon icon23(QIcon::fromTheme(QString::fromUtf8("help-about")));
        doAbout->setIcon(icon23);
        zoom25 = new QAction(MainWindow);
        zoom25->setObjectName("zoom25");
        zoom25->setMenuRole(QAction::MenuRole::NoRole);
        zoom50 = new QAction(MainWindow);
        zoom50->setObjectName("zoom50");
        zoom50->setMenuRole(QAction::MenuRole::NoRole);
        zoom75 = new QAction(MainWindow);
        zoom75->setObjectName("zoom75");
        zoom75->setMenuRole(QAction::MenuRole::NoRole);
        zoom100 = new QAction(MainWindow);
        zoom100->setObjectName("zoom100");
        zoom100->setMenuRole(QAction::MenuRole::NoRole);
        zoom125 = new QAction(MainWindow);
        zoom125->setObjectName("zoom125");
        zoom125->setMenuRole(QAction::MenuRole::NoRole);
        zoom150 = new QAction(MainWindow);
        zoom150->setObjectName("zoom150");
        zoom150->setMenuRole(QAction::MenuRole::NoRole);
        zoom200 = new QAction(MainWindow);
        zoom200->setObjectName("zoom200");
        zoom200->setMenuRole(QAction::MenuRole::NoRole);
        zoom300 = new QAction(MainWindow);
        zoom300->setObjectName("zoom300");
        zoom300->setMenuRole(QAction::MenuRole::NoRole);
        zoom400 = new QAction(MainWindow);
        zoom400->setObjectName("zoom400");
        zoom400->setMenuRole(QAction::MenuRole::NoRole);
        zoomFitWindow = new QAction(MainWindow);
        zoomFitWindow->setObjectName("zoomFitWindow");
        zoomFitWindow->setMenuRole(QAction::MenuRole::NoRole);
        zoomFitWidth = new QAction(MainWindow);
        zoomFitWidth->setObjectName("zoomFitWidth");
        zoomFitWidth->setMenuRole(QAction::MenuRole::NoRole);
        zoomDefine = new QAction(MainWindow);
        zoomDefine->setObjectName("zoomDefine");
        zoomDefine->setMenuRole(QAction::MenuRole::NoRole);
        flipHorizontal = new QAction(MainWindow);
        flipHorizontal->setObjectName("flipHorizontal");
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/icons/icons/flip_horizontal.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        flipHorizontal->setIcon(icon24);
        flipHorizontal->setMenuRole(QAction::MenuRole::NoRole);
        flipVertical = new QAction(MainWindow);
        flipVertical->setObjectName("flipVertical");
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/icons/icons/flip_vertical.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        flipVertical->setIcon(icon25);
        flipVertical->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName("splitter_2");
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Orientation::Horizontal);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName("splitter");
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Orientation::Horizontal);
        graphicItems = new QWidget(splitter);
        graphicItems->setObjectName("graphicItems");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicItems->sizePolicy().hasHeightForWidth());
        graphicItems->setSizePolicy(sizePolicy2);
        graphicItems->setMinimumSize(QSize(150, 0));
        graphicItems->setAutoFillBackground(false);
        graphicItems->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(graphicItems);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter->addWidget(graphicItems);
        graphicsView = new BIGraphicsView(splitter);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);
        graphicsView->setMinimumSize(QSize(500, 300));
        graphicsView->setAutoFillBackground(false);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphicsView->setForegroundBrush(brush1);
        graphicsView->setRenderHints(QPainter::RenderHint::Antialiasing|QPainter::RenderHint::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::DragMode::NoDrag);
        graphicsView->setCacheMode(QGraphicsView::CacheModeFlag::CacheBackground);
        graphicsView->setRubberBandSelectionMode(Qt::ItemSelectionMode::ContainsItemBoundingRect);
        splitter->addWidget(graphicsView);
        splitter_2->addWidget(splitter);
        propertyWidget = new QTabWidget(splitter_2);
        propertyWidget->setObjectName("propertyWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(propertyWidget->sizePolicy().hasHeightForWidth());
        propertyWidget->setSizePolicy(sizePolicy4);
        propertyWidget->setMinimumSize(QSize(220, 0));
        property = new QWidget();
        property->setObjectName("property");
        sizePolicy3.setHeightForWidth(property->sizePolicy().hasHeightForWidth());
        property->setSizePolicy(sizePolicy3);
        verticalLayout_2 = new QVBoxLayout(property);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        scrollArea = new QScrollArea(property);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy5);
        scrollArea->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setFrameShadow(QFrame::Shadow::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        graphicProperty = new QWidget();
        graphicProperty->setObjectName("graphicProperty");
        graphicProperty->setGeometry(QRect(0, 0, 234, 475));
        sizePolicy2.setHeightForWidth(graphicProperty->sizePolicy().hasHeightForWidth());
        graphicProperty->setSizePolicy(sizePolicy2);
        graphicProperty->setMinimumSize(QSize(0, 0));
        graphicProperty->setAutoFillBackground(true);
        verticalLayout_3 = new QVBoxLayout(graphicProperty);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        scrollArea->setWidget(graphicProperty);

        verticalLayout_2->addWidget(scrollArea);

        propertyWidget->addTab(property, QString());
        splitter_2->addWidget(propertyWidget);

        verticalLayout->addWidget(splitter_2);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setAllowedAreas(Qt::ToolBarArea::TopToolBarArea);
        toolBar->setOrientation(Qt::Orientation::Horizontal);
        toolBar->setIconSize(QSize(18, 18));
        toolBar->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setEnabled(true);
        menuBar->setGeometry(QRect(0, 0, 1038, 21));
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy6);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(false);
        fileMenu = new QMenu(menuBar);
        fileMenu->setObjectName("fileMenu");
        editMenu = new QMenu(menuBar);
        editMenu->setObjectName("editMenu");
        viewMenu = new QMenu(menuBar);
        viewMenu->setObjectName("viewMenu");
        layerMenu = new QMenu(menuBar);
        layerMenu->setObjectName("layerMenu");
        helpMenu = new QMenu(menuBar);
        helpMenu->setObjectName("helpMenu");
        MainWindow->setMenuBar(menuBar);

        toolBar->addAction(doSave);
        toolBar->addSeparator();
        toolBar->addAction(undo);
        toolBar->addAction(redo);
        toolBar->addSeparator();
        toolBar->addAction(group);
        toolBar->addAction(ungroup);
        toolBar->addSeparator();
        toolBar->addAction(flipHorizontal);
        toolBar->addAction(flipVertical);
        toolBar->addSeparator();
        toolBar->addAction(toTop);
        toolBar->addAction(toBottom);
        toolBar->addAction(toBack);
        toolBar->addAction(toFront);
        toolBar->addSeparator();
        toolBar->addAction(alignLeft);
        toolBar->addAction(alignRight);
        toolBar->addAction(alignTop);
        toolBar->addAction(alignBottom);
        toolBar->addAction(alignHorizon);
        toolBar->addAction(alignVertical);
        toolBar->addSeparator();
        toolBar->addAction(distributeHorizon);
        toolBar->addAction(distributeVertical);
        toolBar->addSeparator();
        toolBar->addAction(zoomin);
        toolBar->addAction(zoomout);
        toolBar->addSeparator();
        toolBar->addAction(action);
        toolBar->addAction(action_animate);
        toolBar->addSeparator();
        menuBar->addAction(fileMenu->menuAction());
        menuBar->addAction(editMenu->menuAction());
        menuBar->addAction(viewMenu->menuAction());
        menuBar->addAction(layerMenu->menuAction());
        menuBar->addAction(helpMenu->menuAction());
        fileMenu->addAction(doCreate);
        fileMenu->addAction(doOpen);
        fileMenu->addSeparator();
        fileMenu->addAction(doSave);
        fileMenu->addAction(doExport);
        fileMenu->addSeparator();
        fileMenu->addAction(doExit);
        editMenu->addAction(undo);
        editMenu->addAction(redo);
        editMenu->addSeparator();
        editMenu->addAction(doCut);
        editMenu->addAction(doCopy);
        editMenu->addAction(doPast);
        editMenu->addSeparator();
        editMenu->addAction(doSelectAll);
        editMenu->addAction(doUnselectAll);
        viewMenu->addAction(showViewGrid);
        viewMenu->addAction(showViewRefLine);
        viewMenu->addAction(showViewRuler);
        viewMenu->addSeparator();
        viewMenu->addSeparator();
        viewMenu->addAction(zoomin);
        viewMenu->addAction(zoomout);
        viewMenu->addSeparator();
        viewMenu->addAction(doPreview);
        layerMenu->addAction(toTop);
        layerMenu->addAction(toBottom);
        layerMenu->addAction(toFront);
        layerMenu->addAction(toBack);
        layerMenu->addSeparator();
        layerMenu->addAction(alignLeft);
        layerMenu->addAction(alignRight);
        layerMenu->addAction(alignTop);
        layerMenu->addAction(alignBottom);
        layerMenu->addAction(alignHorizon);
        layerMenu->addAction(alignVertical);
        layerMenu->addSeparator();
        layerMenu->addAction(distributeHorizon);
        layerMenu->addAction(distributeVertical);
        layerMenu->addSeparator();
        layerMenu->addAction(group);
        layerMenu->addAction(ungroup);
        helpMenu->addAction(doAbout);

        retranslateUi(MainWindow);

        propertyWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Compelling Data Designer", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\347\273\230\345\233\276", nullptr));
#if QT_CONFIG(tooltip)
        action->setToolTip(QCoreApplication::translate("MainWindow", "\347\273\230\345\210\266\345\233\276\345\203\217", nullptr));
#endif // QT_CONFIG(tooltip)
        action_animate->setText(QCoreApplication::translate("MainWindow", "\345\212\250\347\224\273", nullptr));
        doSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#if QT_CONFIG(tooltip)
        doSave->setToolTip(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        undo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#if QT_CONFIG(tooltip)
        undo->setToolTip(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        undo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        redo->setText(QCoreApplication::translate("MainWindow", "\351\207\215\345\201\232", nullptr));
#if QT_CONFIG(tooltip)
        redo->setToolTip(QCoreApplication::translate("MainWindow", "\351\207\215\345\201\232", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        redo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y", nullptr));
#endif // QT_CONFIG(shortcut)
        group->setText(QCoreApplication::translate("MainWindow", "\347\273\204\345\220\210", nullptr));
#if QT_CONFIG(tooltip)
        group->setToolTip(QCoreApplication::translate("MainWindow", "\347\273\204\345\220\210", nullptr));
#endif // QT_CONFIG(tooltip)
        ungroup->setText(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\347\273\204\345\220\210", nullptr));
#if QT_CONFIG(tooltip)
        ungroup->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\226\346\266\210\347\273\204\345\220\210", nullptr));
#endif // QT_CONFIG(tooltip)
        zoomin->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
#if QT_CONFIG(tooltip)
        zoomin->setToolTip(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        zoomin->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl++", nullptr));
#endif // QT_CONFIG(shortcut)
        zoomout->setText(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
#if QT_CONFIG(tooltip)
        zoomout->setToolTip(QCoreApplication::translate("MainWindow", "\347\274\251\345\260\217", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        zoomout->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
        toFront->setText(QCoreApplication::translate("MainWindow", "\344\270\212\347\247\273", nullptr));
#if QT_CONFIG(tooltip)
        toFront->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\212\347\247\273\344\270\200\345\261\202", nullptr));
#endif // QT_CONFIG(tooltip)
        toBack->setText(QCoreApplication::translate("MainWindow", "\344\270\213\347\247\273", nullptr));
#if QT_CONFIG(tooltip)
        toBack->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\213\347\247\273\344\270\200\345\261\202", nullptr));
#endif // QT_CONFIG(tooltip)
        toTop->setText(QCoreApplication::translate("MainWindow", "\347\275\256\351\241\266", nullptr));
#if QT_CONFIG(tooltip)
        toTop->setToolTip(QCoreApplication::translate("MainWindow", "\347\275\256\351\241\266", nullptr));
#endif // QT_CONFIG(tooltip)
        toBottom->setText(QCoreApplication::translate("MainWindow", "\347\275\256\345\272\225", nullptr));
#if QT_CONFIG(tooltip)
        toBottom->setToolTip(QCoreApplication::translate("MainWindow", "\347\275\256\345\272\225", nullptr));
#endif // QT_CONFIG(tooltip)
        alignLeft->setText(QCoreApplication::translate("MainWindow", "\345\267\246\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignLeft->setToolTip(QCoreApplication::translate("MainWindow", "\345\267\246\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        alignRight->setText(QCoreApplication::translate("MainWindow", "\345\217\263\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignRight->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\263\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        alignTop->setText(QCoreApplication::translate("MainWindow", "\344\270\212\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignTop->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\212\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        alignBottom->setText(QCoreApplication::translate("MainWindow", "\344\270\213\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignBottom->setToolTip(QCoreApplication::translate("MainWindow", "\344\270\213\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        alignHorizon->setText(QCoreApplication::translate("MainWindow", "\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignHorizon->setToolTip(QCoreApplication::translate("MainWindow", "\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        alignVertical->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignVertical->setToolTip(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
        distributeHorizon->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\255\211\350\267\235", nullptr));
#if QT_CONFIG(tooltip)
        distributeHorizon->setToolTip(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\255\211\350\267\235", nullptr));
#endif // QT_CONFIG(tooltip)
        distributeVertical->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\255\211\350\267\235", nullptr));
#if QT_CONFIG(tooltip)
        distributeVertical->setToolTip(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\255\211\350\267\235", nullptr));
#endif // QT_CONFIG(tooltip)
        doExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(tooltip)
        doExit->setToolTip(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#endif // QT_CONFIG(tooltip)
        doCreate->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
#if QT_CONFIG(shortcut)
        doCreate->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        doOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(tooltip)
        doOpen->setToolTip(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        doExport->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
#if QT_CONFIG(tooltip)
        doExport->setToolTip(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doExport->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        doCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#if QT_CONFIG(tooltip)
        doCut->setToolTip(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        doCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#if QT_CONFIG(tooltip)
        doCopy->setToolTip(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        doPast->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#if QT_CONFIG(tooltip)
        doPast->setToolTip(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doPast->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        doSelectAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        doSelectAll->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doSelectAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        doUnselectAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\344\270\215\351\200\211", nullptr));
#if QT_CONFIG(tooltip)
        doUnselectAll->setToolTip(QCoreApplication::translate("MainWindow", "\345\205\250\344\270\215\351\200\211", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        doUnselectAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
        showViewGrid->setText(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274", nullptr));
#if QT_CONFIG(tooltip)
        showViewGrid->setToolTip(QCoreApplication::translate("MainWindow", "\347\275\221\346\240\274", nullptr));
#endif // QT_CONFIG(tooltip)
        showViewRefLine->setText(QCoreApplication::translate("MainWindow", "\345\217\202\350\200\203\347\272\277", nullptr));
#if QT_CONFIG(tooltip)
        showViewRefLine->setToolTip(QCoreApplication::translate("MainWindow", "\345\217\202\350\200\203\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
        showViewRuler->setText(QCoreApplication::translate("MainWindow", "\346\240\207\345\260\272", nullptr));
#if QT_CONFIG(tooltip)
        showViewRuler->setToolTip(QCoreApplication::translate("MainWindow", "\346\240\207\345\260\272", nullptr));
#endif // QT_CONFIG(tooltip)
        doPreview->setText(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
#if QT_CONFIG(tooltip)
        doPreview->setToolTip(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
#endif // QT_CONFIG(tooltip)
        doAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216", nullptr));
#if QT_CONFIG(tooltip)
        doAbout->setToolTip(QCoreApplication::translate("MainWindow", "\346\240\207\345\260\272", nullptr));
#endif // QT_CONFIG(tooltip)
        zoom25->setText(QCoreApplication::translate("MainWindow", "25%", nullptr));
        zoom50->setText(QCoreApplication::translate("MainWindow", "50%", nullptr));
        zoom75->setText(QCoreApplication::translate("MainWindow", "75%", nullptr));
        zoom100->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        zoom125->setText(QCoreApplication::translate("MainWindow", "125%", nullptr));
        zoom150->setText(QCoreApplication::translate("MainWindow", "150%", nullptr));
        zoom200->setText(QCoreApplication::translate("MainWindow", "200%", nullptr));
        zoom300->setText(QCoreApplication::translate("MainWindow", "300%", nullptr));
        zoom400->setText(QCoreApplication::translate("MainWindow", "400%", nullptr));
        zoomFitWindow->setText(QCoreApplication::translate("MainWindow", "\351\200\202\345\272\224\347\252\227\345\217\243", nullptr));
#if QT_CONFIG(shortcut)
        zoomFitWindow->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+H", nullptr));
#endif // QT_CONFIG(shortcut)
        zoomFitWidth->setText(QCoreApplication::translate("MainWindow", "\351\200\202\345\272\224\351\241\265\351\235\242\345\256\275\345\272\246", nullptr));
        zoomDefine->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\256\232\344\271\211", nullptr));
#if QT_CONFIG(shortcut)
        zoomDefine->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+0", nullptr));
#endif // QT_CONFIG(shortcut)
        flipHorizontal->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\277\273\350\275\254", nullptr));
#if QT_CONFIG(tooltip)
        flipHorizontal->setToolTip(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\277\273\350\275\254", nullptr));
#endif // QT_CONFIG(tooltip)
        flipVertical->setText(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\277\273\350\275\254", nullptr));
#if QT_CONFIG(tooltip)
        flipVertical->setToolTip(QCoreApplication::translate("MainWindow", "\345\236\202\347\233\264\347\277\273\350\275\254", nullptr));
#endif // QT_CONFIG(tooltip)
        propertyWidget->setTabText(propertyWidget->indexOf(property), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        editMenu->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        viewMenu->setTitle(QCoreApplication::translate("MainWindow", "\350\247\206\345\233\276", nullptr));
        layerMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\233\276\345\261\202", nullptr));
        helpMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
