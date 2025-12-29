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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *queryText;
    QToolButton *searchBtn;
    QTreeWidget *graphicTree;

    void setupUi(QWidget *GraphicListForm)
    {
        if (GraphicListForm->objectName().isEmpty())
            GraphicListForm->setObjectName("GraphicListForm");
        GraphicListForm->resize(128, 309);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GraphicListForm->sizePolicy().hasHeightForWidth());
        GraphicListForm->setSizePolicy(sizePolicy);
        GraphicListForm->setProperty("floating", QVariant(false));
        verticalLayout = new QVBoxLayout(GraphicListForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        queryText = new QLineEdit(GraphicListForm);
        queryText->setObjectName("queryText");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(queryText->sizePolicy().hasHeightForWidth());
        queryText->setSizePolicy(sizePolicy1);
        queryText->setMaxLength(32767);

        horizontalLayout->addWidget(queryText);

        searchBtn = new QToolButton(GraphicListForm);
        searchBtn->setObjectName("searchBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        searchBtn->setIcon(icon);
        searchBtn->setIconSize(QSize(16, 16));
        searchBtn->setAutoRaise(false);

        horizontalLayout->addWidget(searchBtn);


        verticalLayout->addLayout(horizontalLayout);

        graphicTree = new QTreeWidget(GraphicListForm);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        graphicTree->setHeaderItem(__qtreewidgetitem);
        graphicTree->setObjectName("graphicTree");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicTree->sizePolicy().hasHeightForWidth());
        graphicTree->setSizePolicy(sizePolicy2);
        graphicTree->setFrameShape(QFrame::Shape::Box);
        graphicTree->setFrameShadow(QFrame::Shadow::Plain);
        graphicTree->setLineWidth(0);
        graphicTree->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        graphicTree->setRootIsDecorated(true);
        graphicTree->setColumnCount(1);
        graphicTree->header()->setVisible(false);

        verticalLayout->addWidget(graphicTree);


        retranslateUi(GraphicListForm);

        QMetaObject::connectSlotsByName(GraphicListForm);
    } // setupUi

    void retranslateUi(QWidget *GraphicListForm)
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
