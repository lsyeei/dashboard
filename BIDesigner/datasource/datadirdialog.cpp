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
#include "datadirdialog.h"
#include "datasourcepluginmanager.h"
#include "idatasourceplugin.h"
#include "ui_datadirdialog.h"

#include <QMessageBox>
#include <QResizeEvent>

DataDirDialog::DataDirDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataDirDialog)
{
    ui->setupUi(this);
    layout()->setAlignment(Qt::AlignTop);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setSizePolicy(QSizePolicy{QSizePolicy::Preferred,QSizePolicy::Preferred});

    initDataSourceOption();
    toInitState();
    connect(ui->dataSourceCheckBox, &QCheckBox::checkStateChanged,
            this, &DataDirDialog::onCheckDataSource);
    connect(ui->dataSourceComboBox, &QComboBox::currentIndexChanged,
            this, &DataDirDialog::onDataSourceChanged);
    connect(ui->okButton, &QPushButton::clicked,
            this, [&]{if (validation()){accept();}});
    connect(ui->cancelButton, &QPushButton::clicked,
            this, [&]{reject();});
    connect(ui->topRadio, &QRadioButton::clicked,
            this, &DataDirDialog::onTopChecked);
    connect(ui->childRadio, &QRadioButton::clicked,
            this, &DataDirDialog::onTopChecked);
}

DataDirDialog::~DataDirDialog()
{
    delete ui;
}

void DataDirDialog::setData(DataDirDO dataDir)
{
    data = dataDir;
    auto parentId = dataDir.get_parentId();
    if (parentId < 0) {
        ui->topRadio->setChecked(true);
        ui->childRadio->setVisible(false);
        ui->parentItem->setVisible(false);
    }else{
        ui->childRadio->setVisible(true);
        ui->parentItem->setVisible(true);
        ui->topRadio->setChecked(false);
        ui->childRadio->setChecked(true);
        ui->parentItem->setText(tr("上级分类：") + dataDir.getParentName());
    }
    ui->dirNameEdit->setText(dataDir.get_name());
    auto dataSource = dataDir.getDataSource();
    if (dataSource.isEmpty()) {
        ui->dataSourceCheckBox->setChecked(false);
    }else{
        ui->dataSourceCheckBox->setChecked(true);
        // 查找数据源
        auto pluginId = dataSource.get_sourcePluginId();
        auto index = ui->dataSourceComboBox->findData(pluginId);
        if (index < 0) {
            return;
        }
        // 选中数据源
        ui->dataSourceComboBox->setCurrentIndex(index);
        auto plugin = DataSourcePluginManager::instance()->getPluginById(pluginId);
        auto widget = plugin->connectWidget();
        // 显示数据源参数
        widget->setArgs(dataSource.get_sourceArgs());
        if (!connectWidget.isNull()) {
            ui->dataSourceWidget->layout()->removeWidget(connectWidget);
            connectWidget.clear();
        }
        connectWidget = widget;
        ui->dataSourceWidget->layout()->addWidget(connectWidget);
    }
}

DataDirDO DataDirDialog::getData()
{
    data.set_name(ui->dirNameEdit->text().trimmed());
    data.set_groupId(DataDirDO::GROUP_ID);
    if (ui->topRadio->isChecked()) {
        data.set_parentId(-1);
    }
    if (ui->dataSourceCheckBox->isChecked()) {
        auto source = data.getDataSource();
        auto pluginId = ui->dataSourceComboBox->currentData().toString();
        if(!connectWidget.isNull()){
            auto args = connectWidget->getArgs();
            // 设置数据源参数
            source.set_sourcePluginId(pluginId);
            source.set_sourceArgs(args);
        }
        data.setDataSource(source);
    } else {
        data.setDataSource(DataSourceDO{});
    }

    return data;
}

void DataDirDialog::onCheckDataSource(Qt::CheckState state)
{
    if (state == Qt::Checked) {
        ui->dataSourceComboBox->setVisible(true);
        ui->dataSourceComboBox->setCurrentIndex(-1);
    }else{
        ui->dataSourceComboBox->setVisible(false);
        ui->dataSourceWidget->setVisible(false);
    }
}

void DataDirDialog::onDataSourceChanged(int index)
{
    // 获取选中数据源信息
    auto pluginId = ui->dataSourceComboBox->currentData().toString();
    if (pluginId.isEmpty()) {
        return;
    }
    auto plugin = DataSourcePluginManager::instance()->getPluginById(pluginId);
    if (plugin == nullptr) {
        return;
    }
    auto widget = plugin->connectWidget();
    widget->setArgs(data.getDataSource().get_sourceArgs());
    // 显示选中的数据源配置页面
    if (!connectWidget.isNull()) {
        ui->dataSourceWidget->layout()->removeWidget(connectWidget);
        connectWidget.clear();
    }
    connectWidget = widget;
    ui->dataSourceWidget->layout()->addWidget(connectWidget);
    ui->dataSourceWidget->setVisible(true);
}

void DataDirDialog::onTopChecked()
{
    ui->parentItem->setVisible(ui->childRadio->isChecked());
}

void DataDirDialog::initDataSourceOption()
{
    auto plugins = DataSourcePluginManager::instance()->getAllPlugins();
    foreach (auto plugin, plugins) {
        ui->dataSourceComboBox->addItem(plugin->name(), plugin->id());
    }
}

void DataDirDialog::toInitState()
{
    ui->dataSourceCheckBox->setChecked(false);
    ui->dataSourceComboBox->setVisible(false);
    ui->dataSourceWidget->setVisible(false);
}

bool DataDirDialog::validation()
{
    auto name = ui->dirNameEdit->text().trimmed();
    if (name.isEmpty()) {
        ui->dirNameEdit->setFocus();
        QMessageBox::information(this, tr("提示"), tr("分类名不能为空"));
        return false;
    }
    return true;
}
