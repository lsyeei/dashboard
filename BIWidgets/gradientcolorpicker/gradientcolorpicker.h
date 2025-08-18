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

#ifndef GRADIENTCOLORPICKER_H
#define GRADIENTCOLORPICKER_H

#include <QWidget>

class GradientColorPickerForm;
class GradientColorPicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QGradientStops gradientStops READ gradientStops WRITE setGradientStops NOTIFY gradientStopsChanged FINAL)

public:
    explicit GradientColorPicker(QWidget *parent = nullptr);
    ~ GradientColorPicker();
    QGradientStops gradientStops();
    void setGradientStops(const QGradientStops stops);
Q_SIGNALS:
    void gradientStopsChanged(const QGradientStops stops);
protected Q_SLOTS:
    void onGradientValueChanged();
private:
    GradientColorPickerForm *form{nullptr};

};

#endif // GRADIENTCOLORPICKER_H
