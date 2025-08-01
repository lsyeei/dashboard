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
#include <QAbstractItemView>
#include <QTimeZone>

TimePropertyForm::TimePropertyForm(QWidget *parent)
    : ISubWidget(parent)
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

void TimePropertyForm::setData(const QVariant &data)
{
    if (data.isNull()) {
        return;
    }
    QSignalBlocker hourBlocker(ui->timeFormat);
    QSignalBlocker secondBlocker(ui->autoCheck);
    QSignalBlocker minutesBlocker(ui->alignCenterBtn);
    QSignalBlocker msBlocker(ui->alignJustifyBtn);
    QSignalBlocker hour24Blocker(ui->alignLeftBtn);
    QSignalBlocker hour12Blocker(ui->alignRightBtn);
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
    attr = data.value<TimeProperty>();
    auto index = ui->timeFormat->findData(attr.getFormat());
    if (index < 0) {
        index = 0;
    }
    ui->timeFormat->setCurrentIndex(index);
    ui->autoCheck->setChecked(attr.getIsAuto());
    auto align = attr.getAlignment();
    ui->alignLeftBtn->setChecked(align & Qt::AlignLeft);
    ui->alignCenterBtn->setChecked(align & Qt::AlignCenter);
    ui->alignRightBtn->setChecked(align & Qt::AlignRight);
    ui->alignJustifyBtn->setChecked(align & Qt::AlignJustify);

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

bool TimePropertyForm::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->timeFormat->view() && event->type() == QEvent::ShowToParent) {
        updateFormatOptions();
    }
    return QWidget::eventFilter(watched, event);
}

void TimePropertyForm::onValueChanged()
{
    if (noData) {
        return;
    }
    auto action = sender()->objectName();
    auto font = attr.getFont();
    if (action.compare("timeFormat") == 0) {
        attr.setFormat(ui->timeFormat->currentData().toString());
        if (!attr.getIsAuto()) {
            attr.setTime(getFormatDate(attr.getFormat()));
        }
    }
    if (action.compare("autoCheck") == 0) {
        attr.setIsAuto(ui->autoCheck->isChecked());
        if (!attr.getIsAuto()) {
            attr.setTime(getFormatDate(attr.getFormat()));
        }
    }
    if (action.compare("lcdCheck") == 0) {
        attr.setIsLcd(ui->lcdCheck->isChecked());
        ui->fontFamily->setEnabled(!ui->lcdCheck->isChecked());
    }
    if (action.compare("alignLeftBtn") == 0) {
        attr.setAlignment(Qt::AlignLeft);
    }
    if (action.compare("alignCenterBtn") == 0) {
        attr.setAlignment(Qt::AlignCenter);
    }
    if (action.compare("alignRightBtn") == 0) {
        attr.setAlignment(Qt::AlignRight);
    }
    if (action.compare("alignJustifyBtn") == 0) {
        attr.setAlignment(Qt::AlignJustify);
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
    emit dataChanged(QVariant::fromValue(attr));
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
    layout()->setAlignment(Qt::AlignTop);
    QSignalBlocker lcdBlocker(ui->lcdCheck);
    ui->lcdCheck->setChecked(false);
    ui->background->hide();
    ui->bkColorLabel->hide();

    updateFormatOptions();
}

void TimePropertyForm::initEvent()
{
    connect(ui->timeFormat, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
    connect(ui->autoCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->lcdCheck, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(onValueChanged()));
    connect(ui->alignLeftBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->alignCenterBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->alignRightBtn, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->alignJustifyBtn,SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));

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

    ui->timeFormat->view()->installEventFilter(this);
}

void TimePropertyForm::updateFormatOptions()
{
    auto index = ui->timeFormat->currentIndex();
    if (index < 0) {
        index = 0;
    }
    ui->timeFormat->clear();
    QList<QString> formatList;
    formatList << "yyyy/M/d ddd" << "yyyy年M月d日" << "yyyy年M月d日 ddd"
               << "yyyy/M/d" << "yyyy-M-d ddd" << "yyyy-M-d" << "yyyy-MM-dd"
               << "yy.MM.dd" << "yyyy年M月" << "yyyy年M月d日 h时mm分"
               << "yyyy年M月d日 hh:mm:ss" << "yyyy年M月d日 ddd  hh时mm分ss秒"
               << "hh:mm" << "hh:mm:ss" << "hh时mm分 AP" << "hh时mm分ss秒 AP"
               << "yyyy年"  << "MM月" << "dddd";

    foreach (auto format, formatList) {
        ui->timeFormat->addItem(getFormatDate(format), format);
    }
    ui->timeFormat->setCurrentIndex(index);
}

QString TimePropertyForm::getFormatDate(const QString format)
{
    auto locale = QLocale::system();
    auto data = QDateTime::currentDateTime();
    return locale.toString(data, format);
}
