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
#include "datacontrolform.h"
#include "dataeditorform.h"
#include "dataassignform.h"
#include "datasource/datasourceform.h"
#include "dataactionmanager.h"
#include "ui_dataeditorform.h"

#include <QPushButton>

DataEditorForm::DataEditorForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataEditorForm)
{
    ui->setupUi(this);
    initUI();
}

DataEditorForm::~DataEditorForm()
{
    delete ui;
}

void DataEditorForm::reset()
{
    controlForm->reset();
    assignForm->reset();
    ui->dataEdit->clear();
    ui->controlTypeWidget->setVisible(false);
    controlForm->setVisible(false);
    assignForm->setVisible(false);
    action = DataAction();
}

void DataEditorForm::setGraphicsItem(QGraphicsItem *item)
{
    graphic = item;
    controlForm->setGraphicsItem(item);
    assignForm->setGraphicsItem(item);
}

void DataEditorForm::setData(DataAction data)
{
    action = data;
    if (data.getDataId().isEmpty()) {
        return;
    }
    QSignalBlocker dataBlocker(ui->dataEdit);
    auto dataMarketDo = data.getData();
    auto source = dataMarketDo.getDataSource();
    updateDataEdit(dataMarketDo);

    auto actionType = data.getActionType();
    QSignalBlocker controlBlocker(ui->controlRadio);
    QSignalBlocker assignBlocker(ui->assignmentRadio);
    QSignalBlocker cFormlBlocker(controlForm);
    QSignalBlocker aFormBlocker(assignForm);
    bool flag = actionType == ActionType::CONTROL_GRAPHIC;
    ui->controlTypeWidget->setVisible(true);
    ui->controlRadio->setChecked(flag);
    controlForm->setVisible(flag);
    ui->assignmentRadio->setChecked(!flag);
    assignForm->setVisible(!flag);
    if (flag) {
        controlForm->setData(action.getAction());
        assignForm->setData(QVariant::fromValue(AssignAction()));
    }else{
        assignForm->setData(action.getAction());
        controlForm->setData(QVariant::fromValue(ControlAction()));
    }
}

void DataEditorForm::changeDetailWidget()
{
    bool flag = ui->controlRadio->isChecked();
    assignForm->setVisible(!flag);
    controlForm->setVisible(flag);
    if (flag) {
        action.setActionType(ActionType::CONTROL_GRAPHIC);
        action.setAction(QVariant::fromValue(controlForm->getData()));
    }else{
        action.setActionType(ActionType::ASSIGN_PROPERTY);
        action.setAction(QVariant::fromValue(assignForm->getData()));
    }
    // 发出消息
    emit changedEvent(action);
}

void DataEditorForm::onSelectData()
{
    if (selectorDlg == nullptr) {
        selectorDlg = new QDialog(this);
        selectorDlg->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        selectorDlg->setWindowTitle(tr("选择数据"));

        auto btnBox = new QDialogButtonBox(Qt::Horizontal, selectorDlg);
        btnBox->addButton(tr("确定"), QDialogButtonBox::AcceptRole);
        btnBox->addButton(tr("取消"), QDialogButtonBox::RejectRole);
        connect(btnBox, &QDialogButtonBox::accepted, selectorDlg, &QDialog::accept);
        connect(btnBox, &QDialogButtonBox::rejected, selectorDlg, &QDialog::reject);

        auto dlgLayout = new QVBoxLayout(selectorDlg);
        dlgLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        selectorDlg->setLayout(dlgLayout);

        dataSource = new DataSourceForm(this);
        dataSource->setEditable(false);
        dlgLayout->addWidget(dataSource);
        dlgLayout->addWidget(btnBox);
    }
    if (selectorDlg->exec() == QDialog::Rejected){
        return;
    }
    // 获取选中的数据
    auto data = dataSource->getSelectedData();
    // 更新UI
    updateDataEdit(data);
    ui->controlTypeWidget->setVisible(true);
    QSignalBlocker controlBlocker(ui->controlRadio);
    controlForm->reset();
    assignForm->reset();
    ui->controlRadio->setChecked(true);
    controlForm->setVisible(true);
    assignForm->setVisible(false);
    // 存储数据
    action.setData(data);
    action.setDataId(data.get_uuid());
    action.setSourceId(data.getDataSource().get_uuid());
    action.setActionType(ActionType::CONTROL_GRAPHIC);
    // 发出消息
    emit changedEvent(action);
}

void DataEditorForm::onActionChanged(QVariant data)
{
    action.setAction(data);
    emit changedEvent(action);
}

void DataEditorForm::onTestBtnClicked()
{
    ui->testInfo->setText("");
    if (graphic == nullptr ||
        action.getDataId().isEmpty() ||
        action.getSourceId().isEmpty() ||
        action.getAction().isNull()) {
        return;
    }
    auto actManager = DataActionManager::instance();
    connect(actManager, &DataActionManager::actionTestEnd,
            this, [&](const QString &info){
        ui->testInfo->setText(info);
    }, Qt::SingleShotConnection);
    actManager->testDataAction(action);
}

void DataEditorForm::initUI()
{
    layout()->setAlignment(Qt::AlignTop);
    ui->controlTypeWidget->setVisible(false);
    ui->controlRadio->setChecked(true);
    controlForm = new DataControlForm(this);
    assignForm = new DataAssignForm(this);
    auto vBox = dynamic_cast<QVBoxLayout*>(layout());
    auto index = vBox->indexOf(ui->testLayout);
    vBox->insertWidget(index, controlForm);
    vBox->insertWidget(index, assignForm);
    controlForm->setVisible(false);
    assignForm->setVisible(false);

    connect(ui->controlRadio, &QRadioButton::clicked,
            this, &DataEditorForm::changeDetailWidget);
    connect(ui->assignmentRadio, &QRadioButton::clicked,
            this, &DataEditorForm::changeDetailWidget);
    connect(ui->dataSelectBtn, &QPushButton::clicked,
            this, &DataEditorForm::onSelectData);
    connect(controlForm, &DataControlForm::changedEvent,
            this, &DataEditorForm::onActionChanged);
    connect(assignForm, &DataAssignForm::changedEvent,
            this, &DataEditorForm::onActionChanged);

    connect(ui->testBtn, &QPushButton::clicked,
            this, &DataEditorForm::onTestBtnClicked);
}

void DataEditorForm::updateDataEdit(DataMarketDO data)
{
    auto source = data.getDataSource();
    auto dirName = source.getSourceName();
    auto dataName = data.get_dataName();
    auto text = QString{"%1->%2"};
    if (dirName.isEmpty() || dataName.isEmpty()) {
        if (!dataName.isEmpty()) {
            text = dataName;
        }else{
            text = "";
        }
    }else{
        text = text.arg(dirName, dataName);
    }
    ui->dataEdit->setText(text);
}
