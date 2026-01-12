/********************************************************************************
** Form generated from reading UI file 'datapropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAPROPERTYFORM_H
#define UI_DATAPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataPropertyForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *addBtn;
    QPushButton *delBtn;
    QTableWidget *dataTable;

    void setupUi(QWidget *DataPropertyForm)
    {
        if (DataPropertyForm->objectName().isEmpty())
            DataPropertyForm->setObjectName("DataPropertyForm");
        DataPropertyForm->resize(219, 238);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataPropertyForm->sizePolicy().hasHeightForWidth());
        DataPropertyForm->setSizePolicy(sizePolicy);
        DataPropertyForm->setAutoFillBackground(false);
        verticalLayout_2 = new QVBoxLayout(DataPropertyForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(DataPropertyForm);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setFrameShadow(QFrame::Shadow::Plain);
        scrollArea->setLineWidth(0);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 219, 238));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        addBtn = new QPushButton(scrollAreaWidgetContents);
        addBtn->setObjectName("addBtn");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        addBtn->setIcon(icon);

        horizontalLayout_4->addWidget(addBtn);

        delBtn = new QPushButton(scrollAreaWidgetContents);
        delBtn->setObjectName("delBtn");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        delBtn->setIcon(icon1);

        horizontalLayout_4->addWidget(delBtn);


        verticalLayout_3->addLayout(horizontalLayout_4);

        dataTable = new QTableWidget(scrollAreaWidgetContents);
        dataTable->setObjectName("dataTable");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dataTable->sizePolicy().hasHeightForWidth());
        dataTable->setSizePolicy(sizePolicy2);
        dataTable->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);
        dataTable->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        dataTable->setProperty("showDropIndicator", QVariant(false));
        dataTable->setDragDropOverwriteMode(false);
        dataTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        dataTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_3->addWidget(dataTable);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(DataPropertyForm);

        QMetaObject::connectSlotsByName(DataPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *DataPropertyForm)
    {
        DataPropertyForm->setWindowTitle(QCoreApplication::translate("DataPropertyForm", "\346\225\260\346\215\256", nullptr));
        addBtn->setText(QCoreApplication::translate("DataPropertyForm", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
        delBtn->setText(QCoreApplication::translate("DataPropertyForm", "\345\210\240\351\231\244\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataPropertyForm: public Ui_DataPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAPROPERTYFORM_H
