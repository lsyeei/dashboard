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

#ifndef GRADIENTCOLORPICKERFORM_H
#define GRADIENTCOLORPICKERFORM_H

#include <QWidget>

namespace Ui {
class GradientColorPickerForm;
}
class ColorIndicator;
class GradientColorPickerForm : public QWidget
{
    Q_OBJECT

public:
    explicit GradientColorPickerForm(QWidget *parent = nullptr);
    ~GradientColorPickerForm();
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    QGradientStops getGradientStops();
    void setGradientStops(const QGradientStops &stops);
Q_SIGNALS:
    void valueChanged();
protected slots:
    void onColorChanged(const QColor &oldColor, const QColor &newColor);
    void onColorPosChanged(int value);
    void onDelColorClicked();
    void onColorAlphaChanged(int value);
    void onIndicatorSelect();
    void onIndicatorMoved(const QPoint &offset);
    void onIndicatorMoveEnd();
    void onIndicatorDelete();
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::GradientColorPickerForm *ui;
    // 所有色标集合
    QList<ColorIndicator*> indicators;
    // 当前的色标
    ColorIndicator* currentIndicator;
    void paintColorView(QPaintEvent *event);
    /**
     * @brief addIndicator 添加色标
     * @param pos 位置
     * @param colo 颜色r
     */
    void addIndicator(qreal pos, const QColor &color);
    void delIndicator(ColorIndicator *indicator);
    // void selectIndicator(ColorIndicator *indicator);
    // void updateIndicator(qreal pos, const QColor &color);
    void deselecteIndicators();
    /**
     * @brief pos2Percent 色标位置转换为百分比
     * @param pos 色标位置X
     * @return 百分比
     */
    qreal pos2Percent(int pos);
    /**
     * @brief percent2Pos 百分比转为位置X
     * @param percent 百分比
     * @return 位置X
     */
    int percent2Pos(qreal percent);
    /**
     * @brief updateColorViewSize 修改渐变色视图大小
     */
    // void updateColorViewSize();

};

#endif // GRADIENTCOLORPICKERFORM_H
