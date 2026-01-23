/********************************************************************************
** Form generated from reading UI file 'dataeditorform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAEDITORFORM_H
#define UI_DATAEDITORFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataEditorForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *dataEdit;
    QToolButton *dataSelectBtn;
    QWidget *controlTypeWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QRadioButton *controlRadio;
    QRadioButton *assignmentRadio;
    QHBoxLayout *testLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *testBtn;
    QLabel *testInfo;

    void setupUi(QWidget *DataEditorForm)
    {
        if (DataEditorForm->objectName().isEmpty())
            DataEditorForm->setObjectName("DataEditorForm");
        DataEditorForm->resize(225, 117);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DataEditorForm->sizePolicy().hasHeightForWidth());
        DataEditorForm->setSizePolicy(sizePolicy);
        DataEditorForm->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(DataEditorForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        label_2 = new QLabel(DataEditorForm);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        dataEdit = new QLineEdit(DataEditorForm);
        dataEdit->setObjectName("dataEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dataEdit->sizePolicy().hasHeightForWidth());
        dataEdit->setSizePolicy(sizePolicy1);
        dataEdit->setReadOnly(true);

        horizontalLayout_2->addWidget(dataEdit);

        dataSelectBtn = new QToolButton(DataEditorForm);
        dataSelectBtn->setObjectName("dataSelectBtn");

        horizontalLayout_2->addWidget(dataSelectBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        controlTypeWidget = new QWidget(DataEditorForm);
        controlTypeWidget->setObjectName("controlTypeWidget");
        horizontalLayout = new QHBoxLayout(controlTypeWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(controlTypeWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        controlRadio = new QRadioButton(controlTypeWidget);
        controlRadio->setObjectName("controlRadio");
        controlRadio->setCheckable(true);
        controlRadio->setChecked(true);

        horizontalLayout->addWidget(controlRadio);

        assignmentRadio = new QRadioButton(controlTypeWidget);
        assignmentRadio->setObjectName("assignmentRadio");
        assignmentRadio->setCheckable(true);

        horizontalLayout->addWidget(assignmentRadio);


        verticalLayout_2->addWidget(controlTypeWidget);

        testLayout = new QHBoxLayout();
        testLayout->setObjectName("testLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        testLayout->addItem(horizontalSpacer);

        testBtn = new QPushButton(DataEditorForm);
        testBtn->setObjectName("testBtn");

        testLayout->addWidget(testBtn);


        verticalLayout_2->addLayout(testLayout);

        testInfo = new QLabel(DataEditorForm);
        testInfo->setObjectName("testInfo");
        testInfo->setTextFormat(Qt::TextFormat::AutoText);
        testInfo->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        testInfo->setWordWrap(true);
        testInfo->setMargin(8);
        testInfo->setIndent(2);

        verticalLayout_2->addWidget(testInfo);


        retranslateUi(DataEditorForm);

        QMetaObject::connectSlotsByName(DataEditorForm);
    } // setupUi

    void retranslateUi(QWidget *DataEditorForm)
    {
        DataEditorForm->setWindowTitle(QCoreApplication::translate("DataEditorForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("DataEditorForm", "\346\225\260\346\215\256", nullptr));
        dataSelectBtn->setText(QCoreApplication::translate("DataEditorForm", "\351\200\211\346\213\251", nullptr));
        label_3->setText(QCoreApplication::translate("DataEditorForm", "\350\241\214\344\270\272", nullptr));
        controlRadio->setText(QCoreApplication::translate("DataEditorForm", "\346\216\247\345\210\266\345\233\276\345\205\203", nullptr));
        assignmentRadio->setText(QCoreApplication::translate("DataEditorForm", "\345\261\236\346\200\247\350\265\213\345\200\274", nullptr));
        testBtn->setText(QCoreApplication::translate("DataEditorForm", "\346\265\213\350\257\225", nullptr));
        testInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataEditorForm: public Ui_DataEditorForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAEDITORFORM_H
