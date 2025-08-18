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

#ifndef IPROPERTYFORM_H
#define IPROPERTYFORM_H

#include "icustomgraphic.h"
#include <QWidget>
class IPropertyForm : public QWidget
{
public:
    IPropertyForm() = delete;
    explicit IPropertyForm(QWidget* parent = nullptr):QWidget(parent){};
    virtual void updateData()=0;
    virtual ICustomGraphic *getGraphicItem() = 0;
    virtual void setGraphicItem(ICustomGraphic *graphic) = 0;
};

#endif // IPROPERTYFORM_H
