/********************************************************************************
** Form generated from reading UI file 'spnegoform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPNEGOFORM_H
#define UI_SPNEGOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SPNEGOForm
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
    QLineEdit *spnEdit;

    void setupUi(QWidget *SPNEGOForm)
    {
        if (SPNEGOForm->objectName().isEmpty())
            SPNEGOForm->setObjectName("SPNEGOForm");
        SPNEGOForm->resize(250, 82);
        verticalLayout = new QVBoxLayout(SPNEGOForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(SPNEGOForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        userNameEdit = new QLineEdit(SPNEGOForm);
        userNameEdit->setObjectName("userNameEdit");

        horizontalLayout->addWidget(userNameEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(SPNEGOForm);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_2);

        passwordEdit = new QLineEdit(SPNEGOForm);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(passwordEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(SPNEGOForm);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(label_3);

        spnEdit = new QLineEdit(SPNEGOForm);
        spnEdit->setObjectName("spnEdit");

        horizontalLayout_3->addWidget(spnEdit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(SPNEGOForm);

        QMetaObject::connectSlotsByName(SPNEGOForm);
    } // setupUi

    void retranslateUi(QWidget *SPNEGOForm)
    {
        SPNEGOForm->setWindowTitle(QCoreApplication::translate("SPNEGOForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("SPNEGOForm", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("SPNEGOForm", "\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("SPNEGOForm", "SPN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SPNEGOForm: public Ui_SPNEGOForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPNEGOFORM_H
