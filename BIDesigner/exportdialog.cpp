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

#include "exportdialog.h"
#include "ui_exportdialog.h"

#include <QBuffer>
#include <QFileDialog>
#include <QImageWriter>
#include <QMessageBox>

ExportDialog::ExportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    initUI();
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::setImageSize(const QSize &boardSize, const QSize &selectSize)
{
    defaultBoardSize = boardSize;
    defaultSelectedSize = selectSize;
    if (selectSize.width() == 0 || selectSize.height() == 0) {
        // 禁用
        ui->selectedBtn->hide();
        ui->allBtn->setChecked(true);
    }else{
        ui->selectedBtn->show();
        ui->selectedBtn->setChecked(true);
    }
    onScopeChanged();
}

bool ExportDialog::selectedScope()
{
    return ui->selectedBtn->isChecked();
}

QString ExportDialog::fileName()
{
    return ui->fileName->text();
}

QSize ExportDialog::imageSize()
{
    return {ui->width->value(), ui->height->value()};
}

QString ExportDialog::fileType()
{
    if(ui->svgBtn->isChecked()){
        return "svg";
    } else {
        return ui->format->currentText();
    }
}

int ExportDialog::quality()
{
    return ui->qualityValue->value();
}

QColor ExportDialog::color()
{
    auto color = ui->bgColor->getColor();
    if (!ui->hasBgColor->isChecked()) {
        color.setAlpha(0);
    }
    return color;
}

void ExportDialog::onFileDialog()
{
    auto fileName = QFileDialog::getSaveFileName(this, tr("保存到"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        ui->fileName->setText(fileName);
        onFileTypeChanged();
    }
}

void ExportDialog::onFormatChanged(int index)
{
    Q_UNUSED(index)
    auto format = ui->format->currentText();
    changeFileSuffix(format);
    QByteArray arr;
    QBuffer buf(&arr);
    QImageWriter handle(&buf, format.toLocal8Bit());
    if (handle.supportsOption(QImageIOHandler::Quality)){
        ui->qualityOption->show();
    }else{
        ui->qualityOption->hide();
    }
}

void ExportDialog::onFileTypeChanged()
{
    if (ui->svgBtn->isChecked()) {
        ui->imageOption->hide();
        changeFileSuffix("svg");
    }else{
        ui->imageOption->show();
        onFormatChanged(0);
        changeFileSuffix(ui->format->currentText());
    }
}

void ExportDialog::onQualityChanged()
{
    if (sender() == ui->qualitySlider) {
        ui->qualityValue->blockSignals(true);
        ui->qualityValue->setValue(ui->qualitySlider->value());
        ui->qualityValue->blockSignals(false);
    }else{
        ui->qualitySlider->blockSignals(true);
        ui->qualitySlider->setValue(ui->qualityValue->value());
        ui->qualitySlider->blockSignals(false);
    }
}

void ExportDialog::onScopeChanged()
{
    if (ui->allBtn->isChecked()) {
        ui->width->setValue(defaultBoardSize.width());
        ui->height->setValue(defaultBoardSize.height());
    } else{
        ui->width->setValue(defaultSelectedSize.width());
        ui->height->setValue(defaultSelectedSize.height());
    }
}

void ExportDialog::doExport()
{
    auto fileName = ui->fileName->text();
    auto width = ui->width->value();
    auto height = ui->height->value();
    if (fileName.isEmpty()) {
        ui->fileName->setFocus();
        QMessageBox::information(this, tr("提示"), tr("请选择保存位置"));
    } else if(width <= 0){
        ui->width->setFocus();
        QMessageBox::information(this, tr("提示"), tr("宽度必须大于0"));
    } else if(height <= 0){
        ui->height->setFocus();
        QMessageBox::information(this, tr("提示"), tr("高度必须大于0"));
    }else{
        accept();
    }
}

void ExportDialog::useBgColor()
{
    if(ui->hasBgColor->isChecked()){
        ui->bgColor->show();
    } else {
        ui->bgColor->hide();
    }
}

void ExportDialog::initUI()
{
    ui->svgBtn->setChecked(true);
    ui->imageBtn->setChecked(false);
    ui->imageOption->hide();
    auto formats = QImageWriter::supportedImageFormats();
    ui->format->clear();
    foreach (auto f, formats) {
        ui->format->addItem(QString(f), f);
    }
    ui->format->setCurrentIndex(0);
    onFormatChanged(0);
    ui->allBtn->setChecked(true);
    ui->hasBgColor->setChecked(false);
    ui->bgColor->hide();

    connect(ui->cancleBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->exportBtn, SIGNAL(clicked(bool)), this, SLOT(doExport()));
    connect(ui->fileBtn, SIGNAL(clicked(bool)), this, SLOT(onFileDialog()));
    connect(ui->svgBtn, SIGNAL(toggled(bool)), this, SLOT(onFileTypeChanged()));
    connect(ui->imageBtn, SIGNAL(toggled(bool)), this, SLOT(onFileTypeChanged()));
    connect(ui->format, SIGNAL(currentIndexChanged(int)), this, SLOT(onFormatChanged(int)));
    connect(ui->qualitySlider, SIGNAL(valueChanged(int)), this, SLOT(onQualityChanged()));
    connect(ui->qualityValue, SIGNAL(valueChanged(int)), this, SLOT(onQualityChanged()));
    connect(ui->allBtn, SIGNAL(toggled(bool)), this, SLOT(onScopeChanged()));
    connect(ui->selectedBtn, SIGNAL(toggled(bool)), this, SLOT(onScopeChanged()));
    connect(ui->hasBgColor, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(useBgColor()));
}

void ExportDialog::changeFileSuffix(const QString &suffix)
{
    auto fileName = ui->fileName->text();
    if (!fileName.isEmpty()) {
        auto pos = fileName.lastIndexOf(".");
        if(pos>0){
            fileName = fileName.left(pos+1) + suffix;
        }else{
            fileName += "." + suffix;
        }
        ui->fileName->setText(fileName);
    }
}
