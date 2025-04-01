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

#ifndef UNDOOBJECT_H
#define UNDOOBJECT_H

#include <QVariant>

class UndoObject
{
public:
    UndoObject(){};
    virtual void undo(QVariant undoData) = 0;
    virtual void redo(QVariant redoData) = 0;
    /**
     * @brief undo事件信号
     * @param text 改变信息描述
     * @param undoData 撤销数据
     * @param redoData 重做数据
     */
    Q_SIGNAL virtual void undoEvent(const QString &text, QVariant undoData, QVariant redoData) = 0;

};

#endif // UNDOOBJECT_H
