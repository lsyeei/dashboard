/********************************************************************************
** Form generated from reading UI file 'rectpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTPROPERTYFORM_H
#define UI_RECTPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "fillproperty.h"
#include "lineproperty.h"
#include "posproperty.h"

QT_BEGIN_NAMESPACE

class Ui_RectPropertyForm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    BIComboBox *stateBox;
    QFrame *line_4;
    PosProperty *posProperty;
    QFrame *line_2;
    LineProperty *lineProperty;
    QFrame *line;
    FillProperty *fillProperty;
    QFrame *line_3;
    QHBoxLayout *roundLayout;
    QCheckBox *roundChecked;
    QSpacerItem *roundSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *rotateSpacer;
    QDoubleSpinBox *rotation;
    QWidget *extendWidget;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *RectPropertyForm)
    {
        if (RectPropertyForm->objectName().isEmpty())
            RectPropertyForm->setObjectName("RectPropertyForm");
        RectPropertyForm->setEnabled(true);
        RectPropertyForm->resize(223, 524);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RectPropertyForm->sizePolicy().hasHeightForWidth());
        RectPropertyForm->setSizePolicy(sizePolicy);
        RectPropertyForm->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(RectPropertyForm);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, -1, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(RectPropertyForm);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        stateBox = new BIComboBox(RectPropertyForm);
        stateBox->setObjectName("stateBox");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(stateBox);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout_3);

        line_4 = new QFrame(RectPropertyForm);
        line_4->setObjectName("line_4");
        sizePolicy2.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy2);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_4->setLineWidth(1);
        line_4->setFrameShape(QFrame::Shape::HLine);

        verticalLayout->addWidget(line_4);

        posProperty = new PosProperty(RectPropertyForm);
        posProperty->setObjectName("posProperty");
        sizePolicy.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy);
        posProperty->setMinimumSize(QSize(142, 123));

        verticalLayout->addWidget(posProperty);

        line_2 = new QFrame(RectPropertyForm);
        line_2->setObjectName("line_2");
        sizePolicy2.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy2);
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        lineProperty = new LineProperty(RectPropertyForm);
        lineProperty->setObjectName("lineProperty");
        sizePolicy.setHeightForWidth(lineProperty->sizePolicy().hasHeightForWidth());
        lineProperty->setSizePolicy(sizePolicy);
        lineProperty->setMinimumSize(QSize(0, 0));
        lineProperty->setMaximumSize(QSize(16777215, 16777215));
        lineProperty->setShowLine(true);

        verticalLayout->addWidget(lineProperty);

        line = new QFrame(RectPropertyForm);
        line->setObjectName("line");
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::Shape::HLine);

        verticalLayout->addWidget(line);

        fillProperty = new FillProperty(RectPropertyForm);
        fillProperty->setObjectName("fillProperty");
        fillProperty->setEnabled(true);
        sizePolicy.setHeightForWidth(fillProperty->sizePolicy().hasHeightForWidth());
        fillProperty->setSizePolicy(sizePolicy);
        fillProperty->setMinimumSize(QSize(173, 79));
        fillProperty->setMaximumSize(QSize(16777215, 16777215));
        fillProperty->setProperty("fill", QVariant(true));
        fillProperty->setBrushStyle(Qt::BrushStyle::SolidPattern);

        verticalLayout->addWidget(fillProperty);

        line_3 = new QFrame(RectPropertyForm);
        line_3->setObjectName("line_3");
        sizePolicy2.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy2);
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        roundLayout = new QHBoxLayout();
        roundLayout->setSpacing(6);
        roundLayout->setObjectName("roundLayout");
        roundLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        roundLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(RectPropertyForm);
        roundChecked->setObjectName("roundChecked");
        sizePolicy2.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy2);

        roundLayout->addWidget(roundChecked);

        roundSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        roundLayout->addItem(roundSpacer);

        roundSize = new QSpinBox(RectPropertyForm);
        roundSize->setObjectName("roundSize");
        sizePolicy2.setHeightForWidth(roundSize->sizePolicy().hasHeightForWidth());
        roundSize->setSizePolicy(sizePolicy2);
        roundSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        roundSize->setMaximum(65536);

        roundLayout->addWidget(roundSize);


        verticalLayout->addLayout(roundLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(RectPropertyForm);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(label);

        rotateSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(rotateSpacer);

        rotation = new QDoubleSpinBox(RectPropertyForm);
        rotation->setObjectName("rotation");
        sizePolicy2.setHeightForWidth(rotation->sizePolicy().hasHeightForWidth());
        rotation->setSizePolicy(sizePolicy2);
        rotation->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        rotation->setDecimals(1);
        rotation->setMinimum(-360.000000000000000);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        extendWidget = new QWidget(RectPropertyForm);
        extendWidget->setObjectName("extendWidget");
        sizePolicy.setHeightForWidth(extendWidget->sizePolicy().hasHeightForWidth());
        extendWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(extendWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, 6, 0, 6);

        verticalLayout->addWidget(extendWidget);


        retranslateUi(RectPropertyForm);

        QMetaObject::connectSlotsByName(RectPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *RectPropertyForm)
    {
        RectPropertyForm->setWindowTitle(QCoreApplication::translate("RectPropertyForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("RectPropertyForm", "\347\212\266\346\200\201", nullptr));
        roundChecked->setText(QCoreApplication::translate("RectPropertyForm", "\345\234\206\350\247\222", nullptr));
        roundSize->setSuffix(QCoreApplication::translate("RectPropertyForm", " px", nullptr));
        label->setText(QCoreApplication::translate("RectPropertyForm", "\346\227\213\350\275\254", nullptr));
        rotation->setSuffix(QCoreApplication::translate("RectPropertyForm", " \302\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RectPropertyForm: public Ui_RectPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTPROPERTYFORM_H
