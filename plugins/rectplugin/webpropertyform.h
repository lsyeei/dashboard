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
#ifndef WEBPROPERTYFORM_H
#define WEBPROPERTYFORM_H

#include "webproperty.h"
#include "isubwidget.h"
#include "ksyntaxhighlighting/repository.h"

namespace KSyntaxHighlighting
{
class SyntaxHighlighter;
}

namespace Ui {
class WebPropertyForm;
}

class WebPropertyForm : public ISubWidget
{
    Q_OBJECT

public:
    explicit WebPropertyForm(QWidget *parent = nullptr);
    ~WebPropertyForm();
    // ISubWidget interface
    void setData(const QVariant &data) override;
protected Q_SLOTS:
    void onValueChanged();
    void onSelectFile();
private:
    Ui::WebPropertyForm *ui;
    WebProperty attr;
    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;

    void initUI();
    void setEditorHighlight();

};

#endif // WEBPROPERTYFORM_H
