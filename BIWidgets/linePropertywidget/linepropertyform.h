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

#include <QLayout>
#include <QWidget>

namespace Ui {
class LinePropertyForm;
}

class LinePropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit LinePropertyForm(QWidget *parent = nullptr);
    ~LinePropertyForm();

    Qt::PenStyle lineStyle() const;
    void setLineStyle(Qt::PenStyle newLineStyle);

    QColor lineColor() const;
    void setLineColor(const QColor &newLineColor);

    int lineWidth() const;
    void setLineWidth(int newLineWidth);
    bool getShowLine() const;
    void setShowLine(bool newShowLine);
    bool alwaysShow() const;
    void setAlwaysShow(bool value);

Q_SIGNALS:
    void valueChanged();
    void sizeChanged(const QSize &size);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_lineStyle_currentIndexChanged(int index);
    void on_lineColor_colorChanged(const QColor &oldColor, const QColor &newColor);
    void on_lineWidth_valueChanged(int arg1);
    void on_lineChecked_toggled(bool checked);

private:
    Ui::LinePropertyForm *ui;
    // 屏幕缩放比
    qreal screenRatio{1};
    QMap<QString, QString> lineStyleName;
    // 是否显示线条
    bool showLine{true};
    // 线条颜色
    QColor color{Qt::white};
    // 线条宽度
    int width{1};
    // 线条样式
    Qt::PenStyle style{Qt::SolidLine};
    // 线条样式在comboBox中的索引
    QMap<Qt::PenStyle, qint16> styleIndex;
    bool hideCheck{false};

    void initLineStyleName();
    void initLineStyle();
    void showLineChanged();
    void setConstraint(QLayout::SizeConstraint constraint);
};

#endif // LINEPROPERTYFORM_H
