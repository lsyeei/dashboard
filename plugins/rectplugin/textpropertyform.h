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

#ifndef TEXTPROPERTYFORM_H
#define TEXTPROPERTYFORM_H

#include "isubwidget.h"
#include <QTextCharFormat>
#include <QWidget>

namespace Ui {
class TextPropertyForm;
}

class TextPropertyForm : public ISubWidget
{
    Q_OBJECT

public:
    explicit TextPropertyForm(QWidget *parent = nullptr);
    ~TextPropertyForm();

    QTextCharFormat getCharFormat() const;
    QTextBlockFormat getBlockFormat() const;
    // ISubWidget interface
    void setData(const QVariant &data) override;

private Q_SLOTS:
    void onCharFormatChanged();
    void setFontSize();
    void setLetterSpace();
    void onBlockFormatChanged();
    void setLineHeight();
    void showBlock();
    void showFont();
    void onListFormatChanged();
private:
    Ui::TextPropertyForm *ui;
    QTextCharFormat charFormat;
    QTextBlockFormat blockFormat;
    void initFontFamilies();
    void initEvent();
    void setCharFormat(const QTextCharFormat &format);
    void setBlockFormat(const QTextBlockFormat &format);
};

#endif // TEXTPROPERTYFORM_H
