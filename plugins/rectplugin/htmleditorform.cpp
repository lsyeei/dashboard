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

#include "htmleditorform.h"
#include "ui_htmleditorform.h"

#include <QCloseEvent>
#include <QWebEngineView>

HtmlEditorForm::HtmlEditorForm(QWidget *parent)
    : /*QWidget*/QDialog(parent)
    , ui(new Ui::HtmlEditorForm)
{
    ui->setupUi(this);
    createHtmlEditor();
}

HtmlEditorForm::~HtmlEditorForm()
{
    delete ui;
    view->page()->deleteLater();
    view->close();
}

void HtmlEditorForm::setHTML(const QString &data)
{
    if (view == nullptr) {
        return;
    }
    view->page()->runJavaScript(QString("editor.setHtml('%1')").arg(data),
                                [&](const QVariant &value){
                                    // qDebug() << "set html ok";
                                });
}

void HtmlEditorForm::setText(const QString &data)
{
    if (view == nullptr) {
        return;
    }
    view->page()->runJavaScript(QString("editor.setHtml('%1')").arg(data),
                                [&](const QVariant &value){
                                    // qDebug() << "set text ok";
                                });
}

void HtmlEditorForm::closeEvent(QCloseEvent *event)
{
    view->page()->runJavaScript("editor.getHtml()",
                                [&](const QVariant &value){
                                    emit this->editEnd(value.toString());
                                });
    hide();
    event->ignore();
}

void HtmlEditorForm::onHtmlLoaded()
{
    // qDebug() << "加载完成....";
}

void HtmlEditorForm::createHtmlEditor()
{
    view = new QWebEngineView();
    view->setUrl(QStringLiteral("qrc:/html/editor/index.html"));
    view->page()->setVisible(true);
    layout()->addWidget(view);
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(onHtmlLoaded()));
}
