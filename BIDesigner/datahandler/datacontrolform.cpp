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
#include "animation/animationfactory.h"
#include "bigraphicsscene.h"
#include "datasource/datasourceform.h"
#include "icustomgraphic.h"
#include "qjsonarray.h"
#include "ui_datacontrolform.h"

#include <datahandler/controlaction.h>

#include <QJsonDocument>

#define DATA_ROLE Qt::UserRole + 1

DataControlForm::DataControlForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataControlForm)
{
    ui->setupUi(this);
    initUI();
}

DataControlForm::~DataControlForm()
{
    delete ui;
}

void DataControlForm::initStateOption(ICustomGraphic* customGraphic)
{
    QSignalBlocker stateBlocker(ui->stateOptions);
    ui->stateOptions->clear();
    auto stateStr = customGraphic->getCustomData("stateSet");
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(stateStr.toUtf8(), &error);
    if (doc.isArray()) {
        auto array = doc.array();
        foreach (auto it, array) {
            if(!it.isObject()){
                continue;
            }
            auto obj = it.toObject();
            auto id = obj["id"].toInt();
            auto name = obj["name"].toString();
            ui->stateOptions->addItem(name, QVariant::fromValue(NamedId(id, name)));
        }
        ui->stateOptions->setCurrentIndex(-1);
    }else{
        qWarning() << __FUNCTION__ << "get graphic stateSet error:"
                   << error.errorString();
    }
}

void DataControlForm::initPropertyOption(ICustomGraphic* customGraphic)
{
    QSignalBlocker blocker(ui->propertyOptions);
    ui->propertyOptions->clear();
    auto list = customGraphic->metadataList();
    foreach (auto meta, list) {
        if (meta.mode== OperateMode::ReadOnly ||
            meta.name.compare("state") == 0) {
            continue;
        }
        ui->propertyOptions->addItem(meta.alias, QVariant::fromValue(meta));
    }
    ui->propertyOptions->setCurrentIndex(-1);
}

void DataControlForm::initAnimationOption(ICustomGraphic* customGraphic)
{
    if (customGraphic == nullptr) {
        return;
    }
    auto scene = customGraphic->scene();
    auto s = dynamic_cast<BIGraphicsScene*>(scene);
    if (s == nullptr){
        return;
    }
    auto graophicId = s->getItemId(customGraphic);
    auto groups = AnimationFactory::instance()->graphicAnimation(graophicId);
    foreach (auto group, groups) {
        ui->animationOptions->addItem(group.getName(),
                QVariant::fromValue(NamedId(group.getId(), group.getName())));
    }
    ui->animationOptions->setCurrentIndex(-1);
}

void DataControlForm::selectStateOption(NamedId data)
{
    auto index = ui->stateOptions->count() - 1;
    for(;index >= 0; --index){
        auto option = ui->stateOptions->itemData(index).value<NamedId>();
        if (option.getId() == data.getId()) {
            break;
        }
    }
    ui->stateOptions->setCurrentIndex(index);
    ui->stateWidget->setVisible(true);
}

void DataControlForm::selectAnimationOption(NamedId data)
{
    auto index = ui->animationOptions->count() - 1;
    for(;index >= 0; --index){
        auto option = ui->animationOptions->itemData(index).value<NamedId>();
        if (option.getId() == data.getId()) {
            break;
        }
    }
    ui->animationOptions->setCurrentIndex(index);
    ui->animateWidget->setVisible(true);
}

void DataControlForm::setGraphicsItem(QGraphicsItem *item)
{
    graphic = item;
    auto customGraphic = dynamic_cast<ICustomGraphic*>(item);
    // 获取状态选项
    initStateOption(customGraphic);
    // 获取属性选项
    initPropertyOption(customGraphic);
    // 获取图元动画
    initAnimationOption(customGraphic);
}

void DataControlForm::setData(QVariant action)
{
    if (!action.canConvert<ControlAction>()) {
        return;
    }
    controlAction = action.value<ControlAction>();
    QSignalBlocker tableBlocker(ui->actionTable);
    reset();
    foreach (auto item, controlAction.getLogicList()) {
        addActionTableItem(item);
    }
    ui->actionTable->clearSelection();
}

void DataControlForm::controlTypeChanged(int index)
{
    Q_UNUSED(index)
    auto controlType = ui->controlOptions->currentData().value<ControlType>();
    ui->stateWidget->setVisible(controlType == ControlType::SWITCH_STATE);
    ui->animateWidget->setVisible(controlType == ControlType::PLAY_ANIMATION);
    ui->propertyWidget->setVisible(controlType == ControlType::SET_PROPERTY);
    dataChanged();
}

void DataControlForm::symbolChanged(int index)
{
    Q_UNUSED(index)
    auto symbol = ui->symbolOptions->itemData(index).value<LogicSymbol>();
    bool flag = symbol == LogicSymbol::RANGE;
    ui->minValueSpin->setVisible(true);
    ui->valueSpliter->setVisible(flag);
    ui->maxValueSpin->setVisible(flag);
    if (!ui->controlOptions->isVisible()) {
        showControlOption(true);
        auto count = ui->controlOptions->count();
        int index = count>0?0:-1;
        ui->controlOptions->setCurrentIndex(index);
    }
    dataChanged();
}

void DataControlForm::addLogic()
{
    newFlag = true;

    ui->actionTable->blockSignals(true);
    ui->actionTable->clearSelection();
    reset(false);
    ui->configWidget->setVisible(true);
    ui->actionTable->blockSignals(false);
    QSignalBlocker controlBlocker(ui->controlOptions);
    auto count = ui->controlOptions->count();
    int index = count>0?0:-1;
    ui->controlOptions->setCurrentIndex(index);
}

void DataControlForm::delLogic()
{
    auto row = ui->actionTable->currentRow();
    if(row < 0){
        return;
    }
    auto item = ui->actionTable->item(row,0);    
    ui->actionTable->removeRow(row);
    ui->actionTable->clearSelection();
    ui->configWidget->setVisible(false);
    // 发出改动信号
    collectAndEmit();
}

void DataControlForm::onStateChanged()
{
    dataChanged();
}

void DataControlForm::onPropertyChanged()
{
    if (ui->propertyOptions->currentIndex() < 0) {
        ui->propertyLabel->setText("");
        return;
    }
    auto meta = ui->propertyOptions->currentData().value<CustomMetadata>();
    QString text{"数据类型：%1 \r\n例:  %2"};
    text = text.arg(meta.dataTypeName(), meta.dataExample);
    ui->propertyLabel->setText(text);
    dataChanged();
}

void DataControlForm::editLogic()
{
    newFlag = false;
    ui->configWidget->setVisible(true);
    auto row = ui->actionTable->currentRow();
    if(row < 0){
        reset(false);
        return;
    }
    auto item = ui->actionTable->item(row,0);
    auto logic = item->data(DATA_ROLE).value<ControlLogic>();

    QSignalBlocker symbolBlocker(ui->symbolOptions);
    QSignalBlocker controlBlocker(ui->controlOptions);
    QSignalBlocker stateBlocker(ui->stateOptions);
    QSignalBlocker animateBlocker(ui->animationOptions);
    QSignalBlocker propertyBlocker(ui->propertyOptions);
    QSignalBlocker minValueBlocker(ui->minValueSpin);
    QSignalBlocker maxValueBlocker(ui->maxValueSpin);

    auto symbol = logic.getsymbol();
    int index = ui->symbolOptions->findData(QVariant::fromValue(symbol));
    ui->symbolOptions->setCurrentIndex(index);
    if(symbol == LogicSymbol::RANGE){
        auto range = logic.getRange();
        ui->minValueSpin->setValue(range.first);
        ui->maxValueSpin->setValue(range.second);
        showRangeValue(true);

    }else{
        ui->minValueSpin->setValue(logic.getThreshold());
        showRangeValue(false);
    }

    ui->controlLabel->setVisible(true);
    ui->controlOptions->setVisible(true);
    auto controlType = logic.getControlType();
    index = ui->controlOptions->findData(QVariant::fromValue(controlType));
    ui->controlOptions->setCurrentIndex(index);
    AssignAction assignAction;
    switch (controlType) {
    case ControlType::SWITCH_STATE:
        selectStateOption(logic.getSwitchState());
        break;
    case ControlType::PLAY_ANIMATION:
        selectAnimationOption(logic.getAnimation());
        break;
    case ControlType::SET_PROPERTY:
        assignAction = logic.getControlObj().value<AssignAction>();
        auto index = ui->propertyOptions->count() - 1;
        for (; index >= 0; -- index) {
            auto meta = ui->propertyOptions->itemData(index).value<CustomMetadata>();
            if (meta.name.compare(assignAction.getPropertyName()) == 0) {
                break;
            }
        }
        ui->propertyOptions->setCurrentIndex(index);
        ui->propertyValueEdit->setText(assignAction.getDefaultValue());
        ui->propertyWidget->setVisible(true);
        break;
    }
}

void DataControlForm::initUI()
{
    layout()->setAlignment(Qt::AlignTop);
    ui->animateWidget->setVisible(false);
    ui->stateWidget->setVisible(false);
    ui->propertyWidget->setVisible(false);
    ui->configWidget->setVisible(false);

    auto symbolList = ControlAction::logicSymbolList();
    foreach (auto item, symbolList) {
        ui->symbolOptions->addItem(item.getName(), item.getId());
    }
    ui->symbolOptions->setCurrentIndex(-1);
    auto controlTypeList = ControlAction::controlTypeList();
    foreach (auto item, controlTypeList) {
        ui->controlOptions->addItem(item.getName(), item.getId());
    }
    ui->controlOptions->setCurrentIndex(-1);

    ui->stateOptions->setCurrentIndex(-1);
    ui->animationOptions->setCurrentIndex(-1);
    ui->propertyOptions->setCurrentIndex(-1);
    ui->minValueSpin->setVisible(false);
    ui->valueSpliter->setVisible(false);
    ui->maxValueSpin->setVisible(false);

    // 表格设置
    ui->actionTable->setColumnCount(3);
    ui->actionTable->setHorizontalHeaderLabels({"条件","动作","内容"});
    ui->actionTable->setColumnWidth(0, 60);
    ui->actionTable->setColumnWidth(1, 60);
    ui->actionTable->setColumnWidth(2, 100);
    ui->actionTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->actionTable->setVerticalHeader(new NumberHeader{Qt::Vertical});
    ui->actionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->actionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->actionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->addBtn, &QToolButton::clicked,
            this, &DataControlForm::addLogic);
    connect(ui->actionTable, &QTableWidget::itemSelectionChanged,
            this, &DataControlForm::editLogic);
    connect(ui->delBtn, &QToolButton::clicked, this, &DataControlForm::delLogic);
    connect(ui->controlOptions, &QComboBox::currentIndexChanged,
            this, &DataControlForm::controlTypeChanged);
    connect(ui->symbolOptions, &QComboBox::currentIndexChanged,
            this, &DataControlForm::symbolChanged);
    connect(ui->animationOptions, &QComboBox::currentIndexChanged,
            this, [&]{dataChanged();});
    connect(ui->stateOptions, &QComboBox::currentIndexChanged,
            this, &DataControlForm::onStateChanged);
    connect(ui->propertyOptions, &QComboBox::currentIndexChanged,
            this, &DataControlForm::onPropertyChanged);
    connect(ui->propertyValueEdit, &QLineEdit::editingFinished,
            this, [&]{dataChanged();});
    connect(ui->minValueSpin, &QDoubleSpinBox::editingFinished,
            this, [&]{dataChanged();});
    connect(ui->maxValueSpin, &QDoubleSpinBox::editingFinished,
            this, [&]{dataChanged();});
}

void DataControlForm::reset(bool includeTable)
{
    if(includeTable){
        QSignalBlocker tableBlocker(ui->actionTable);
        ui->actionTable->clearSelection();
        ui->actionTable->clearContents();
        ui->actionTable->setRowCount(0);
    }

    QSignalBlocker symbolBlocker(ui->symbolOptions);
    QSignalBlocker controlBlocker(ui->controlOptions);
    QSignalBlocker stateBlocker(ui->stateOptions);
    QSignalBlocker animateBlocker(ui->animationOptions);
    QSignalBlocker propertyBlocker(ui->propertyOptions);
    QSignalBlocker minValueBlocker(ui->minValueSpin);
    QSignalBlocker maxValueBlocker(ui->maxValueSpin);

    ui->animateWidget->setVisible(false);
    ui->stateWidget->setVisible(false);
    ui->propertyWidget->setVisible(false);
    ui->configWidget->setVisible(false);

    showControlOption(false);
    ui->controlOptions->setCurrentIndex(-1);
    ui->stateOptions->setCurrentIndex(-1);
    ui->symbolOptions->setCurrentIndex(-1);
    ui->animationOptions->setCurrentIndex(-1);
    ui->propertyOptions->setCurrentIndex(-1);
    ui->minValueSpin->setVisible(false);
    ui->valueSpliter->setVisible(false);
    ui->maxValueSpin->setVisible(false);
}

void DataControlForm::addActionTableItem(ControlLogic logic)
{
    auto row = ui->actionTable->rowCount();
    ui->actionTable->insertRow(row);
    auto item = new QTableWidgetItem(logic.symbolSummary());
    item->setData(DATA_ROLE, QVariant::fromValue(logic));
    ui->actionTable->setItem(row, 0, item);

    ui->actionTable->setItem(row, 1, new QTableWidgetItem(logic.controlTypeName()));

    ui->actionTable->setItem(row, 2, new QTableWidgetItem(logic.controlObjName()));
}

void DataControlForm::showRangeValue(bool flag)
{
    ui->minValueSpin->setVisible(true);
    ui->maxValueSpin->setVisible(flag);
    ui->valueSpliter->setVisible(flag);
}

void DataControlForm::dataChanged()
{
    // 获取当前动作逻辑
    ControlLogic logic;
    auto row = ui->actionTable->currentRow();
    if (!newFlag) {
        auto item = ui->actionTable->item(row, 0);
        if (item == nullptr) {
            return;
        }
        logic = item->data(DATA_ROLE).value<ControlLogic>();
    }
    // 获取条件数据
    auto symbol = ui->symbolOptions->currentData().value<LogicSymbol>();
    logic.setsymbol(symbol);
    if (symbol == LogicSymbol::RANGE) {
        logic.setRange(ui->minValueSpin->value(), ui->maxValueSpin->value());
    }else{
        logic.setThreshold(ui->minValueSpin->value());
    }
    // 获取控制方式
    auto controlType = ui->controlOptions->currentData().value<ControlType>();
    logic.setControlType(controlType);
    switch (controlType) {
    case ControlType::SWITCH_STATE:
        logic.setControlObj(ui->stateOptions->currentData());
        break;
    case ControlType::PLAY_ANIMATION:
        logic.setControlObj(ui->animationOptions->currentData());
        break;
    case ControlType::SET_PROPERTY:
        AssignAction act;
        auto meta = ui->propertyOptions->currentData().value<CustomMetadata>();
        act.setPropertyName(meta.name);
        act.setPropertyAlias(ui->propertyOptions->currentText());
        act.setDefaultValue(ui->propertyValueEdit->text().trimmed());
        logic.setControlObj(QVariant::fromValue(act));
        break;
    }
     if (newFlag) {
        // 保存新建数据
        ui->actionTable->blockSignals(true);
        addActionTableItem(logic);
        auto index = ui->actionTable->rowCount()-1;
        ui->actionTable->selectRow(index);
        ui->actionTable->setCurrentItem(ui->actionTable->item(index,0));
        ui->actionTable->blockSignals(false);
        newFlag = false;
     }else{
         auto item = ui->actionTable->item(row, 0);
         item->setText(logic.symbolSummary());
         item->setData(DATA_ROLE, QVariant::fromValue(logic));
         item = ui->actionTable->item(row, 1);
         item->setText(logic.controlTypeName());
         item = ui->actionTable->item(row, 2);
         item->setText(logic.controlObjName());
     }
     // 获取全部数据，并触发数据变更信号
     collectAndEmit();
}

void DataControlForm::collectAndEmit()
{
    QList<ControlLogic> list;
    int count = ui->actionTable->rowCount();
    for (int i = 0; i < count; ++i) {
        auto item = ui->actionTable->item(i,0);
        if(item){
            list << item->data(DATA_ROLE).value<ControlLogic>();
        }
    }
    controlAction.setLogicList(list);
    emit changedEvent(QVariant::fromValue(controlAction));
}

void DataControlForm::showControlOption(bool flag)
{
    ui->controlOptions->setVisible(flag);
    ui->controlLabel->setVisible(flag);
}
