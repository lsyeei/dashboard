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
#include "datadialog.h"
#include "datasourcemanager.h"
#include "idatasourceplugin.h"
#include "jsutil/jsutil.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "ui_datadialog.h"
#include <QJSEngine>
#include <syntaxfactory.h>

DataDialog::DataDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataDialog)
{
    ui->setupUi(this);
    ui->processWidget->setVisible(false);
    ui->processCheck->setChecked(false);
    ui->codeTestBtn->setVisible(false);
    ui->processSplitter->setStretchFactor(0,3);
    ui->processSplitter->setStretchFactor(1,1);
    SyntaxFactory::instance()->highlightDocument(ui->processCodeEdit->document(), "javascript");
    ui->processCodeEdit->setPlainText(R"((data)=>{
        return{
            value:data
        }
    })");
    connect(ui->cancelBtn, &QPushButton::clicked,
            this, [&]{this->reject();});
    connect(ui->okBtn, &QPushButton::clicked,
            this,[&]{if(validate()) accept();});
    connect(ui->processCheck, &QCheckBox::checkStateChanged,
            this,[&]{
        ui->processWidget->setVisible(ui->processCheck->isChecked());
        ui->codeTestBtn->setVisible(ui->processCheck->isChecked());
    });
    connect(ui->codeTestBtn, &QPushButton::clicked, this, &DataDialog::onTestProcessCode);
}

DataDialog::~DataDialog()
{
    delete ui;
}

void DataDialog::setData(DataMarketDO dataObj)
{
    data = dataObj;
    auto dataSource = data.getDataSource();
    // 显示插件窗口
    auto pluginId = dataSource.get_sourcePluginId();
    if (pluginId.isEmpty()) {
        return;
    }
    auto plugin = DataSourceManager::instance()->getPluginById(pluginId);
    if (plugin == nullptr) {
        return;
    }
    if (!queryWidget.isNull()) {
        ui->dataWidget->layout()->removeWidget(queryWidget);
        queryWidget.clear();
    }
    queryWidget = plugin->dataWidget();
    queryWidget->setDataSource(dataSource.get_sourceArgs());
    queryWidget->setArgs(data.get_requestArgs());
    ui->dataWidget->layout()->addWidget(queryWidget);
    // 显示其它内容
    ui->dataNameEdit->setText(data.get_dataName());
    ui->periodSpin->setValue(data.get_requestPeriod());
    ui->noteEdit->setText(data.get_note());
    auto code = data.get_processCode();
    if (!code.isEmpty()) {
        ui->processCheck->setChecked(true);
        ui->processCodeEdit->setPlainText(code);
        ui->processWidget->setVisible(true);
        ui->codeTestBtn->setVisible(true);
    }else{
        ui->processWidget->setVisible(false);
        ui->processCheck->setChecked(false);
        ui->codeTestBtn->setVisible(false);
    }
}

DataMarketDO DataDialog::getData()
{
    updateData();
    return data;
}

void DataDialog::onTestProcessCode()
{
    auto code = ui->processCodeEdit->toPlainText().trimmed();
    if (code.isEmpty()){
        return;
    }
    updateData();
    // 获取数据源内容
    auto source = data.getDataSource();
    auto plugin = DataSourceManager::instance()->getPluginById(source.get_sourcePluginId());
    if (plugin == nullptr) {
        ui->codeTestEdit->setPlainText("data source not found");
        return;
    }
    auto dataSource = plugin->dataSource();
    if (dataSource == nullptr) {
        ui->codeTestEdit->setPlainText("data source is null");
        return;
    }
    if(!dataSource->connect(source.get_sourceArgs())){
        ui->codeTestEdit->setPlainText("data source connect falied");
        return;
    }
    auto queryData = dataSource->query(data.get_requestArgs());

    // 设置js参数
    auto jsutil = JSUtil::instance();
    QJSValueList args;
    args << jsutil->jsonDocToJSValue(queryData);

    // 执行js代码
    auto result = jsutil->evaluate(code, args);
    ui->codeTestEdit->setPlainText(jsutil->JSValueToString(result));
}

void DataDialog::updateData()
{
    data.set_dataName(ui->dataNameEdit->text().trimmed());
    data.set_requestPeriod(ui->periodSpin->value());
    data.set_note(ui->noteEdit->text().trimmed());
    data.set_requestArgs(queryWidget->getArgs());
    data.set_processCode(ui->processCodeEdit->toPlainText());
}

bool DataDialog::validate()
{
    if (ui->dataNameEdit->text().trimmed().isEmpty()) {
        ui->dataNameEdit->setFocus();
        return false;
    }
    return true;
}
