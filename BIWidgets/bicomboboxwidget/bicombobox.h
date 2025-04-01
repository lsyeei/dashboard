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

#ifndef BICOMBOBOX_H
#define BICOMBOBOX_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>


class QComboBox;

class ComboEditor;
namespace Ui {
class ComboBoxForm;
}
class QDESIGNER_WIDGET_EXPORT BIComboBox : public QWidget
{
    Q_OBJECT

public:
    explicit BIComboBox(QWidget *parent = nullptr);
    ~BIComboBox();
    QComboBox* getComboBox();
    void clear();
    int currentIndex();
    void setCurrentItem(int index);
    QString itemText(int index);
    QVariant itemData(int index);
    void addItem(QString name, QVariant data);
    void removeItem(int index);
    // QWidget interface
    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void currentIndexChanged(int index);
    void itemRemoved(QString name, QVariant data);
    void itemAdded(int index);
    void itemModified(int index);

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_editBtn_clicked();

    void editEnd();

private:
    Ui::ComboBoxForm *ui;
    bool addFlag{false};
    bool editFlag{false};


    void enableEdit();

};

#endif // BICOMBOBOX_H
