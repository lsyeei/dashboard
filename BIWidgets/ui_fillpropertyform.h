/********************************************************************************
** Form generated from reading UI file 'fillpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILLPROPERTYFORM_H
#define UI_FILLPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_FillPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *fillChecked;
    QComboBox *brushStyle1;
    ColorPicker *baseColor;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *gradientChecked;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *gradientBtn;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *imageChecked;
    QLabel *fileName;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *FillPropertyForm)
    {
        if (FillPropertyForm->objectName().isEmpty())
            FillPropertyForm->setObjectName("FillPropertyForm");
        FillPropertyForm->resize(196, 148);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FillPropertyForm->sizePolicy().hasHeightForWidth());
        FillPropertyForm->setSizePolicy(sizePolicy);
        FillPropertyForm->setMinimumSize(QSize(0, 0));
        FillPropertyForm->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(FillPropertyForm);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        fillChecked = new QCheckBox(FillPropertyForm);
        fillChecked->setObjectName("fillChecked");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fillChecked->sizePolicy().hasHeightForWidth());
        fillChecked->setSizePolicy(sizePolicy1);
        fillChecked->setMinimumSize(QSize(0, 22));
        fillChecked->setChecked(false);

        horizontalLayout->addWidget(fillChecked);

        brushStyle1 = new QComboBox(FillPropertyForm);
        brushStyle1->setObjectName("brushStyle1");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(brushStyle1->sizePolicy().hasHeightForWidth());
        brushStyle1->setSizePolicy(sizePolicy2);
        brushStyle1->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
        brushStyle1->setIconSize(QSize(16, 16));
        brushStyle1->setFrame(true);

        horizontalLayout->addWidget(brushStyle1);

        baseColor = new ColorPicker(FillPropertyForm);
        baseColor->setObjectName("baseColor");
        sizePolicy1.setHeightForWidth(baseColor->sizePolicy().hasHeightForWidth());
        baseColor->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(baseColor);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        gradientChecked = new QRadioButton(FillPropertyForm);
        gradientChecked->setObjectName("gradientChecked");
        sizePolicy1.setHeightForWidth(gradientChecked->sizePolicy().hasHeightForWidth());
        gradientChecked->setSizePolicy(sizePolicy1);
        gradientChecked->setMinimumSize(QSize(0, 22));
        gradientChecked->setChecked(false);
        gradientChecked->setAutoExclusive(false);

        horizontalLayout_2->addWidget(gradientChecked);

        horizontalSpacer_2 = new QSpacerItem(10, 0, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        gradientBtn = new QPushButton(FillPropertyForm);
        gradientBtn->setObjectName("gradientBtn");
        sizePolicy1.setHeightForWidth(gradientBtn->sizePolicy().hasHeightForWidth());
        gradientBtn->setSizePolicy(sizePolicy1);
        gradientBtn->setMinimumSize(QSize(90, 0));
        gradientBtn->setText(QString::fromUtf8(""));
        gradientBtn->setFlat(true);

        horizontalLayout_2->addWidget(gradientBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_3->setContentsMargins(-1, -1, 0, -1);
        imageChecked = new QRadioButton(FillPropertyForm);
        imageChecked->setObjectName("imageChecked");
        sizePolicy1.setHeightForWidth(imageChecked->sizePolicy().hasHeightForWidth());
        imageChecked->setSizePolicy(sizePolicy1);
        imageChecked->setAutoExclusive(false);

        horizontalLayout_3->addWidget(imageChecked);

        fileName = new QLabel(FillPropertyForm);
        fileName->setObjectName("fileName");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fileName->sizePolicy().hasHeightForWidth());
        fileName->setSizePolicy(sizePolicy3);
        fileName->setMinimumSize(QSize(102, 77));
        fileName->setMaximumSize(QSize(1024, 768));
        fileName->setSizeIncrement(QSize(0, 0));
        fileName->setBaseSize(QSize(0, 0));
        fileName->setAcceptDrops(true);
        fileName->setAutoFillBackground(false);
        fileName->setFrameShape(QFrame::Shape::Box);
        fileName->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_3->addWidget(fileName);

        horizontalSpacer = new QSpacerItem(40, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(FillPropertyForm);

        QMetaObject::connectSlotsByName(FillPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *FillPropertyForm)
    {
        FillPropertyForm->setWindowTitle(QCoreApplication::translate("FillPropertyForm", "Form", nullptr));
        fillChecked->setText(QCoreApplication::translate("FillPropertyForm", "\345\241\253\345\205\205", nullptr));
        gradientChecked->setText(QCoreApplication::translate("FillPropertyForm", "\346\270\220\345\217\230", nullptr));
        imageChecked->setText(QCoreApplication::translate("FillPropertyForm", "\345\233\276\347\211\207", nullptr));
        fileName->setText(QCoreApplication::translate("FillPropertyForm", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FillPropertyForm: public Ui_FillPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILLPROPERTYFORM_H
