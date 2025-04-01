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

#ifndef BIUNDOCOMMAND_H
#define BIUNDOCOMMAND_H

#include "undoobject.h"

#include <QUndoCommand>
#include <QVariant>

class BIUndoCommand : public QUndoCommand
{
public:
    BIUndoCommand(UndoObject *obj, QVariant undoData, QVariant redoData, QUndoCommand *parent = nullptr);
    BIUndoCommand(UndoObject *obj, QVariant undoData, QVariant redoData, const QString &text, QUndoCommand *parent = nullptr);

    // QUndoCommand interface
    void undo() override;
    void redo() override;
private:
    UndoObject *obj;
    QVariant undoData;
    QVariant redoData;
};

#endif // BIUNDOCOMMAND_H
