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

#ifndef TEXTPROPERTY_H
#define TEXTPROPERTY_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QWidget>

class TextPropertyForm;
class QDESIGNER_WIDGET_EXPORT TextProperty : public QWidget
{
    Q_OBJECT
public:
    explicit TextProperty(QWidget *parent = nullptr);
    ~TextProperty();
    QTextCharFormat getCharFormat() const;
    QTextBlockFormat getBlockFormat() const;
    void setTextFormat(const QTextFormat &format);
    // QWidget interface
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
Q_SIGNALS:
    void textFormatChanged(const QTextFormat &format);
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
private Q_SLOTS:
    void onFormChangeFormat(const QTextFormat &format);
private:
    QScopedPointer<TextPropertyForm> form;
};

#endif // TEXTPROPERTY_H
