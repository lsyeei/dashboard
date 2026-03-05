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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QPlainTextEdit *urlEdit;
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
        ConnectForm->resize(250, 105);
        verticalLayout = new QVBoxLayout(ConnectForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(ConnectForm);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        urlEdit = new QPlainTextEdit(ConnectForm);
        urlEdit->setObjectName("urlEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(urlEdit->sizePolicy().hasHeightForWidth());
        urlEdit->setSizePolicy(sizePolicy);
        urlEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        urlEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

        verticalLayout->addWidget(urlEdit);

        paramWidget = new QWidget(ConnectForm);
        paramWidget->setObjectName("paramWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(paramWidget->sizePolicy().hasHeightForWidth());
        paramWidget->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(authRadio->sizePolicy().hasHeightForWidth());
        authRadio->setSizePolicy(sizePolicy1);
        authRadio->setMinimumSize(QSize(0, 26));
        authRadio->setAutoFillBackground(false);
        authRadio->setChecked(true);

        horizontalLayout_3->addWidget(authRadio);

        headerRadio = new QRadioButton(paramWidget);
        headerRadio->setObjectName("headerRadio");
        sizePolicy1.setHeightForWidth(headerRadio->sizePolicy().hasHeightForWidth());
        headerRadio->setSizePolicy(sizePolicy1);
        headerRadio->setMinimumSize(QSize(0, 26));
        headerRadio->setAutoFillBackground(false);

        horizontalLayout_3->addWidget(headerRadio);

        cookieRadio = new QRadioButton(paramWidget);
        cookieRadio->setObjectName("cookieRadio");
        sizePolicy1.setHeightForWidth(cookieRadio->sizePolicy().hasHeightForWidth());
        cookieRadio->setSizePolicy(sizePolicy1);
        cookieRadio->setMinimumSize(QSize(0, 26));

        horizontalLayout_3->addWidget(cookieRadio);

        settingRadio = new QRadioButton(paramWidget);
        settingRadio->setObjectName("settingRadio");
        sizePolicy1.setHeightForWidth(settingRadio->sizePolicy().hasHeightForWidth());
        settingRadio->setSizePolicy(sizePolicy1);
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
