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
#include "syntaxfactory.h"
#include "ui_htmlpropertyform.h"

HtmlPropertyForm::HtmlPropertyForm(QWidget *parent)
    : ISubWidget(parent)
    , ui(new Ui::HtmlPropertyForm)
{
    ui->setupUi(this);

    layout()->setAlignment(Qt::AlignTop);
    connect(ui->updateBtn, SIGNAL(clicked(bool)), this, SLOT(syncText()));

    createEditor();

    SyntaxFactory::instance()->highlightDocument(ui->textEdit->document(), "html");
}

HtmlPropertyForm::~HtmlPropertyForm()
{
    delete ui;
}

void HtmlPropertyForm::createEditor()
{
    ui->eidtBtn->hide();
}

void HtmlPropertyForm::setData(const QVariant &data)
{
    ui->textEdit->blockSignals(true);
    ui->textEdit->setPlainText(data.toString());
    ui->textEdit->blockSignals(false);
}

void HtmlPropertyForm::onEditButtonClicked()
{
}

void HtmlPropertyForm::onEditEnd(const QString &data)
{
    ui->textEdit->setPlainText(data);
}

void HtmlPropertyForm::syncText()
{
    emit dataChanged(ui->textEdit->toPlainText());
}
