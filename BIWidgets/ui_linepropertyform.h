/********************************************************************************
** Form generated from reading UI file 'linepropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEPROPERTYFORM_H
#define UI_LINEPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_LinePropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *lineChecked;
    ColorPicker *lineColor;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *lineStyle;
    QSpinBox *lineWidth;

    void setupUi(QWidget *LinePropertyForm)
    {
        if (LinePropertyForm->objectName().isEmpty())
            LinePropertyForm->setObjectName("LinePropertyForm");
        LinePropertyForm->resize(239, 56);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LinePropertyForm->sizePolicy().hasHeightForWidth());
        LinePropertyForm->setSizePolicy(sizePolicy);
        LinePropertyForm->setMinimumSize(QSize(0, 0));
        LinePropertyForm->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(LinePropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        lineChecked = new QCheckBox(LinePropertyForm);
        lineChecked->setObjectName("lineChecked");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineChecked->sizePolicy().hasHeightForWidth());
        lineChecked->setSizePolicy(sizePolicy1);
        lineChecked->setMinimumSize(QSize(0, 0));
        lineChecked->setMaximumSize(QSize(16777215, 16777215));
        lineChecked->setCheckable(true);
        lineChecked->setChecked(true);

        horizontalLayout->addWidget(lineChecked);

        lineColor = new ColorPicker(LinePropertyForm);
        lineColor->setObjectName("lineColor");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineColor->sizePolicy().hasHeightForWidth());
        lineColor->setSizePolicy(sizePolicy2);
        lineColor->setMinimumSize(QSize(45, 22));
        lineColor->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(lineColor, 0, Qt::AlignmentFlag::AlignVCenter);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        lineStyle = new QComboBox(LinePropertyForm);
        lineStyle->setObjectName("lineStyle");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineStyle->sizePolicy().hasHeightForWidth());
        lineStyle->setSizePolicy(sizePolicy3);
        lineStyle->setMinimumSize(QSize(0, 0));
        lineStyle->setMaximumSize(QSize(16777215, 16777215));
        lineStyle->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToMinimumContentsLengthWithIcon);
        lineStyle->setFrame(false);

        horizontalLayout_2->addWidget(lineStyle, 0, Qt::AlignmentFlag::AlignVCenter);

        lineWidth = new QSpinBox(LinePropertyForm);
        lineWidth->setObjectName("lineWidth");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineWidth->sizePolicy().hasHeightForWidth());
        lineWidth->setSizePolicy(sizePolicy4);
        lineWidth->setMinimumSize(QSize(0, 0));
        lineWidth->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineWidth->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        lineWidth->setMinimum(1);
        lineWidth->setMaximum(99999);
        lineWidth->setValue(1);

        horizontalLayout_2->addWidget(lineWidth);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LinePropertyForm);

        QMetaObject::connectSlotsByName(LinePropertyForm);
    } // setupUi

    void retranslateUi(QWidget *LinePropertyForm)
    {
        LinePropertyForm->setWindowTitle(QCoreApplication::translate("LinePropertyForm", "Form", nullptr));
        lineChecked->setText(QCoreApplication::translate("LinePropertyForm", "\347\272\277\346\235\241", nullptr));
        lineWidth->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LinePropertyForm: public Ui_LinePropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEPROPERTYFORM_H
