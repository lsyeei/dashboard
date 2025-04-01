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

#include "fillpropertyform.h"
#include "gradientparamdialog.h"
#include "ui_fillpropertyform.h"
#include <QMetaEnum>
#include <QScreen>
#include <QPainter>
#include <QAbstractItemView>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QSizePolicy>
#include <QThread>

FillPropertyForm::FillPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FillPropertyForm)
{
    ui->setupUi(this);
    init();
    gradientForm = new GradientParamDialog(this);
    ui->gradientBtn->installEventFilter(this);
    connect(gradientForm, SIGNAL(valueChanged()), this, SLOT(onGradientParamChanged()));
}

FillPropertyForm::~FillPropertyForm()
{
    delete ui;
    if (gradientForm) {
        delete gradientForm;
    }
}

void FillPropertyForm::setImageFileName(const QString &newImageFileName)
{
    if (newImageFileName.isEmpty()) {
        setIsImage(false);
        return;
    }
    QFile f;
    if (!f.exists(newImageFileName)) {
        setIsImage(false);
        qWarning() << tr("图片") << newImageFileName << tr("不存在");
        return;
    }
    setIsImage(true);
    imageFileName = newImageFileName;
    ui->fileName->setToolTip(imageFileName);
    QPixmap map(imageFileName);
    QSize size = ui->fileName->size();
    ui->fileName->setPixmap(map.scaled(size.width(), size.height()));
}

QString FillPropertyForm::getImageFileName() const
{
    return imageFileName;
}

bool FillPropertyForm::getIsFill() const
{
    return isFill;
}

void FillPropertyForm::setIsFill(bool newIsFill)
{
    isFill = newIsFill;
    showHide();
}

Qt::BrushStyle FillPropertyForm::getStyle() const
{
    return style;
}

void FillPropertyForm::setStyle(Qt::BrushStyle newStyle)
{
    style = newStyle;
    int styleValue = QVariant::fromValue(style).toInt();
    isGradient = false;
    isImage = false;
    if (styleValue == 0){
        // 不填充
        setIsFill(false);
        return;
    }
    if (styleValue == 24){
        // 图像填充
        setIsImage(true);
        return;
    }
    if (styleValue < 15){
        // 单色填充
        ui->brushStyle1->blockSignals(true);
        ui->brushStyle1->setCurrentIndex(style - 1);
        ui->brushStyle1->blockSignals(false);
        setIsFill(true);
    }else{
        // 渐变填充
        gradientForm->setGradientType(style);
        setIsGradient(true);
    }
}

QColor FillPropertyForm::getBaseColor() const
{
    return baseColor;
}

void FillPropertyForm::setBaseColor(const QColor &newBaseColor)
{
    baseColor = newBaseColor;
    ui->baseColor->blockSignals(true);
    ui->baseColor->setColor(baseColor);
    ui->baseColor->blockSignals(false);
}

bool FillPropertyForm::getIsGradient() const
{
    return isGradient;
}

void FillPropertyForm::setIsGradient(bool newIsGradient)
{
    isGradient = newIsGradient;
    if (newIsGradient){
        style = gradientForm->getGradientType();
    }else if(style == Qt::LinearGradientPattern ||
            style == Qt::ConicalGradientPattern ||
            style == Qt::RadialGradientPattern){
        style = Qt::BrushStyle(ui->brushStyle1->currentData().toInt());
    }
    showHide();
}

bool FillPropertyForm::getIsImage() const
{
    return isImage;
}

void FillPropertyForm::setIsImage(bool newIsImage) {
    isImage = newIsImage;
    if (newIsImage){
        style = Qt::TexturePattern;
    }else if(style == Qt::TexturePattern){
        style = Qt::BrushStyle(ui->brushStyle1->currentData().toInt());
    }
    showHide();
}

QGradientStops FillPropertyForm::getGradientStops() const
{
    return gradientStops;
}

void FillPropertyForm::setGradientStops(const QGradientStops &newGradientStops)
{
    gradientStops = newGradientStops;
    if(gradientForm){
        gradientForm->setGradientStops(newGradientStops);
    }
}

void FillPropertyForm::setGradientSpread(QGradient::Spread spread)
{
    gradientForm->setGradientSpread(spread);
}

QGradient::Spread FillPropertyForm::getGradientSpread()
{
    return gradientForm->getGradientSpread();
}

void FillPropertyForm::setControlPoint(const QPainterPath &path, const QPolygonF &points)
{
    if (path.isEmpty() && points.isEmpty()) {
        return;
    }
    gradientForm->setControlPoint(path, points);
}

QPolygonF FillPropertyForm::getControlPoint()
{
    return gradientForm->getControlPoint();
}

bool FillPropertyForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->brushStyle1->view() && event->type() == QEvent::Resize)
    {
        // view 大小改变时重新初始化
        initBrushStyle1();
    }
    if(watched == ui->fileName && event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = (QMouseEvent *)event;
        if (mouseEvent->button() == Qt::LeftButton){
            // 点击图像时打开文件选择框
            changeImage();
        }
    }
    if (watched == ui->gradientBtn && event->type() == QEvent::Paint) {
        paintGraientBtn();
        event->accept();
    }
    return QWidget::eventFilter(watched, event);
}

void FillPropertyForm::resizeEvent(QResizeEvent *event)
{
    emit sizeChanged(event->size());
}

void FillPropertyForm::on_fillChecked_toggled(bool checked)
{
    isFill = checked;
    isGradient = false;
    isImage = false;
    if (!checked){
        style = Qt::NoBrush;
    }else{
        style = Qt::BrushStyle(ui->brushStyle1->currentData().toInt());
    }
    showHide();
    emit valueChanged();
}

void FillPropertyForm::on_brushStyle1_currentIndexChanged(int index)
{
    int styleIndex = ui->brushStyle1->itemData(index).toInt();
    style = Qt::BrushStyle(styleIndex);
    emit valueChanged();
}

void FillPropertyForm::on_baseColor_colorChanged(const QColor &oldColor, const QColor &newColor)
{
    Q_UNUSED(oldColor)
    baseColor = newColor;
    if (!ui->imageChecked && !ui->gradientChecked) {
        initBrushStyle1();
    }
    emit valueChanged();
}

void FillPropertyForm::on_gradientChecked_toggled(bool checked)
{
    isGradient = checked;
    if (checked){
        isImage = !checked;
        style = gradientForm->getGradientType();
    } else if (!ui->imageChecked->isChecked()){
        style = Qt::BrushStyle(ui->brushStyle1->currentData().toInt());
    }
    showHide();
    emit gradientChanged();
}

void FillPropertyForm::on_imageChecked_toggled(bool checked)
{
    isImage = checked;
    if (checked){
        isGradient = !checked;
        style = Qt::TexturePattern;
    }else{
        style = Qt::BrushStyle(ui->brushStyle1->currentData().toInt());
    }
    showHide();
    emit valueChanged();
}

void FillPropertyForm::on_gradientBtn_clicked()
{
    if(gradientForm == nullptr){
        gradientForm = new GradientParamDialog(this);
        connect(gradientForm, SIGNAL(valueChanged()), this, SLOT(onGradientParamChanged()));
    }
    gradientForm->show();
    // gradientForm->setRotateValue(gradientRotation);
    if (gradientStops.isEmpty()) {
        gradientStops = gradientForm->getGradientStops();
        // gradientStops << QGradientStop{0, baseColor} << QGradientStop{1, endColor};
    }else {
        gradientForm->setGradientStops(gradientStops);
    }
}

void FillPropertyForm::showHide() {
    if (isFill || isGradient || isImage) {
        ui->gradientChecked->show();
        ui->imageChecked->show();
        if (isImage) {
            ui->brushStyle1->hide();
            ui->baseColor->hide();
            ui->gradientBtn->hide();
            ui->fileName->show();
            isGradient = false;
        } else if(isGradient){
            ui->brushStyle1->hide();
            ui->baseColor->hide();
            ui->gradientBtn->show();
            ui->gradientBtn->repaint();
            ui->fileName->hide();
        }else{
            ui->brushStyle1->show();
            ui->baseColor->show();
            ui->gradientBtn->hide();
            ui->fileName->hide();
        }
    }else{
        ui->brushStyle1->hide();
        ui->baseColor->hide();
        ui->gradientChecked->hide();
        ui->gradientBtn->hide();
        ui->imageChecked->hide();
        ui->fileName->hide();
    }
    ui->fillChecked->blockSignals(true);
    ui->fillChecked->setChecked(isFill);
    ui->fillChecked->blockSignals(false);

    ui->gradientChecked->setAutoExclusive(false);
    ui->gradientChecked->blockSignals(true);
    ui->gradientChecked->setChecked(isGradient);
    ui->gradientChecked->blockSignals(false);

    ui->imageChecked->setAutoExclusive(false);
    ui->imageChecked->blockSignals(true);
    ui->imageChecked->setChecked(isImage);
    ui->imageChecked->blockSignals(false);

    // 触发窗口改变大小
    emit sizeChanged(size());
}

void FillPropertyForm::onGradientParamChanged()
{
    style = gradientForm->getGradientType();
    gradientStops = gradientForm->getGradientStops();
    ui->gradientBtn->repaint();
    emit gradientChanged();
}

void FillPropertyForm::setSizePolicy(QWidget *obj, bool retainSize) {
    QSizePolicy policy = obj->sizePolicy();
    policy.setRetainSizeWhenHidden(retainSize);
    obj->setSizePolicy(policy);
}


void FillPropertyForm::init() {
    screenRatio = QApplication::primaryScreen()->devicePixelRatio();

    setSizePolicy(ui->brushStyle1, false);
    setSizePolicy(ui->gradientChecked, false);
    setSizePolicy(ui->imageChecked, false);
    setSizePolicy(ui->baseColor, false);
    setSizePolicy(ui->fileName, false);
    // hideAll();

    // 设置comboBox的视图为自定义视图，拦截view的事件
    QAbstractItemView* view =ui->brushStyle1->view();
    if (view) {
        view->installEventFilter(this);
    }

    initBrushStyle1();

    ui->fileName->installEventFilter(this);

    ui->horizontalLayout_3->setAlignment(ui->imageChecked, Qt::AlignTop);

    showHide();
}


void FillPropertyForm::initBrushStyle1()
{
    QComboBox *style1 = ui->brushStyle1;

    qint16 width = style1->sizeHint().width() - 8;
    qint16 height = style1->iconSize().height();
    int index = style1->currentIndex();
    style1->clear();

    for (int i = 1; i < 15; i++)
    {
        QPixmap pixmap(width * screenRatio, height * screenRatio);
        pixmap.fill(Qt::transparent);
        pixmap.setDevicePixelRatio(screenRatio);
        // 绘制
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        painter.setRenderHint(QPainter::VerticalSubpixelPositioning);
        painter.setRenderHint(QPainter::LosslessImageRendering);
        QBrush brush;
        brush.setStyle(Qt::BrushStyle(i));
        brush.setColor(Qt::gray);//(baseColor);
        painter.setBrush(brush);
        QPen pen(Qt::NoPen);
        painter.setPen(pen);
        painter.drawRect(0, 0, width, height);
        painter.end();
        QIcon icon(pixmap);
        style1->addItem(icon,"", i);
    }
    style1->setIconSize({width, height});

    if (index > -1){
        style1->setCurrentIndex(index);
    }else{
        style1->setCurrentIndex(0);
    }
}

void FillPropertyForm::changeImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择图片"),
                                                    QDir::currentPath(),
                                 tr("Images (*.png *.bmp *.jpg *.jpeg)"));
    if(fileName.isNull()){
        return;
    }
    setImageFileName(fileName);
    emit valueChanged();
}


void FillPropertyForm::hideAll()
{
    ui->brushStyle1->hide();
    ui->gradientChecked->hide();
    ui->imageChecked->hide();
    ui->baseColor->hide();
    ui->gradientBtn->hide();
    ui->fileName->hide();
}


void FillPropertyForm::setConstraint(QLayout::SizeConstraint constraint)
{
    auto localLayout = layout();
    localLayout->setSizeConstraint(constraint);
    setLayout(localLayout);
}

void FillPropertyForm::paintGraientBtn()
{
    auto rect = ui->gradientBtn->rect();
    QLinearGradient g{rect.topLeft(), rect.topRight()};
    g.setSpread(gradientForm->getGradientSpread());
    g.setStops(gradientForm->getGradientStops());

    QPainter painter(ui->gradientBtn);
    painter.setBrush(g);
    painter.setPen(QPen{Qt::NoPen});
    painter.drawRect(rect);
    painter.end();
}

