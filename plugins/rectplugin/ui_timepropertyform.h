/********************************************************************************
** Form generated from reading UI file 'timepropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEPROPERTYFORM_H
#define UI_TIMEPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorpicker.h"

QT_BEGIN_NAMESPACE

class Ui_TimePropertyForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *expandStyle;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QFrame *styleLine;
    QWidget *styleWidget;
    QVBoxLayout *verticalLayout_3;
    QComboBox *timeFormat;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *autoCheck;
    QCheckBox *lcdCheck;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QToolButton *alignLeftBtn;
    QToolButton *alignCenterBtn;
    QToolButton *alignRightBtn;
    QToolButton *alignJustifyBtn;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *expandFont;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_10;
    QFrame *fontLine;
    QWidget *fontWidget;
    QVBoxLayout *verticalLayout;
    QFontComboBox *fontFamily;
    QHBoxLayout *horizontalLayout;
    QLabel *label_12;
    QSpinBox *fontSize;
    QToolButton *increaseSizeBtn;
    QToolButton *decreaseSizeBtn;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *strikeOutBtn;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *spaceOptions;
    QDoubleSpinBox *letterSpace;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    ColorPicker *foreground;
    QSpacerItem *horizontalSpacer_6;
    QLabel *bkColorLabel;
    ColorPicker *background;
    QSpacerItem *horizontalSpacer_13;

    void setupUi(QWidget *TimePropertyForm)
    {
        if (TimePropertyForm->objectName().isEmpty())
            TimePropertyForm->setObjectName("TimePropertyForm");
        TimePropertyForm->resize(214, 305);
        verticalLayout_2 = new QVBoxLayout(TimePropertyForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        expandStyle = new QToolButton(TimePropertyForm);
        expandStyle->setObjectName("expandStyle");
        expandStyle->setMaximumSize(QSize(16, 16));
        expandStyle->setAutoRaise(true);
        expandStyle->setArrowType(Qt::ArrowType::RightArrow);

        horizontalLayout_6->addWidget(expandStyle);

        label_5 = new QLabel(TimePropertyForm);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_5);

        horizontalSpacer = new QSpacerItem(6, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        styleLine = new QFrame(TimePropertyForm);
        styleLine->setObjectName("styleLine");
        styleLine->setFrameShape(QFrame::Shape::HLine);
        styleLine->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_6->addWidget(styleLine);

        horizontalLayout_6->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_6);

        styleWidget = new QWidget(TimePropertyForm);
        styleWidget->setObjectName("styleWidget");
        verticalLayout_3 = new QVBoxLayout(styleWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        timeFormat = new QComboBox(styleWidget);
        timeFormat->setObjectName("timeFormat");

        verticalLayout_3->addWidget(timeFormat);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        autoCheck = new QCheckBox(styleWidget);
        autoCheck->setObjectName("autoCheck");

        horizontalLayout_7->addWidget(autoCheck);

        lcdCheck = new QCheckBox(styleWidget);
        lcdCheck->setObjectName("lcdCheck");

        horizontalLayout_7->addWidget(lcdCheck);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_11 = new QLabel(styleWidget);
        label_11->setObjectName("label_11");
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        horizontalLayout_8->addWidget(label_11);

        alignLeftBtn = new QToolButton(styleWidget);
        alignLeftBtn->setObjectName("alignLeftBtn");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/align-left.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignLeftBtn->setIcon(icon);
        alignLeftBtn->setCheckable(true);
        alignLeftBtn->setAutoExclusive(true);

        horizontalLayout_8->addWidget(alignLeftBtn);

        alignCenterBtn = new QToolButton(styleWidget);
        alignCenterBtn->setObjectName("alignCenterBtn");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/align-center.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignCenterBtn->setIcon(icon1);
        alignCenterBtn->setCheckable(true);
        alignCenterBtn->setAutoExclusive(true);

        horizontalLayout_8->addWidget(alignCenterBtn);

        alignRightBtn = new QToolButton(styleWidget);
        alignRightBtn->setObjectName("alignRightBtn");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/align-right.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignRightBtn->setIcon(icon2);
        alignRightBtn->setCheckable(true);
        alignRightBtn->setAutoExclusive(true);

        horizontalLayout_8->addWidget(alignRightBtn);

        alignJustifyBtn = new QToolButton(styleWidget);
        alignJustifyBtn->setObjectName("alignJustifyBtn");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/align-justify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignJustifyBtn->setIcon(icon3);
        alignJustifyBtn->setCheckable(true);
        alignJustifyBtn->setAutoExclusive(true);

        horizontalLayout_8->addWidget(alignJustifyBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_2->addWidget(styleWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        expandFont = new QToolButton(TimePropertyForm);
        expandFont->setObjectName("expandFont");
        expandFont->setMaximumSize(QSize(16, 16));
        expandFont->setAutoRaise(true);
        expandFont->setArrowType(Qt::ArrowType::RightArrow);

        horizontalLayout_5->addWidget(expandFont);

        label_4 = new QLabel(TimePropertyForm);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_10 = new QSpacerItem(6, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        fontLine = new QFrame(TimePropertyForm);
        fontLine->setObjectName("fontLine");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(fontLine->sizePolicy().hasHeightForWidth());
        fontLine->setSizePolicy(sizePolicy2);
        fontLine->setFrameShape(QFrame::Shape::HLine);
        fontLine->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_5->addWidget(fontLine);

        horizontalLayout_5->setStretch(3, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);

        fontWidget = new QWidget(TimePropertyForm);
        fontWidget->setObjectName("fontWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fontWidget->sizePolicy().hasHeightForWidth());
        fontWidget->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(fontWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 9);
        fontFamily = new QFontComboBox(fontWidget);
        fontFamily->setObjectName("fontFamily");

        verticalLayout->addWidget(fontFamily);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        label_12 = new QLabel(fontWidget);
        label_12->setObjectName("label_12");
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setMargin(0);

        horizontalLayout->addWidget(label_12);

        fontSize = new QSpinBox(fontWidget);
        fontSize->setObjectName("fontSize");
        sizePolicy2.setHeightForWidth(fontSize->sizePolicy().hasHeightForWidth());
        fontSize->setSizePolicy(sizePolicy2);
        fontSize->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        fontSize->setMinimum(1);
        fontSize->setMaximum(999);
        fontSize->setValue(16);

        horizontalLayout->addWidget(fontSize);

        increaseSizeBtn = new QToolButton(fontWidget);
        increaseSizeBtn->setObjectName("increaseSizeBtn");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/increase.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        increaseSizeBtn->setIcon(icon4);

        horizontalLayout->addWidget(increaseSizeBtn);

        decreaseSizeBtn = new QToolButton(fontWidget);
        decreaseSizeBtn->setObjectName("decreaseSizeBtn");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/decrease.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        decreaseSizeBtn->setIcon(icon5);

        horizontalLayout->addWidget(decreaseSizeBtn);

        horizontalSpacer_5 = new QSpacerItem(6, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        boldBtn = new QToolButton(fontWidget);
        boldBtn->setObjectName("boldBtn");
        boldBtn->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"font-weight:bold;"));
        boldBtn->setIconSize(QSize(16, 16));
        boldBtn->setCheckable(true);

        horizontalLayout_2->addWidget(boldBtn);

        italicBtn = new QToolButton(fontWidget);
        italicBtn->setObjectName("italicBtn");
        italicBtn->setStyleSheet(QString::fromUtf8("font: italic 10pt \"Liberation Serif\";"));
        italicBtn->setCheckable(true);

        horizontalLayout_2->addWidget(italicBtn);

        underlineBtn = new QToolButton(fontWidget);
        underlineBtn->setObjectName("underlineBtn");
        underlineBtn->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"text-decoration: underline;"));
        underlineBtn->setCheckable(true);

        horizontalLayout_2->addWidget(underlineBtn);

        strikeOutBtn = new QToolButton(fontWidget);
        strikeOutBtn->setObjectName("strikeOutBtn");
        strikeOutBtn->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"text-decoration: line-through;"));
        strikeOutBtn->setCheckable(true);

        horizontalLayout_2->addWidget(strikeOutBtn);

        horizontalSpacer_11 = new QSpacerItem(10, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(fontWidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        spaceOptions = new QComboBox(fontWidget);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/tighten2.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/tighten1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/stand.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon8, QString());
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/loose1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon9, QString());
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/loose2.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon10, QString());
        spaceOptions->addItem(QString());
        spaceOptions->setObjectName("spaceOptions");
        sizePolicy2.setHeightForWidth(spaceOptions->sizePolicy().hasHeightForWidth());
        spaceOptions->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(spaceOptions);

        letterSpace = new QDoubleSpinBox(fontWidget);
        letterSpace->setObjectName("letterSpace");
        letterSpace->setEnabled(false);
        sizePolicy2.setHeightForWidth(letterSpace->sizePolicy().hasHeightForWidth());
        letterSpace->setSizePolicy(sizePolicy2);
        letterSpace->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        letterSpace->setDecimals(1);
        letterSpace->setMinimum(-999.000000000000000);
        letterSpace->setMaximum(999.000000000000000);
        letterSpace->setSingleStep(0.500000000000000);
        letterSpace->setValue(0.000000000000000);

        horizontalLayout_3->addWidget(letterSpace);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_2 = new QLabel(fontWidget);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(label_2);

        foreground = new ColorPicker(fontWidget);
        foreground->setObjectName("foreground");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(foreground->sizePolicy().hasHeightForWidth());
        foreground->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(foreground);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        bkColorLabel = new QLabel(fontWidget);
        bkColorLabel->setObjectName("bkColorLabel");
        sizePolicy.setHeightForWidth(bkColorLabel->sizePolicy().hasHeightForWidth());
        bkColorLabel->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(bkColorLabel);

        background = new ColorPicker(fontWidget);
        background->setObjectName("background");
        sizePolicy4.setHeightForWidth(background->sizePolicy().hasHeightForWidth());
        background->setSizePolicy(sizePolicy4);

        horizontalLayout_4->addWidget(background);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(fontWidget);


        retranslateUi(TimePropertyForm);

        spaceOptions->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TimePropertyForm);
    } // setupUi

    void retranslateUi(QWidget *TimePropertyForm)
    {
        TimePropertyForm->setWindowTitle(QCoreApplication::translate("TimePropertyForm", "Form", nullptr));
        expandStyle->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
        label_5->setText(QCoreApplication::translate("TimePropertyForm", "\346\240\267\345\274\217", nullptr));
        autoCheck->setText(QCoreApplication::translate("TimePropertyForm", "\350\207\252\345\212\250\346\233\264\346\226\260", nullptr));
        lcdCheck->setText(QCoreApplication::translate("TimePropertyForm", "\346\266\262\346\231\266\346\225\260\345\255\227", nullptr));
        label_11->setText(QCoreApplication::translate("TimePropertyForm", "\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignLeftBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\267\246\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignLeftBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignLeftBtn->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignCenterBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignCenterBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignCenterBtn->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignRightBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\217\263\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignRightBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignRightBtn->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignJustifyBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\344\270\244\347\253\257\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignJustifyBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignJustifyBtn->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
        expandFont->setText(QCoreApplication::translate("TimePropertyForm", "...", nullptr));
        label_4->setText(QCoreApplication::translate("TimePropertyForm", "\345\255\227\344\275\223", nullptr));
        label_12->setText(QCoreApplication::translate("TimePropertyForm", "\345\244\247\345\260\217", nullptr));
        fontSize->setSuffix(QCoreApplication::translate("TimePropertyForm", " pt", nullptr));
#if QT_CONFIG(tooltip)
        increaseSizeBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\242\236\345\244\247\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        increaseSizeBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        increaseSizeBtn->setText(QCoreApplication::translate("TimePropertyForm", "+", nullptr));
#if QT_CONFIG(tooltip)
        decreaseSizeBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\207\217\345\260\217\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        decreaseSizeBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        decreaseSizeBtn->setText(QCoreApplication::translate("TimePropertyForm", "-", nullptr));
#if QT_CONFIG(tooltip)
        boldBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\212\240\347\262\227", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        boldBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        boldBtn->setText(QCoreApplication::translate("TimePropertyForm", "B", nullptr));
#if QT_CONFIG(tooltip)
        italicBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\346\226\234\344\275\223", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        italicBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        italicBtn->setText(QCoreApplication::translate("TimePropertyForm", " I ", nullptr));
#if QT_CONFIG(tooltip)
        underlineBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        underlineBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        underlineBtn->setText(QCoreApplication::translate("TimePropertyForm", "U", nullptr));
#if QT_CONFIG(tooltip)
        strikeOutBtn->setToolTip(QCoreApplication::translate("TimePropertyForm", "\345\210\240\351\231\244\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        strikeOutBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        strikeOutBtn->setText(QCoreApplication::translate("TimePropertyForm", "S", nullptr));
        label->setText(QCoreApplication::translate("TimePropertyForm", "\345\255\227\347\254\246\351\227\264\350\267\235", nullptr));
        spaceOptions->setItemText(0, QCoreApplication::translate("TimePropertyForm", "\345\276\210\347\264\247", nullptr));
        spaceOptions->setItemText(1, QCoreApplication::translate("TimePropertyForm", "\347\264\247", nullptr));
        spaceOptions->setItemText(2, QCoreApplication::translate("TimePropertyForm", "\346\240\207\345\207\206", nullptr));
        spaceOptions->setItemText(3, QCoreApplication::translate("TimePropertyForm", "\346\235\276", nullptr));
        spaceOptions->setItemText(4, QCoreApplication::translate("TimePropertyForm", "\345\276\210\346\235\276", nullptr));
        spaceOptions->setItemText(5, QCoreApplication::translate("TimePropertyForm", "\350\207\252\345\256\232\344\271\211", nullptr));

        letterSpace->setSuffix(QCoreApplication::translate("TimePropertyForm", " pt", nullptr));
        label_2->setText(QCoreApplication::translate("TimePropertyForm", "\345\211\215\346\231\257\350\211\262", nullptr));
        bkColorLabel->setText(QCoreApplication::translate("TimePropertyForm", "\350\203\214\346\231\257\350\211\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimePropertyForm: public Ui_TimePropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEPROPERTYFORM_H
