/********************************************************************************
** Form generated from reading UI file 'oauth2form.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OAUTH2FORM_H
#define UI_OAUTH2FORM_H

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

class Ui_OAuth2Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QComboBox *locationCombo;
    QLabel *label_2;
    QComboBox *tokenTypeCombo;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QComboBox *authModelCombo;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *authUrlEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLineEdit *tokenUrlEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_6;
    QLineEdit *callbackUrlEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLineEdit *clientIdEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QLineEdit *clientSecretEdit;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QPushButton *testBtn;

    void setupUi(QWidget *OAuth2Form)
    {
        if (OAuth2Form->objectName().isEmpty())
            OAuth2Form->setObjectName("OAuth2Form");
        OAuth2Form->resize(250, 225);
        verticalLayout = new QVBoxLayout(OAuth2Form);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label = new QLabel(OAuth2Form);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label);

        locationCombo = new QComboBox(OAuth2Form);
        locationCombo->setObjectName("locationCombo");

        horizontalLayout_6->addWidget(locationCombo);

        label_2 = new QLabel(OAuth2Form);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_2);

        tokenTypeCombo = new QComboBox(OAuth2Form);
        tokenTypeCombo->setObjectName("tokenTypeCombo");

        horizontalLayout_6->addWidget(tokenTypeCombo);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_3 = new QLabel(OAuth2Form);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_3);

        authModelCombo = new QComboBox(OAuth2Form);
        authModelCombo->setObjectName("authModelCombo");

        horizontalLayout_8->addWidget(authModelCombo);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(OAuth2Form);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_4);

        authUrlEdit = new QLineEdit(OAuth2Form);
        authUrlEdit->setObjectName("authUrlEdit");

        horizontalLayout_5->addWidget(authUrlEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(OAuth2Form);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_5);

        tokenUrlEdit = new QLineEdit(OAuth2Form);
        tokenUrlEdit->setObjectName("tokenUrlEdit");

        horizontalLayout_4->addWidget(tokenUrlEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_6 = new QLabel(OAuth2Form);
        label_6->setObjectName("label_6");
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_6);

        callbackUrlEdit = new QLineEdit(OAuth2Form);
        callbackUrlEdit->setObjectName("callbackUrlEdit");

        horizontalLayout_3->addWidget(callbackUrlEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_7 = new QLabel(OAuth2Form);
        label_7->setObjectName("label_7");
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_7);

        clientIdEdit = new QLineEdit(OAuth2Form);
        clientIdEdit->setObjectName("clientIdEdit");

        horizontalLayout_2->addWidget(clientIdEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_8 = new QLabel(OAuth2Form);
        label_8->setObjectName("label_8");
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_8);

        clientSecretEdit = new QLineEdit(OAuth2Form);
        clientSecretEdit->setObjectName("clientSecretEdit");

        horizontalLayout->addWidget(clientSecretEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        testBtn = new QPushButton(OAuth2Form);
        testBtn->setObjectName("testBtn");

        horizontalLayout_9->addWidget(testBtn);


        verticalLayout->addLayout(horizontalLayout_9);


        retranslateUi(OAuth2Form);

        QMetaObject::connectSlotsByName(OAuth2Form);
    } // setupUi

    void retranslateUi(QWidget *OAuth2Form)
    {
        OAuth2Form->setWindowTitle(QCoreApplication::translate("OAuth2Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("OAuth2Form", "\346\267\273\345\212\240\344\275\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("OAuth2Form", "Token\347\261\273\345\236\213", nullptr));
        label_3->setText(QCoreApplication::translate("OAuth2Form", "\346\216\210\346\235\203\346\250\241\345\274\217", nullptr));
        label_4->setText(QCoreApplication::translate("OAuth2Form", "Auth URL", nullptr));
        label_5->setText(QCoreApplication::translate("OAuth2Form", "Access Token URL", nullptr));
        label_6->setText(QCoreApplication::translate("OAuth2Form", "callback URL", nullptr));
        label_7->setText(QCoreApplication::translate("OAuth2Form", "Client ID", nullptr));
        label_8->setText(QCoreApplication::translate("OAuth2Form", "Client Secret", nullptr));
        testBtn->setText(QCoreApplication::translate("OAuth2Form", "\350\216\267\345\217\226token", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OAuth2Form: public Ui_OAuth2Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OAUTH2FORM_H
