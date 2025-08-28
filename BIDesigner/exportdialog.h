﻿/**
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

#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();
    void setImageSize(const QSize &boardSize, const QSize &selectSize);
    bool selectedScope();
    QString fileName();
    QSize imageSize();
    QString fileType();
    int quality();
    QColor color();

protected Q_SLOTS:
    void onFileDialog();
    void onFormatChanged(int index);
    void onFileTypeChanged();
    void onQualityChanged();
    void onScopeChanged();
    void doExport();
    void useBgColor();
private:
    Ui::ExportDialog *ui;
    QSize defaultBoardSize;
    QSize defaultSelectedSize;

    void initUI();
    void changeFileSuffix(const QString &suffix);
};

#endif // EXPORTDIALOG_H
