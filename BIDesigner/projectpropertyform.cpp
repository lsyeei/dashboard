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

#include "projectpropertyform.h"
#include "ui_projectpropertyform.h"

#include <QPainterPath>

ProjectPropertyForm::ProjectPropertyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ProjectPropertyForm)
{
    ui->setupUi(this);
    connect(ui->projectName, SIGNAL(editingFinished()), this, SLOT(projectPropertyChanged()));
    connect(ui->author, SIGNAL(editingFinished()), this, SLOT(projectPropertyChanged()));
    connect(ui->pageName, SIGNAL(editingFinished()), this, SLOT(pagePropertyChanged()));
    connect(ui->pageWidth, SIGNAL(valueChanged(int)), this, SLOT(pagePropertyChanged()));
    connect(ui->pageHeight, SIGNAL(valueChanged(int)), this, SLOT(pagePropertyChanged()));
    connect(ui->fillProperty, SIGNAL(propertyChanged(Qt::BrushStyle,QColor,QString)),
            this, SLOT(pagePropertyChanged()));
    connect(ui->fillProperty, SIGNAL(gradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)),
            this, SLOT(onGradientChanged(Qt::BrushStyle,QGradientStops,QGradient::Spread,QPolygonF)));
    connect(ui->showGrid, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(gridStateChanged()));
    connect(ui->lineWidth, SIGNAL(valueChanged(double)), this, SLOT(pagePropertyChanged()));
    connect(ui->lineColor, SIGNAL(colorChanged(QColor,QColor)), this, SLOT(pagePropertyChanged()));
    connect(ui->showRefLine, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(refLineStateChanged()));
    connect(ui->showRuer, SIGNAL(checkStateChanged(Qt::CheckState)), this, SLOT(rulerStateChanged()));
}

ProjectPropertyForm::~ProjectPropertyForm()
{
    delete ui;
}

void ProjectPropertyForm::initProjectData(const ProjectProperty &projectData)
{
    ui->projectName->setText(projectData.getName());
    ui->author->setText(projectData.getAuthor());
}

void ProjectPropertyForm::initPageData(const PageProperty &pageData)
{
    ui->pageName->setText(pageData.getName());
    ui->pageWidth->setValue(pageData.getWidth());
    ui->pageHeight->setValue(pageData.getHeight());
    ui->fillProperty->setIsFill(pageData.getShowLine());
    auto brush = pageData.getBrushProperty();
    QPainterPath path;
    path.addRect({0,0,page.getWidth()*1.0,page.getHeight()*1.0});
    ui->fillProperty->setBaseColor(brush.getColor());
    ui->fillProperty->setBrushStyle(brush.getStyle());
    ui->fillProperty->setImageFile(brush.getImage());
    ui->fillProperty->setGradientSpread(brush.getgradientSpread());
    ui->fillProperty->setGradientStops(brush.getGradientStops());
    ui->fillProperty->setControlPoint(path, brush.getLocation());
    ui->showGrid->setChecked(pageData.getShowLine());
    ui->lineWidth->setValue(pageData.getPenProperty().getWidth());
    ui->lineColor->setColor(pageData.getPenProperty().getColor());
}

void ProjectPropertyForm::showRuler(bool flag)
{
    QSignalBlocker rulerBlocker(ui->showRuer);
    ui->showRuer->setChecked(flag);
}

void ProjectPropertyForm::showGrid(bool flag)
{
    QSignalBlocker blocker(ui->showGrid);
    ui->showGrid->setChecked(flag);
    ui->lineWidth->setVisible(flag);
    ui->lineColor->setVisible(flag);
}

void ProjectPropertyForm::showRefLine(bool flag)
{
    QSignalBlocker blocker(ui->showRefLine);
    ui->showRefLine->setChecked(flag);
}

void ProjectPropertyForm::projectPropertyChanged()
{
    project.setAuthor(ui->author->text());
    project.setName(ui->projectName->text());
    emit projectPropertyEvent(project);
}

void ProjectPropertyForm::pagePropertyChanged()
{
    page.setName(ui->pageName->text().trimmed());
    page.setWidth(ui->pageWidth->value());
    page.setHeight(ui->pageHeight->value());
    PenProperty pen;
    if (ui->showGrid->isChecked()) {
        pen.setStyle(Qt::DashLine);
    }else{
        pen.setStyle(Qt::NoPen);
    }

    pen.setWidth(ui->lineWidth->value());
    pen.setColor(ui->lineColor->getColor());
    page.setPenProperty(pen);
    page.setShowLine(ui->showGrid->isChecked());
    if (sender() == ui->fillProperty) {
        BrushProperty brush;
        brush.setStyle(ui->fillProperty->brushStyle());
        brush.setColor(ui->fillProperty->baseColor());
        brush.setImage(ui->fillProperty->imageFile());
        brush.setGradientStops(ui->fillProperty->gradientStops());//QGradientStops{});
        brush.setLocation(ui->fillProperty->controlPoint());//QPolygonF{});
        page.setBrushProperty(brush);
    }

    emit pagePropertyEvent(page);
}

void ProjectPropertyForm::gridStateChanged()
{
    bool flag = ui->showGrid->isChecked();
    ui->lineWidth->setVisible(flag);
    ui->lineColor->setVisible(flag);
    pagePropertyChanged();
}

void ProjectPropertyForm::rulerStateChanged()
{
    emit rulerStateEvent(ui->showRuer->isChecked());
}

void ProjectPropertyForm::refLineStateChanged()
{
    emit refLineStateEvent(ui->showRefLine->isChecked());
}

void ProjectPropertyForm::onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops, QGradient::Spread spread, const QPolygonF &points)
{
    BrushProperty brush;
    brush.setStyle(brushStyle);
    brush.setGradientStops(stops);
    brush.setgradientSpread(spread);
    brush.setLocation(points);
    page.setBrushProperty(brush);

    emit pagePropertyEvent(page);
}
