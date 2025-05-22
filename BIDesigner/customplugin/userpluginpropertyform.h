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
#ifndef USERPLUGINPROPERTYFORM_H
#define USERPLUGINPROPERTYFORM_H

#include "ipropertyform.h"
#include "zoneproperty.h"
#include <QWidget>

class AbstractZoneItem;
namespace Ui {
class UserPluginPropertyForm;
}

class UserPluginPropertyForm : public IPropertyForm
{
    Q_OBJECT

public:
    explicit UserPluginPropertyForm(QWidget *parent = nullptr);
    ~UserPluginPropertyForm();
    // IPropertyForm interface
    void updateData() override;
    ICustomGraphic *getGraphicItem() override;
    void setGraphicItem(ICustomGraphic *graphic) override;
private slots:
    void on_roundChecked_toggled(bool checked);
    void on_roundSize_valueChanged(int arg1);
    void on_rotation_valueChanged(double arg1);
    void posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio);
    void lineStyleChanged(Qt::PenStyle style, QColor Color, int width);
    void on_restoreBtn_clicked();

private:
    Ui::UserPluginPropertyForm *ui;
    AbstractZoneItem *graphicItem;
    ZoneProperty attr;
    void initUI();
    void initEvent();

};

#endif // USERPLUGINPROPERTYFORM_H
