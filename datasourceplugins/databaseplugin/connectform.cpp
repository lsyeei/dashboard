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
#include "connectform.h"
#include "driverdescription.h"
#include "qsqlerror.h"
#include "ui_connectform.h"

#include <QFileDialog>
#include <QListView>
#include <QSqlDatabase>
#include <QToolTip>

ConnectForm::ConnectForm(QWidget *parent)
    : IDataSourceWidget(parent)
    , ui(new Ui::ConnectForm)
{
    ui->setupUi(this);
    ui->fileBtn->setVisible(false);
    ui->connectOptionCheck->setChecked(false);
    ui->connectOptionEdit->setVisible(false);
    initDriverOptions();
    connect(ui->testButton, &QPushButton::clicked,
            this, &ConnectForm::onTestBtnClicked);
    connect(ui->driverCombo, &QComboBox::currentIndexChanged,
            this, &ConnectForm::onDriverChanged);
    connect(ui->fileBtn, &QToolButton::clicked,
            this, &ConnectForm::onFileBtnClicked);
    connect(ui->connectOptionCheck, &QCheckBox::checkStateChanged,
            this, [&]{ui->connectOptionEdit->setVisible(ui->connectOptionCheck->isChecked());});
}

ConnectForm::~ConnectForm()
{
    delete ui;
}

void ConnectForm::initDriverOptions()
{
    foreach(auto driver, drivers){
        ui->driverCombo->addItem(driver.getDbms(), driver.getName());
        auto index = ui->driverCombo->count() - 1;
        ui->driverCombo->setItemData(index, driver.getNote(), Qt::ToolTipRole);
    }
    auto view = qobject_cast<QListView*>(ui->driverCombo->view());
    if (view) {
        // 为列表视图安装事件过滤器
        view->viewport()->installEventFilter(this);
        // 启用提示
        view->viewport()->setMouseTracking(true);
    }
}

void ConnectForm::updateParam()
{
    params.setDriver(ui->driverCombo->currentData().toString());
    params.setHost(ui->hostEdit->text().trimmed());
    params.setPort(ui->portSpin->value());
    params.setDatabaseName(ui->databaseNameEdit->text().trimmed());
    params.setUserName(ui->userNameEdit->text().trimmed());
    params.setPassword(ui->passwordEdit->text().trimmed());
    params.setOptions(ui->connectOptionEdit->toPlainText().trimmed());
}

QString ConnectForm::getArgs()
{
    updateParam();
    return params.toJson();
}

void ConnectForm::setArgs(const QString &args)
{
    // QSignalBlocker driverBlocker(ui->driverCombo);
    // QSignalBlocker hostBlocker(ui->hostEdit);
    // QSignalBlocker portBlocker(ui->portSpin);
    QSignalBlocker databaseBlocker(ui->databaseNameEdit);
    QSignalBlocker userBlocker(ui->userNameEdit);
    QSignalBlocker pswBlocker(ui->passwordEdit);
    QSignalBlocker optionBlocker(ui->connectOptionEdit);
    params = ConnectArg::fromJson(args);
    auto driver = params.getDriver();
    auto index = ui->driverCombo->findData(driver);
    if (index > -1) {
        ui->driverCombo->setCurrentIndex(index);
    }
    ui->hostEdit->setText(params.getHost());
    ui->portSpin->setValue(params.getPort());
    ui->databaseNameEdit->setText(params.getDatabaseName());
    ui->userNameEdit->setText(params.getUserName());
    ui->passwordEdit->setText(params.getPassword());
    ui->connectOptionEdit->setPlainText(params.getOptions());
}

void ConnectForm::onTestBtnClicked()
{
    updateParam();
    auto driver = params.getDriver();
    auto dbName = params.getDatabaseName();
    auto host = params.getHost();
    if (driver.isEmpty() || dbName.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("参数不完整，请检查驱动与数据库配置"));
        return;
    }
    auto connectName = "connectTest";
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, connectName);
    db.setHostName(host);
    db.setDatabaseName(dbName);
    db.setUserName(params.getUserName());
    db.setPassword(params.getPassword());
    int port = params.getPort();
    if(port > 0){
        db.setPort(port);
    }
    auto options = params.getOptions();
    if (!options.isEmpty()) {
        db.setConnectOptions(options);
    }
    if (!db.open()){
        QMessageBox::information(this, tr("提示"),
                tr("数据库连接失败，") + db.lastError().text());
    }else{
        QMessageBox::information(this, tr("提示"), tr("连接成功"));
    }
    db.removeDatabase(connectName);
}

void ConnectForm::onDriverChanged(int index)
{
    Q_UNUSED(index)
    auto driver = ui->driverCombo->currentData().toString();
    bool flag{false};
    if (driver.compare("QSQLITE") == 0) {
        flag = true;
    }
    ui->fileBtn->setVisible(flag);
    ui->hostWidget->setVisible(!flag);
}

void ConnectForm::onFileBtnClicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("打开"),
                        QDir::currentPath(), tr("SQLite(*.*)"));
    if (fileName.isEmpty()) {
        return;
    }
    ui->databaseNameEdit->setText(fileName);
}

bool ConnectForm::eventFilter(QObject *watched, QEvent *event)
{
    // 判断事件是否来自 comboBox 的列表视口
    if (watched == ui->driverCombo->view()->viewport()) {
        if (event->type() == QEvent::ToolTip) {
            QHelpEvent *helpEvent = static_cast<QHelpEvent*>(event);
            // 获取鼠标位置对应的选项索引
            QListView *listView = qobject_cast<QListView*>(ui->driverCombo->view());
            QModelIndex index = listView->indexAt(helpEvent->pos());

            if (index.isValid()) {
                // 设置提示文本
                int itemIndex = index.row();
                if (itemIndex >= 0) {
                    auto tips = ui->driverCombo->itemData(itemIndex, Qt::ToolTipRole).toString();
                    QToolTip::showText(helpEvent->globalPos(), tips);
                } else {
                    QToolTip::hideText();
                }
            } else {
                QToolTip::hideText();
            }
            return true; // 事件已处理
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开时隐藏提示
            QToolTip::hideText();
        }
    }
    return QWidget::eventFilter(watched, event);
}
