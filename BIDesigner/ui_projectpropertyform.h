/********************************************************************************
** Form generated from reading UI file 'projectpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTPROPERTYFORM_H
#define UI_PROJECTPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"
#include "fillproperty.h"

QT_BEGIN_NAMESPACE

class Ui_ProjectPropertyForm
{
public:
    QVBoxLayout *verticalLayout_6;
    QGroupBox *projectBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *projectName;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *author;
    QGroupBox *pageBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *pageName;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSpinBox *pageWidth;
    QLabel *label_5;
    QSpinBox *pageHeight;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    FillProperty *fillProperty;
    QGroupBox *viewBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *showGrid;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *lineWidth;
    ColorPicker *lineColor;
    QCheckBox *showRefLine;
    QCheckBox *showRuer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ProjectPropertyForm)
    {
        if (ProjectPropertyForm->objectName().isEmpty())
            ProjectPropertyForm->setObjectName("ProjectPropertyForm");
        ProjectPropertyForm->resize(266, 636);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProjectPropertyForm->sizePolicy().hasHeightForWidth());
        ProjectPropertyForm->setSizePolicy(sizePolicy);
        verticalLayout_6 = new QVBoxLayout(ProjectPropertyForm);
        verticalLayout_6->setSpacing(9);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout_6->setContentsMargins(0, -1, 0, -1);
        projectBox = new QGroupBox(ProjectPropertyForm);
        projectBox->setObjectName("projectBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(projectBox->sizePolicy().hasHeightForWidth());
        projectBox->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(projectBox);
        verticalLayout_3->setSpacing(9);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(-1, 9, -1, 9);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(projectBox);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label);

        projectName = new QLineEdit(projectBox);
        projectName->setObjectName("projectName");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(projectName->sizePolicy().hasHeightForWidth());
        projectName->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(projectName);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(projectBox);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(label_3);

        author = new QLineEdit(projectBox);
        author->setObjectName("author");
        sizePolicy3.setHeightForWidth(author->sizePolicy().hasHeightForWidth());
        author->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(author);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_6->addWidget(projectBox);

        pageBox = new QGroupBox(ProjectPropertyForm);
        pageBox->setObjectName("pageBox");
        sizePolicy1.setHeightForWidth(pageBox->sizePolicy().hasHeightForWidth());
        pageBox->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(pageBox);
        verticalLayout_2->setSpacing(9);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 9, -1, 9);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(pageBox);
        label_2->setObjectName("label_2");
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(label_2);

        pageName = new QLineEdit(pageBox);
        pageName->setObjectName("pageName");
        sizePolicy3.setHeightForWidth(pageName->sizePolicy().hasHeightForWidth());
        pageName->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(pageName);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_4 = new QLabel(pageBox);
        label_4->setObjectName("label_4");

        horizontalLayout_6->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_6 = new QLabel(pageBox);
        label_6->setObjectName("label_6");
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_6);

        pageWidth = new QSpinBox(pageBox);
        pageWidth->setObjectName("pageWidth");
        sizePolicy.setHeightForWidth(pageWidth->sizePolicy().hasHeightForWidth());
        pageWidth->setSizePolicy(sizePolicy);
        pageWidth->setMaximumSize(QSize(16777215, 16777215));
        pageWidth->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        pageWidth->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        pageWidth->setMinimum(100);
        pageWidth->setMaximum(16777215);

        horizontalLayout_4->addWidget(pageWidth);

        label_5 = new QLabel(pageBox);
        label_5->setObjectName("label_5");
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(label_5);

        pageHeight = new QSpinBox(pageBox);
        pageHeight->setObjectName("pageHeight");
        sizePolicy.setHeightForWidth(pageHeight->sizePolicy().hasHeightForWidth());
        pageHeight->setSizePolicy(sizePolicy);
        pageHeight->setWrapping(false);
        pageHeight->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        pageHeight->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        pageHeight->setMinimum(100);
        pageHeight->setMaximum(16777215);

        horizontalLayout_4->addWidget(pageHeight);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_7 = new QLabel(pageBox);
        label_7->setObjectName("label_7");

        horizontalLayout_7->addWidget(label_7);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        fillProperty = new FillProperty(pageBox);
        fillProperty->setObjectName("fillProperty");
        fillProperty->setProperty("fill", QVariant(true));
        fillProperty->setBrushStyle(Qt::BrushStyle::SolidPattern);
        fillProperty->setBaseColor(QColor(24, 20, 29));

        horizontalLayout_8->addWidget(fillProperty);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_6->addWidget(pageBox);

        viewBox = new QGroupBox(ProjectPropertyForm);
        viewBox->setObjectName("viewBox");
        sizePolicy1.setHeightForWidth(viewBox->sizePolicy().hasHeightForWidth());
        viewBox->setSizePolicy(sizePolicy1);
        verticalLayout_5 = new QVBoxLayout(viewBox);
        verticalLayout_5->setSpacing(9);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(-1, 9, -1, 9);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        showGrid = new QCheckBox(viewBox);
        showGrid->setObjectName("showGrid");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(showGrid->sizePolicy().hasHeightForWidth());
        showGrid->setSizePolicy(sizePolicy4);
        showGrid->setChecked(true);

        horizontalLayout_5->addWidget(showGrid);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        lineWidth = new QDoubleSpinBox(viewBox);
        lineWidth->setObjectName("lineWidth");
        sizePolicy3.setHeightForWidth(lineWidth->sizePolicy().hasHeightForWidth());
        lineWidth->setSizePolicy(sizePolicy3);
        lineWidth->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineWidth->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        lineWidth->setDecimals(1);
        lineWidth->setMinimum(0.500000000000000);
        lineWidth->setSingleStep(0.500000000000000);

        horizontalLayout_5->addWidget(lineWidth);

        lineColor = new ColorPicker(viewBox);
        lineColor->setObjectName("lineColor");
        sizePolicy4.setHeightForWidth(lineColor->sizePolicy().hasHeightForWidth());
        lineColor->setSizePolicy(sizePolicy4);
        lineColor->setColor(QColor(33, 33, 33));

        horizontalLayout_5->addWidget(lineColor);


        verticalLayout_5->addLayout(horizontalLayout_5);

        showRefLine = new QCheckBox(viewBox);
        showRefLine->setObjectName("showRefLine");
        sizePolicy3.setHeightForWidth(showRefLine->sizePolicy().hasHeightForWidth());
        showRefLine->setSizePolicy(sizePolicy3);
        showRefLine->setChecked(true);

        verticalLayout_5->addWidget(showRefLine);

        showRuer = new QCheckBox(viewBox);
        showRuer->setObjectName("showRuer");
        sizePolicy3.setHeightForWidth(showRuer->sizePolicy().hasHeightForWidth());
        showRuer->setSizePolicy(sizePolicy3);
        showRuer->setChecked(true);

        verticalLayout_5->addWidget(showRuer);


        verticalLayout_6->addWidget(viewBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        retranslateUi(ProjectPropertyForm);

        QMetaObject::connectSlotsByName(ProjectPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *ProjectPropertyForm)
    {
        ProjectPropertyForm->setWindowTitle(QCoreApplication::translate("ProjectPropertyForm", "Form", nullptr));
        projectBox->setTitle(QCoreApplication::translate("ProjectPropertyForm", "\351\241\271\347\233\256", nullptr));
        label->setText(QCoreApplication::translate("ProjectPropertyForm", "\351\241\271\347\233\256\345\220\215\347\247\260", nullptr));
        label_3->setText(QCoreApplication::translate("ProjectPropertyForm", "\344\275\234\350\200\205", nullptr));
        pageBox->setTitle(QCoreApplication::translate("ProjectPropertyForm", "\351\241\265\351\235\242", nullptr));
        label_2->setText(QCoreApplication::translate("ProjectPropertyForm", "\351\241\265\351\235\242\345\220\215\347\247\260", nullptr));
        label_4->setText(QCoreApplication::translate("ProjectPropertyForm", "\345\244\247\351\241\265\351\235\242\345\260\217", nullptr));
        label_6->setText(QCoreApplication::translate("ProjectPropertyForm", "\345\256\275", nullptr));
        pageWidth->setSuffix(QCoreApplication::translate("ProjectPropertyForm", "px", nullptr));
        label_5->setText(QCoreApplication::translate("ProjectPropertyForm", "\351\253\230", nullptr));
        pageHeight->setSuffix(QCoreApplication::translate("ProjectPropertyForm", "px", nullptr));
        label_7->setText(QCoreApplication::translate("ProjectPropertyForm", "\351\241\265\351\235\242\350\203\214\346\231\257", nullptr));
        viewBox->setTitle(QCoreApplication::translate("ProjectPropertyForm", "\350\247\206\345\233\276", nullptr));
        showGrid->setText(QCoreApplication::translate("ProjectPropertyForm", "\347\275\221\346\240\274", nullptr));
        lineWidth->setSuffix(QCoreApplication::translate("ProjectPropertyForm", "px", nullptr));
        showRefLine->setText(QCoreApplication::translate("ProjectPropertyForm", "\345\217\202\350\200\203\347\272\277", nullptr));
        showRuer->setText(QCoreApplication::translate("ProjectPropertyForm", "\346\240\207\345\260\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectPropertyForm: public Ui_ProjectPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTPROPERTYFORM_H
