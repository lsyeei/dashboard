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

#include "textpropertyform.h"
#include "ui_textpropertyform.h"

#include <QFontDatabase>

TextPropertyForm::TextPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextPropertyForm)
{
    ui->setupUi(this);
    ui->blockLine->hide();
    ui->blockWidget->hide();
    initFontFamilies();
    initEvent();
}

TextPropertyForm::~TextPropertyForm()
{
    delete ui;
}

QTextCharFormat TextPropertyForm::getCharFormat() const
{
    return charFormat;
}

void TextPropertyForm::setCharFormat(const QTextCharFormat &format)
{
    charFormat = format;
    auto font = format.font();
    auto familyIndex = ui->fontFamily->findText(font.family());
    if (familyIndex < 0) {
        familyIndex = 0;
    }
    ui->fontFamily->setCurrentIndex(familyIndex);
    ui->fontSize->setValue(font.pointSize());
    ui->boldBtn->setChecked(font.bold());
    ui->italicBtn->setChecked(font.italic());
    ui->underlineBtn->setChecked(font.underline());
    ui->strikeOutBtn->setChecked(font.strikeOut());
    ui->letterSpace->setValue(font.letterSpacing());
    ui->letterSpace->setEnabled(true);
    ui->spaceOptions->setCurrentIndex(5);
    ui->subScriptBtn->setChecked(format.verticalAlignment() == QTextCharFormat::AlignSubScript);
    ui->superScriptBtn->setChecked(format.verticalAlignment() == QTextCharFormat::AlignSuperScript);
    auto brush = format.foreground();
    if (brush.style() != Qt::NoBrush) {
        ui->foreground->setColor(brush.color());
    } else {
        ui->foreground->setColor(Qt::white);
    }
    brush = format.background();
    if (brush.style() != Qt::NoBrush) {
        ui->background->setColor(brush.color());
    } else {
        ui->background->setColor(Qt::white);
    }
}

QTextBlockFormat TextPropertyForm::getBlockFormat() const
{
    return blockFormat;
}

void TextPropertyForm::setBlockFormat(const QTextBlockFormat &format)
{
    blockFormat = format;
    auto align = format.alignment();
    ui->alignLeftBtn->setChecked(align & Qt::AlignLeft);
    ui->alignCenterBtn->setChecked(align & Qt::AlignCenter);
    ui->alignRightBtn->setChecked(align & Qt::AlignRight);
    ui->alignJustifyBtn->setChecked(align & Qt::AlignJustify);
    ui->lineHeightOptions->setCurrentIndex(4);
    ui->lineHeight->setEnabled(true);
    ui->lineHeight->setValue(format.lineHeight());
    ui->topMargin->setValue(format.topMargin());
    ui->bottomMargin->setValue(format.bottomMargin());
    ui->textIndent->setValue(format.textIndent());
}

void TextPropertyForm::setTextFormat(const QTextFormat &format)
{
    if (format.isBlockFormat()) {
        setBlockFormat(format.toBlockFormat());
    }
    if (format.isCharFormat()) {
        setCharFormat(format.toCharFormat());
    }
    if (format.isListFormat()) {
        auto listFormat = format.toListFormat();
        if (listFormat.style() <= -4 ) {
            ui->numberListBtn->setChecked(true);
            ui->radioListBtn->setChecked(false);
        }else if(listFormat.style() < 0){
            ui->radioListBtn->setChecked(true);
            ui->numberListBtn->setChecked(false);
        } else{
            ui->numberListBtn->setChecked(false);
            ui->radioListBtn->setChecked(false);
        }
    }
}

void TextPropertyForm::onCharFormatChanged()
{
    auto action = sender()->objectName();
    auto font = charFormat.font();
    if (action.compare("fontFamily") == 0) {
        font.setFamily(ui->fontFamily->currentText());
    }
    if (action.compare("fontSize") == 0) {
        font.setPointSize(ui->fontSize->value());
    }
    if (action.compare("boldBtn") == 0) {
        font.setBold(ui->boldBtn->isChecked());
    }
    if (action.compare("italicBtn") == 0) {
        font.setItalic(ui->italicBtn->isChecked());
    }
    if (action.compare("underlineBtn") == 0) {
        font.setUnderline(ui->underlineBtn->isChecked());
    }
    if (action.compare("strikeOutBtn") == 0) {
        font.setStrikeOut(ui->strikeOutBtn->isChecked());
    }
    if (action.compare("subScriptBtn") == 0) {
        if (ui->subScriptBtn->isChecked()) {
            charFormat.setVerticalAlignment(QTextCharFormat::AlignSubScript);
            ui->superScriptBtn->setChecked(false);
        } else {
            charFormat.setVerticalAlignment(QTextCharFormat::AlignNormal);
        }

    }
    if (action.compare("superScriptBtn") == 0) {
        if (ui->superScriptBtn->isChecked()) {
            charFormat.setVerticalAlignment(QTextCharFormat::AlignSuperScript);
            ui->subScriptBtn->setChecked(false);
        } else {
            charFormat.setVerticalAlignment(QTextCharFormat::AlignNormal);
        }
    }
    if (action.compare("letterSpace") == 0) {
        font.setLetterSpacing(QFont::AbsoluteSpacing, ui->letterSpace->value());
    }
    if (action.compare("foreground") == 0) {
        QBrush brush = charFormat.foreground();
        brush.setColor(ui->foreground->getColor());
        brush.setStyle(Qt::SolidPattern);
        charFormat.setForeground(brush);
    }
    if (action.compare("background") == 0) {
        QBrush brush = charFormat.background();
        brush.setColor(ui->background->getColor());
        brush.setStyle(Qt::SolidPattern);
        charFormat.setBackground(brush);
    }
    charFormat.setFont(font, QTextCharFormat::FontPropertiesSpecifiedOnly);
    emit textFormatChanged(charFormat);
}

void TextPropertyForm::setFontSize()
{
    auto value = ui->fontSize->value();
    auto action = sender()->objectName();
    if (action.compare("increaseSizeBtn") == 0) {
        value += 1;
    }else if(action.compare("decreaseSizeBtn") == 0){
        value -= 1;
    }
    ui->fontSize->setValue(value);
}

void TextPropertyForm::setLetterSpace()
{
    auto index = ui->spaceOptions->currentIndex();
    qreal value = 0;
    if (index == 5) {
        ui->letterSpace->setEnabled(true);
        value = ui->letterSpace->value();
    } else {
        ui->letterSpace->setEnabled(false);
        switch (index) {
        case 0:
            value = -3;
            break;
        case 1:
            value = -1.5;
            break;
        case 2:
            value = 0;
            break;
        case 3:
            value = 3;
            break;
        case 4:
            value = 6;
            break;
        default:
            break;
        }
    }
    ui->letterSpace->setValue(value);
}

void TextPropertyForm::onBlockFormatChanged()
{
    auto action = sender()->objectName();
    if (action.compare("alignLeftBtn") == 0) {
        blockFormat.setAlignment(ui->alignLeftBtn->isChecked()?Qt::AlignLeft:Qt::AlignLeft);
    }
    if (action.compare("alignRightBtn") == 0) {
        blockFormat.setAlignment(ui->alignRightBtn->isChecked()?Qt::AlignRight:Qt::AlignLeft);
    }
    if (action.compare("alignCenterBtn") == 0) {
        blockFormat.setAlignment(ui->alignCenterBtn->isChecked()?Qt::AlignHCenter:Qt::AlignLeft);
    }
    if (action.compare("alignJustifyBtn") == 0) {
        blockFormat.setAlignment(ui->alignJustifyBtn->isChecked()?Qt::AlignJustify:Qt::AlignLeft);
    }
    if (action.compare("increaseIndentBtn") == 0) {
        auto indent = blockFormat.indent();qDebug() << "last indent:" << indent;
        blockFormat.setIndent(indent + 1);
    }
    if (action.compare("decreaseIndentBtn") == 0) {
        auto indent = blockFormat.indent();
        if (indent >= 1) {
            indent -= 1;
        }else{
            indent = 0;
        }
        blockFormat.setIndent(indent);
    }
    if (action.compare("textIndent") == 0) {
        blockFormat.setTextIndent(ui->textIndent->value());
    }
    if (action.compare("lineHeight") == 0) {
        blockFormat.setLineHeight(ui->lineHeight->value(), QTextBlockFormat::LineDistanceHeight);
    }
    if (action.compare("topMargin") == 0) {
        blockFormat.setTopMargin(ui->topMargin->value());
    }
    if (action.compare("bottomMargin") == 0) {
        blockFormat.setBottomMargin(ui->bottomMargin->value());
    }
    emit textFormatChanged(blockFormat);
}

void TextPropertyForm::setLineHeight()
{
    auto index = ui->lineHeightOptions->currentIndex();
    qreal value = 0;
    if (index == 4) {
        ui->lineHeight->setEnabled(true);
        value = ui->lineHeight->value();
    } else {
        auto charinfo = blockFormat.toCharFormat();
        QFontMetrics metrics(charinfo.font());
        qreal height = metrics.height();
        ui->lineHeight->setEnabled(false);
        switch (index) {
        case 0:
            value = 0;
            break;
        case 1:
            value = height*0.15;
            break;
        case 2:
            value = height*0.5;
            break;
        case 3:
            value = height*1.0;
            break;
        default:
            break;
        }
    }
    blockFormat.setLineHeight(value, QTextBlockFormat::LineDistanceHeight);
    emit textFormatChanged(blockFormat);
}

void TextPropertyForm::showBlock()
{
    if (ui->blockWidget->isHidden()) {
        ui->expandBlock->setArrowType(Qt::RightArrow);
        ui->blockWidget->show();
        ui->blockLine->show();
    } else {
        ui->expandBlock->setArrowType(Qt::DownArrow);
        ui->blockWidget->hide();
        ui->blockLine->hide();
    }
}

void TextPropertyForm::showFont()
{
    if (ui->fontWidget->isHidden()) {
        ui->expandFont->setArrowType(Qt::RightArrow);
        ui->fontWidget->show();
        ui->fontLine->show();
    } else {
        ui->expandFont->setArrowType(Qt::DownArrow);
        ui->fontWidget->hide();
        ui->fontLine->hide();
    }

}

void TextPropertyForm::onListFormatChanged()
{
    auto action = sender()->objectName();
    QTextListFormat format;
    format.setIndent(2);
    if (action.compare("numberListBtn") == 0) {
        if (ui->numberListBtn->isChecked()) {
            format.setStyle(QTextListFormat::ListDecimal);
            format.setStart(1);
        }
        ui->radioListBtn->setChecked(false);
    } else if (action.compare("radioListBtn") == 0) {
        if (ui->radioListBtn->isChecked()){
            format.setStyle(QTextListFormat::ListDisc);
        }
        ui->numberListBtn->setChecked(false);
    }
    emit textFormatChanged(format);
}

void TextPropertyForm::initFontFamilies()
{
    auto families = QFontDatabase::families();
    ui->fontFamily->clear();
    foreach (auto name , families) {
        ui->fontFamily->addItem(name);
    }
}

void TextPropertyForm::initEvent()
{
    connect(ui->fontFamily, SIGNAL(currentIndexChanged(int)), this, SLOT(onCharFormatChanged()));
    connect(ui->fontSize, SIGNAL(valueChanged(int)), this, SLOT(onCharFormatChanged()));
    connect(ui->boldBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->italicBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->underlineBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->strikeOutBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->subScriptBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->superScriptBtn, SIGNAL(toggled(bool)), this, SLOT(onCharFormatChanged()));
    connect(ui->letterSpace, SIGNAL(valueChanged(double)), this, SLOT(onCharFormatChanged()));
    connect(ui->foreground, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(onCharFormatChanged()));
    connect(ui->background, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(onCharFormatChanged()));
    connect(ui->increaseSizeBtn, SIGNAL(clicked(bool)), this, SLOT(setFontSize()));
    connect(ui->decreaseSizeBtn, SIGNAL(clicked(bool)), this, SLOT(setFontSize()));
    connect(ui->spaceOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(setLetterSpace()));

    connect(ui->alignLeftBtn, SIGNAL(toggled(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->alignCenterBtn, SIGNAL(toggled(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->alignRightBtn, SIGNAL(toggled(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->alignJustifyBtn, SIGNAL(toggled(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->increaseIndentBtn, SIGNAL(clicked(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->decreaseIndentBtn, SIGNAL(clicked(bool)), this, SLOT(onBlockFormatChanged()));
    connect(ui->lineHeight, SIGNAL(valueChanged(double)), this, SLOT(onBlockFormatChanged()));
    connect(ui->topMargin, SIGNAL(valueChanged(double)), this, SLOT(onBlockFormatChanged()));
    connect(ui->bottomMargin, SIGNAL(valueChanged(double)), this, SLOT(onBlockFormatChanged()));
    connect(ui->textIndent, SIGNAL(valueChanged(double)), this, SLOT(onBlockFormatChanged()));
    connect(ui->lineHeightOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(setLineHeight()));

    connect(ui->expandBlock, SIGNAL(clicked(bool)), this, SLOT(showBlock()));
    connect(ui->expandFont, SIGNAL(clicked(bool)), this, SLOT(showFont()));

    connect(ui->radioListBtn, SIGNAL(clicked(bool)), this, SLOT(onListFormatChanged()));
    connect(ui->numberListBtn, SIGNAL(clicked(bool)), this, SLOT(onListFormatChanged()));
}
