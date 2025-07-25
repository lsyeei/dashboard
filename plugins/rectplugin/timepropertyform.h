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
#ifndef TIMEPROPERTYFORM_H
#define TIMEPROPERTYFORM_H

#include "timeproperty.h"
#include <QWidget>

namespace Ui {
class TimePropertyForm;
}

class TimePropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit TimePropertyForm(QWidget *parent = nullptr);
    ~TimePropertyForm();
    void setData(const TimeProperty &property);
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;
Q_SIGNALS:
    void dataChanged(const TimeProperty &property);
protected Q_SLOTS:
    void onValueChanged();
    void setFontSize();
    void setLetterSpace();
    void showFont();
    void showStyle();
private:
    Ui::TimePropertyForm *ui;
    bool noData{true};
    void initUI();
    void initEvent();
    void updateFormatOptions();
    QString getFormatDate(const QString format);
    TimeProperty attr;
};


#endif // TIMEPROPERTYFORM_H
