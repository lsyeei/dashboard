/********************************************************************************
** Form generated from reading UI file 'graphiclistform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICLISTFORM_H
#define UI_GRAPHICLISTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphicListForm
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *queryText;
    QToolButton *searchBtn;
    QTreeWidget *graphicTree;

    void setupUi(QDockWidget *GraphicListForm)
    {
        if (GraphicListForm->objectName().isEmpty())
            GraphicListForm->setObjectName("GraphicListForm");
        GraphicListForm->resize(154, 484);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphicListForm->sizePolicy().hasHeightForWidth());
        GraphicListForm->setSizePolicy(sizePolicy);
        GraphicListForm->setFloating(true);
        GraphicListForm->setAllowedAreas(Qt::DockWidgetArea::LeftDockWidgetArea|Qt::DockWidgetArea::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, -1, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        queryText = new QLineEdit(dockWidgetContents);
        queryText->setObjectName("queryText");

        horizontalLayout->addWidget(queryText);

        searchBtn = new QToolButton(dockWidgetContents);
        searchBtn->setObjectName("searchBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        searchBtn->setIcon(icon);
        searchBtn->setIconSize(QSize(16, 16));
        searchBtn->setAutoRaise(false);

        horizontalLayout->addWidget(searchBtn);


        verticalLayout->addLayout(horizontalLayout);

        graphicTree = new QTreeWidget(dockWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        graphicTree->setHeaderItem(__qtreewidgetitem);
        graphicTree->setObjectName("graphicTree");
        graphicTree->setFrameShape(QFrame::Shape::Box);
        graphicTree->setFrameShadow(QFrame::Shadow::Plain);
        graphicTree->setLineWidth(0);
        graphicTree->setRootIsDecorated(true);
        graphicTree->setColumnCount(1);
        graphicTree->header()->setVisible(false);

        verticalLayout->addWidget(graphicTree);

        GraphicListForm->setWidget(dockWidgetContents);

        retranslateUi(GraphicListForm);

        QMetaObject::connectSlotsByName(GraphicListForm);
    } // setupUi

    void retranslateUi(QDockWidget *GraphicListForm)
    {
        GraphicListForm->setWindowTitle(QCoreApplication::translate("GraphicListForm", "\347\273\223\346\236\204\350\247\206\345\233\276", nullptr));
        searchBtn->setText(QCoreApplication::translate("GraphicListForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GraphicListForm: public Ui_GraphicListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICLISTFORM_H
