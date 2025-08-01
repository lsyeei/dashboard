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
#include "webpropertyform.h"
#include "ui_webpropertyform.h"
#include "ksyntaxhighlighting/repository.h"
#include "ksyntaxhighlighting/repository_p.h"
#include "ksyntaxhighlighting/syntaxhighlighter.h"
#include "ksyntaxhighlighting/definition_p.h"
#include "ksyntaxhighlighting/themedata_p.h"
#include <QFileDialog>

WebPropertyForm::WebPropertyForm(QWidget *parent)
    : ISubWidget(parent)
    , ui(new Ui::WebPropertyForm)
{
    ui->setupUi(this);
    initUI();
    setEditorHighlight();
}

WebPropertyForm::~WebPropertyForm()
{
    delete ui;
}

void WebPropertyForm::setData(const QVariant &data)
{
    if (data.isNull()) {
        return;
    }
    attr = data.value<WebProperty>();
    // 更新UI
    QSignalBlocker moveBlock(ui->moveCheck);
    QSignalBlocker urlBlock(ui->urlRadio);
    QSignalBlocker urlBlock2(ui->urlEdit);
    QSignalBlocker fileBlock(ui->fileRadio);
    QSignalBlocker codeBlock(ui->codeRadio);
    QSignalBlocker codeBlock2(ui->codeEdit);
    auto type = attr.getType();
    auto content = attr.getContent();
    ui->moveCheck->setChecked(attr.getDragFlag());
    switch (type) {
    case PageType::URL:
        ui->urlRadio->setChecked(true);
        break;
    case PageType::FILE:
        ui->fileRadio->setChecked(true);
        break;
    default:
        ui->codeRadio->setChecked(true);
        break;
    }
    ui->urlWidget->setVisible(type != PageType::CODE);
    ui->codeEdit->setVisible(type == PageType::CODE);
    ui->fileBtn->setVisible(type == PageType::FILE);
    ui->urlEdit->setEnabled(type == PageType::URL);
    if (type == PageType::FILE){
        ui->codeEdit->setText(content);
    }else{
        ui->urlEdit->setText(content);
    }
}

void WebPropertyForm::onValueChanged()
{
    auto obj = sender();
    auto act = obj->objectName();
    PageType type = attr.getType();
    bool trigFlag{false};
    if (act.compare("urlRadio") == 0) {
        ui->urlWidget->setVisible(true);
        ui->fileBtn->setVisible(false);
        ui->codeEdit->setVisible(false);
        type = PageType::URL;
    }
    if (act.compare("fileRadio") == 0) {
        ui->urlWidget->setVisible(true);
        ui->fileBtn->setVisible(true);
        ui->codeEdit->setVisible(false);
        type = PageType::FILE;
    }
    if (act.compare("codeRadio") == 0) {
        ui->urlWidget->setVisible(false);
        ui->codeEdit->setVisible(true);
        type = PageType::CODE;
    }
    attr.setType(type);
    if (act.compare("updateBtn") == 0) {
        auto content = ui->urlEdit->text();
        if (ui->codeRadio->isChecked()) {
            content = ui->codeEdit->toPlainText();
        }
        if (!content.isEmpty()){
            attr.setContent(content);
        }
        trigFlag = true;
    }
    if(act.compare("moveCheck") == 0) {
        attr.setDragFlag(ui->moveCheck->isChecked());
        trigFlag = true;
    }
    if (trigFlag) {
        emit dataChanged(QVariant::fromValue(attr));
    }
}

void WebPropertyForm::onSelectFile()
{
    auto file = QFileDialog::getOpenFileName(this, tr("选择HTML文件"), QDir::currentPath(), "HTML (*.html);;js (*.js)");
    if (!file.isEmpty()) {
        ui->urlEdit->setText(file);
    }
}

void WebPropertyForm::initUI()
{
    layout()->setAlignment(Qt::AlignTop);
    ui->codeRadio->setChecked(true);
    ui->urlWidget->hide();
    connect(ui->moveCheck, SIGNAL(stateChanged(int)), this, SLOT(onValueChanged()));
    connect(ui->urlRadio, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->fileRadio, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->codeRadio, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(ui->fileBtn, SIGNAL(clicked(bool)), this, SLOT(onSelectFile()));
    connect(ui->updateBtn, SIGNAL(clicked(bool)), this, SLOT(onValueChanged()));
}

void WebPropertyForm::setEditorHighlight()
{
    using namespace KSyntaxHighlighting;
    m_highlighter = new SyntaxHighlighter(ui->codeEdit->document());

    auto repoData = RepositoryPrivate::get(&m_repository);
    repoData->loadSyntaxFolder(&m_repository, ":/html");
    repoData->computeAlternativeDefLists();
    m_highlighter->setDefinition(m_repository.definitionForName("HTML"));

    Theme themeDef;
    auto themeData = ThemeData::get(themeDef);
    themeData->load(":/html/atom-one-light.theme");
    m_highlighter->setTheme(themeDef);
}
