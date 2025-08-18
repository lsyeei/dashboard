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

#ifndef COLORPICKERPRIVATE_H
#define COLORPICKERPRIVATE_H
#include "svghelper.h"
#include <QObject>

class ColorPicker;
class ColorPickerPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(ColorPicker);
public:
    explicit ColorPickerPrivate(ColorPicker *parent);
    ColorPicker *q_ptr;
    /**
     * @brief 打开颜色选择对话框，选择颜色
     */
    void pickerColor();

    SvgHelper icon{QString(":/icons/sip-line.svg")};
    // 默认大小
    QSize defaultSize{90, 44};
    // 最小大小
    QSize minSize{45, 22};
    // 建议大小
    QSize hintSize{45, 22};
    // 正常按钮背景色
    const QColor normalColor{0xEEEEEE};
    // 悬停按钮背景色
    const QColor hoverColor{0xE5E5E5};
    // 选择的颜色
    QColor color{Qt::white};
    // 使用的字体
    QString fontFamily;
    // 鼠标悬停
    bool isHover{false};
};

#endif // COLORPICKERPRIVATE_H
