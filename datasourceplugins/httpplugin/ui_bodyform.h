/********************************************************************************
** Form generated from reading UI file 'bodyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODYFORM_H
#define UI_BODYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BodyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *contentTypeCombo;
    QSpacerItem *horizontalSpacer;
    QLabel *tipLabel;
    QTextEdit *contentEdit;

    void setupUi(QWidget *BodyForm)
    {
        if (BodyForm->objectName().isEmpty())
            BodyForm->setObjectName("BodyForm");
        BodyForm->resize(250, 117);
        verticalLayout = new QVBoxLayout(BodyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(BodyForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        contentTypeCombo = new QComboBox(BodyForm);
        contentTypeCombo->setObjectName("contentTypeCombo");
        contentTypeCombo->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        horizontalLayout->addWidget(contentTypeCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tipLabel = new QLabel(BodyForm);
        tipLabel->setObjectName("tipLabel");

        verticalLayout->addWidget(tipLabel);

        contentEdit = new QTextEdit(BodyForm);
        contentEdit->setObjectName("contentEdit");
        contentEdit->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

        verticalLayout->addWidget(contentEdit);


        retranslateUi(BodyForm);

        QMetaObject::connectSlotsByName(BodyForm);
    } // setupUi

    void retranslateUi(QWidget *BodyForm)
    {
        BodyForm->setWindowTitle(QCoreApplication::translate("BodyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("BodyForm", "\347\261\273\345\236\213", nullptr));
        tipLabel->setText(QCoreApplication::translate("BodyForm", "\344\274\240\350\276\223\345\206\205\345\256\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BodyForm: public Ui_BodyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODYFORM_H
