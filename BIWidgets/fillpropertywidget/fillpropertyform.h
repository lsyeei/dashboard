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

#ifndef FILLPROPERTYFORM_H
#define FILLPROPERTYFORM_H

#include <QLayout>
#include <QWidget>

namespace Ui {
class FillPropertyForm;
}
class GradientParamDialog;

class FillPropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit FillPropertyForm(QWidget *parent = nullptr);
    ~FillPropertyForm();

    void setImageFileName(const QString &newImageFileName);

    QString getImageFileName() const;

    bool getIsFill() const;
    void setIsFill(bool newIsFill);

    Qt::BrushStyle getStyle() const;
    void setStyle(Qt::BrushStyle newStyle);

    QColor getBaseColor() const;
    void setBaseColor(const QColor &newBaseColor);

    bool getIsGradient() const;
    void setIsGradient(bool newIsGradient);

    bool getIsImage() const;
    void setIsImage(bool newIsImage);

    QGradientStops getGradientStops() const;
    void setGradientStops(const QGradientStops &newGradientStops);

    void setGradientSpread(QGradient::Spread spread);
    QGradient::Spread getGradientSpread();

    /**
     * @brief setControlPoint 设置渐变控制点
     * @param path 参照路径
     * @param points 控制点位
     */
    void setControlPoint(const QPainterPath &path, const QPolygonF &points);
    QPolygonF getControlPoint();

signals:
    /**
     * @brief 属性改变消息
     */
    void valueChanged();
    void gradientChanged();
    void sizeChanged(const QSize &size);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_fillChecked_toggled(bool checked);

    void on_brushStyle1_currentIndexChanged(int index);

    void on_baseColor_colorChanged(const QColor &oldColor, const QColor &newColor);

    void on_gradientChecked_toggled(bool checked);

    void on_imageChecked_toggled(bool checked);

    void on_gradientBtn_clicked();
    void onGradientParamChanged();

private:
    Ui::FillPropertyForm *ui;
    // 屏幕缩放比例
    qreal screenRatio{1};

    // 是否填充
    bool isFill{false};
    // 画刷样式
    Qt::BrushStyle style{Qt::SolidPattern};
    // 画刷颜色
    QColor baseColor{Qt::white};
    // 渐变色或辐射色的最终颜色
    QColor endColor{Qt::white};
    // 是否为渐变色
    bool isGradient{false};
    // 是否采用背景图
    bool isImage{false};
    // 背景图文件
    QString imageFileName;
    //渐变参数
    qreal gradientRotation{0};
    QGradientStops gradientStops;
    // 渐变色参数
    GradientParamDialog *gradientForm{nullptr};

    /**
     * @brief 设置隐藏后是否占位
     * @param obj 控件对象
     * @param retainSize true 占位，false 不占位
     */
    void setSizePolicy(QWidget *obj, bool retainSize);
    /**
     * @brief 初始化控件，并隐藏
     */
    void init();
    /**
     * @brief 使用图标初始化画刷样式
     */
    void initBrushStyle1();
    /**
     * @brief 重选图片
     */
    void changeImage();
    /**
     * @brief 各控件显示隐藏逻辑
     */
    void showHide();
    /**
     * @brief 隐藏所有属性
     */
    void hideAll();
    void setConstraint(QLayout::SizeConstraint constraint);
    // 绘制渐变色配置按钮
    void paintGraientBtn();
};

#endif // FILLPROPERTYFORM_H
