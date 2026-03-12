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
#ifndef DATAPROPERTYFORM_H
#define DATAPROPERTYFORM_H

#include "datahandler/dataaction.h"
#include "undoobject.h"
#include <QWidget>

class ICustomGraphic;
class DataEditorForm;
namespace Ui {
class DataPropertyForm;
}

class DataPropertyForm : public QWidget, public UndoObject
{
    Q_OBJECT

public:
    explicit DataPropertyForm(QWidget *parent = nullptr);
    ~DataPropertyForm();
    void setGraphicItem(ICustomGraphic *item);
    // UndoObject 接口实现
    void undo(QVariant undoData) override;
    void redo(QVariant redoData) override;
Q_SIGNALS:
    void undoEvent(const QString &text, QVariant undoData, QVariant redoData) override;
protected Q_SLOTS:
    void onNewDataProperty();
    void onEditDataProperty();
    void onDelDataProperty();
    void onDataChanged(DataAction action);
private:
    Ui::DataPropertyForm *ui;
    // 当前图元对象
    ICustomGraphic *graphicItem;
    QString graphicId{""};
    // 配置编辑窗口
    DataEditorForm *dataEditor;
    // 添加数据标志
    bool newFlag{false};

    void initUI();
    void addTableItem(DataAction action, int beforeIndex = -1);
    // UndoObject 辅助方法
    void undoTrigger(QString text, QList<UndoAction> actions);
    void parseUndoAction(QVariant undoData, bool isUndo);
    /**
     * @brief 普通的撤销命令
     * @param action 命令动作名词
     * @param data 数据
     * @param isUndo true 执行撤销，false 执行redo
     */
    void commonAction(QString action, QVariant data, bool isUndo = true);
    int findTableItem(const QString &dataId);
};

#endif // DATAPROPERTYFORM_H
