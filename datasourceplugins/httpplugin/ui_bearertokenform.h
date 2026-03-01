/********************************************************************************
** Form generated from reading UI file 'bearertokenform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEARERTOKENFORM_H
#define UI_BEARERTOKENFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BearerTokenForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *tokenEdit;

    void setupUi(QWidget *BearerTokenForm)
    {
        if (BearerTokenForm->objectName().isEmpty())
            BearerTokenForm->setObjectName("BearerTokenForm");
        BearerTokenForm->resize(250, 74);
        verticalLayout = new QVBoxLayout(BearerTokenForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(BearerTokenForm);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        tokenEdit = new QPlainTextEdit(BearerTokenForm);
        tokenEdit->setObjectName("tokenEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tokenEdit->sizePolicy().hasHeightForWidth());
        tokenEdit->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(tokenEdit);


        retranslateUi(BearerTokenForm);

        QMetaObject::connectSlotsByName(BearerTokenForm);
    } // setupUi

    void retranslateUi(QWidget *BearerTokenForm)
    {
        BearerTokenForm->setWindowTitle(QCoreApplication::translate("BearerTokenForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("BearerTokenForm", "Token", nullptr));
        tokenEdit->setPlaceholderText(QCoreApplication::translate("BearerTokenForm", "token", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BearerTokenForm: public Ui_BearerTokenForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEARERTOKENFORM_H
