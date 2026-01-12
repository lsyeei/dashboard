/********************************************************************************
** Form generated from reading UI file 'datarelateform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATARELATEFORM_H
#define UI_DATARELATEFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataRelateForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *propertyOptions;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *defaultValueEdit;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveBtn;

    void setupUi(QWidget *DataRelateForm)
    {
        if (DataRelateForm->objectName().isEmpty())
            DataRelateForm->setObjectName("DataRelateForm");
        DataRelateForm->resize(219, 148);
        verticalLayout = new QVBoxLayout(DataRelateForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        label_3 = new QLabel(DataRelateForm);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DataRelateForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        propertyOptions = new QComboBox(DataRelateForm);
        propertyOptions->setObjectName("propertyOptions");

        horizontalLayout->addWidget(propertyOptions);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        label_2 = new QLabel(DataRelateForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        defaultValueEdit = new QLineEdit(DataRelateForm);
        defaultValueEdit->setObjectName("defaultValueEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(defaultValueEdit->sizePolicy().hasHeightForWidth());
        defaultValueEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(defaultValueEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        saveBtn = new QPushButton(DataRelateForm);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout_8->addWidget(saveBtn);


        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(DataRelateForm);

        QMetaObject::connectSlotsByName(DataRelateForm);
    } // setupUi

    void retranslateUi(QWidget *DataRelateForm)
    {
        DataRelateForm->setWindowTitle(QCoreApplication::translate("DataRelateForm", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("DataRelateForm", "\345\205\263\350\201\224\346\225\260\346\215\256\345\210\260\345\261\236\346\200\247", nullptr));
        label->setText(QCoreApplication::translate("DataRelateForm", "\345\261\236\346\200\247", nullptr));
        label_2->setText(QCoreApplication::translate("DataRelateForm", "\351\273\230\350\256\244\345\200\274", nullptr));
        saveBtn->setText(QCoreApplication::translate("DataRelateForm", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataRelateForm: public Ui_DataRelateForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATARELATEFORM_H
