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

#ifndef POSPROPERTYFORM_H
#define POSPROPERTYFORM_H

#include <QWidget>

namespace Ui {
class PosPropertyForm;
}

class PosPropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit PosPropertyForm(QWidget *parent = nullptr);
    ~PosPropertyForm();

    qint32 getLeft() const;
    void setLeft(qint32 newLeft);

    qint32 getTop() const;
    void setTop(qint32 newTop);

    qint32 getWidth() const;
    void setWidth(qint32 newWidth);

    qint32 getHeight() const;
    void setHeight(qint32 newHeight);

    bool getAspectRatio() const;
    void setAspectRatio(bool newAspectRatio);
Q_SIGNALS:
    void valueChanged();

private slots:
    void on_leftValue_valueChanged(int arg1);

    void on_topValue_valueChanged(int arg1);

    void on_widthValue_valueChanged(int arg1);

    void on_heightValue_valueChanged(int arg1);

    void on_aspectRatioChecked_toggled(bool checked);

private:
    Ui::PosPropertyForm *ui;

    qint32 left{0};
    qint32 top{0};
    qint32 width{0};
    qint32 height{0};
    bool aspectRatio{false};
    // 宽高比
    qreal ratio{0};
    void aspectRatioChanged();
    void heightChanged();
    void widthChanged();
    void enbaleAspectRatio();
    void initRatio();
};

#endif // POSPROPERTYFORM_H
