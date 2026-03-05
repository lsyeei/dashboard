/********************************************************************************
** Form generated from reading UI file 'queryform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUERYFORM_H
#define UI_QUERYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QueryForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *queryMethodCombo;
    QLineEdit *queryUrlEdit;
    QLabel *label;
    QWidget *paramWidget;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *paramRadio;
    QRadioButton *bodyRadio;
    QRadioButton *headerRadio;
    QWidget *replyWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *switchBtn;
    QLabel *label_2;
    QTextEdit *replyEdit;

    void setupUi(QWidget *QueryForm)
    {
        if (QueryForm->objectName().isEmpty())
            QueryForm->setObjectName("QueryForm");
        QueryForm->resize(250, 158);
        verticalLayout_2 = new QVBoxLayout(QueryForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        queryMethodCombo = new QComboBox(QueryForm);
        queryMethodCombo->setObjectName("queryMethodCombo");

        horizontalLayout->addWidget(queryMethodCombo);

        queryUrlEdit = new QLineEdit(QueryForm);
        queryUrlEdit->setObjectName("queryUrlEdit");

        horizontalLayout->addWidget(queryUrlEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        label = new QLabel(QueryForm);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        paramWidget = new QWidget(QueryForm);
        paramWidget->setObjectName("paramWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
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
        paramRadio = new QRadioButton(paramWidget);
        paramRadio->setObjectName("paramRadio");
        sizePolicy.setHeightForWidth(paramRadio->sizePolicy().hasHeightForWidth());
        paramRadio->setSizePolicy(sizePolicy);
        paramRadio->setMinimumSize(QSize(0, 26));
        paramRadio->setAutoFillBackground(false);
        paramRadio->setChecked(true);

        horizontalLayout_3->addWidget(paramRadio);

        bodyRadio = new QRadioButton(paramWidget);
        bodyRadio->setObjectName("bodyRadio");
        sizePolicy.setHeightForWidth(bodyRadio->sizePolicy().hasHeightForWidth());
        bodyRadio->setSizePolicy(sizePolicy);
        bodyRadio->setMinimumSize(QSize(0, 26));

        horizontalLayout_3->addWidget(bodyRadio);

        headerRadio = new QRadioButton(paramWidget);
        headerRadio->setObjectName("headerRadio");
        sizePolicy.setHeightForWidth(headerRadio->sizePolicy().hasHeightForWidth());
        headerRadio->setSizePolicy(sizePolicy);
        headerRadio->setMinimumSize(QSize(0, 26));
        headerRadio->setAutoFillBackground(false);

        horizontalLayout_3->addWidget(headerRadio);


        verticalLayout_2->addWidget(paramWidget);

        replyWidget = new QWidget(QueryForm);
        replyWidget->setObjectName("replyWidget");
        verticalLayout = new QVBoxLayout(replyWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        switchBtn = new QToolButton(replyWidget);
        switchBtn->setObjectName("switchBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(switchBtn->sizePolicy().hasHeightForWidth());
        switchBtn->setSizePolicy(sizePolicy1);
        switchBtn->setIconSize(QSize(8, 8));
        switchBtn->setAutoRaise(true);
        switchBtn->setArrowType(Qt::ArrowType::DownArrow);

        horizontalLayout_2->addWidget(switchBtn);

        label_2 = new QLabel(replyWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_2);

        replyEdit = new QTextEdit(replyWidget);
        replyEdit->setObjectName("replyEdit");
        sizePolicy.setHeightForWidth(replyEdit->sizePolicy().hasHeightForWidth());
        replyEdit->setSizePolicy(sizePolicy);
        replyEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        replyEdit->setReadOnly(true);

        verticalLayout->addWidget(replyEdit);


        verticalLayout_2->addWidget(replyWidget);


        retranslateUi(QueryForm);

        QMetaObject::connectSlotsByName(QueryForm);
    } // setupUi

    void retranslateUi(QWidget *QueryForm)
    {
        QueryForm->setWindowTitle(QCoreApplication::translate("QueryForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("QueryForm", "\350\257\267\346\261\202\345\217\202\346\225\260", nullptr));
        paramRadio->setText(QCoreApplication::translate("QueryForm", "Params", nullptr));
        bodyRadio->setText(QCoreApplication::translate("QueryForm", "Body", nullptr));
        headerRadio->setText(QCoreApplication::translate("QueryForm", "Headers", nullptr));
        switchBtn->setText(QCoreApplication::translate("QueryForm", "...", nullptr));
        label_2->setText(QCoreApplication::translate("QueryForm", "\350\277\224\345\233\236\345\223\215\345\272\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QueryForm: public Ui_QueryForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUERYFORM_H
