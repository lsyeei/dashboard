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

#include "bicombobox.h"
#include "comboeditor.h"

#include <QKeyEvent>
#include <ui_bicomboboxform.h>
#include <QLineEdit>

BIComboBox::BIComboBox(QWidget *parent) :
    QWidget(parent), ui(new Ui::ComboBoxForm)
{
    ui->setupUi(this);
    ui->comboBox->setDuplicatesEnabled(false);
}

BIComboBox::~BIComboBox()
{
    delete ui;
}

QComboBox *BIComboBox::getComboBox()
{
    return ui->comboBox;
}

void BIComboBox::clear()
{
    ui->comboBox->clear();
}

int BIComboBox::currentIndex()
{
    return ui->comboBox->currentIndex();
}

void BIComboBox::setCurrentItem(int index)
{
    ui->comboBox->setCurrentIndex(index);
}

QString BIComboBox::itemText(int index)
{
    return ui->comboBox->itemText(index);
}

QVariant BIComboBox::itemData(int index)
{
    return ui->comboBox->itemData(index);
}

void BIComboBox::addItem(QString name, QVariant data)
{
    ui->comboBox->addItem(name, data);
}

void BIComboBox::removeItem(int index)
{
    ui->comboBox->removeItem(index);
}

QSize BIComboBox::sizeHint() const
{
    return {275, 30};
}


QSize BIComboBox::minimumSizeHint() const
{
    return {275, 30};
}

void BIComboBox::on_comboBox_currentIndexChanged(int index)
{
    if (index <0) {
        return;
    }
    emit currentIndexChanged(index);
}


void BIComboBox::on_addBtn_clicked()
{
    ui->comboBox->blockSignals(true);
    ui->comboBox->addItem(tr("新项目"));
    int index = ui->comboBox->count() - 1;
    ui->comboBox->setCurrentIndex(index);
    ui->comboBox->blockSignals(false);
    enableEdit();
    addFlag = true;
}

void BIComboBox::on_removeBtn_clicked()
{
    auto index = ui->comboBox->currentIndex();
    if (index >= 0){
        auto name = ui->comboBox->itemText(index);
        auto data = ui->comboBox->itemData(index);
        ui->comboBox->removeItem(index);
        emit itemRemoved(name, data);
    }
}

void BIComboBox::on_editBtn_clicked()
{
    auto index = ui->comboBox->currentIndex();
    if (index >= 0){
        enableEdit();
        editFlag = true;
    }
}



void BIComboBox::editEnd()
{
    // 修改文字
    auto index = ui->comboBox->currentIndex();
    auto text = ui->comboBox->currentText();
    ui->comboBox->setItemText(index, text);
    ui->comboBox->setEditable(false);
    // qDebug() << "editEnd ......" << index << text << editFlag;
    if (addFlag) {
        emit itemAdded(index);
        addFlag = false;
    }else if (editFlag) {
        emit itemModified(index);
        editFlag = false;
    }
}

void BIComboBox::enableEdit()
{
    ui->comboBox->setEditable(true);
    ComboEditor *editor = new ComboEditor(this);
    ui->comboBox->setLineEdit(editor);
    connect(editor, SIGNAL(editEnd()), this, SLOT(editEnd()));
    ui->comboBox->setFocus(Qt::OtherFocusReason);
    ui->comboBox->lineEdit()->selectAll();
}
