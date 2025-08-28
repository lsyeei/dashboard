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

#ifndef HTMLEDITORFORM_H
#define HTMLEDITORFORM_H

#include <QDialog>
// #include <QWidget>

class QWebEngineView;
namespace Ui {
class HtmlEditorForm;
}

class HtmlEditorForm : public QDialog/*QWidget*/
{
    Q_OBJECT

public:
    explicit HtmlEditorForm(QWidget *parent = nullptr);
    ~HtmlEditorForm();
    void setHTML(const QString &data);
    void setText(const QString &data);

Q_SIGNALS:
    void editEnd(const QString &data);
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

protected Q_SLOTS:
    void onHtmlLoaded();

private:
    Ui::HtmlEditorForm *ui;
    QWebEngineView *view{nullptr};
    void createHtmlEditor();
};

#endif // HTMLEDITORFORM_H
