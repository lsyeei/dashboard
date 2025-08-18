/********************************************************************************
** Form generated from reading UI file 'gradientparamdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADIENTPARAMDIALOG_H
#define UI_GRADIENTPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gradientcolorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_GradientParamDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QWidget *preview;
    QWidget *radialParam;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSlider *focalRadius;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSlider *centerRadius;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *gradientType;
    QComboBox *spreadOption;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *presets;
    QSpacerItem *horizontalSpacer;
    GradientColorPicker *gradientColorPicker;

    void setupUi(QDialog *GradientParamDialog)
    {
        if (GradientParamDialog->objectName().isEmpty())
            GradientParamDialog->setObjectName("GradientParamDialog");
        GradientParamDialog->resize(468, 248);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GradientParamDialog->sizePolicy().hasHeightForWidth());
        GradientParamDialog->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(GradientParamDialog);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        preview = new QWidget(GradientParamDialog);
        preview->setObjectName("preview");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy1);
        preview->setMinimumSize(QSize(180, 180));
        preview->setAutoFillBackground(false);

        verticalLayout_2->addWidget(preview);

        radialParam = new QWidget(GradientParamDialog);
        radialParam->setObjectName("radialParam");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(radialParam->sizePolicy().hasHeightForWidth());
        radialParam->setSizePolicy(sizePolicy2);
        verticalLayout_3 = new QVBoxLayout(radialParam);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(radialParam);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_2);

        focalRadius = new QSlider(radialParam);
        focalRadius->setObjectName("focalRadius");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(focalRadius->sizePolicy().hasHeightForWidth());
        focalRadius->setSizePolicy(sizePolicy3);
        focalRadius->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_4->addWidget(focalRadius);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_3 = new QLabel(radialParam);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        centerRadius = new QSlider(radialParam);
        centerRadius->setObjectName("centerRadius");
        centerRadius->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_5->addWidget(centerRadius);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_2->addWidget(radialParam);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        gradientType = new QComboBox(GradientParamDialog);
        gradientType->setObjectName("gradientType");
        gradientType->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);
        gradientType->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        horizontalLayout_2->addWidget(gradientType);

        spreadOption = new QComboBox(GradientParamDialog);
        spreadOption->setObjectName("spreadOption");
        spreadOption->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);
        spreadOption->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        horizontalLayout_2->addWidget(spreadOption);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label = new QLabel(GradientParamDialog);
        label->setObjectName("label");
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label);

        presets = new QComboBox(GradientParamDialog);
        presets->setObjectName("presets");
        sizePolicy2.setHeightForWidth(presets->sizePolicy().hasHeightForWidth());
        presets->setSizePolicy(sizePolicy2);
        presets->setInsertPolicy(QComboBox::InsertPolicy::NoInsert);
        presets->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
        presets->setIconSize(QSize(64, 16));

        horizontalLayout_3->addWidget(presets);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        gradientColorPicker = new GradientColorPicker(GradientParamDialog);
        gradientColorPicker->setObjectName("gradientColorPicker");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(gradientColorPicker->sizePolicy().hasHeightForWidth());
        gradientColorPicker->setSizePolicy(sizePolicy4);

        verticalLayout->addWidget(gradientColorPicker);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(GradientParamDialog);

        QMetaObject::connectSlotsByName(GradientParamDialog);
    } // setupUi

    void retranslateUi(QDialog *GradientParamDialog)
    {
        GradientParamDialog->setWindowTitle(QCoreApplication::translate("GradientParamDialog", "\346\270\220\345\217\230\345\217\202\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("GradientParamDialog", "\347\204\246\347\202\271\345\215\212\345\276\204\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("GradientParamDialog", "\350\276\220\345\260\204\345\215\212\345\276\204\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("GradientParamDialog", "\351\242\204\347\275\256\351\242\234\350\211\262\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GradientParamDialog: public Ui_GradientParamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADIENTPARAMDIALOG_H
