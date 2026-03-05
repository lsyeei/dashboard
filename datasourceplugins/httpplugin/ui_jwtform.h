/********************************************************************************
** Form generated from reading UI file 'jwtform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JWTFORM_H
#define UI_JWTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JWTForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *locationCombo;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *headerPrefixEdit;
    QLabel *label_3;
    QPlainTextEdit *tokenEdit;

    void setupUi(QWidget *JWTForm)
    {
        if (JWTForm->objectName().isEmpty())
            JWTForm->setObjectName("JWTForm");
        JWTForm->resize(250, 180);
        verticalLayout = new QVBoxLayout(JWTForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(JWTForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        locationCombo = new QComboBox(JWTForm);
        locationCombo->setObjectName("locationCombo");

        horizontalLayout->addWidget(locationCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(JWTForm);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        headerPrefixEdit = new QLineEdit(JWTForm);
        headerPrefixEdit->setObjectName("headerPrefixEdit");

        horizontalLayout_2->addWidget(headerPrefixEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        label_3 = new QLabel(JWTForm);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        tokenEdit = new QPlainTextEdit(JWTForm);
        tokenEdit->setObjectName("tokenEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tokenEdit->sizePolicy().hasHeightForWidth());
        tokenEdit->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(tokenEdit);


        retranslateUi(JWTForm);

        QMetaObject::connectSlotsByName(JWTForm);
    } // setupUi

    void retranslateUi(QWidget *JWTForm)
    {
        JWTForm->setWindowTitle(QCoreApplication::translate("JWTForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("JWTForm", "\346\267\273\345\212\240\344\275\215\347\275\256", nullptr));
        label_2->setText(QCoreApplication::translate("JWTForm", "Header\345\211\215\347\274\200", nullptr));
        headerPrefixEdit->setText(QCoreApplication::translate("JWTForm", "Bearer", nullptr));
        label_3->setText(QCoreApplication::translate("JWTForm", "Token", nullptr));
        tokenEdit->setPlaceholderText(QCoreApplication::translate("JWTForm", "JWT Token", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JWTForm: public Ui_JWTForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JWTFORM_H
