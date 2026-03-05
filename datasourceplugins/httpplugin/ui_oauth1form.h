/********************************************************************************
** Form generated from reading UI file 'oauth1form.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OAUTH1FORM_H
#define UI_OAUTH1FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OAuth1Form
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *locationCombo;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *consumerKeyEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *consumerSecretEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *tokenEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *tokenSecretEdit;

    void setupUi(QWidget *OAuth1Form)
    {
        if (OAuth1Form->objectName().isEmpty())
            OAuth1Form->setObjectName("OAuth1Form");
        OAuth1Form->resize(250, 140);
        verticalLayout = new QVBoxLayout(OAuth1Form);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(OAuth1Form);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        locationCombo = new QComboBox(OAuth1Form);
        locationCombo->setObjectName("locationCombo");

        horizontalLayout->addWidget(locationCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(OAuth1Form);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        consumerKeyEdit = new QLineEdit(OAuth1Form);
        consumerKeyEdit->setObjectName("consumerKeyEdit");

        horizontalLayout_2->addWidget(consumerKeyEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(OAuth1Form);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        consumerSecretEdit = new QLineEdit(OAuth1Form);
        consumerSecretEdit->setObjectName("consumerSecretEdit");
        consumerSecretEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_3->addWidget(consumerSecretEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(OAuth1Form);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_4);

        tokenEdit = new QLineEdit(OAuth1Form);
        tokenEdit->setObjectName("tokenEdit");

        horizontalLayout_4->addWidget(tokenEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(OAuth1Form);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_5);

        tokenSecretEdit = new QLineEdit(OAuth1Form);
        tokenSecretEdit->setObjectName("tokenSecretEdit");
        tokenSecretEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_5->addWidget(tokenSecretEdit);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(OAuth1Form);

        QMetaObject::connectSlotsByName(OAuth1Form);
    } // setupUi

    void retranslateUi(QWidget *OAuth1Form)
    {
        OAuth1Form->setWindowTitle(QCoreApplication::translate("OAuth1Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("OAuth1Form", "\346\267\273\345\212\240\344\275\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("OAuth1Form", "Consumer Key", nullptr));
        label_3->setText(QCoreApplication::translate("OAuth1Form", "Consumer Secret", nullptr));
        label_4->setText(QCoreApplication::translate("OAuth1Form", "Token", nullptr));
        label_5->setText(QCoreApplication::translate("OAuth1Form", "Token Secret", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OAuth1Form: public Ui_OAuth1Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OAUTH1FORM_H
