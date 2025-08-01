/********************************************************************************
** Form generated from reading UI file 'grouppropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPPROPERTYFORM_H
#define UI_GROUPPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bicombobox.h"
#include "fillproperty.h"
#include "lineproperty.h"
#include "posproperty.h"

QT_BEGIN_NAMESPACE

class Ui_GroupPropertyForm
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
    QHBoxLayout *horizontalLayout;
    QCheckBox *roundChecked;
    QSpacerItem *horizontalSpacer;
    QSpinBox *roundSize;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *rotation;
    QCheckBox *mergeCheck;
    QWidget *mergeOptions;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *unit;
    QToolButton *intersect;
    QToolButton *subtract;
    QToolButton *exclude;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *GroupPropertyForm)
    {
        if (GroupPropertyForm->objectName().isEmpty())
            GroupPropertyForm->setObjectName("GroupPropertyForm");
        GroupPropertyForm->resize(320, 517);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GroupPropertyForm->sizePolicy().hasHeightForWidth());
        GroupPropertyForm->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(GroupPropertyForm);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout->setContentsMargins(0, -1, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_2 = new QLabel(GroupPropertyForm);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label_2);

        stateBox = new BIComboBox(GroupPropertyForm);
        stateBox->setObjectName("stateBox");
        sizePolicy1.setHeightForWidth(stateBox->sizePolicy().hasHeightForWidth());
        stateBox->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(stateBox);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout_3);

        line_4 = new QFrame(GroupPropertyForm);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_4);

        posProperty = new PosProperty(GroupPropertyForm);
        posProperty->setObjectName("posProperty");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(posProperty->sizePolicy().hasHeightForWidth());
        posProperty->setSizePolicy(sizePolicy2);
        posProperty->setMinimumSize(QSize(0, 0));
        posProperty->setAspectRatio(true);

        verticalLayout->addWidget(posProperty);

        line_2 = new QFrame(GroupPropertyForm);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        lineProperty = new LineProperty(GroupPropertyForm);
        lineProperty->setObjectName("lineProperty");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineProperty->sizePolicy().hasHeightForWidth());
        lineProperty->setSizePolicy(sizePolicy3);
        lineProperty->setMinimumSize(QSize(0, 22));
        lineProperty->setMaximumSize(QSize(16777215, 22));
        lineProperty->setShowLine(false);

        verticalLayout->addWidget(lineProperty);

        line = new QFrame(GroupPropertyForm);
        line->setObjectName("line");
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::Shape::HLine);

        verticalLayout->addWidget(line);

        fillProperty = new FillProperty(GroupPropertyForm);
        fillProperty->setObjectName("fillProperty");
        sizePolicy2.setHeightForWidth(fillProperty->sizePolicy().hasHeightForWidth());
        fillProperty->setSizePolicy(sizePolicy2);
        fillProperty->setMinimumSize(QSize(0, 80));
        fillProperty->setMaximumSize(QSize(16777215, 80));
        fillProperty->setProperty("fill", QVariant(true));

        verticalLayout->addWidget(fillProperty);

        line_3 = new QFrame(GroupPropertyForm);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        roundChecked = new QCheckBox(GroupPropertyForm);
        roundChecked->setObjectName("roundChecked");
        sizePolicy.setHeightForWidth(roundChecked->sizePolicy().hasHeightForWidth());
        roundChecked->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(roundChecked);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        roundSize = new QSpinBox(GroupPropertyForm);
        roundSize->setObjectName("roundSize");
        sizePolicy.setHeightForWidth(roundSize->sizePolicy().hasHeightForWidth());
        roundSize->setSizePolicy(sizePolicy);
        roundSize->setMaximum(65536);

        horizontalLayout->addWidget(roundSize);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(GroupPropertyForm);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        rotation = new QDoubleSpinBox(GroupPropertyForm);
        rotation->setObjectName("rotation");
        rotation->setDecimals(1);
        rotation->setMinimum(-360.000000000000000);
        rotation->setMaximum(360.000000000000000);

        horizontalLayout_2->addWidget(rotation);


        verticalLayout->addLayout(horizontalLayout_2);

        mergeCheck = new QCheckBox(GroupPropertyForm);
        mergeCheck->setObjectName("mergeCheck");

        verticalLayout->addWidget(mergeCheck);

        mergeOptions = new QWidget(GroupPropertyForm);
        mergeOptions->setObjectName("mergeOptions");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(mergeOptions->sizePolicy().hasHeightForWidth());
        mergeOptions->setSizePolicy(sizePolicy4);
        horizontalLayout_4 = new QHBoxLayout(mergeOptions);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        horizontalLayout_4->setContentsMargins(6, 0, 6, 6);
        unit = new QToolButton(mergeOptions);
        unit->setObjectName("unit");
        sizePolicy1.setHeightForWidth(unit->sizePolicy().hasHeightForWidth());
        unit->setSizePolicy(sizePolicy1);
        QIcon icon;
        icon.addFile(QString::fromUtf8("icons/shapes_unite.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        unit->setIcon(icon);
        unit->setCheckable(true);
        unit->setAutoExclusive(true);
        unit->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(unit);

        intersect = new QToolButton(mergeOptions);
        intersect->setObjectName("intersect");
        sizePolicy1.setHeightForWidth(intersect->sizePolicy().hasHeightForWidth());
        intersect->setSizePolicy(sizePolicy1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("icons/shapes_intersect.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        intersect->setIcon(icon1);
        intersect->setCheckable(true);
        intersect->setAutoExclusive(true);
        intersect->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(intersect);

        subtract = new QToolButton(mergeOptions);
        subtract->setObjectName("subtract");
        sizePolicy1.setHeightForWidth(subtract->sizePolicy().hasHeightForWidth());
        subtract->setSizePolicy(sizePolicy1);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icons/shapes_minus_back.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        subtract->setIcon(icon2);
        subtract->setCheckable(true);
        subtract->setAutoExclusive(true);
        subtract->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(subtract);

        exclude = new QToolButton(mergeOptions);
        exclude->setObjectName("exclude");
        sizePolicy1.setHeightForWidth(exclude->sizePolicy().hasHeightForWidth());
        exclude->setSizePolicy(sizePolicy1);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("icons/shapes_exclude.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        exclude->setIcon(icon3);
        exclude->setCheckable(true);
        exclude->setAutoExclusive(true);
        exclude->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextBesideIcon);

        horizontalLayout_4->addWidget(exclude);


        verticalLayout->addWidget(mergeOptions);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(GroupPropertyForm);

        QMetaObject::connectSlotsByName(GroupPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *GroupPropertyForm)
    {
        GroupPropertyForm->setWindowTitle(QCoreApplication::translate("GroupPropertyForm", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("GroupPropertyForm", "\347\212\266\346\200\201", nullptr));
        roundChecked->setText(QCoreApplication::translate("GroupPropertyForm", "\345\234\206\350\247\222", nullptr));
        roundSize->setSuffix(QCoreApplication::translate("GroupPropertyForm", "px", nullptr));
        label->setText(QCoreApplication::translate("GroupPropertyForm", "\346\227\213\350\275\254", nullptr));
        rotation->setSuffix(QCoreApplication::translate("GroupPropertyForm", "\302\260C", nullptr));
        mergeCheck->setText(QCoreApplication::translate("GroupPropertyForm", "\350\236\215\345\220\210", nullptr));
#if QT_CONFIG(tooltip)
        unit->setToolTip(QCoreApplication::translate("GroupPropertyForm", "\345\220\210\345\271\266", nullptr));
#endif // QT_CONFIG(tooltip)
        unit->setText(QCoreApplication::translate("GroupPropertyForm", "\345\220\210\345\271\266", nullptr));
#if QT_CONFIG(tooltip)
        intersect->setToolTip(QCoreApplication::translate("GroupPropertyForm", "\344\272\244\351\233\206", nullptr));
#endif // QT_CONFIG(tooltip)
        intersect->setText(QCoreApplication::translate("GroupPropertyForm", "\344\272\244\351\233\206", nullptr));
#if QT_CONFIG(tooltip)
        subtract->setToolTip(QCoreApplication::translate("GroupPropertyForm", "\345\267\256\351\233\206", nullptr));
#endif // QT_CONFIG(tooltip)
        subtract->setText(QCoreApplication::translate("GroupPropertyForm", "\345\267\256\351\233\206", nullptr));
#if QT_CONFIG(tooltip)
        exclude->setToolTip(QCoreApplication::translate("GroupPropertyForm", "\346\216\222\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
        exclude->setText(QCoreApplication::translate("GroupPropertyForm", "\346\216\222\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupPropertyForm: public Ui_GroupPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPPROPERTYFORM_H
