/********************************************************************************
** Form generated from reading UI file 'dataassignform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAASSIGNFORM_H
#define UI_DATAASSIGNFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataAssignForm
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
    QHBoxLayout *horizontalLayout_3;
    QLabel *propertyLabel;

    void setupUi(QWidget *DataAssignForm)
    {
        if (DataAssignForm->objectName().isEmpty())
            DataAssignForm->setObjectName("DataAssignForm");
        DataAssignForm->resize(219, 132);
        verticalLayout = new QVBoxLayout(DataAssignForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        label_3 = new QLabel(DataAssignForm);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DataAssignForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        propertyOptions = new QComboBox(DataAssignForm);
        propertyOptions->setObjectName("propertyOptions");

        horizontalLayout->addWidget(propertyOptions);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 5, -1, 5);
        label_2 = new QLabel(DataAssignForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        defaultValueEdit = new QLineEdit(DataAssignForm);
        defaultValueEdit->setObjectName("defaultValueEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(defaultValueEdit->sizePolicy().hasHeightForWidth());
        defaultValueEdit->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(defaultValueEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        propertyLabel = new QLabel(DataAssignForm);
        propertyLabel->setObjectName("propertyLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(propertyLabel->sizePolicy().hasHeightForWidth());
        propertyLabel->setSizePolicy(sizePolicy2);
        propertyLabel->setWordWrap(true);
        propertyLabel->setMargin(10);

        horizontalLayout_3->addWidget(propertyLabel);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DataAssignForm);

        QMetaObject::connectSlotsByName(DataAssignForm);
    } // setupUi

    void retranslateUi(QWidget *DataAssignForm)
    {
        DataAssignForm->setWindowTitle(QCoreApplication::translate("DataAssignForm", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("DataAssignForm", "\345\205\263\350\201\224\346\225\260\346\215\256\345\210\260\345\261\236\346\200\247", nullptr));
        label->setText(QCoreApplication::translate("DataAssignForm", "\345\261\236\346\200\247", nullptr));
        label_2->setText(QCoreApplication::translate("DataAssignForm", "\351\273\230\350\256\244\345\200\274", nullptr));
        propertyLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataAssignForm: public Ui_DataAssignForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAASSIGNFORM_H
