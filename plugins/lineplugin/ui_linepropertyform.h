/********************************************************************************
** Form generated from reading UI file 'linepropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEPROPERTYFORM_H
#define UI_LINEPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "lineproperty.h"

QT_BEGIN_NAMESPACE

class Ui_LinePropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    BIComboBox *stateBox;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_9;
    QSpacerItem *verticalSpacer_2;
    QSpinBox *centerX;
    QSpinBox *centerY;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_10;
    QLabel *label_11;
    LineProperty *linePen;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *startTypeOptions;
    QLabel *label_3;
    QSpinBox *startSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *endTypeOptions;
    QLabel *label_4;
    QSpinBox *endSize;
    QWidget *corner;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *roundCorner;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *cornerSzie;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *flowAnimation;
    QWidget *animationParam;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *duration;
    QCheckBox *backward;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *dashLen;
    QLabel *label_7;
    QDoubleSpinBox *dashRatio;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LinePropertyForm)
    {
        if (LinePropertyForm->objectName().isEmpty())
            LinePropertyForm->setObjectName("LinePropertyForm");
        LinePropertyForm->resize(214, 410);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LinePropertyForm->sizePolicy().hasHeightForWidth());
        LinePropertyForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(LinePropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_8 = new QLabel(LinePropertyForm);
        label_8->setObjectName("label_8");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(label_8);

        stateBox = new BIComboBox(LinePropertyForm);
        stateBox->setObjectName("stateBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy2);

        horizontalLayout_7->addWidget(stateBox);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_9 = new QLabel(LinePropertyForm);
        label_9->setObjectName("label_9");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(label_9);

        verticalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(verticalSpacer_2);

        centerX = new QSpinBox(LinePropertyForm);
        centerX->setObjectName("centerX");
        centerX->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        centerX->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        centerX->setMinimum(-99999);
        centerX->setMaximum(999999);

        horizontalLayout_8->addWidget(centerX);

        centerY = new QSpinBox(LinePropertyForm);
        centerY->setObjectName("centerY");
        centerY->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        centerY->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        centerY->setProperty("showGroupSeparator", QVariant(false));
        centerY->setMinimum(-99999);
        centerY->setMaximum(999999);

        horizontalLayout_8->addWidget(centerY);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setContentsMargins(-1, 0, -1, 0);
        horizontalSpacer = new QSpacerItem(48, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);

        horizontalSpacer_3 = new QSpacerItem(40, 10, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        label_10 = new QLabel(LinePropertyForm);
        label_10->setObjectName("label_10");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);
        label_10->setMinimumSize(QSize(71, 0));
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(label_10);

        label_11 = new QLabel(LinePropertyForm);
        label_11->setObjectName("label_11");
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);
        label_11->setMinimumSize(QSize(71, 0));
        label_11->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_9->addWidget(label_11);


        verticalLayout_3->addLayout(horizontalLayout_9);


        horizontalLayout_10->addLayout(verticalLayout_3);


        verticalLayout->addLayout(horizontalLayout_10);

        linePen = new LineProperty(LinePropertyForm);
        linePen->setObjectName("linePen");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(linePen->sizePolicy().hasHeightForWidth());
        linePen->setSizePolicy(sizePolicy5);
        linePen->setMinimumSize(QSize(0, 60));
        linePen->setMaximumSize(QSize(16777215, 60));
        linePen->setShowLine(true);

        verticalLayout->addWidget(linePen);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(LinePropertyForm);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        startTypeOptions = new QComboBox(LinePropertyForm);
        startTypeOptions->setObjectName("startTypeOptions");
        startTypeOptions->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
        startTypeOptions->setIconSize(QSize(20, 10));

        horizontalLayout->addWidget(startTypeOptions);

        label_3 = new QLabel(LinePropertyForm);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_3);

        startSize = new QSpinBox(LinePropertyForm);
        startSize->setObjectName("startSize");
        startSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        startSize->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        startSize->setMinimum(5);
        startSize->setMaximum(99999);

        horizontalLayout->addWidget(startSize);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(LinePropertyForm);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);

        endTypeOptions = new QComboBox(LinePropertyForm);
        endTypeOptions->setObjectName("endTypeOptions");
        endTypeOptions->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
        endTypeOptions->setIconSize(QSize(20, 10));

        horizontalLayout_2->addWidget(endTypeOptions);

        label_4 = new QLabel(LinePropertyForm);
        label_4->setObjectName("label_4");
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_4);

        endSize = new QSpinBox(LinePropertyForm);
        endSize->setObjectName("endSize");
        endSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        endSize->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        endSize->setMinimum(5);
        endSize->setMaximum(99999);

        horizontalLayout_2->addWidget(endSize);


        verticalLayout->addLayout(horizontalLayout_2);

        corner = new QWidget(LinePropertyForm);
        corner->setObjectName("corner");
        sizePolicy.setHeightForWidth(corner->sizePolicy().hasHeightForWidth());
        corner->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(corner);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        roundCorner = new QCheckBox(corner);
        roundCorner->setObjectName("roundCorner");
        sizePolicy3.setHeightForWidth(roundCorner->sizePolicy().hasHeightForWidth());
        roundCorner->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(roundCorner);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        cornerSzie = new QSpinBox(corner);
        cornerSzie->setObjectName("cornerSzie");
        sizePolicy.setHeightForWidth(cornerSzie->sizePolicy().hasHeightForWidth());
        cornerSzie->setSizePolicy(sizePolicy);
        cornerSzie->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        cornerSzie->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        cornerSzie->setMaximum(99999);

        horizontalLayout_4->addWidget(cornerSzie);


        verticalLayout->addWidget(corner);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        flowAnimation = new QCheckBox(LinePropertyForm);
        flowAnimation->setObjectName("flowAnimation");
        sizePolicy.setHeightForWidth(flowAnimation->sizePolicy().hasHeightForWidth());
        flowAnimation->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(flowAnimation);


        verticalLayout->addLayout(horizontalLayout_3);

        animationParam = new QWidget(LinePropertyForm);
        animationParam->setObjectName("animationParam");
        sizePolicy.setHeightForWidth(animationParam->sizePolicy().hasHeightForWidth());
        animationParam->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(animationParam);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_5 = new QLabel(animationParam);
        label_5->setObjectName("label_5");
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(label_5);

        duration = new QSpinBox(animationParam);
        duration->setObjectName("duration");
        QSizePolicy sizePolicy6(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(duration->sizePolicy().hasHeightForWidth());
        duration->setSizePolicy(sizePolicy6);
        duration->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        duration->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        duration->setMinimum(100);
        duration->setMaximum(60000);
        duration->setSingleStep(100);
        duration->setValue(500);

        horizontalLayout_5->addWidget(duration);

        backward = new QCheckBox(animationParam);
        backward->setObjectName("backward");

        horizontalLayout_5->addWidget(backward);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_6 = new QLabel(animationParam);
        label_6->setObjectName("label_6");
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(label_6);

        dashLen = new QSpinBox(animationParam);
        dashLen->setObjectName("dashLen");
        QSizePolicy sizePolicy7(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(dashLen->sizePolicy().hasHeightForWidth());
        dashLen->setSizePolicy(sizePolicy7);
        dashLen->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dashLen->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        dashLen->setMinimum(1);
        dashLen->setMaximum(9999);

        horizontalLayout_6->addWidget(dashLen);

        label_7 = new QLabel(animationParam);
        label_7->setObjectName("label_7");
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(label_7);

        dashRatio = new QDoubleSpinBox(animationParam);
        dashRatio->setObjectName("dashRatio");
        QSizePolicy sizePolicy8(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(dashRatio->sizePolicy().hasHeightForWidth());
        dashRatio->setSizePolicy(sizePolicy8);
        dashRatio->setMinimumSize(QSize(50, 0));
        dashRatio->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        dashRatio->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        dashRatio->setDecimals(2);
        dashRatio->setMaximum(1.000000000000000);
        dashRatio->setSingleStep(0.100000000000000);
        dashRatio->setValue(0.500000000000000);

        horizontalLayout_6->addWidget(dashRatio);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout->addWidget(animationParam);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(LinePropertyForm);

        QMetaObject::connectSlotsByName(LinePropertyForm);
    } // setupUi

    void retranslateUi(QWidget *LinePropertyForm)
    {
        LinePropertyForm->setWindowTitle(QCoreApplication::translate("LinePropertyForm", "Form", nullptr));
        label_8->setText(QCoreApplication::translate("LinePropertyForm", "\347\212\266\346\200\201", nullptr));
        label_9->setText(QCoreApplication::translate("LinePropertyForm", "\344\270\255\345\277\203\344\275\215\347\275\256", nullptr));
        centerX->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        centerY->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        centerY->setPrefix(QString());
        label_10->setText(QCoreApplication::translate("LinePropertyForm", "x", nullptr));
        label_11->setText(QCoreApplication::translate("LinePropertyForm", "y", nullptr));
        label->setText(QCoreApplication::translate("LinePropertyForm", "\350\265\267\347\202\271", nullptr));
        label_3->setText(QCoreApplication::translate("LinePropertyForm", "\345\244\247\345\260\217", nullptr));
        startSize->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        label_2->setText(QCoreApplication::translate("LinePropertyForm", "\347\273\210\347\202\271", nullptr));
        label_4->setText(QCoreApplication::translate("LinePropertyForm", "\345\244\247\345\260\217", nullptr));
        endSize->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        roundCorner->setText(QCoreApplication::translate("LinePropertyForm", "\345\234\206\346\213\220\350\247\222", nullptr));
        cornerSzie->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        flowAnimation->setText(QCoreApplication::translate("LinePropertyForm", "\346\265\201\345\212\250\345\212\250\347\224\273", nullptr));
        label_5->setText(QCoreApplication::translate("LinePropertyForm", "\351\200\237\345\272\246", nullptr));
        duration->setSuffix(QCoreApplication::translate("LinePropertyForm", " ms", nullptr));
        duration->setPrefix(QString());
        backward->setText(QCoreApplication::translate("LinePropertyForm", "\345\217\215\345\220\221", nullptr));
        label_6->setText(QCoreApplication::translate("LinePropertyForm", "\347\272\277\351\225\277", nullptr));
        dashLen->setSuffix(QCoreApplication::translate("LinePropertyForm", " px", nullptr));
        label_7->setText(QCoreApplication::translate("LinePropertyForm", "\345\215\240\347\251\272\346\257\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LinePropertyForm: public Ui_LinePropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEPROPERTYFORM_H
