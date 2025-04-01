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

#ifndef FILLPROPERTY_H
#define FILLPROPERTY_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>

class FillPropertyForm;
class QDESIGNER_WIDGET_EXPORT FillProperty : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(bool fill READ isFill WRITE setIsFill NOTIFY isFillChanged FINAL);
    Q_PROPERTY(bool gradient READ gradient WRITE setGradient NOTIFY gradientChanged FINAL);
    Q_PROPERTY(bool fillImage READ fillImage WRITE setFillImage NOTIFY fillImageChanged FINAL);
    Q_PROPERTY(Qt::BrushStyle brushStyle READ brushStyle WRITE setBrushStyle NOTIFY brushStyleChanged FINAL);
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor NOTIFY baseColorChanged FINAL);
    Q_PROPERTY(QColor endColor READ endColor WRITE setEndColor NOTIFY endColorChanged FINAL);
    Q_PROPERTY(QString imageFile READ imageFile WRITE setImageFile NOTIFY imageFileChanged FINAL);
public:
    explicit FillProperty(QWidget *parent = nullptr);
    ~FillProperty();
    bool isFill() const;
    void setIsFill(bool newFill);

    Qt::BrushStyle brushStyle() const;
    void setBrushStyle(Qt::BrushStyle newBrushStyle);

    QColor baseColor() const;
    void setBaseColor(const QColor &newBaseColor);

    QColor endColor() const;
    void setEndColor(const QColor &newEndColor);

    QString imageFile() const;
    void setImageFile(const QString &newImageFile);

    bool gradient() const;
    void setGradient(bool newGradient);

    bool fillImage() const;
    void setFillImage(bool newFillImage);

Q_SIGNALS:
    /**
     * @brief 填充属性改变消息
     * @param brushStyle 画刷样式
     * @param baseColor 起始颜色
     * @param endColor 终点颜色
     * @param imageFile 图片路径
     */
    void propertyChanged(Qt::BrushStyle brushStyle, const QColor &baseColor,
                         const QColor &endColor, const QString imageFile);

    void isFillChanged(bool newFill);

    void brushStyleChanged(Qt::BrushStyle newBrushStyle);

    void baseColorChanged(const QColor &newBaseColor);

    void endColorChanged(const QColor &newEndColor);

    void imageFileChanged(const QString &newImageFile);

    void gradientChanged(bool newGradient);

    void fillImageChanged(bool newFillImage);

protected:
    void resizeEvent(QResizeEvent *event);
private Q_SLOTS:
    /**
     * @brief 接收任意单一属性修改消息
     */
    void formValueChanged();
    void formSizeChanged(QSize size);
private:
    QScopedPointer<FillPropertyForm> form;
};

#endif // FILLPROPERTY_H
