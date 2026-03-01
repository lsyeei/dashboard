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
#include "settingform.h"
#include "ui_settingform.h"

#include <QNetworkRequest>

SettingForm::SettingForm(QWidget *parent)
    : AbstractSubForm(parent)
    , ui(new Ui::SettingForm)
{
    ui->setupUi(this);
    QString style = R"(
        #sslCheck{
            color:palette(button-text);
        }
        #sslCheck::indicator{
            width:26px;
            height:26px;
            border-image: url(:/icon/switch-OFF.svg);
        }
        #sslCheck::indicator:checked{
            width:26px;
            height:26px;
            border-radius: 13px;
            border-image: url(:/icon/switch-ON.svg);
        }
    )";
    initVersion();
    initRedirect();
    ui->sslCheck->setStyleSheet(style);

    connect(ui->versionCombo, &QComboBox::currentIndexChanged,
            this, &SettingForm::onVersionChanged);
    connect(ui->sslCheck, &QCheckBox::checkStateChanged,
            this, &SettingForm::onSslChanged);
    connect(ui->timeoutSpin, &QSpinBox::valueChanged,
            this, &SettingForm::onTimeoutChanged);
    connect(ui->redirectCombo, &QComboBox::currentIndexChanged,
            this, &SettingForm::onRedirectChanged);
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::setData(const QVariant &data)
{
    setting = data.value<HttpSetting>();
    // 更行UI数据
    QSignalBlocker vBlocker(ui->versionCombo);
    QSignalBlocker timeBlocker(ui->timeoutSpin);
    QSignalBlocker redirectBlocker(ui->redirectCombo);
    QSignalBlocker sslBlocker(ui->sslCheck);
    auto version = setting.getVersion();
    auto index = ui->versionCombo->findData(QVariant::fromValue(version));
    ui->versionCombo->setCurrentIndex(index);
    ui->timeoutSpin->setValue(setting.getTimeout());
    auto redirect = setting.getRedirectPolicy();
    index = ui->redirectCombo->findData(redirect);
    ui->redirectCombo->setCurrentIndex(index);
}

QVariant SettingForm::getData() const
{
    return QVariant::fromValue(setting);
}

void SettingForm::onVersionChanged()
{
    auto version = ui->versionCombo->currentData().value<HttpVersion>();
    setting.setVersion(version);
    emit dataChangedEvent(QVariant::fromValue(setting));
}

void SettingForm::onSslChanged()
{

}

void SettingForm::onTimeoutChanged()
{
    setting.setTimeout(ui->timeoutSpin->value());
    emit dataChangedEvent(QVariant::fromValue(setting));
}

void SettingForm::onRedirectChanged()
{
    auto data = ui->redirectCombo->currentData().toInt();
    setting.setRedirectPolicy(data);
    emit dataChangedEvent(QVariant::fromValue(setting));
}

void SettingForm::initVersion()
{
    QSignalBlocker version(ui->versionCombo);
    ui->versionCombo->clear();
    auto list = HttpSetting::versionList();
    foreach (auto item, list) {
        ui->versionCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
    ui->versionCombo->setCurrentIndex(1);
}

void SettingForm::initRedirect()
{
    QList<QPair<QString, QNetworkRequest::RedirectPolicy>> list = {
        {tr("Manual"), QNetworkRequest::ManualRedirectPolicy},
        {tr("No Less Safe"), QNetworkRequest::NoLessSafeRedirectPolicy},
        {tr("Same Origin"), QNetworkRequest::SameOriginRedirectPolicy},
        {tr("Reject"), QNetworkRequest::QNetworkRequest::UserVerifiedRedirectPolicy}};
    QSignalBlocker redirect(ui->redirectCombo);
    ui->redirectCombo->clear();
    foreach (auto item, list) {
        ui->redirectCombo->addItem(item.first, QVariant::fromValue(item.second));
    }
    ui->redirectCombo->setCurrentIndex(-1);
}
