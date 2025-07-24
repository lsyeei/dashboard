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

#ifndef RECTPROPERTYFORM_H
#define RECTPROPERTYFORM_H

#include "abstractzoneitem.h"
#include "ipropertyform.h"
#include "itextobject.h"
#include "timeproperty.h"
#include "zoneproperty.h"

#include <QTextCharFormat>

class TextPropertyForm;
class HtmlPropertyForm;
class TimePropertyForm;
namespace Ui {
class RectPropertyForm;
}

class RectPropertyForm : public IPropertyForm, public ITextObject
{
    Q_OBJECT

public:
    explicit RectPropertyForm(QWidget *parent = nullptr);
    ~RectPropertyForm();

    void setGraphicItem(ICustomGraphic *item) override;
    ICustomGraphic *getGraphicItem() override;
    void updateData() override;
    void hideRound();
    void addTextProperty();
    void addHtmlProperty();
    void addTimeProperty();
    // ITextObject interface
    void setTextFormat(const QTextFormat &format) override;
    
Q_SIGNALS:
    /**
     * @brief 圆角大小改变
     * @param roundSize 圆角大小
     */
    void roundChanged(qint16 roundSize);
    /**
     * @brief 旋转角度改变
     * @param rotate 旋转角度
     */
    void rotateChanged(qint16 rotate);

private slots:
    void on_roundChecked_toggled(bool checked);
    void on_roundSize_valueChanged(int arg1);
    void on_rotation_valueChanged(double arg1);
    void posChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio);
    void lineStyleChanged(Qt::PenStyle style, QColor Color, int width);
    void brushChanged(Qt::BrushStyle brushStyle, const QColor &baseColor,
                     const QString imageFile);
    void onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops,
                           QGradient::Spread spread, const QPolygonF &points);

    void on_stateBox_itemAdded(int index);

    void on_stateBox_itemModified(int index);

    void on_stateBox_itemRemoved(const QString &name, const QVariant &data);

    void on_stateBox_currentIndexChanged(int index);
    void onTextFormatChanged(const QTextFormat &format);
    void onHtmlChanged(const QString &data);
    void onTimeStyleChanged(const TimeProperty &data);

private:
    Ui::RectPropertyForm *ui;
    // 图形元件
    AbstractZoneItem *graphicItem{nullptr};
    // 属性
    ZoneProperty attr;
    TextPropertyForm *textAttr{nullptr};
    HtmlPropertyForm *htmlAttr{nullptr};
    TimePropertyForm *timeAttr{nullptr};
};

#endif // RECTPROPERTYFORM_H
