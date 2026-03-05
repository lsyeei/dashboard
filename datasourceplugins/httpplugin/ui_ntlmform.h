/********************************************************************************
** Form generated from reading UI file 'ntlmform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NTLMFORM_H
#define UI_NTLMFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NTLMForm
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

    void setupUi(QWidget *NTLMForm)
    {
        if (NTLMForm->objectName().isEmpty())
            NTLMForm->setObjectName("NTLMForm");
        NTLMForm->resize(250, 111);
        verticalLayout = new QVBoxLayout(NTLMForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(NTLMForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        userNameEdit = new QLineEdit(NTLMForm);
        userNameEdit->setObjectName("userNameEdit");

        horizontalLayout->addWidget(userNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(NTLMForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        passwordEdit = new QLineEdit(NTLMForm);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(NTLMForm);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        realmEdit = new QLineEdit(NTLMForm);
        realmEdit->setObjectName("realmEdit");

        horizontalLayout_3->addWidget(realmEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_4 = new QLabel(NTLMForm);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_4);

        spnEdit = new QLineEdit(NTLMForm);
        spnEdit->setObjectName("spnEdit");

        horizontalLayout_4->addWidget(spnEdit);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(NTLMForm);

        QMetaObject::connectSlotsByName(NTLMForm);
    } // setupUi

    void retranslateUi(QWidget *NTLMForm)
    {
        NTLMForm->setWindowTitle(QCoreApplication::translate("NTLMForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("NTLMForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("NTLMForm", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("NTLMForm", "\345\237\237(Realm)", nullptr));
        label_4->setText(QCoreApplication::translate("NTLMForm", "SPN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NTLMForm: public Ui_NTLMForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NTLMFORM_H
