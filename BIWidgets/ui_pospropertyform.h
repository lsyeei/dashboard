/********************************************************************************
** Form generated from reading UI file 'pospropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSPROPERTYFORM_H
#define UI_POSPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PosPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *posLabel;
    QSpinBox *leftValue;
    QSpinBox *topValue;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *leftLabel;
    QLabel *topLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *widthValue;
    QSpinBox *heightValue;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *aspectRatioChecked;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *PosPropertyForm)
    {
        if (PosPropertyForm->objectName().isEmpty())
            PosPropertyForm->setObjectName("PosPropertyForm");
        PosPropertyForm->resize(212, 122);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PosPropertyForm->sizePolicy().hasHeightForWidth());
        PosPropertyForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PosPropertyForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        posLabel = new QLabel(PosPropertyForm);
        posLabel->setObjectName("posLabel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(posLabel->sizePolicy().hasHeightForWidth());
        posLabel->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(posLabel);

        leftValue = new QSpinBox(PosPropertyForm);
        leftValue->setObjectName("leftValue");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leftValue->sizePolicy().hasHeightForWidth());
        leftValue->setSizePolicy(sizePolicy2);
        leftValue->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        leftValue->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        leftValue->setMinimum(-2147483647);
        leftValue->setMaximum(2147483647);

        horizontalLayout->addWidget(leftValue);

        topValue = new QSpinBox(PosPropertyForm);
        topValue->setObjectName("topValue");
        sizePolicy2.setHeightForWidth(topValue->sizePolicy().hasHeightForWidth());
        topValue->setSizePolicy(sizePolicy2);
        topValue->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        topValue->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        topValue->setMinimum(-2147483647);
        topValue->setMaximum(2147483647);

        horizontalLayout->addWidget(topValue);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        horizontalSpacer = new QSpacerItem(24, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        leftLabel = new QLabel(PosPropertyForm);
        leftLabel->setObjectName("leftLabel");
        sizePolicy2.setHeightForWidth(leftLabel->sizePolicy().hasHeightForWidth());
        leftLabel->setSizePolicy(sizePolicy2);
        leftLabel->setMinimumSize(QSize(0, 0));
        leftLabel->setMaximumSize(QSize(16777215, 16777215));
        leftLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(leftLabel);

        topLabel = new QLabel(PosPropertyForm);
        topLabel->setObjectName("topLabel");
        sizePolicy2.setHeightForWidth(topLabel->sizePolicy().hasHeightForWidth());
        topLabel->setSizePolicy(sizePolicy2);
        topLabel->setMinimumSize(QSize(0, 0));
        topLabel->setMaximumSize(QSize(16777215, 16777215));
        topLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_2->addWidget(topLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(-1, 6, -1, -1);
        label = new QLabel(PosPropertyForm);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        widthValue = new QSpinBox(PosPropertyForm);
        widthValue->setObjectName("widthValue");
        sizePolicy2.setHeightForWidth(widthValue->sizePolicy().hasHeightForWidth());
        widthValue->setSizePolicy(sizePolicy2);
        widthValue->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        widthValue->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        widthValue->setMaximum(2147483647);

        horizontalLayout_3->addWidget(widthValue);

        heightValue = new QSpinBox(PosPropertyForm);
        heightValue->setObjectName("heightValue");
        sizePolicy2.setHeightForWidth(heightValue->sizePolicy().hasHeightForWidth());
        heightValue->setSizePolicy(sizePolicy2);
        heightValue->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        heightValue->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        heightValue->setMaximum(2147483647);

        horizontalLayout_3->addWidget(heightValue);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(24, 13, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        widthLabel = new QLabel(PosPropertyForm);
        widthLabel->setObjectName("widthLabel");
        widthLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(widthLabel);

        heightLabel = new QLabel(PosPropertyForm);
        heightLabel->setObjectName("heightLabel");
        heightLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(heightLabel);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 6, -1, -1);
        aspectRatioChecked = new QCheckBox(PosPropertyForm);
        aspectRatioChecked->setObjectName("aspectRatioChecked");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(aspectRatioChecked->sizePolicy().hasHeightForWidth());
        aspectRatioChecked->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(aspectRatioChecked);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_5);

        QWidget::setTabOrder(leftValue, topValue);
        QWidget::setTabOrder(topValue, widthValue);
        QWidget::setTabOrder(widthValue, heightValue);

        retranslateUi(PosPropertyForm);

        QMetaObject::connectSlotsByName(PosPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *PosPropertyForm)
    {
        PosPropertyForm->setWindowTitle(QCoreApplication::translate("PosPropertyForm", "Form", nullptr));
        posLabel->setText(QCoreApplication::translate("PosPropertyForm", "\344\275\215\347\275\256", nullptr));
        leftValue->setSuffix(QCoreApplication::translate("PosPropertyForm", " px", nullptr));
        topValue->setSuffix(QCoreApplication::translate("PosPropertyForm", " px", nullptr));
        leftLabel->setText(QCoreApplication::translate("PosPropertyForm", "\345\267\246", nullptr));
        topLabel->setText(QCoreApplication::translate("PosPropertyForm", "\344\270\212", nullptr));
        label->setText(QCoreApplication::translate("PosPropertyForm", "\345\244\247\345\260\217", nullptr));
        widthValue->setSuffix(QCoreApplication::translate("PosPropertyForm", " px", nullptr));
        heightValue->setSuffix(QCoreApplication::translate("PosPropertyForm", " px", nullptr));
        widthLabel->setText(QCoreApplication::translate("PosPropertyForm", "\345\256\275", nullptr));
        heightLabel->setText(QCoreApplication::translate("PosPropertyForm", "\351\253\230", nullptr));
        aspectRatioChecked->setText(QCoreApplication::translate("PosPropertyForm", "\351\231\220\345\210\266\346\257\224\344\276\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PosPropertyForm: public Ui_PosPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSPROPERTYFORM_H
