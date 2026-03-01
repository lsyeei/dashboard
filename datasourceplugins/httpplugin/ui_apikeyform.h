/********************************************************************************
** Form generated from reading UI file 'apikeyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APIKEYFORM_H
#define UI_APIKEYFORM_H

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

class Ui_APIKeyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QComboBox *locationCombo;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *keyEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *valueEdit;

    void setupUi(QWidget *APIKeyForm)
    {
        if (APIKeyForm->objectName().isEmpty())
            APIKeyForm->setObjectName("APIKeyForm");
        APIKeyForm->resize(250, 82);
        verticalLayout = new QVBoxLayout(APIKeyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_6 = new QLabel(APIKeyForm);
        label_6->setObjectName("label_6");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(label_6);

        locationCombo = new QComboBox(APIKeyForm);
        locationCombo->setObjectName("locationCombo");

        horizontalLayout_9->addWidget(locationCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_4 = new QLabel(APIKeyForm);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_4);

        keyEdit = new QLineEdit(APIKeyForm);
        keyEdit->setObjectName("keyEdit");

        horizontalLayout_8->addWidget(keyEdit);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_5 = new QLabel(APIKeyForm);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(label_5);

        valueEdit = new QLineEdit(APIKeyForm);
        valueEdit->setObjectName("valueEdit");

        horizontalLayout_7->addWidget(valueEdit);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(APIKeyForm);

        QMetaObject::connectSlotsByName(APIKeyForm);
    } // setupUi

    void retranslateUi(QWidget *APIKeyForm)
    {
        APIKeyForm->setWindowTitle(QCoreApplication::translate("APIKeyForm", "Form", nullptr));
        label_6->setText(QCoreApplication::translate("APIKeyForm", "\346\267\273\345\212\240\344\275\215\347\275\256", nullptr));
        label_4->setText(QCoreApplication::translate("APIKeyForm", "key", nullptr));
        label_5->setText(QCoreApplication::translate("APIKeyForm", "value", nullptr));
    } // retranslateUi

};

namespace Ui {
    class APIKeyForm: public Ui_APIKeyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APIKEYFORM_H
