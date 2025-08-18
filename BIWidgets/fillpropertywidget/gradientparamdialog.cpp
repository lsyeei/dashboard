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

#include "gradientparamdialog.h"
#include "hoverpoints.h"
#include "ui_gradientparamdialog.h"

#include <QCloseEvent>

GradientParamDialog::GradientParamDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GradientParamDialog)
{
    ui->setupUi(this);
    createPresetsIcon();
    setWindowModality(Qt::WindowModal);
    initUI();
    initEvent();

}

GradientParamDialog::~GradientParamDialog()
{
    delete ui;
}

void GradientParamDialog::setGradientType(Qt::BrushStyle type)
{
    for(int i=0; i<ui->gradientType->count(); i++){
        if (ui->gradientType->itemData(i).value<Qt::BrushStyle>() == type) {
            ui->gradientType->setCurrentIndex(i);
            break;
        }
    }
}

Qt::BrushStyle GradientParamDialog::getGradientType()
{
    return ui->gradientType->currentData().value<Qt::BrushStyle>();
}

void GradientParamDialog::setGradientSpread(QGradient::Spread spread)
{
    for(int i=0; i<ui->spreadOption->count(); i++){
        if (ui->spreadOption->itemData(i).value<QGradient::Spread>() == spread) {
            ui->spreadOption->setCurrentIndex(i);
            break;
        }
    }
}

QGradient::Spread GradientParamDialog::getGradientSpread()
{
    return ui->spreadOption->currentData().value<QGradient::Spread>();
}

void GradientParamDialog::setControlPoint(const QPainterPath &path, const QPolygonF &points)
{
    if (path.isEmpty()) {
        return;
    }
    // 等比例缩放参照路径，计算预览路径
    shapeBound = path.boundingRect();
    auto canvasBound = ui->preview->rect();
    QLineF l1{shapeBound.topLeft(), shapeBound.bottomRight()};
    QLineF l2{canvasBound.topLeft(), canvasBound.bottomRight()};
    shapeRatio = (l2.length() - previewPadding) / l1.length();
    QTransform trans;
    trans.scale(shapeRatio, shapeRatio);
    previewShapePath = trans.map(path);
    auto bound = previewShapePath.boundingRect();
    auto offset = canvasBound.center() - bound.center();
    trans.reset();
    trans.translate(offset.x(), offset.y());
    previewShapePath = trans.map(previewShapePath);

    QPolygonF pts;
    auto rect = ui->preview->rect();
    auto center = rect.center();
    if (points.isEmpty()) {
        pts << center - QPointF{rect.width()/4.0, 0}
            << center + QPointF{rect.width()/4.0, 0};
    } else {
        // 等比例缩放控制点到预览路径内
        auto shapeCenter = shapeBound.center();
        l1.setPoints(shapeCenter, points[0]);
        l2.setPoints(center,{0,0});

        for(int i=0;i<2;i++){
            l1.setP2(points[i]);
            l2.setAngle(l1.angle());
            l2.setLength(l1.length() * shapeRatio);
            pts << l2.p2();
        }
        if (points.count() >= 3) {
            radialPoint = points[2] * shapeRatio;
        }
    }

    hoverPoint->setPoints({pts[0], pts[1]});
    ui->preview->repaint();
}

QPolygonF GradientParamDialog::getControlPoint()
{
    QPolygonF points = hoverPoint->points();
    if (radialPoint.x() > 0 || radialPoint.y() > 0) {
        points << radialPoint;
    }

    if (previewShapePath.isEmpty()) {
        return QPolygonF();//points;
    }
    QPolygonF pts;
    auto shapeCenter = shapeBound.center();
    auto rect = ui->preview->rect();
    auto center = rect.center();
    QLineF l1{center, points[0]};
    QLineF l2{shapeCenter,shapeCenter+QPointF{1,0}};

    for(int i=0;i<2;i++){
        l1.setP2(points[i]);
        l2.setAngle(l1.angle());
        l2.setLength(l1.length() / shapeRatio);
        pts << l2.p2();
    }
    if (points.count() >= 3) {
        pts << points[2] / shapeRatio;
    }

    return pts;
}

void GradientParamDialog::setGradientStops(const QGradientStops &stops)
{
    ui->gradientColorPicker->setGradientStops(stops);
    ui->presets->setCurrentIndex(0);
}

QGradientStops GradientParamDialog::getGradientStops()
{
    return ui->gradientColorPicker->gradientStops();
}

bool GradientParamDialog::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->preview && event->type() == QEvent::Paint) {
        paintPreView();
        event->accept();
    }
    return QWidget::eventFilter(watched, event);
}

void GradientParamDialog::paintPreView()
{
    QPolygonF pts = hoverPoint->points();

    QGradient g;
    auto gradientType = ui->gradientType->currentData().value<Qt::BrushStyle>();
    if (gradientType == Qt::LinearGradientPattern) {
        g = QLinearGradient(pts.at(0), pts.at(1));

    } else if (gradientType == Qt::RadialGradientPattern) {
        g = QRadialGradient(pts.at(0), radialPoint.x(), pts.at(1), radialPoint.y());
    } else {
        QLineF l(pts.at(0), pts.at(1));
        qreal angle = QLineF(0, 0, 1, 0).angleTo(l);
        g = QConicalGradient(pts.at(0), angle);
    }

    g.setStops(ui->gradientColorPicker->gradientStops());
    g.setSpread(QGradient::Spread(ui->spreadOption->currentData().toInt()));

    QPainter p(ui->preview);
    p.setBrush(g);
    p.setPen(Qt::NoPen);

    p.drawRect(rect());
    if (!previewShapePath.isEmpty()) {
        p.setCompositionMode(QPainter::CompositionMode_Difference);//QPainter::CompositionMode_Exclusion
        p.strokePath(previewShapePath, QPen(Qt::white, 1, Qt::SolidLine));
    }
    p.end();
}

void GradientParamDialog::onGradientStopsChanged(QGradientStops stops)
{
    Q_UNUSED(stops)
    updatePreView();
    QSignalBlocker presetBlocker(ui->presets);
    ui->presets->setCurrentIndex(0);
}


void GradientParamDialog::onPresetsChanged(int value)
{
    if (value <= 0) {
        return;
    }
    auto preset = ui->presets->currentData().value<QGradient::Preset>();
    QGradient gradient(preset);
    ui->gradientColorPicker->setGradientStops(gradient.stops());
    updatePreView();
}

void GradientParamDialog::updatePreView()
{
    if (ui->gradientType->currentData().value<Qt::BrushStyle>() == Qt::RadialGradientPattern) {
        // 确保焦点在中心直径内
        auto points = hoverPoint->points();
        QLineF l{points[0], points[1]};
        auto maxLen = radialPoint.x()-radialPoint.y()-1;
        if (l.length() >= maxLen) {
            l.setLength(maxLen);
            points[1] = l.p2();
            hoverPoint->setPoints(points);
        }
    }
    ui->preview->repaint();
    emit valueChanged();
}

void GradientParamDialog::onGradientTypeChanged()
{
    auto style = ui->gradientType->currentData().value<Qt::BrushStyle>();
    if (style == Qt::RadialGradientPattern) {
        if (!shapeBound.isEmpty()) {
            auto rect = previewShapePath.boundingRect();
            auto r = 1.2*qMax(rect.width(), rect.height())/2;
            ui->centerRadius->setRange(100*r/3.0, r*100);
            ui->focalRadius->setRange(0, r*100/2.0);
            if (radialPoint.x() < r/3.0) {
                radialPoint.setX(qMin(ui->preview->width(), ui->preview->height()) / 3.0);
                ui->centerRadius->setValue(radialPoint.x()*100);
            }
            ui->centerRadius->setValue(radialPoint.x()*100);
            ui->focalRadius->setMaximum(radialPoint.x()*100);
            if (radialPoint.y() < r/10.0) {
                radialPoint.setY(r/10.0);
            }
            ui->focalRadius->setValue(radialPoint.y()*100);
        }
        ui->radialParam->show();
    }else{
        ui->radialParam->hide();
    }

    updatePreView();
}

void GradientParamDialog::onRadialParamChanged()
{
    auto centerRadius = ui->centerRadius->value()/100;
    radialPoint.setX(centerRadius);
    ui->focalRadius->blockSignals(true);
    ui->focalRadius->setMaximum(centerRadius*20);
    if (ui->focalRadius->value() > ui->focalRadius->maximum()) {
        ui->focalRadius->setValue(ui->focalRadius->maximum()/4);
    }
    ui->focalRadius->blockSignals(false);
    radialPoint.setY(ui->focalRadius->value()/100);
    updatePreView();
}

void GradientParamDialog::closeEvent(QCloseEvent *event)
{
    hide();
    event->accept();
}

void GradientParamDialog::initUI()
{
    layout()->setAlignment(Qt::AlignTop);
    hoverPoint = new HoverPoints(ui->preview, HoverPoints::CircleShape);
    hoverPoint->setEditable(false);
    hoverPoint->setConnectionType(HoverPoints::NoConnection);
    auto rect = ui->preview->rect();
    QPolygonF points;
    points << rect.center() - QPointF{rect.width()*1.0/4,0}
           << rect.center() + QPointF{rect.width()*1.0/4,0};
    hoverPoint->setPoints(points);
    hoverPoint->setPointSize({16,16});

    ui->gradientType->clear();
    ui->gradientType->addItem(tr("线性"), QVariant::fromValue(Qt::LinearGradientPattern));
    ui->gradientType->addItem(tr("辐射"), QVariant::fromValue(Qt::RadialGradientPattern));
    ui->gradientType->addItem(tr("圆锥"), QVariant::fromValue(Qt::ConicalGradientPattern));
    ui->gradientType->setCurrentIndex(0);
    ui->radialParam->hide();

    ui->spreadOption->clear();
    ui->spreadOption->addItem(tr("填充"), QVariant::fromValue(QGradient::PadSpread));
    ui->spreadOption->addItem(tr("镜像"), QVariant::fromValue(QGradient::ReflectSpread));
    ui->spreadOption->addItem(tr("重复"), QVariant::fromValue(QGradient::RepeatSpread));
    ui->spreadOption->setCurrentIndex(0);

    ui->presets->clear();
    ui->presets->setIconSize({64,16});
    ui->presets->addItem("", 0);
    auto presets = QMetaEnum::fromType<QGradient::Preset>();
    for(int i=0;i<presets.keyCount()-1;i++){
        ui->presets->addItem(presetIconMap[presets.value(i)], "", QGradient::Preset(presets.value(i)));//presets.key(i)
    }
    ui->presets->setCurrentIndex(0);
}

QMap<int, QIcon> GradientParamDialog::presetIconMap;

void GradientParamDialog::initEvent()
{
    ui->preview->installEventFilter(this);
    connect(ui->gradientColorPicker, SIGNAL(gradientStopsChanged(QGradientStops)), this, SLOT(onGradientStopsChanged(QGradientStops)));
    connect(ui->presets, SIGNAL(currentIndexChanged(int)), this, SLOT(onPresetsChanged(int)));
    connect(ui->gradientType, SIGNAL(currentIndexChanged(int)), this, SLOT(onGradientTypeChanged()));
    connect(ui->spreadOption, SIGNAL(currentIndexChanged(int)), this, SLOT(updatePreView()));
    connect(hoverPoint, SIGNAL(pointsChanged(QPolygonF)), this, SLOT(updatePreView()));
    connect(ui->centerRadius, SIGNAL(valueChanged(int)), this, SLOT(onRadialParamChanged()));
    connect(ui->focalRadius, SIGNAL(valueChanged(int)), this, SLOT(onRadialParamChanged()));
}


void GradientParamDialog::createPresetsIcon()
{
    if (!presetIconMap.isEmpty()) {
        return;
    }
    qreal screenRatio = QApplication::primaryScreen()->devicePixelRatio();
    auto presets = QMetaEnum::fromType<QGradient::Preset>();
    int width = 64;
    int height = 16;
    for(int i=0;i<presets.keyCount()-1;i++){
        QPixmap pixmap(width * screenRatio, height * screenRatio);
        pixmap.fill(Qt::transparent);
        pixmap.setDevicePixelRatio(screenRatio);
        // 绘制
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
        painter.setRenderHint(QPainter::LosslessImageRendering);
        auto colorSet = QGradient(QGradient::Preset(presets.value(i)));
        QLinearGradient gradient({0,8}, {64,8});
        gradient.setStops(colorSet.stops());
        painter.setBrush(gradient);
        QPen pen(Qt::NoPen);
        painter.setPen(pen);
        painter.drawRect(0, 0, width, height);
        painter.end();
        presetIconMap[presets.value(i)] = QIcon{pixmap};
    }
}
