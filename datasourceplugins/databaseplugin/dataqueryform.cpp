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
#include "dataqueryform.h"
#include "syntaxfactory.h"
#include "ui_dataqueryform.h"
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QJsonDocument>
#include "database.h"

DataQueryForm::DataQueryForm(QWidget *parent)
    : IDataQueryWidget(parent)
    , ui(new Ui::DataQueryForm)
{
    ui->setupUi(this);
    ui->tableSplitter->setStretchFactor(0,1);
    ui->tableSplitter->setStretchFactor(1,4);
    ui->fieldSplitter->setStretchFactor(0,1);
    ui->fieldSplitter->setStretchFactor(1,3);

    tableModel = new QStandardItemModel(this);
    tableFilter = new QSortFilterProxyModel(this);
    tableFilter->setSourceModel(tableModel);
    tableFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->tableList->setModel(tableFilter);
    ui->tableList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    fieldModel = new QStandardItemModel(this);
    fieldFilter = new QSortFilterProxyModel(this);
    fieldFilter->setSourceModel(fieldModel);
    fieldFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    ui->fieldList->setModel(fieldFilter);
    ui->fieldList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    SyntaxFactory::instance()->highlightDocument(ui->sqlEdit->document(), "sql");

    connect(ui->testButton, &QPushButton::clicked,
            this, &DataQueryForm::onTestBtnClicked);
    connect(ui->tableList, &QListView::clicked,
            this, &DataQueryForm::onTableChanged);
    connect(ui->tableEdit, &QLineEdit::textChanged,
            this, &DataQueryForm::onFindTable);
    connect(ui->fieldEdit, &QLineEdit::textChanged,
            this, &DataQueryForm::onFindField);
}

DataQueryForm::~DataQueryForm()
{
    delete ui;
}

QString DataQueryForm::getArgs()
{
    params.setSQL(ui->sqlEdit->toPlainText().trimmed());
    params.setAction(Action::Select);
    return params.toJson();
}

void DataQueryForm::setArgs(const QString &args)
{
    params = QueryArg::fromJson(args);
    ui->sqlEdit->setPlainText(params.getSQL());
}

void DataQueryForm::setDataSource(const QString &dataSourceArgs)
{
    connectArgs = dataSourceArgs;
    Database db(dataSourceArgs);
    auto tableList = db.tables();
    db.disconnect();
    foreach (auto table, tableList){
        tableModel->appendRow(new QStandardItem(table));
    }
}

void DataQueryForm::onTestBtnClicked()
{
    Database db(connectArgs);
    auto result = db.query(getArgs());
    ui->testResultEdit->clear();
    ui->testResultEdit->setPlainText(result.toJson());
}

void DataQueryForm::onTableChanged(QModelIndex proxyIndex)
{
    if (!proxyIndex.isValid()) {
        return;
    }
    auto index = tableFilter->mapToSource(proxyIndex);
    if (!index.isValid()) {
        return;
    }
    auto item = tableModel->itemFromIndex(index);
    if (item == nullptr) {
        return;
    }
    fieldModel->clear();
    auto table = item->text();
    Database db(connectArgs);
    auto fields = db.tableFields(table);
    db.disconnect();
    foreach (auto field, fields) {
        fieldModel->appendRow(new QStandardItem(field.name()));
    }
}

void DataQueryForm::onFindTable(const QString &text)
{
    tableFilter->setFilterRegularExpression(text);
}

void DataQueryForm::onFindField(const QString &text)
{
    fieldFilter->setFilterRegularExpression(text);
}
