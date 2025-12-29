/********************************************************************************
** Form generated from reading UI file 'connectform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTFORM_H
#define UI_CONNECTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *driverCombo;
    QWidget *hostWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *hostEdit;
    QLabel *label_4;
    QSpinBox *portSpin;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *databaseNameEdit;
    QToolButton *fileBtn;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *userNameEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *passwordEdit;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *connectOptionCheck;
    QPlainTextEdit *connectOptionEdit;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *testButton;

    void setupUi(QWidget *ConnectForm)
    {
        if (ConnectForm->objectName().isEmpty())
            ConnectForm->setObjectName("ConnectForm");
        ConnectForm->resize(158, 228);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnectForm->sizePolicy().hasHeightForWidth());
        ConnectForm->setSizePolicy(sizePolicy);
        ConnectForm->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(ConnectForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(ConnectForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        driverCombo = new QComboBox(ConnectForm);
        driverCombo->setObjectName("driverCombo");
        driverCombo->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLengthWithIcon);

        horizontalLayout->addWidget(driverCombo);


        verticalLayout->addLayout(horizontalLayout);

        hostWidget = new QWidget(ConnectForm);
        hostWidget->setObjectName("hostWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hostWidget->sizePolicy().hasHeightForWidth());
        hostWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(hostWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(hostWidget);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_3);

        hostEdit = new QLineEdit(hostWidget);
        hostEdit->setObjectName("hostEdit");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(hostEdit->sizePolicy().hasHeightForWidth());
        hostEdit->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(hostEdit);

        label_4 = new QLabel(hostWidget);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_4);

        portSpin = new QSpinBox(hostWidget);
        portSpin->setObjectName("portSpin");
        sizePolicy3.setHeightForWidth(portSpin->sizePolicy().hasHeightForWidth());
        portSpin->setSizePolicy(sizePolicy3);
        portSpin->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        portSpin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        portSpin->setMaximum(999999);

        horizontalLayout_2->addWidget(portSpin);


        verticalLayout->addWidget(hostWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        label_2 = new QLabel(ConnectForm);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        databaseNameEdit = new QLineEdit(ConnectForm);
        databaseNameEdit->setObjectName("databaseNameEdit");

        horizontalLayout_3->addWidget(databaseNameEdit);

        fileBtn = new QToolButton(ConnectForm);
        fileBtn->setObjectName("fileBtn");

        horizontalLayout_3->addWidget(fileBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(ConnectForm);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_5);

        userNameEdit = new QLineEdit(ConnectForm);
        userNameEdit->setObjectName("userNameEdit");
        sizePolicy3.setHeightForWidth(userNameEdit->sizePolicy().hasHeightForWidth());
        userNameEdit->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(userNameEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(ConnectForm);
        label_6->setObjectName("label_6");
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_6);

        passwordEdit = new QLineEdit(ConnectForm);
        passwordEdit->setObjectName("passwordEdit");
        sizePolicy3.setHeightForWidth(passwordEdit->sizePolicy().hasHeightForWidth());
        passwordEdit->setSizePolicy(sizePolicy3);
        passwordEdit->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);

        horizontalLayout_5->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        connectOptionCheck = new QCheckBox(ConnectForm);
        connectOptionCheck->setObjectName("connectOptionCheck");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(connectOptionCheck->sizePolicy().hasHeightForWidth());
        connectOptionCheck->setSizePolicy(sizePolicy4);

        verticalLayout_2->addWidget(connectOptionCheck);

        connectOptionEdit = new QPlainTextEdit(ConnectForm);
        connectOptionEdit->setObjectName("connectOptionEdit");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(connectOptionEdit->sizePolicy().hasHeightForWidth());
        connectOptionEdit->setSizePolicy(sizePolicy5);
        connectOptionEdit->setMinimumSize(QSize(0, 0));
        connectOptionEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

        verticalLayout_2->addWidget(connectOptionEdit);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        testButton = new QPushButton(ConnectForm);
        testButton->setObjectName("testButton");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(testButton->sizePolicy().hasHeightForWidth());
        testButton->setSizePolicy(sizePolicy6);

        horizontalLayout_6->addWidget(testButton);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(ConnectForm);

        QMetaObject::connectSlotsByName(ConnectForm);
    } // setupUi

    void retranslateUi(QWidget *ConnectForm)
    {
        ConnectForm->setWindowTitle(QCoreApplication::translate("ConnectForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("ConnectForm", "\346\225\260\346\215\256\345\272\223\347\261\273\345\236\213", nullptr));
        label_3->setText(QCoreApplication::translate("ConnectForm", "\344\270\273\346\234\272", nullptr));
        label_4->setText(QCoreApplication::translate("ConnectForm", "\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectForm", "\346\225\260\346\215\256\345\272\223", nullptr));
        fileBtn->setText(QCoreApplication::translate("ConnectForm", "...", nullptr));
        label_5->setText(QCoreApplication::translate("ConnectForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_6->setText(QCoreApplication::translate("ConnectForm", "\345\257\206\347\240\201", nullptr));
        connectOptionCheck->setText(QCoreApplication::translate("ConnectForm", "\350\277\236\346\216\245\351\200\211\351\241\271", nullptr));
        testButton->setText(QCoreApplication::translate("ConnectForm", "\346\265\213\350\257\225\350\277\236\346\216\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectForm: public Ui_ConnectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTFORM_H
