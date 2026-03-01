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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *urlEdit;
    QWidget *paramWidget;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *authRadio;
    QRadioButton *headerRadio;
    QRadioButton *cookieRadio;
    QRadioButton *settingRadio;

    void setupUi(QWidget *ConnectForm)
    {
        if (ConnectForm->objectName().isEmpty())
            ConnectForm->setObjectName("ConnectForm");
        ConnectForm->resize(250, 55);
        verticalLayout = new QVBoxLayout(ConnectForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(ConnectForm);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        urlEdit = new QLineEdit(ConnectForm);
        urlEdit->setObjectName("urlEdit");

        horizontalLayout_2->addWidget(urlEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        paramWidget = new QWidget(ConnectForm);
        paramWidget->setObjectName("paramWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(paramWidget->sizePolicy().hasHeightForWidth());
        paramWidget->setSizePolicy(sizePolicy);
        paramWidget->setMinimumSize(QSize(0, 26));
        paramWidget->setAutoFillBackground(false);
        paramWidget->setStyleSheet(QString::fromUtf8("QRadioButton::indicator{\n"
"	width:0;\n"
"    height:0;\n"
"    margin:0;\n"
"    padding:0;\n"
"    border:none;\n"
"}\n"
"QRadioButton{\n"
"color:palette(button-text);\n"
"background-color:palette(button);\n"
"}\n"
"QRadioButton:hover {\n"
"    background-color: palette(highlight);\n"
"}\n"
"QRadioButton:checked {\n"
"    background-color: palette(highlight); \n"
"    color:palette(button-text);\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(paramWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        authRadio = new QRadioButton(paramWidget);
        authRadio->setObjectName("authRadio");
        sizePolicy.setHeightForWidth(authRadio->sizePolicy().hasHeightForWidth());
        authRadio->setSizePolicy(sizePolicy);
        authRadio->setMinimumSize(QSize(0, 26));
        authRadio->setAutoFillBackground(false);
        authRadio->setChecked(true);

        horizontalLayout_3->addWidget(authRadio);

        headerRadio = new QRadioButton(paramWidget);
        headerRadio->setObjectName("headerRadio");
        sizePolicy.setHeightForWidth(headerRadio->sizePolicy().hasHeightForWidth());
        headerRadio->setSizePolicy(sizePolicy);
        headerRadio->setMinimumSize(QSize(0, 26));
        headerRadio->setAutoFillBackground(false);

        horizontalLayout_3->addWidget(headerRadio);

        cookieRadio = new QRadioButton(paramWidget);
        cookieRadio->setObjectName("cookieRadio");
        sizePolicy.setHeightForWidth(cookieRadio->sizePolicy().hasHeightForWidth());
        cookieRadio->setSizePolicy(sizePolicy);
        cookieRadio->setMinimumSize(QSize(0, 26));

        horizontalLayout_3->addWidget(cookieRadio);

        settingRadio = new QRadioButton(paramWidget);
        settingRadio->setObjectName("settingRadio");
        sizePolicy.setHeightForWidth(settingRadio->sizePolicy().hasHeightForWidth());
        settingRadio->setSizePolicy(sizePolicy);
        settingRadio->setMinimumSize(QSize(0, 26));

        horizontalLayout_3->addWidget(settingRadio);


        verticalLayout->addWidget(paramWidget);


        retranslateUi(ConnectForm);

        QMetaObject::connectSlotsByName(ConnectForm);
    } // setupUi

    void retranslateUi(QWidget *ConnectForm)
    {
        ConnectForm->setWindowTitle(QCoreApplication::translate("ConnectForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("ConnectForm", "BASE URL", nullptr));
        authRadio->setText(QCoreApplication::translate("ConnectForm", "Auth", nullptr));
        headerRadio->setText(QCoreApplication::translate("ConnectForm", "Headers", nullptr));
        cookieRadio->setText(QCoreApplication::translate("ConnectForm", "Cookies", nullptr));
        settingRadio->setText(QCoreApplication::translate("ConnectForm", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectForm: public Ui_ConnectForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTFORM_H
