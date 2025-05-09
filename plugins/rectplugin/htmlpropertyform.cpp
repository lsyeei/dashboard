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

#include "htmlpropertyform.h"
#include "ksyntaxhighlighting/repository.h"
#include "ksyntaxhighlighting/repository_p.h"
// #include "htmleditorform.h"
#include "ui_htmlpropertyform.h"

#include "ksyntaxhighlighting/syntaxhighlighter.h"
#include "ksyntaxhighlighting/definition_p.h"
#include "ksyntaxhighlighting/themedata_p.h"

HtmlPropertyForm::HtmlPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HtmlPropertyForm)
{
    ui->setupUi(this);

    connect(ui->updateBtn, SIGNAL(clicked(bool)), this, SLOT(syncText()));

    createEditor();

    setEditorHighlight();
}

HtmlPropertyForm::~HtmlPropertyForm()
{
    delete ui;
    // if (editor) {
    //     editor->deleteLater();
    // }
}

void HtmlPropertyForm::createEditor()
{
    ui->eidtBtn->hide();
    // editor = new HtmlEditorForm();
    // connect(editor, SIGNAL(editEnd(QString)), this, SLOT(onEditEnd(QString)));
    // connect(ui->eidtBtn, SIGNAL(clicked(bool)), this, SLOT(onEditButtonClicked()));
}

void HtmlPropertyForm::setHtml(const QString &data)
{
    ui->textEdit->blockSignals(true);
    ui->textEdit->setPlainText(data);
    ui->textEdit->blockSignals(false);
}

void HtmlPropertyForm::onEditButtonClicked()
{
    // editor->setHTML(ui->textEdit->toPlainText());
    // editor->setParent(this);
    // editor->exec();//->show();
}

void HtmlPropertyForm::onEditEnd(const QString &data)
{
    ui->textEdit->setPlainText(data);
}

void HtmlPropertyForm::syncText()
{
    emit htmlChanged(ui->textEdit->toPlainText());
}

void HtmlPropertyForm::setEditorHighlight()
{
    using namespace KSyntaxHighlighting;
    m_highlighter = new SyntaxHighlighter(ui->textEdit->document());

    auto repoData = RepositoryPrivate::get(&m_repository);
    repoData->loadSyntaxFolder(&m_repository, ":/html");
    repoData->computeAlternativeDefLists();
    m_highlighter->setDefinition(m_repository.definitionForName("HTML"));

    // Definition def;
    // auto defData = DefinitionData::get(def);
    // defData->repo = new Repository();
    // defData->loadMetaData(":/html/html.xml");
    // defData->loadMetaData(":/html/css.xml");
    // defData->loadMetaData(":/html/doxygen.xml");
    // defData->loadMetaData(":/html/comments.xml");
    // defData->loadMetaData(":/html/javascript.xml");
    // m_highlighter->setDefinition(def);

    Theme themeDef;
    auto themeData = ThemeData::get(themeDef);
    themeData->load(":/html/atom-one-light.theme");
    m_highlighter->setTheme(themeDef);
}


