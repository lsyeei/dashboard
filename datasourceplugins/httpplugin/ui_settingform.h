/********************************************************************************
** Form generated from reading UI file 'settingform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGFORM_H
#define UI_SETTINGFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *versionCombo;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *redirectCombo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *timeoutSpin;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *sslCheck;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SettingForm)
    {
        if (SettingForm->objectName().isEmpty())
            SettingForm->setObjectName("SettingForm");
        SettingForm->resize(250, 108);
        verticalLayout = new QVBoxLayout(SettingForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SettingForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        versionCombo = new QComboBox(SettingForm);
        versionCombo->setObjectName("versionCombo");

        horizontalLayout->addWidget(versionCombo);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(SettingForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        redirectCombo = new QComboBox(SettingForm);
        redirectCombo->setObjectName("redirectCombo");

        horizontalLayout_2->addWidget(redirectCombo);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(SettingForm);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        timeoutSpin = new QSpinBox(SettingForm);
        timeoutSpin->setObjectName("timeoutSpin");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(timeoutSpin->sizePolicy().hasHeightForWidth());
        timeoutSpin->setSizePolicy(sizePolicy1);
        timeoutSpin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        timeoutSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        timeoutSpin->setMaximum(99999999);

        horizontalLayout_3->addWidget(timeoutSpin);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        sslCheck = new QCheckBox(SettingForm);
        sslCheck->setObjectName("sslCheck");
        sslCheck->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        sslCheck->setAutoFillBackground(false);
        sslCheck->setChecked(false);
        sslCheck->setTristate(false);

        horizontalLayout_4->addWidget(sslCheck);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(SettingForm);

        QMetaObject::connectSlotsByName(SettingForm);
    } // setupUi

    void retranslateUi(QWidget *SettingForm)
    {
        SettingForm->setWindowTitle(QCoreApplication::translate("SettingForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SettingForm", "HTTP \347\211\210\346\234\254", nullptr));
        label_2->setText(QCoreApplication::translate("SettingForm", "\351\207\215\345\256\232\345\220\221", nullptr));
        label_3->setText(QCoreApplication::translate("SettingForm", "\350\277\236\346\216\245\350\266\205\346\227\266", nullptr));
        timeoutSpin->setSuffix(QCoreApplication::translate("SettingForm", "ms", nullptr));
        sslCheck->setText(QCoreApplication::translate("SettingForm", "SSL/TLS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingForm: public Ui_SettingForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGFORM_H
