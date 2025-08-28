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

#ifndef COLORPICKER_H
#define COLORPICKER_H
// #if defined(COLOR_PICKER_LIB)
// #define COLOR_PICKER_EXPORT Q_DECL_EXPORT
// #else
// #define COLOR_PICKER_EXPORT Q_DECL_IMPORT
// #endif

#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>

class ColorPickerPrivate;
class /*COLOR_PICKER_EXPORT*/QDESIGNER_WIDGET_EXPORT ColorPicker : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

public:
    explicit ColorPicker(QWidget *parent = nullptr);
    ~ColorPicker();
    QColor getColor() const;
    void setColor(QColor newColor);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    int heightForWidth(int width) const;
    bool hasHeightForWidth() const;
Q_SIGNALS:
    void colorChanged(const QColor oldColor, const QColor newColor);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QScopedPointer<ColorPickerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(ColorPicker)
};

#endif // COLORPICKER_H
