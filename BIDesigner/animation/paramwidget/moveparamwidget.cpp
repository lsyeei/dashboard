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

#include "moveparamwidget.h"
#include "animation/path/imovepathplugin.h"
#include "bigraphicsscene.h"
#include "qgraphicsscene.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <animation/path/movepathfactory.h>

MoveParamWidget::MoveParamWidget(const QString &typeId, QWidget* parent)
    : AbstractParamWidget(typeId, parent){
    initUI();
}


void MoveParamWidget::initWidget()
{
    AnimationParam data;
    data.setTypeId(animationType);
    update(data);
}

void MoveParamWidget::update(const AnimationParam &value)
{
    AbstractParamWidget::update(value);
    clearPath();
    QSignalBlocker optionBlocker(pathOption);
    if (value.getValueTo().canConvert<QPair<QString,QString>>()) {
        auto data = value.getValueTo().value<QPair<QString,QString>>();
        if (data.first.isEmpty()) {
            pathType = 0;
            pathItems[pathType] = nullptr;
            pathOption->setCurrentIndex(0);
        } else {
            pathType =pathOption->findData(data.first);
            pathOption->setCurrentIndex(pathType);
            // 创建移动路径
            pathItems[pathType] = restorePath(data.first, data.second);
        }
    } else {
        pathType = 0;
        pathItems[pathType] = nullptr;
        pathOption->setCurrentIndex(0);
    }
}

void MoveParamWidget::onPathOptionChanged()
{
    if (owner) {
        owner->setSelected(true);
    }
    if (pathItems[pathType] != nullptr) {
        pathItems[pathType]->hide();
    }
    pathType = pathOption->currentIndex();
    if(pathItems[pathType] == nullptr){
        drawBtn->setEnabled(true);
    } else {
        pathItems[pathType]->show();
        drawBtn->setEnabled(false);
    }
}

void MoveParamWidget::onDrawPath()
{
    if (owner == nullptr) {
        return;
    }
    pathType = pathOption->currentIndex();
    // 给视图设置下一个要绘制的图元
    auto scene = owner->scene();
    auto path = MovePathFactory::instance()->createPath(pathOption->currentData().toString());
    if (path == nullptr) {
        return;
    }
    pathItems[pathType] = path;
    path->setMaster(owner);
    // owner->setSelected(false);
    dynamic_cast<BIGraphicsScene*>(scene)->hideItem(path);
    scene->addItem(path);
    path->setParentItem(owner);
    scene->setFocus(Qt::MouseFocusReason);
    connect(path, SIGNAL(pathChanged()), this, SLOT(onPathChanged()));
}

void MoveParamWidget::onPathChanged()
{
    if (pathItems[pathType] != nullptr){
        param.setValueFrom(QVariant::fromValue(pathItems[pathType]->path()));
        param.setValueTo(QVariant::fromValue(
            QPair<QString, QString>{pathOption->currentData().toString(),
                                    pathItems[pathType]->toXml()}));
        AbstractParamWidget::onValueChanged();
    }
}

void MoveParamWidget::initUI()
{
    auto r = new QHBoxLayout();
    r->setContentsMargins(0,0,0,0);
    layout->addLayout(r);

    r->addWidget(new QLabel{tr("运动路径：")});
    pathOption = new QComboBox();
    r->addWidget(pathOption);
    drawBtn = new QPushButton{tr("绘制")};
    r->addWidget(drawBtn);
    r->addStretch();

    pathOption->clear();
    auto pathItems = MovePathFactory::instance()->allPath();
    foreach (auto item, pathItems) {
        pathOption->addItem(item->name(), item->id());
    }

    connect(pathOption, SIGNAL(currentIndexChanged(int)), this, SLOT(onPathOptionChanged()));
    connect(drawBtn, SIGNAL(clicked(bool)), this, SLOT(onDrawPath()));
}

void MoveParamWidget::clearPath()
{
    pathType = -1;
    if (owner) {
        auto scene = owner->scene();
        for (int i = 0; i < pathItems.count(); ++i) {
            if (pathItems[i]) {
                scene->removeItem(pathItems[i]);
                pathItems[i] = nullptr;
            }
        }
    }
    pathItems.clear();
}

IMovePath *MoveParamWidget::restorePath(const QString &pathPluginId, const QString &xml)
{
    if (owner == nullptr) {
        return nullptr;
    }
    auto path = MovePathFactory::instance()->createPath(pathPluginId, xml);
    if (path == nullptr){
        return nullptr;
    }
    auto scene = owner->scene();
    scene->addItem(path);
    path->setParentItem(owner);
    path->setMaster(owner);
    dynamic_cast<BIGraphicsScene*>(scene)->hideItem(path);
    connect(path, SIGNAL(pathChanged()), this, SLOT(onPathChanged()));
    return path;
}

void MoveParamWidget::hideEvent(QHideEvent *event)
{
    // 属性设置隐藏时，自动清除路径
    if(isHidden()){
        clearPath();
    }
    QWidget::hideEvent(event);
}
