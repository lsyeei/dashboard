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

#ifndef GRADIENTPARAMDIALOG_H
#define GRADIENTPARAMDIALOG_H

#include <QDialog>
#include <QPainterPath>

namespace Ui {
class GradientParamDialog;
}
class HoverPoints;
class GradientParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradientParamDialog(QWidget *parent = nullptr);
    ~GradientParamDialog();
    void setGradientType(Qt::BrushStyle type);
    Qt::BrushStyle getGradientType();
    void setGradientSpread(QGradient::Spread spread);
    QGradient::Spread getGradientSpread();
    /**
     * @brief setControlPoint 设置控制点
     * @param path 参考路径
     * @param points 控制点
     */
    void setControlPoint(const QPainterPath &path, const QPolygonF &points);
    QPolygonF getControlPoint();
    void setGradientStops(const QGradientStops &stops);
    QGradientStops getGradientStops();
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
Q_SIGNALS:
    void valueChanged();
protected Q_SLOTS:
    void paintPreView();
    void onGradientStopsChanged(QGradientStops stops);
    void onPresetsChanged(int value);
    void updatePreView();
    void onGradientTypeChanged();
    void onRadialParamChanged();
    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    // 预置颜色的图标， key 预置色枚举值， value 图标
    static QMap<int, QIcon> presetIconMap;
    Ui::GradientParamDialog *ui;
    HoverPoints *hoverPoint;
    // preview 留白
    int previewPadding{50};
    QPainterPath previewShapePath;
    // shape的真实大小
    QRectF shapeBound;
    // preview对角线与shape bound 对角线的比值
    qreal shapeRatio{1};
    // 辐射渐变的中心直径X和焦点直径Y
    QPointF radialPoint;

    void initUI();
    void initEvent();
    void createPresetsIcon();
};

#endif // GRADIENTPARAMDIALOG_H
