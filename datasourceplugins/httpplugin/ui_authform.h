/********************************************************************************
** Form generated from reading UI file 'authform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHFORM_H
#define UI_AUTHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *authMethodCombo;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *AuthForm)
    {
        if (AuthForm->objectName().isEmpty())
            AuthForm->setObjectName("AuthForm");
        AuthForm->resize(250, 24);
        verticalLayout = new QVBoxLayout(AuthForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(AuthForm);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_3);

        authMethodCombo = new QComboBox(AuthForm);
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->addItem(QString());
        authMethodCombo->setObjectName("authMethodCombo");

        horizontalLayout_4->addWidget(authMethodCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(AuthForm);

        QMetaObject::connectSlotsByName(AuthForm);
    } // setupUi

    void retranslateUi(QWidget *AuthForm)
    {
        AuthForm->setWindowTitle(QCoreApplication::translate("AuthForm", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("AuthForm", "\347\261\273\345\236\213", nullptr));
        authMethodCombo->setItemText(0, QCoreApplication::translate("AuthForm", "No Auth", nullptr));
        authMethodCombo->setItemText(1, QCoreApplication::translate("AuthForm", "Bearer Token", nullptr));
        authMethodCombo->setItemText(2, QCoreApplication::translate("AuthForm", "JWT", nullptr));
        authMethodCombo->setItemText(3, QCoreApplication::translate("AuthForm", "Basic Auth", nullptr));
        authMethodCombo->setItemText(4, QCoreApplication::translate("AuthForm", "Digest Auth", nullptr));
        authMethodCombo->setItemText(5, QCoreApplication::translate("AuthForm", "API Key", nullptr));
        authMethodCombo->setItemText(6, QCoreApplication::translate("AuthForm", "OAuth 1.0", nullptr));
        authMethodCombo->setItemText(7, QCoreApplication::translate("AuthForm", "OAuth 2.0", nullptr));

    } // retranslateUi

};

namespace Ui {
    class AuthForm: public Ui_AuthForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHFORM_H
