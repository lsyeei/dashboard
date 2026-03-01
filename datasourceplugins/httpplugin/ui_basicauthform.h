/********************************************************************************
** Form generated from reading UI file 'basicauthform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASICAUTHFORM_H
#define UI_BASICAUTHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BasicAuthForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *userNameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *realmEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *spnEdit;

    void setupUi(QWidget *BasicAuthForm)
    {
        if (BasicAuthForm->objectName().isEmpty())
            BasicAuthForm->setObjectName("BasicAuthForm");
        BasicAuthForm->resize(250, 111);
        verticalLayout = new QVBoxLayout(BasicAuthForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(BasicAuthForm);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        userNameEdit = new QLineEdit(BasicAuthForm);
        userNameEdit->setObjectName("userNameEdit");

        horizontalLayout->addWidget(userNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(BasicAuthForm);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        passwordEdit = new QLineEdit(BasicAuthForm);
        passwordEdit->setObjectName("passwordEdit");

        horizontalLayout_2->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(BasicAuthForm);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        realmEdit = new QLineEdit(BasicAuthForm);
        realmEdit->setObjectName("realmEdit");

        horizontalLayout_3->addWidget(realmEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(BasicAuthForm);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        spnEdit = new QLineEdit(BasicAuthForm);
        spnEdit->setObjectName("spnEdit");

        horizontalLayout_4->addWidget(spnEdit);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(BasicAuthForm);

        QMetaObject::connectSlotsByName(BasicAuthForm);
    } // setupUi

    void retranslateUi(QWidget *BasicAuthForm)
    {
        BasicAuthForm->setWindowTitle(QCoreApplication::translate("BasicAuthForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("BasicAuthForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("BasicAuthForm", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("BasicAuthForm", "realm", nullptr));
        label_4->setText(QCoreApplication::translate("BasicAuthForm", "SPN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BasicAuthForm: public Ui_BasicAuthForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASICAUTHFORM_H
