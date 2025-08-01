/********************************************************************************
** Form generated from reading UI file 'exportdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTDIALOG_H
#define UI_EXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_ExportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QRadioButton *allBtn;
    QRadioButton *selectedBtn;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QRadioButton *svgBtn;
    QRadioButton *imageBtn;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_5;
    QSpinBox *width;
    QLabel *label_6;
    QSpinBox *height;
    QSpacerItem *horizontalSpacer_4;
    QWidget *imageOption;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QComboBox *format;
    QCheckBox *hasBgColor;
    ColorPicker *bgColor;
    QSpacerItem *horizontalSpacer_5;
    QWidget *qualityOption;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QSlider *qualitySlider;
    QSpinBox *qualityValue;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *fileName;
    QToolButton *fileBtn;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exportBtn;
    QPushButton *cancleBtn;
    QButtonGroup *formatGroup;
    QButtonGroup *scopeGroup;

    void setupUi(QDialog *ExportDialog)
    {
        if (ExportDialog->objectName().isEmpty())
            ExportDialog->setObjectName("ExportDialog");
        ExportDialog->setWindowModality(Qt::WindowModality::WindowModal);
        ExportDialog->resize(368, 227);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExportDialog->sizePolicy().hasHeightForWidth());
        ExportDialog->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ExportDialog);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_7 = new QLabel(ExportDialog);
        label_7->setObjectName("label_7");

        horizontalLayout_6->addWidget(label_7);

        allBtn = new QRadioButton(ExportDialog);
        scopeGroup = new QButtonGroup(ExportDialog);
        scopeGroup->setObjectName("scopeGroup");
        scopeGroup->addButton(allBtn);
        allBtn->setObjectName("allBtn");
        allBtn->setAutoExclusive(true);

        horizontalLayout_6->addWidget(allBtn);

        selectedBtn = new QRadioButton(ExportDialog);
        scopeGroup->addButton(selectedBtn);
        selectedBtn->setObjectName("selectedBtn");
        selectedBtn->setAutoExclusive(true);

        horizontalLayout_6->addWidget(selectedBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(ExportDialog);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        svgBtn = new QRadioButton(ExportDialog);
        formatGroup = new QButtonGroup(ExportDialog);
        formatGroup->setObjectName("formatGroup");
        formatGroup->addButton(svgBtn);
        svgBtn->setObjectName("svgBtn");
        svgBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(svgBtn);

        imageBtn = new QRadioButton(ExportDialog);
        formatGroup->addButton(imageBtn);
        imageBtn->setObjectName("imageBtn");
        imageBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(imageBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(ExportDialog);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        label_5 = new QLabel(ExportDialog);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        width = new QSpinBox(ExportDialog);
        width->setObjectName("width");
        width->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        width->setMaximum(999999);

        horizontalLayout_3->addWidget(width);

        label_6 = new QLabel(ExportDialog);
        label_6->setObjectName("label_6");

        horizontalLayout_3->addWidget(label_6);

        height = new QSpinBox(ExportDialog);
        height->setObjectName("height");
        height->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        height->setMaximum(999999);

        horizontalLayout_3->addWidget(height);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        imageOption = new QWidget(ExportDialog);
        imageOption->setObjectName("imageOption");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageOption->sizePolicy().hasHeightForWidth());
        imageOption->setSizePolicy(sizePolicy1);
        imageOption->setMinimumSize(QSize(0, 0));
        horizontalLayout_7 = new QHBoxLayout(imageOption);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(imageOption);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        format = new QComboBox(imageOption);
        format->setObjectName("format");

        horizontalLayout_7->addWidget(format);

        hasBgColor = new QCheckBox(imageOption);
        hasBgColor->setObjectName("hasBgColor");

        horizontalLayout_7->addWidget(hasBgColor);

        bgColor = new ColorPicker(imageOption);
        bgColor->setObjectName("bgColor");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(bgColor->sizePolicy().hasHeightForWidth());
        bgColor->setSizePolicy(sizePolicy2);
        bgColor->setMinimumSize(QSize(45, 22));

        horizontalLayout_7->addWidget(bgColor);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(imageOption);

        qualityOption = new QWidget(ExportDialog);
        qualityOption->setObjectName("qualityOption");
        horizontalLayout_4 = new QHBoxLayout(qualityOption);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(qualityOption);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        qualitySlider = new QSlider(qualityOption);
        qualitySlider->setObjectName("qualitySlider");
        qualitySlider->setMaximum(100);
        qualitySlider->setValue(80);
        qualitySlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_4->addWidget(qualitySlider);

        qualityValue = new QSpinBox(qualityOption);
        qualityValue->setObjectName("qualityValue");
        qualityValue->setAlignment(Qt::AlignmentFlag::AlignCenter);
        qualityValue->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        qualityValue->setMaximum(100);

        horizontalLayout_4->addWidget(qualityValue);


        verticalLayout->addWidget(qualityOption);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(ExportDialog);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        fileName = new QLineEdit(ExportDialog);
        fileName->setObjectName("fileName");

        horizontalLayout->addWidget(fileName);

        fileBtn = new QToolButton(ExportDialog);
        fileBtn->setObjectName("fileBtn");

        horizontalLayout->addWidget(fileBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        exportBtn = new QPushButton(ExportDialog);
        exportBtn->setObjectName("exportBtn");

        horizontalLayout_5->addWidget(exportBtn);

        cancleBtn = new QPushButton(ExportDialog);
        cancleBtn->setObjectName("cancleBtn");

        horizontalLayout_5->addWidget(cancleBtn);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(ExportDialog);

        QMetaObject::connectSlotsByName(ExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ExportDialog)
    {
        ExportDialog->setWindowTitle(QCoreApplication::translate("ExportDialog", "\345\257\274\345\207\272", nullptr));
        label_7->setText(QCoreApplication::translate("ExportDialog", "\350\214\203\345\233\264\357\274\232", nullptr));
        allBtn->setText(QCoreApplication::translate("ExportDialog", "\345\205\250\351\203\250\345\233\276\345\205\203", nullptr));
        selectedBtn->setText(QCoreApplication::translate("ExportDialog", "\351\200\211\344\270\255\345\233\276\345\205\203", nullptr));
        label_2->setText(QCoreApplication::translate("ExportDialog", "\346\240\274\345\274\217\357\274\232", nullptr));
        svgBtn->setText(QCoreApplication::translate("ExportDialog", "SVG", nullptr));
        imageBtn->setText(QCoreApplication::translate("ExportDialog", "\345\233\276\347\211\207", nullptr));
        label_3->setText(QCoreApplication::translate("ExportDialog", "\345\244\247\345\260\217\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("ExportDialog", "\345\256\275", nullptr));
        width->setSuffix(QCoreApplication::translate("ExportDialog", "px", nullptr));
        width->setPrefix(QString());
        label_6->setText(QCoreApplication::translate("ExportDialog", "\351\253\230", nullptr));
        height->setSuffix(QCoreApplication::translate("ExportDialog", "px", nullptr));
        height->setPrefix(QString());
        label_9->setText(QCoreApplication::translate("ExportDialog", "\346\240\274\345\274\217\357\274\232", nullptr));
        hasBgColor->setText(QCoreApplication::translate("ExportDialog", "\345\272\225\350\211\262", nullptr));
        label_4->setText(QCoreApplication::translate("ExportDialog", "\345\233\276\345\203\217\350\264\250\351\207\217\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("ExportDialog", "\344\277\235\345\255\230\345\210\260\357\274\232", nullptr));
        fileBtn->setText(QCoreApplication::translate("ExportDialog", "...", nullptr));
        exportBtn->setText(QCoreApplication::translate("ExportDialog", "\345\257\274\345\207\272", nullptr));
        cancleBtn->setText(QCoreApplication::translate("ExportDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportDialog: public Ui_ExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTDIALOG_H
