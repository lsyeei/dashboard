/********************************************************************************
** Form generated from reading UI file 'gradientcolorpickerform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADIENTCOLORPICKERFORM_H
#define UI_GRADIENTCOLORPICKERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_GradientColorPickerForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *colorView;
    QWidget *markPanel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    ColorPicker *colorPicker;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QSpinBox *colorAlpha;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *colorPos;
    QSpacerItem *horizontalSpacer;
    QPushButton *delColor;

    void setupUi(QWidget *GradientColorPickerForm)
    {
        if (GradientColorPickerForm->objectName().isEmpty())
            GradientColorPickerForm->setObjectName("GradientColorPickerForm");
        GradientColorPickerForm->resize(261, 161);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GradientColorPickerForm->sizePolicy().hasHeightForWidth());
        GradientColorPickerForm->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(GradientColorPickerForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        colorView = new QWidget(GradientColorPickerForm);
        colorView->setObjectName("colorView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorView->sizePolicy().hasHeightForWidth());
        colorView->setSizePolicy(sizePolicy1);
        colorView->setMinimumSize(QSize(0, 20));

        verticalLayout_3->addWidget(colorView);

        markPanel = new QWidget(GradientColorPickerForm);
        markPanel->setObjectName("markPanel");
        sizePolicy1.setHeightForWidth(markPanel->sizePolicy().hasHeightForWidth());
        markPanel->setSizePolicy(sizePolicy1);
        markPanel->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(markPanel);


        verticalLayout_2->addLayout(verticalLayout_3);

        groupBox = new QGroupBox(GradientColorPickerForm);
        groupBox->setObjectName("groupBox");
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(6, -1, 6, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label = new QLabel(groupBox);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        colorPicker = new ColorPicker(groupBox);
        colorPicker->setObjectName("colorPicker");
        sizePolicy1.setHeightForWidth(colorPicker->sizePolicy().hasHeightForWidth());
        colorPicker->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(colorPicker);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_3);

        colorAlpha = new QSpinBox(groupBox);
        colorAlpha->setObjectName("colorAlpha");
        sizePolicy1.setHeightForWidth(colorAlpha->sizePolicy().hasHeightForWidth());
        colorAlpha->setSizePolicy(sizePolicy1);
        colorAlpha->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        colorAlpha->setMaximum(255);

        horizontalLayout->addWidget(colorAlpha);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        colorPos = new QSpinBox(groupBox);
        colorPos->setObjectName("colorPos");
        sizePolicy1.setHeightForWidth(colorPos->sizePolicy().hasHeightForWidth());
        colorPos->setSizePolicy(sizePolicy1);
        colorPos->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        colorPos->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        colorPos->setMaximum(100);

        horizontalLayout_2->addWidget(colorPos);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        delColor = new QPushButton(groupBox);
        delColor->setObjectName("delColor");
        sizePolicy1.setHeightForWidth(delColor->sizePolicy().hasHeightForWidth());
        delColor->setSizePolicy(sizePolicy1);
        delColor->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        delColor->setContextMenuPolicy(Qt::ContextMenuPolicy::NoContextMenu);

        horizontalLayout_2->addWidget(delColor);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox);


        retranslateUi(GradientColorPickerForm);

        QMetaObject::connectSlotsByName(GradientColorPickerForm);
    } // setupUi

    void retranslateUi(QWidget *GradientColorPickerForm)
    {
        GradientColorPickerForm->setWindowTitle(QCoreApplication::translate("GradientColorPickerForm", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("GradientColorPickerForm", "\350\211\262\346\240\207", nullptr));
        label->setText(QCoreApplication::translate("GradientColorPickerForm", "\351\242\234\350\211\262\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("GradientColorPickerForm", "\351\200\217\346\230\216\345\272\246\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("GradientColorPickerForm", "\344\275\215\347\275\256\357\274\232", nullptr));
        colorPos->setSuffix(QCoreApplication::translate("GradientColorPickerForm", "%", nullptr));
        delColor->setText(QCoreApplication::translate("GradientColorPickerForm", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GradientColorPickerForm: public Ui_GradientColorPickerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADIENTCOLORPICKERFORM_H
