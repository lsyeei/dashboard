/********************************************************************************
** Form generated from reading UI file 'userpluginpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPLUGINPROPERTYFORM_H
#define UI_USERPLUGINPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "lineproperty.h"
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
    LineProperty *lineProperty;
    QHBoxLayout *horizontalLayout;
    QCheckBox *roundChecked;
    QSpacerItem *horizontalSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *rotation;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *restoreBtn;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *UserPluginPropertyForm)
    {
        if (UserPluginPropertyForm->objectName().isEmpty())
            UserPluginPropertyForm->setObjectName("UserPluginPropertyForm");
        UserPluginPropertyForm->resize(200, 309);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserPluginPropertyForm->sizePolicy().hasHeightForWidth());
        UserPluginPropertyForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(UserPluginPropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(UserPluginPropertyForm);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        stateBox = new BIComboBox(UserPluginPropertyForm);
        stateBox->setObjectName("stateBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(stateBox);


        verticalLayout->addLayout(horizontalLayout_3);

        posProperty = new PosProperty(UserPluginPropertyForm);
        posProperty->setObjectName("posProperty");
        sizePolicy.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy);
        posProperty->setMinimumSize(QSize(0, 0));
        posProperty->setAspectRatio(true);

        verticalLayout->addWidget(posProperty);

        lineProperty = new LineProperty(UserPluginPropertyForm);
        lineProperty->setObjectName("lineProperty");
        lineProperty->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(lineProperty);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(UserPluginPropertyForm);
        roundChecked->setObjectName("roundChecked");
        sizePolicy2.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(roundChecked);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

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
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(UserPluginPropertyForm);
        label->setObjectName("label");
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        rotation = new QDoubleSpinBox(UserPluginPropertyForm);
        rotation->setObjectName("rotation");
        sizePolicy2.setHeightForWidth(rotation->sizePolicy().hasHeightForWidth());
        rotation->setSizePolicy(sizePolicy2);
        rotation->setDecimals(1);
        rotation->setMinimum(-360.000000000000000);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        restoreBtn = new QPushButton(UserPluginPropertyForm);
        restoreBtn->setObjectName("restoreBtn");
        sizePolicy1.setHeightForWidth(restoreBtn->sizePolicy().hasHeightForWidth());
        restoreBtn->setSizePolicy(sizePolicy1);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::SystemReboot));
        restoreBtn->setIcon(icon);
        restoreBtn->setFlat(true);

        horizontalLayout_4->addWidget(restoreBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);


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
        restoreBtn->setText(QCoreApplication::translate("UserPluginPropertyForm", "\345\216\237\345\247\213\345\244\247\345\260\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserPluginPropertyForm: public Ui_UserPluginPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPLUGINPROPERTYFORM_H
