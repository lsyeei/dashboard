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

#ifndef PROJECTPROPERTYFORM_H
#define PROJECTPROPERTYFORM_H

#include "pageproperty.h"
#include "projectProperty.h"
#include <QWidget>

namespace Ui {
class ProjectPropertyForm;
}

class ProjectPropertyForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPropertyForm(QWidget *parent = nullptr);
    ~ProjectPropertyForm();
    /**
     * @brief 初始化页面数据
     * @param projectData project属性
     */
    void initProjectData(const ProjectProperty &projectData);
    /**
     * @brief 初始化页面数据
     * @param pageData page属性
     */
    void initPageData(const PageProperty &pageData);
    void showRuler(bool flag);
    void showGrid(bool flag);
    void showRefLine(bool flag);
Q_SIGNALS:
    void projectPropertyEvent(const ProjectProperty &data);
    void pagePropertyEvent(const PageProperty &data);
    void rulerStateEvent(bool flag);
    void refLineStateEvent(bool flag);
private Q_SLOTS:
    void projectPropertyChanged();
    void pagePropertyChanged();
    void gridStateChanged();
    void rulerStateChanged();
    void refLineStateChanged();
    void onGradientChanged(Qt::BrushStyle brushStyle, const QGradientStops &stops,
                           QGradient::Spread spread, const QPolygonF &points);
private:
    Ui::ProjectPropertyForm *ui;
    ProjectProperty project;
    PageProperty page;
};

#endif // PROJECTPROPERTYFORM_H
