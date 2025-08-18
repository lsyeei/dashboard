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

#ifndef LINEPROPERTYFORM_H
#define LINEPROPERTYFORM_H

#include "ipropertyform.h"
#include "linebaseproperty.h"
#include <QWidget>

namespace Ui {
class LinePropertyForm;
}
class AbstractLineItem;
class LinePropertyForm : public IPropertyForm
{
    Q_OBJECT

public:
    explicit LinePropertyForm(QWidget *parent = nullptr);
    ~LinePropertyForm();
    // IPropertyForm interface
    void updateData() override;
    ICustomGraphic *getGraphicItem() override;
    void setGraphicItem(ICustomGraphic *graphic) override;
    void showCornerProperty();
protected Q_SLOTS:
    void onLinePenChanged(Qt::PenStyle style, const QColor &color, int width);
    void onStartTypeChanged(int index);
    void onStartSizeChanged(int value);
    void onEndTypeChanged(int index);
    void onEndSizeChanged(int value);
    void onFlowAnimationClicked();
    void onRoundCornerClicked();
    void onCornerSizeChanged();
    void onFlowAnimationChanged();
    void onStateAdded(int index);
    void onStateModified(int index);
    void onStateRemoved(const QString &name, const QVariant &data);
    void onStateIndexChanged(int index);
    void onPosChanged(int value);
private:
    Ui::LinePropertyForm *ui;
    LineBaseProperty attr;
    AbstractLineItem *graphicItem;
    void initUI();
    void initEvent();
    void initArrowType();
};

#endif // LINEPROPERTYFORM_H
