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

#ifndef CIRCLESLIDER_H
#define CIRCLESLIDER_H

#include <QWidget>

class CircleSlider : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal min READ getMin WRITE setMin NOTIFY minChanged FINAL)
    Q_PROPERTY(qreal max READ getMax WRITE setMax NOTIFY maxChanged FINAL)
    Q_PROPERTY(qreal value READ getValue WRITE setValue NOTIFY valueChanged FINAL)

public:
    explicit CircleSlider(QWidget *parent = nullptr);

    // QWidget interface
    qreal getMin() const;
    void setMin(qreal newMin);

    qreal getMax() const;
    void setMax(qreal newMax);

    qreal getValue() const;
    void setValue(qreal newValue);
    // QWidget interface
    int heightForWidth(int width) const Q_DECL_OVERRIDE;
    bool hasHeightForWidth() const Q_DECL_OVERRIDE;

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

signals:
    void minChanged();

    void maxChanged();

    void valueChanged(qreal value);

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    // QWidget interface
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
private:
    // 最小值
    qreal min{0};
    // 最大值
    qreal max{100};
    // 当前值
    qreal value{0};
    // 鼠标左键按下
    bool mousePressed{false};

    void mouseEvent(QMouseEvent *event);

};

#endif // CIRCLESLIDER_H
