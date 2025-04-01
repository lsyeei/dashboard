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

#ifndef COMBOEDITOR_H
#define COMBOEDITOR_H

#include <QKeyEvent>
#include <QLineEdit>


class ComboEditor : public QLineEdit
{
    Q_OBJECT
public:
    ComboEditor(QWidget *parent = nullptr) : QLineEdit(parent){};
    ~ComboEditor() = default;
signals:
    void editEnd();

    // QWidget interface
protected:
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

inline void ComboEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        emit editEnd();
        event->accept();
    }
    QLineEdit::keyPressEvent(event);
}

inline void ComboEditor::focusOutEvent(QFocusEvent *event)
{
    emit editEnd();
    event->accept();
}


#endif // COMBOEDITOR_H
