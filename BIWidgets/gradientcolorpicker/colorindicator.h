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

#ifndef COLORINDICATOR_H
#define COLORINDICATOR_H

#include <QWidget>

class ColorIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit ColorIndicator(const QColor &indicatorColor, qreal pos, QWidget *parent = nullptr);
    void setSelected(bool flag);
    void setColor(const QColor &value);
    void setColorPos(qreal pos);
    bool isSelected();
    QGradientStop getColor();
    int heightForWidth(int width) const Q_DECL_OVERRIDE;
    bool hasHeightForWidth() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
signals:
    void selectEvent();
    void posMoveEvent(const QPoint &offset);
    void moveEndEvent();
    void deleteEvent();
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    // 表示的颜色
    QColor color{Qt::white};
    bool selected{false};
    qreal colorPos{0};
    // 控件宽度
    int width{8};
    QPointF lastPos;
    bool moveFlag{false};
    bool deleteFlag{false};
};

#endif // COLORINDICATOR_H
