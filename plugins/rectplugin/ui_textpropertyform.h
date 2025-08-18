/********************************************************************************
** Form generated from reading UI file 'textpropertyform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTPROPERTYFORM_H
#define UI_TEXTPROPERTYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
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

class Ui_TextPropertyForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *expandFont;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_10;
    QFrame *fontLine;
    QWidget *fontWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_12;
    QComboBox *fontFamily;
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
    QToolButton *subScriptBtn;
    QToolButton *superScriptBtn;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QComboBox *spaceOptions;
    QDoubleSpinBox *letterSpace;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    ColorPicker *foreground;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    ColorPicker *background;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *expandBlock;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_9;
    QFrame *blockLine;
    QWidget *blockWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QToolButton *alignLeftBtn;
    QToolButton *alignCenterBtn;
    QToolButton *alignRightBtn;
    QToolButton *alignJustifyBtn;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QDoubleSpinBox *textIndent;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_10;
    QToolButton *increaseIndentBtn;
    QToolButton *decreaseIndentBtn;
    QSpacerItem *horizontalSpacer_14;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QComboBox *lineHeightOptions;
    QDoubleSpinBox *lineHeight;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QDoubleSpinBox *topMargin;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QDoubleSpinBox *bottomMargin;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_13;
    QToolButton *numberListBtn;
    QToolButton *radioListBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TextPropertyForm)
    {
        if (TextPropertyForm->objectName().isEmpty())
            TextPropertyForm->setObjectName("TextPropertyForm");
        TextPropertyForm->resize(205, 405);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TextPropertyForm->sizePolicy().hasHeightForWidth());
        TextPropertyForm->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(TextPropertyForm);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        expandFont = new QToolButton(TextPropertyForm);
        expandFont->setObjectName("expandFont");
        expandFont->setMaximumSize(QSize(16, 16));
        expandFont->setAutoRaise(true);
        expandFont->setArrowType(Qt::ArrowType::RightArrow);

        horizontalLayout_5->addWidget(expandFont);

        label_4 = new QLabel(TextPropertyForm);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_10 = new QSpacerItem(6, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        fontLine = new QFrame(TextPropertyForm);
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

        verticalLayout_3->addLayout(horizontalLayout_5);

        fontWidget = new QWidget(TextPropertyForm);
        fontWidget->setObjectName("fontWidget");
        sizePolicy.setHeightForWidth(fontWidget->sizePolicy().hasHeightForWidth());
        fontWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(fontWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout->setContentsMargins(0, 9, 0, -1);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalLayout_12->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        fontFamily = new QComboBox(fontWidget);
        fontFamily->setObjectName("fontFamily");
        sizePolicy2.setHeightForWidth(fontFamily->sizePolicy().hasHeightForWidth());
        fontFamily->setSizePolicy(sizePolicy2);
        fontFamily->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
        fontFamily->setMinimumContentsLength(0);
        fontFamily->setFrame(true);

        horizontalLayout_12->addWidget(fontFamily);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_12 = new QLabel(fontWidget);
        label_12->setObjectName("label_12");
        sizePolicy1.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy1);
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/increase.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        increaseSizeBtn->setIcon(icon);

        horizontalLayout->addWidget(increaseSizeBtn);

        decreaseSizeBtn = new QToolButton(fontWidget);
        decreaseSizeBtn->setObjectName("decreaseSizeBtn");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/decrease.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        decreaseSizeBtn->setIcon(icon1);

        horizontalLayout->addWidget(decreaseSizeBtn);

        horizontalSpacer_5 = new QSpacerItem(6, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
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

        subScriptBtn = new QToolButton(fontWidget);
        subScriptBtn->setObjectName("subScriptBtn");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/subScript.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        subScriptBtn->setIcon(icon2);
        subScriptBtn->setCheckable(true);
        subScriptBtn->setAutoExclusive(false);

        horizontalLayout_2->addWidget(subScriptBtn);

        superScriptBtn = new QToolButton(fontWidget);
        superScriptBtn->setObjectName("superScriptBtn");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/superScript.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        superScriptBtn->setIcon(icon3);
        superScriptBtn->setCheckable(true);
        superScriptBtn->setAutoExclusive(false);

        horizontalLayout_2->addWidget(superScriptBtn);

        horizontalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label = new QLabel(fontWidget);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(label);

        spaceOptions = new QComboBox(fontWidget);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/tighten2.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/tighten1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon5, QString());
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/stand.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/loose1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/loose2.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        spaceOptions->addItem(icon8, QString());
        spaceOptions->addItem(QString());
        spaceOptions->setObjectName("spaceOptions");
        sizePolicy2.setHeightForWidth(spaceOptions->sizePolicy().hasHeightForWidth());
        spaceOptions->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(spaceOptions);

        letterSpace = new QDoubleSpinBox(fontWidget);
        letterSpace->setObjectName("letterSpace");
        letterSpace->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(letterSpace->sizePolicy().hasHeightForWidth());
        letterSpace->setSizePolicy(sizePolicy3);
        letterSpace->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        letterSpace->setDecimals(1);
        letterSpace->setMinimum(-999.000000000000000);
        letterSpace->setMaximum(999.000000000000000);
        letterSpace->setSingleStep(0.500000000000000);
        letterSpace->setValue(0.000000000000000);

        horizontalLayout_3->addWidget(letterSpace);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_2 = new QLabel(fontWidget);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_2);

        foreground = new ColorPicker(fontWidget);
        foreground->setObjectName("foreground");
        sizePolicy2.setHeightForWidth(foreground->sizePolicy().hasHeightForWidth());
        foreground->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(foreground);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        label_3 = new QLabel(fontWidget);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(label_3);

        background = new ColorPicker(fontWidget);
        background->setObjectName("background");
        sizePolicy2.setHeightForWidth(background->sizePolicy().hasHeightForWidth());
        background->setSizePolicy(sizePolicy2);

        horizontalLayout_4->addWidget(background);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_13);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(fontWidget);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        expandBlock = new QToolButton(TextPropertyForm);
        expandBlock->setObjectName("expandBlock");
        expandBlock->setMaximumSize(QSize(16, 16));
        expandBlock->setAutoRaise(true);
        expandBlock->setArrowType(Qt::ArrowType::DownArrow);

        horizontalLayout_6->addWidget(expandBlock);

        label_5 = new QLabel(TextPropertyForm);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(label_5);

        horizontalSpacer_9 = new QSpacerItem(6, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        blockLine = new QFrame(TextPropertyForm);
        blockLine->setObjectName("blockLine");
        sizePolicy2.setHeightForWidth(blockLine->sizePolicy().hasHeightForWidth());
        blockLine->setSizePolicy(sizePolicy2);
        blockLine->setFrameShape(QFrame::Shape::HLine);
        blockLine->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_6->addWidget(blockLine);

        horizontalLayout_6->setStretch(3, 1);

        verticalLayout_3->addLayout(horizontalLayout_6);

        blockWidget = new QWidget(TextPropertyForm);
        blockWidget->setObjectName("blockWidget");
        sizePolicy.setHeightForWidth(blockWidget->sizePolicy().hasHeightForWidth());
        blockWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(blockWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_11 = new QLabel(blockWidget);
        label_11->setObjectName("label_11");
        sizePolicy1.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy1);

        horizontalLayout_7->addWidget(label_11);

        alignLeftBtn = new QToolButton(blockWidget);
        alignLeftBtn->setObjectName("alignLeftBtn");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/align-left.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignLeftBtn->setIcon(icon9);
        alignLeftBtn->setCheckable(true);
        alignLeftBtn->setAutoExclusive(true);

        horizontalLayout_7->addWidget(alignLeftBtn);

        alignCenterBtn = new QToolButton(blockWidget);
        alignCenterBtn->setObjectName("alignCenterBtn");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/align-center.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignCenterBtn->setIcon(icon10);
        alignCenterBtn->setCheckable(true);
        alignCenterBtn->setAutoExclusive(true);

        horizontalLayout_7->addWidget(alignCenterBtn);

        alignRightBtn = new QToolButton(blockWidget);
        alignRightBtn->setObjectName("alignRightBtn");
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/align-right.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignRightBtn->setIcon(icon11);
        alignRightBtn->setCheckable(true);
        alignRightBtn->setAutoExclusive(true);

        horizontalLayout_7->addWidget(alignRightBtn);

        alignJustifyBtn = new QToolButton(blockWidget);
        alignJustifyBtn->setObjectName("alignJustifyBtn");
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/align-justify.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        alignJustifyBtn->setIcon(icon12);
        alignJustifyBtn->setCheckable(true);
        alignJustifyBtn->setAutoExclusive(true);

        horizontalLayout_7->addWidget(alignJustifyBtn);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        horizontalLayout_11->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_9 = new QLabel(blockWidget);
        label_9->setObjectName("label_9");
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);

        horizontalLayout_11->addWidget(label_9);

        textIndent = new QDoubleSpinBox(blockWidget);
        textIndent->setObjectName("textIndent");
        sizePolicy2.setHeightForWidth(textIndent->sizePolicy().hasHeightForWidth());
        textIndent->setSizePolicy(sizePolicy2);
        textIndent->setDecimals(1);

        horizontalLayout_11->addWidget(textIndent);

        horizontalSpacer_8 = new QSpacerItem(6, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_10 = new QLabel(blockWidget);
        label_10->setObjectName("label_10");
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);

        horizontalLayout_13->addWidget(label_10);

        increaseIndentBtn = new QToolButton(blockWidget);
        increaseIndentBtn->setObjectName("increaseIndentBtn");
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/Increase_Indent.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        increaseIndentBtn->setIcon(icon13);

        horizontalLayout_13->addWidget(increaseIndentBtn);

        decreaseIndentBtn = new QToolButton(blockWidget);
        decreaseIndentBtn->setObjectName("decreaseIndentBtn");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/Descrease_Indent.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        decreaseIndentBtn->setIcon(icon14);

        horizontalLayout_13->addWidget(decreaseIndentBtn);

        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_14);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_6 = new QLabel(blockWidget);
        label_6->setObjectName("label_6");
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_8->addWidget(label_6);

        lineHeightOptions = new QComboBox(blockWidget);
        lineHeightOptions->addItem(QString());
        lineHeightOptions->addItem(QString());
        lineHeightOptions->addItem(QString());
        lineHeightOptions->addItem(QString());
        lineHeightOptions->addItem(QString());
        lineHeightOptions->setObjectName("lineHeightOptions");
        lineHeightOptions->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        horizontalLayout_8->addWidget(lineHeightOptions);

        lineHeight = new QDoubleSpinBox(blockWidget);
        lineHeight->setObjectName("lineHeight");
        lineHeight->setEnabled(false);
        sizePolicy3.setHeightForWidth(lineHeight->sizePolicy().hasHeightForWidth());
        lineHeight->setSizePolicy(sizePolicy3);
        lineHeight->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        lineHeight->setDecimals(1);

        horizontalLayout_8->addWidget(lineHeight);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_7 = new QLabel(blockWidget);
        label_7->setObjectName("label_7");
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(label_7);

        topMargin = new QDoubleSpinBox(blockWidget);
        topMargin->setObjectName("topMargin");
        sizePolicy2.setHeightForWidth(topMargin->sizePolicy().hasHeightForWidth());
        topMargin->setSizePolicy(sizePolicy2);
        topMargin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        topMargin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        topMargin->setDecimals(1);

        horizontalLayout_10->addWidget(topMargin);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_8 = new QLabel(blockWidget);
        label_8->setObjectName("label_8");
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);

        horizontalLayout_14->addWidget(label_8);

        bottomMargin = new QDoubleSpinBox(blockWidget);
        bottomMargin->setObjectName("bottomMargin");
        sizePolicy2.setHeightForWidth(bottomMargin->sizePolicy().hasHeightForWidth());
        bottomMargin->setSizePolicy(sizePolicy2);
        bottomMargin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        bottomMargin->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::NoButtons);
        bottomMargin->setDecimals(1);

        horizontalLayout_14->addWidget(bottomMargin);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalLayout_9->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        label_13 = new QLabel(blockWidget);
        label_13->setObjectName("label_13");
        sizePolicy1.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(label_13);

        numberListBtn = new QToolButton(blockWidget);
        numberListBtn->setObjectName("numberListBtn");
        sizePolicy1.setHeightForWidth(numberListBtn->sizePolicy().hasHeightForWidth());
        numberListBtn->setSizePolicy(sizePolicy1);
        numberListBtn->setMinimumSize(QSize(0, 0));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/List_Numbered.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        numberListBtn->setIcon(icon15);
        numberListBtn->setCheckable(true);

        horizontalLayout_9->addWidget(numberListBtn);

        radioListBtn = new QToolButton(blockWidget);
        radioListBtn->setObjectName("radioListBtn");
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/List_Bullets.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        radioListBtn->setIcon(icon16);
        radioListBtn->setCheckable(true);

        horizontalLayout_9->addWidget(radioListBtn);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_9);


        verticalLayout_3->addWidget(blockWidget);


        retranslateUi(TextPropertyForm);

        spaceOptions->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TextPropertyForm);
    } // setupUi

    void retranslateUi(QWidget *TextPropertyForm)
    {
        TextPropertyForm->setWindowTitle(QCoreApplication::translate("TextPropertyForm", "Form", nullptr));
        expandFont->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
        label_4->setText(QCoreApplication::translate("TextPropertyForm", "\345\255\227\344\275\223", nullptr));
        label_12->setText(QCoreApplication::translate("TextPropertyForm", "\345\244\247\345\260\217", nullptr));
        fontSize->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
#if QT_CONFIG(tooltip)
        increaseSizeBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\242\236\345\244\247\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        increaseSizeBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        increaseSizeBtn->setText(QCoreApplication::translate("TextPropertyForm", "+", nullptr));
#if QT_CONFIG(tooltip)
        decreaseSizeBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\207\217\345\260\217\345\255\227\345\217\267", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        decreaseSizeBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        decreaseSizeBtn->setText(QCoreApplication::translate("TextPropertyForm", "-", nullptr));
#if QT_CONFIG(tooltip)
        boldBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\212\240\347\262\227", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        boldBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        boldBtn->setText(QCoreApplication::translate("TextPropertyForm", "B", nullptr));
#if QT_CONFIG(tooltip)
        italicBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\346\226\234\344\275\223", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        italicBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        italicBtn->setText(QCoreApplication::translate("TextPropertyForm", " I ", nullptr));
#if QT_CONFIG(tooltip)
        underlineBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\344\270\213\345\210\222\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        underlineBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        underlineBtn->setText(QCoreApplication::translate("TextPropertyForm", "U", nullptr));
#if QT_CONFIG(tooltip)
        strikeOutBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\210\240\351\231\244\347\272\277", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        strikeOutBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        strikeOutBtn->setText(QCoreApplication::translate("TextPropertyForm", "S", nullptr));
#if QT_CONFIG(tooltip)
        subScriptBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\344\270\213\346\240\207", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        subScriptBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        subScriptBtn->setText(QCoreApplication::translate("TextPropertyForm", "X2", nullptr));
#if QT_CONFIG(tooltip)
        superScriptBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\344\270\212\346\240\207", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        superScriptBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        superScriptBtn->setText(QCoreApplication::translate("TextPropertyForm", "X2", nullptr));
        label->setText(QCoreApplication::translate("TextPropertyForm", "\345\255\227\347\254\246\351\227\264\350\267\235", nullptr));
        spaceOptions->setItemText(0, QCoreApplication::translate("TextPropertyForm", "\345\276\210\347\264\247", nullptr));
        spaceOptions->setItemText(1, QCoreApplication::translate("TextPropertyForm", "\347\264\247", nullptr));
        spaceOptions->setItemText(2, QCoreApplication::translate("TextPropertyForm", "\346\240\207\345\207\206", nullptr));
        spaceOptions->setItemText(3, QCoreApplication::translate("TextPropertyForm", "\346\235\276", nullptr));
        spaceOptions->setItemText(4, QCoreApplication::translate("TextPropertyForm", "\345\276\210\346\235\276", nullptr));
        spaceOptions->setItemText(5, QCoreApplication::translate("TextPropertyForm", "\350\207\252\345\256\232\344\271\211", nullptr));

        letterSpace->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
        label_2->setText(QCoreApplication::translate("TextPropertyForm", "\345\211\215\346\231\257\350\211\262", nullptr));
        label_3->setText(QCoreApplication::translate("TextPropertyForm", "\350\203\214\346\231\257\350\211\262", nullptr));
        expandBlock->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
        label_5->setText(QCoreApplication::translate("TextPropertyForm", "\346\256\265\350\220\275", nullptr));
        label_11->setText(QCoreApplication::translate("TextPropertyForm", "\345\257\271\351\275\220", nullptr));
#if QT_CONFIG(tooltip)
        alignLeftBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\267\246\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignLeftBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignLeftBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignCenterBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\261\205\344\270\255\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignCenterBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignCenterBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignRightBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\217\263\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignRightBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignRightBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        alignJustifyBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\344\270\244\347\253\257\345\257\271\351\275\220", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        alignJustifyBtn->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        alignJustifyBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
        label_9->setText(QCoreApplication::translate("TextPropertyForm", "\351\246\226\350\241\214\347\274\251\350\277\233", nullptr));
        textIndent->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
        label_10->setText(QCoreApplication::translate("TextPropertyForm", "\346\256\265\350\220\275\347\274\251\350\277\233", nullptr));
#if QT_CONFIG(tooltip)
        increaseIndentBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\242\236\345\212\240\346\256\265\350\220\275\347\274\251\350\277\233", nullptr));
#endif // QT_CONFIG(tooltip)
        increaseIndentBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        decreaseIndentBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\207\217\345\260\221\346\256\265\350\220\275\347\274\251\350\277\233", nullptr));
#endif // QT_CONFIG(tooltip)
        decreaseIndentBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
        label_6->setText(QCoreApplication::translate("TextPropertyForm", "\350\241\214\350\267\235", nullptr));
        lineHeightOptions->setItemText(0, QCoreApplication::translate("TextPropertyForm", "\345\215\225\345\200\215", nullptr));
        lineHeightOptions->setItemText(1, QCoreApplication::translate("TextPropertyForm", "1.15\345\200\215", nullptr));
        lineHeightOptions->setItemText(2, QCoreApplication::translate("TextPropertyForm", "1.5\345\200\215", nullptr));
        lineHeightOptions->setItemText(3, QCoreApplication::translate("TextPropertyForm", "\345\217\214\345\200\215", nullptr));
        lineHeightOptions->setItemText(4, QCoreApplication::translate("TextPropertyForm", "\345\233\272\345\256\232", nullptr));

        lineHeight->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
        label_7->setText(QCoreApplication::translate("TextPropertyForm", "\346\256\265\345\211\215", nullptr));
        topMargin->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
        label_8->setText(QCoreApplication::translate("TextPropertyForm", "\346\256\265\345\220\216", nullptr));
        bottomMargin->setSuffix(QCoreApplication::translate("TextPropertyForm", " pt", nullptr));
        label_13->setText(QCoreApplication::translate("TextPropertyForm", "\345\210\227\350\241\250", nullptr));
#if QT_CONFIG(tooltip)
        numberListBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\210\207\346\215\242\346\227\240\345\272\217\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        numberListBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
#if QT_CONFIG(tooltip)
        radioListBtn->setToolTip(QCoreApplication::translate("TextPropertyForm", "\345\210\207\346\215\242\346\234\211\345\272\217\345\210\227\350\241\250", nullptr));
#endif // QT_CONFIG(tooltip)
        radioListBtn->setText(QCoreApplication::translate("TextPropertyForm", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextPropertyForm: public Ui_TextPropertyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTPROPERTYFORM_H
