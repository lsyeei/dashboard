/********************************************************************************
** Form generated from reading UI file 'dataqueryform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAQUERYFORM_H
#define UI_DATAQUERYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataQueryForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QSplitter *tableSplitter;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *tableEdit;
    QListView *tableList;
    QSplitter *fieldSplitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *fieldEdit;
    QListView *fieldList;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QPlainTextEdit *sqlEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *testButton;
    QPlainTextEdit *testResultEdit;

    void setupUi(QWidget *DataQueryForm)
    {
        if (DataQueryForm->objectName().isEmpty())
            DataQueryForm->setObjectName("DataQueryForm");
        DataQueryForm->resize(226, 222);
        verticalLayout_2 = new QVBoxLayout(DataQueryForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableSplitter = new QSplitter(DataQueryForm);
        tableSplitter->setObjectName("tableSplitter");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableSplitter->sizePolicy().hasHeightForWidth());
        tableSplitter->setSizePolicy(sizePolicy);
        tableSplitter->setOrientation(Qt::Orientation::Horizontal);
        verticalLayoutWidget = new QWidget(tableSplitter);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        tableEdit = new QLineEdit(verticalLayoutWidget);
        tableEdit->setObjectName("tableEdit");
        tableEdit->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(tableEdit);


        verticalLayout_4->addLayout(horizontalLayout_3);

        tableList = new QListView(verticalLayoutWidget);
        tableList->setObjectName("tableList");
        sizePolicy.setHeightForWidth(tableList->sizePolicy().hasHeightForWidth());
        tableList->setSizePolicy(sizePolicy);
        tableList->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustIgnored);

        verticalLayout_4->addWidget(tableList);

        tableSplitter->addWidget(verticalLayoutWidget);
        fieldSplitter = new QSplitter(tableSplitter);
        fieldSplitter->setObjectName("fieldSplitter");
        sizePolicy.setHeightForWidth(fieldSplitter->sizePolicy().hasHeightForWidth());
        fieldSplitter->setSizePolicy(sizePolicy);
        fieldSplitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(fieldSplitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        fieldEdit = new QLineEdit(layoutWidget);
        fieldEdit->setObjectName("fieldEdit");
        fieldEdit->setClearButtonEnabled(true);

        horizontalLayout->addWidget(fieldEdit);


        verticalLayout->addLayout(horizontalLayout);

        fieldList = new QListView(layoutWidget);
        fieldList->setObjectName("fieldList");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fieldList->sizePolicy().hasHeightForWidth());
        fieldList->setSizePolicy(sizePolicy1);
        fieldList->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        fieldList->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContentsOnFirstShow);
        fieldList->setResizeMode(QListView::ResizeMode::Adjust);
        fieldList->setSelectionRectVisible(true);

        verticalLayout->addWidget(fieldList);

        fieldSplitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(fieldSplitter);
        layoutWidget1->setObjectName("layoutWidget1");
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        sqlEdit = new QPlainTextEdit(layoutWidget1);
        sqlEdit->setObjectName("sqlEdit");
        sqlEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

        verticalLayout_3->addWidget(sqlEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        testButton = new QPushButton(layoutWidget1);
        testButton->setObjectName("testButton");

        horizontalLayout_2->addWidget(testButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        testResultEdit = new QPlainTextEdit(layoutWidget1);
        testResultEdit->setObjectName("testResultEdit");
        testResultEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        testResultEdit->setReadOnly(true);

        verticalLayout_3->addWidget(testResultEdit);

        fieldSplitter->addWidget(layoutWidget1);
        tableSplitter->addWidget(fieldSplitter);

        verticalLayout_2->addWidget(tableSplitter);


        retranslateUi(DataQueryForm);

        QMetaObject::connectSlotsByName(DataQueryForm);
    } // setupUi

    void retranslateUi(QWidget *DataQueryForm)
    {
        DataQueryForm->setWindowTitle(QCoreApplication::translate("DataQueryForm", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("DataQueryForm", "\350\241\250", nullptr));
        label_2->setText(QCoreApplication::translate("DataQueryForm", "\345\255\227\346\256\265", nullptr));
        label_3->setText(QCoreApplication::translate("DataQueryForm", "SQL \350\257\255\345\217\245", nullptr));
        testButton->setText(QCoreApplication::translate("DataQueryForm", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataQueryForm: public Ui_DataQueryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAQUERYFORM_H
