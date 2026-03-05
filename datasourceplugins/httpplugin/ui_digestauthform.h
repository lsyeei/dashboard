/********************************************************************************
** Form generated from reading UI file 'digestauthform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGESTAUTHFORM_H
#define UI_DIGESTAUTHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DigestAuthForm
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

    void setupUi(QWidget *DigestAuthForm)
    {
        if (DigestAuthForm->objectName().isEmpty())
            DigestAuthForm->setObjectName("DigestAuthForm");
        DigestAuthForm->resize(250, 82);
        verticalLayout = new QVBoxLayout(DigestAuthForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(DigestAuthForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        userNameEdit = new QLineEdit(DigestAuthForm);
        userNameEdit->setObjectName("userNameEdit");

        horizontalLayout->addWidget(userNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(DigestAuthForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        passwordEdit = new QLineEdit(DigestAuthForm);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(DigestAuthForm);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        realmEdit = new QLineEdit(DigestAuthForm);
        realmEdit->setObjectName("realmEdit");

        horizontalLayout_3->addWidget(realmEdit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(DigestAuthForm);

        QMetaObject::connectSlotsByName(DigestAuthForm);
    } // setupUi

    void retranslateUi(QWidget *DigestAuthForm)
    {
        DigestAuthForm->setWindowTitle(QCoreApplication::translate("DigestAuthForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("DigestAuthForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("DigestAuthForm", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("DigestAuthForm", "Realm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DigestAuthForm: public Ui_DigestAuthForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGESTAUTHFORM_H
