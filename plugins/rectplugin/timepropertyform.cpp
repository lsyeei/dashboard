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
#include "timepropertyform.h"
#include "ui_timepropertyform.h"

TimePropertyForm::TimePropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TimePropertyForm)
{
    ui->setupUi(this);
    initUI();
    initEvent();
}

TimePropertyForm::~TimePropertyForm()
{
    delete ui;
}

void TimePropertyForm::setData(const TimeProperty &property)
{
    QSignalBlocker hourBlocker(ui->hourCheck);
    QSignalBlocker secondBlocker(ui->secondCheck);
    QSignalBlocker minutesBlocker(ui->minutesCheck);
    QSignalBlocker msBlocker(ui->msecondCheck);
    QSignalBlocker hour24Blocker(ui->hour24Radio);
    QSignalBlocker hour12Blocker(ui->hour12Radio);
    QSignalBlocker lcdBlocker(ui->lcdCheck);
    QSignalBlocker fontFamilyBlocker(ui->fontFamily);
    QSignalBlocker fontSizeBlocker(ui->fontSize);
    QSignalBlocker boldBtnBlocker(ui->boldBtn);
    QSignalBlocker italicBtnBlocker(ui->italicBtn);
    QSignalBlocker underlineBtnBlocker(ui->underlineBtn);
    QSignalBlocker strikeOutBtnBlocker(ui->strikeOutBtn);
    QSignalBlocker letterSpaceBlocker(ui->letterSpace);
    QSignalBlocker spaceOptionsBlocker(ui->spaceOptions);
    QSignalBlocker foregroundBlocker(ui->foreground);
    QSignalBlocker backgroundBlocker(ui->background);
    attr = property;
    parseTimeFormat(attr.getFormat());
    auto font = attr.getFont();
    if (!attr.getIsLcd()) {
        ui->fontFamily->setEnabled(true);
        ui->fontFamily->setCurrentFont(font);
    }else{
        ui->lcdCheck->setChecked(true);
        ui->fontFamily->setEnabled(false);
    }
    ui->fontSize->setValue(font.pointSize());
    ui->boldBtn->setChecked(font.bold());
    ui->italicBtn->setChecked(font.italic());
    ui->underlineBtn->setChecked(font.underline());
    ui->strikeOutBtn->setChecked(font.strikeOut());
    ui->letterSpace->setValue(font.letterSpacing());
    ui->letterSpace->setEnabled(true);
    ui->spaceOptions->setCurrentIndex(5);
    auto foreground = attr.getForeground();
    if (foreground.isValid()) {
        ui->foreground->setColor(foreground);
    } else {
        ui->foreground->setColor(Qt::white);
    }
    auto background = attr.getBackground();
    if (background.isValid()) {
        ui->background->setColor(background);
    } else {
        ui->background->setColor(Qt::white);
    }
    noData = false;
}

void TimePropertyForm::onValueChanged()
{
    if (noData) {
        return;
    }
    auto action = sender()->objectName();
    auto font = attr.getFont();
    if (action.compare("hourCheck") == 0 || action.compare("minutesCheck") == 0 ||
        action.compare("secondCheck") == 0 || action.compare("msecondCheck") == 0  ||
        action.compare("hour24Radio") == 0 || action.compare("hour12Radio") == 0) {
        ui->hour24Radio->setVisible(ui->hourCheck->isChecked());
        ui->hour12Radio->setVisible(ui->hourCheck->isChecked());
        attr.setFormat(getTimeFormat());
    }
    if (action.compare("lcdCheck") == 0) {
        attr.setIsLcd(ui->lcdCheck->isChecked());
        ui->fontFamily->setEnabled(!ui->lcdCheck->isChecked());
    }
    if (action.compare("fontFamily") == 0) {
        font.setFamily(ui->fontFamily->currentFont().family());
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
    if (action.compare("letterSpace") == 0) {
        font.setLetterSpacing(QFont::AbsoluteSpacing, ui->letterSpace->value());
    }
    attr.setFont(font);
    if (action.compare("foreground") == 0) {
        attr.setForeground(ui->foreground->getColor());
    }
    if (action.compare("background") == 0) {
        attr.setBackground(ui->background->getColor());
    }
    emit dataChanged(attr);
}

void TimePropertyForm::setFontSize()
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

void TimePropertyForm::setLetterSpace()
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

void TimePropertyForm::showFont()
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

void TimePropertyForm::showStyle()
{
    if (ui->styleWidget->isHidden()) {
        ui->expandStyle->setArrowType(Qt::RightArrow);
        ui->styleWidget->show();
        ui->styleLine->show();
    } else {
        ui->expandStyle->setArrowType(Qt::DownArrow);
        ui->styleWidget->hide();
        ui->styleLine->hide();
    }
}

void TimePropertyForm::initUI()
{
    QSignalBlocker hourBlocker(ui->hourCheck);
    QSignalBlocker secondBlocker(ui->secondCheck);
    QSignalBlocker minutesBlocker(ui->minutesCheck);
    QSignalBlocker msBlocker(ui->msecondCheck);
    QSignalBlocker hour24Blocker(ui->hour24Radio);
    QSignalBlocker hour12Blocker(ui->hour12Radio);
    QSignalBlocker lcdBlocker(ui->lcdCheck);
    ui->hourCheck->setChecked(true);
    ui->secondCheck->setChecked(true);
    ui->minutesCheck->setChecked(true);
    ui->msecondCheck->setChecked(false);
    ui->hour24Radio->setChecked(true);
    ui->lcdCheck->setChecked(false);
    ui->background->hide();
    ui->bkColorLabel->hide();
}

void TimePropertyForm::initEvent()
{
    connect(ui->hourCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->minutesCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->secondCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->msecondCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->hour24Radio, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->hour12Radio, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->lcdCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->fontFamily, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
    connect(ui->fontSize, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged()));
    connect(ui->boldBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->italicBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->underlineBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->strikeOutBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->letterSpace, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged()));
    connect(ui->foreground, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(onValueChanged()));
    connect(ui->background, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(onValueChanged()));
    connect(ui->increaseSizeBtn, SIGNAL(clicked(bool)), this, SLOT(setFontSize()));
    connect(ui->decreaseSizeBtn, SIGNAL(clicked(bool)), this, SLOT(setFontSize()));
    connect(ui->spaceOptions, SIGNAL(currentIndexChanged(int)), this, SLOT(setLetterSpace()));

    connect(ui->expandFont, SIGNAL(clicked(bool)), this, SLOT(showFont()));
    connect(ui->expandStyle, SIGNAL(clicked(bool)), this, SLOT(showStyle()));
}

QString TimePropertyForm::getTimeFormat()
{
    QString format;
    QString h{""}, m{""}, s{""}, ms{""};
    h = ui->hourCheck->isChecked()?"hh":"";
    m = ui->minutesCheck->isChecked()?"mm":"";
    s = ui->secondCheck->isChecked()?"ss":"";
    ms = ui->msecondCheck->isChecked()?"zzz":"";
    if (!h.isEmpty()) {
        format = h;
    }
    if (!m.isEmpty()) {
        if (format.isEmpty()) {
            format = m;
        }else{
            format += ":" + m;
        }
    }
    if (!s.isEmpty()) {
        if (format.isEmpty()) {
            format = s;
        }else{
            format += ":" + s;
        }
    }
    if (!ms.isEmpty()) {
        if (format.isEmpty()) {
            format = ms;
        }else{
            format += "." + ms;
        }
    }
    if (!h.isEmpty() && ui->hour12Radio->isChecked()) {
        format += " Ap";
    }
    return format;
}

void TimePropertyForm::parseTimeFormat(const QString &format)
{

}
