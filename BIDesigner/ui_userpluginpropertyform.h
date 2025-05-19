/********************************************************************************
** Form generated from reading UI file 'userpluginpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPLUGINPROPERTYFORM_H
#define UI_USERPLUGINPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "posproperty.h"

QT_BEGIN_NAMESPACE

class Ui_UserPluginPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    BIComboBox *stateBox;
    PosProperty *posProperty;
    QHBoxLayout *horizontalLayout;
    QCheckBox *roundChecked;
    QSpacerItem *horizontalSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *rotation;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *UserPluginPropertyForm)
    {
        if (UserPluginPropertyForm->objectName().isEmpty())
            UserPluginPropertyForm->setObjectName("UserPluginPropertyForm");
        UserPluginPropertyForm->resize(320, 251);
        verticalLayout = new QVBoxLayout(UserPluginPropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_2 = new QLabel(UserPluginPropertyForm);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_2);

        stateBox = new BIComboBox(UserPluginPropertyForm);
        stateBox->setObjectName("stateBox");
        sizePolicy.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(stateBox);

        horizontalLayout_3->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout_3);

        posProperty = new PosProperty(UserPluginPropertyForm);
        posProperty->setObjectName("posProperty");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy1);
        posProperty->setMinimumSize(QSize(0, 0));
        posProperty->setAspectRatio(true);

        verticalLayout->addWidget(posProperty);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(UserPluginPropertyForm);
        roundChecked->setObjectName("roundChecked");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(roundChecked);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        roundSize = new QSpinBox(UserPluginPropertyForm);
        roundSize->setObjectName("roundSize");
        sizePolicy2.setHeightForWidth(roundSize->sizePolicy().hasHeightForWidth());
        roundSize->setSizePolicy(sizePolicy2);
        roundSize->setMaximum(65536);

        horizontalLayout->addWidget(roundSize);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(UserPluginPropertyForm);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        rotation = new QDoubleSpinBox(UserPluginPropertyForm);
        rotation->setObjectName("rotation");
        rotation->setDecimals(1);
        rotation->setMinimum(-360.000000000000000);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(UserPluginPropertyForm);

        QMetaObject::connectSlotsByName(UserPluginPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *UserPluginPropertyForm)
    {
        UserPluginPropertyForm->setWindowTitle(QCoreApplication::translate("UserPluginPropertyForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("UserPluginPropertyForm", "\347\212\266\346\200\201", nullptr));
        roundChecked->setText(QCoreApplication::translate("UserPluginPropertyForm", "\345\234\206\350\247\222", nullptr));
        roundSize->setSuffix(QCoreApplication::translate("UserPluginPropertyForm", "px", nullptr));
        label->setText(QCoreApplication::translate("UserPluginPropertyForm", "\346\227\213\350\275\254", nullptr));
        rotation->setSuffix(QCoreApplication::translate("UserPluginPropertyForm", "\302\260C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserPluginPropertyForm: public Ui_UserPluginPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPLUGINPROPERTYFORM_H
