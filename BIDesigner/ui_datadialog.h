/********************************************************************************
** Form generated from reading UI file 'datadialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIALOG_H
#define UI_DATADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *dataNameEdit;
    QLabel *label_2;
    QSpinBox *periodSpin;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *noteEdit;
    QWidget *dataWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *processCheck;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *codeTestBtn;
    QWidget *processWidget;
    QHBoxLayout *horizontalLayout_5;
    QSplitter *processSplitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QTextEdit *processCodeEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QPlainTextEdit *codeTestEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *DataDialog)
    {
        if (DataDialog->objectName().isEmpty())
            DataDialog->setObjectName("DataDialog");
        DataDialog->resize(356, 216);
        verticalLayout_2 = new QVBoxLayout(DataDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DataDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        dataNameEdit = new QLineEdit(DataDialog);
        dataNameEdit->setObjectName("dataNameEdit");

        horizontalLayout->addWidget(dataNameEdit);

        label_2 = new QLabel(DataDialog);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        periodSpin = new QSpinBox(DataDialog);
        periodSpin->setObjectName("periodSpin");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(periodSpin->sizePolicy().hasHeightForWidth());
        periodSpin->setSizePolicy(sizePolicy);
        periodSpin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        periodSpin->setMaximum(3600);

        horizontalLayout->addWidget(periodSpin);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(DataDialog);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        noteEdit = new QLineEdit(DataDialog);
        noteEdit->setObjectName("noteEdit");

        horizontalLayout_3->addWidget(noteEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        dataWidget = new QWidget(DataDialog);
        dataWidget->setObjectName("dataWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dataWidget->sizePolicy().hasHeightForWidth());
        dataWidget->setSizePolicy(sizePolicy1);
        verticalLayout = new QVBoxLayout(dataWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_2->addWidget(dataWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        processCheck = new QCheckBox(DataDialog);
        processCheck->setObjectName("processCheck");

        horizontalLayout_6->addWidget(processCheck);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        codeTestBtn = new QPushButton(DataDialog);
        codeTestBtn->setObjectName("codeTestBtn");

        horizontalLayout_6->addWidget(codeTestBtn);


        verticalLayout_2->addLayout(horizontalLayout_6);

        processWidget = new QWidget(DataDialog);
        processWidget->setObjectName("processWidget");
        horizontalLayout_5 = new QHBoxLayout(processWidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        processSplitter = new QSplitter(processWidget);
        processSplitter->setObjectName("processSplitter");
        processSplitter->setOrientation(Qt::Orientation::Horizontal);
        layoutWidget = new QWidget(processSplitter);
        layoutWidget->setObjectName("layoutWidget");
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        processCodeEdit = new QTextEdit(layoutWidget);
        processCodeEdit->setObjectName("processCodeEdit");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(processCodeEdit->sizePolicy().hasHeightForWidth());
        processCodeEdit->setSizePolicy(sizePolicy2);
        processCodeEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContentsOnFirstShow);

        verticalLayout_3->addWidget(processCodeEdit);

        processSplitter->addWidget(layoutWidget);
        verticalLayoutWidget_2 = new QWidget(processSplitter);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName("label_5");

        verticalLayout_4->addWidget(label_5);

        codeTestEdit = new QPlainTextEdit(verticalLayoutWidget_2);
        codeTestEdit->setObjectName("codeTestEdit");
        sizePolicy2.setHeightForWidth(codeTestEdit->sizePolicy().hasHeightForWidth());
        codeTestEdit->setSizePolicy(sizePolicy2);
        codeTestEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContentsOnFirstShow);
        codeTestEdit->setReadOnly(true);

        verticalLayout_4->addWidget(codeTestEdit);

        processSplitter->addWidget(verticalLayoutWidget_2);

        horizontalLayout_5->addWidget(processSplitter);


        verticalLayout_2->addWidget(processWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okBtn = new QPushButton(DataDialog);
        okBtn->setObjectName("okBtn");

        horizontalLayout_2->addWidget(okBtn);

        cancelBtn = new QPushButton(DataDialog);
        cancelBtn->setObjectName("cancelBtn");

        horizontalLayout_2->addWidget(cancelBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(DataDialog);

        QMetaObject::connectSlotsByName(DataDialog);
    } // setupUi

    void retranslateUi(QDialog *DataDialog)
    {
        DataDialog->setWindowTitle(QCoreApplication::translate("DataDialog", "\346\267\273\345\212\240\346\225\260\346\215\256", nullptr));
        label->setText(QCoreApplication::translate("DataDialog", "\346\225\260\346\215\256\345\220\215\347\247\260", nullptr));
        label_2->setText(QCoreApplication::translate("DataDialog", "\345\210\267\346\226\260\345\221\250\346\234\237", nullptr));
        periodSpin->setSuffix(QCoreApplication::translate("DataDialog", "\347\247\222", nullptr));
        label_3->setText(QCoreApplication::translate("DataDialog", "\346\263\250\351\207\212", nullptr));
        processCheck->setText(QCoreApplication::translate("DataDialog", "\346\225\260\346\215\256\345\244\204\347\220\206", nullptr));
        codeTestBtn->setText(QCoreApplication::translate("DataDialog", "\346\265\213\350\257\225", nullptr));
        label_4->setText(QCoreApplication::translate("DataDialog", "\350\276\223\345\205\245\345\244\204\347\220\206\346\225\260\346\215\256\347\232\204JS\344\273\243\347\240\201", nullptr));
        label_5->setText(QCoreApplication::translate("DataDialog", "\346\265\213\350\257\225\347\273\223\346\236\234", nullptr));
        okBtn->setText(QCoreApplication::translate("DataDialog", "\347\241\256\345\256\232", nullptr));
        cancelBtn->setText(QCoreApplication::translate("DataDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataDialog: public Ui_DataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIALOG_H
