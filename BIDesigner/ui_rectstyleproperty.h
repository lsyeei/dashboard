/**
* This file is part of the dashboard library
* 
* Copyright 2025 lishiying  lsyeei@163.com
* 
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/********************************************************************************
** Form generated from reading UI file 'rectstyleproperty.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECTSTYLEPROPERTY_H
#define UI_RECTSTYLEPROPERTY_H

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
#include "fillproperty.h"
#include "lineproperty.h"
#include "posproperty.h"

QT_BEGIN_NAMESPACE

class Ui_RectStyleProperty
{
public:
    QVBoxLayout *verticalLayout;
    PosProperty *posProperty;
    QFrame *line_2;
    LineProperty *lineProperty;
    QFrame *line;
    FillProperty *fillProperty;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *roundChecked;
    QSpacerItem *horizontalSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *rotation;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *RectStyleProperty)
    {
        if (RectStyleProperty->objectName().isEmpty())
            RectStyleProperty->setObjectName("RectStyleProperty");
        RectStyleProperty->resize(256, 489);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RectStyleProperty->sizePolicy().hasHeightForWidth());
        RectStyleProperty->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(RectStyleProperty);
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, -1, 0, 0);
        posProperty = new PosProperty(RectStyleProperty);
        posProperty->setObjectName("posProperty");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy1);
        posProperty->setMinimumSize(QSize(0, 105));

        verticalLayout->addWidget(posProperty);

        line_2 = new QFrame(RectStyleProperty);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        lineProperty = new LineProperty(RectStyleProperty);
        lineProperty->setObjectName("lineProperty");
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineProperty->sizePolicy().hasHeightForWidth());
        lineProperty->setSizePolicy(sizePolicy2);
        lineProperty->setMinimumSize(QSize(0, 52));
        lineProperty->setMaximumSize(QSize(16777215, 52));
        lineProperty->setShowLine(true);

        verticalLayout->addWidget(lineProperty);

        line = new QFrame(RectStyleProperty);
        line->setObjectName("line");
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        fillProperty = new FillProperty(RectStyleProperty);
        fillProperty->setObjectName("fillProperty");
        sizePolicy2.setHeightForWidth(fillProperty->sizePolicy().hasHeightForWidth());
        fillProperty->setSizePolicy(sizePolicy2);
        fillProperty->setMinimumSize(QSize(0, 80));
        fillProperty->setMaximumSize(QSize(16777215, 80));
        fillProperty->setProperty("fill", QVariant(true));

        verticalLayout->addWidget(fillProperty);

        line_3 = new QFrame(RectStyleProperty);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(RectStyleProperty);
        roundChecked->setObjectName("roundChecked");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(roundChecked);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        roundSize = new QSpinBox(RectStyleProperty);
        roundSize->setObjectName("roundSize");
        sizePolicy3.setHeightForWidth(roundSize->sizePolicy().hasHeightForWidth());
        roundSize->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(roundSize);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(RectStyleProperty);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        rotation = new QDoubleSpinBox(RectStyleProperty);
        rotation->setObjectName("rotation");
        rotation->setDecimals(1);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(RectStyleProperty);

        QMetaObject::connectSlotsByName(RectStyleProperty);
    } // setupUi

    void retranslateUi(QWidget *RectStyleProperty)
    {
        RectStyleProperty->setWindowTitle(QCoreApplication::translate("RectStyleProperty", "Form", nullptr));
        roundChecked->setText(QCoreApplication::translate("RectStyleProperty", "\345\234\206\350\247\222", nullptr));
        roundSize->setSuffix(QCoreApplication::translate("RectStyleProperty", "px", nullptr));
        label->setText(QCoreApplication::translate("RectStyleProperty", "\346\227\213\350\275\254", nullptr));
        rotation->setSuffix(QCoreApplication::translate("RectStyleProperty", "\302\260C", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RectStyleProperty: public Ui_RectStyleProperty {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECTSTYLEPROPERTY_H
