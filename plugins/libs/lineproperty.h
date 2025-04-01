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

#ifndef LINEPROPERTY_H
#define LINEPROPERTY_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>

class LinePropertyForm;
class QDESIGNER_WIDGET_EXPORT LineProperty : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool showLine READ showLine WRITE setShowLine NOTIFY showLineChanged FINAL)
    Q_PROPERTY(Qt::PenStyle lineStyle READ lineStyle WRITE setLineStyle NOTIFY lineStyleChanged FINAL)
    Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged FINAL)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged FINAL)
public:
    explicit LineProperty(QWidget *parent = nullptr);
    ~LineProperty();

    Qt::PenStyle lineStyle() const;
    void setLineStyle(Qt::PenStyle newLineStyle);

    int lineWidth() const;
    void setLineWidth(int newLineWidth);

    QColor lineColor() const;
    void setLineColor(const QColor &newLineColor);

    bool showLine() const;
    void setShowLine(bool newShowLine);

Q_SIGNALS:
    void propertyChanged(Qt::PenStyle style, QColor Color, int width);

    void lineStyleChanged(Qt::PenStyle style);

    void lineWidthChanged(qreal width);

    void lineColorChanged(QColor color);

    void showLineChanged();

protected:
    void resizeEvent(QResizeEvent *event);
private Q_SLOTS:
    void formValueChanged();
    void formSizeChanged(const QSize & size);
private:
    QScopedPointer<LinePropertyForm> form;
};

#endif // LINEPROPERTY_H
