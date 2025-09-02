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

#include "animationfactory.h"
#include "animationform.h"
#include "bigraphicsscene.h"
#include "bigraphicsview.h"
#include "graphicrootwidget.h"
#include "ui_animationform.h"

#include <QMenu>
#include "icustomgraphic.h"
#include <animation/path/movepathfactory.h>
#include "animation/abstractparamwidget.h"

AnimationForm::AnimationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AnimationForm)
{
    ui->setupUi(this);
    initUI();
}

AnimationForm::~AnimationForm()
{
    delete ui;
}

void AnimationForm::setGraphicItem(ICustomGraphic *item)
{
    if (item == nullptr || graphicItem == item) {
        return;
    }
    if (!player.isNull()){
        // 终止正在执行的动画
        onPlay();
        graphicItem->setSelected(false);
    }

    graphicItem = item;

    // 隐藏属性面板
    ui->property->hide();
    auto childs = ui->property->children();
    foreach (auto child, childs) {
        if (child->isWidgetType()) {
            dynamic_cast<QWidget*>(child)->hide();
        }
    }

    // 更新数据
    QSignalBlocker animationView(ui->animationView);
    ui->animationView->clear();
    auto factory = AnimationFactory::instance();
    auto typeList = factory->animateTypeList();
    foreach (auto type, typeList) {
        type->paramWidget()->setOwner(item);
    }

    auto scene = dynamic_cast<BIGraphicsScene*>(item->scene());
    if (scene == nullptr) {
        return;
    }
    auto id = scene->getItemId(item);
    if (id.isEmpty()) {
        return;
    }
    auto actions = factory->graphicAnimation(id);
    if (actions.isEmpty()) {
        return;
    }
    foreach (auto act, actions) {
        addAnimateItem(act);
    }
    ui->animationView->setCurrentItemIndex(-1);
}

void AnimationForm::onAnimationMenuSelected()
{
    auto obj = sender();
    if (obj == nullptr) {
        return;
    }
    graphicItem->setSelected(true);
    auto typeId = obj->property("id").toString();
    auto type = AnimationFactory::instance()->getAnimateType(typeId);
    if (type) {
        auto widget = type->paramWidget();
        widget->initWidget();
        if(addAnimateItem(widget->getParam())){
            widget->show();
            ui->property->show();
        }
    }
}

void AnimationForm::onRemoveAnimate()
{
    auto index = ui->animationView->currentItemIndex();
    if (index < 0) {
        return;
    }
    auto param = ui->animationView->getItem(index).params;
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    if (type) {
        type->paramWidget()->hide();
    }
    ui->animationView->removeItem(index);
    // 删除动画数据
    AnimationFactory::instance()->updateAnimate(graphicItem, ui->animationView->getAllAnimationParams());
    ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);
}

void AnimationForm::onPlay()
{
    if (player.isNull()){
        player = AnimationFactory::instance()->play(graphicItem);
        if (player == nullptr) {
            qDebug() << "未找到动画配置";
            return;
        }
        emit playEvent(true);
        graphicItem->setSelected(false);
        graphicItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        connect(player, SIGNAL(finished()), this, SLOT(onPlayEnd()), Qt::QueuedConnection);
        ui->playBtn->setText(tr("停止"));
        ui->playBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        editItemIndex = ui->animationView->currentItemIndex();
        ui->animationView->setCurrentItemIndex(-1);
    } else {
        player->stop();
        onPlayEnd();
    }
}

void AnimationForm::onPlayEnd()
{
    ui->playBtn->setText(tr("播放"));
    ui->playBtn->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
    player.clear();
    ui->animationView->setCurrentItemIndex(editItemIndex);
    graphicItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    graphicItem->setSelected(true);
    emit playEvent(false);
}

void AnimationForm::onAnimateSelectChanged(int oldIndex, int newIndex)
{
    // 使能移除按钮
    ui->removeBtn->setEnabled(newIndex >= 0);
    if (newIndex < 0) {
        if (oldIndex >= 0){
            // 隐藏原来索引对应的属性
            auto param = ui->animationView->getItem(oldIndex).params;
            auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
            if (type){
                type->paramWidget()->hide();
            }
        }
        return;
    }
    auto param = ui->animationView->getItem(oldIndex).params;
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    if (type == nullptr || oldIndex != newIndex) {
        if (type) {
            type->paramWidget()->hide();
        }
        param = ui->animationView->getItem(newIndex).params;
        type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    }
    ui->property->show();
    auto widget = type->paramWidget();
    widget->update(param);
    widget->show();
}

void AnimationForm::onAnimateParamChanged()
{
    auto index = ui->animationView->currentItemIndex();
    if (index < 0) {
        return;
    }
    auto obj = sender();
    auto widget = dynamic_cast<AbstractParamWidget*>(obj);
    if (widget == nullptr) {
        return;
    }
    auto param = widget->getParam();

    if (ui->animationView->setAnimationParam(index, param)){
        // 更新图元动画参数
        AnimationFactory::instance()->updateAnimate(graphicItem, ui->animationView->getAllAnimationParams());
    }else{
        // 重新显示原参数
        onAnimateSelectChanged(index, index);
    }
}

void AnimationForm::hideEvent(QHideEvent *event)
{
    // qDebug() << __FUNCTION__;
    // 隐藏当前路径
    ui->animationView->setCurrentItemIndex(-1);
    QWidget::hideEvent(event);
}

void AnimationForm::initUI()
{
    ui->property->hide();
    // 禁用按钮
    ui->removeBtn->setDisabled(true);
    ui->playBtn->setDisabled(true);
    // 添加动画菜单
    auto typeList = AnimationFactory::instance()->animateTypeList();

    actionMenu = new QMenu(this);
    foreach (auto item, typeList) {
        auto menu = actionMenu->addAction(item->getIcon(), item->getName(),
                                          this, SLOT(onAnimationMenuSelected()));
        menu->setProperty("id", item->getId());
        auto widget = item->paramWidget();
        ui->property->layout()->addWidget(widget);
        connect(widget, SIGNAL(paramChanged()), this, SLOT(onAnimateParamChanged()));
        widget->hide();
    }

    ui->addBtn->setMenu(actionMenu);

    // 动画列表
    ui->animationView->clear();
    connect(ui->animationView, SIGNAL(itemSelectionChanged(int,int)), this, SLOT(onAnimateSelectChanged(int,int)));
    // 按钮事件
    connect(ui->removeBtn, SIGNAL(clicked(bool)), this, SLOT(onRemoveAnimate()));
    connect(ui->playBtn, SIGNAL(clicked(bool)), this, SLOT(onPlay()));

}


bool AnimationForm::addAnimateItem(const AnimationParam &param)
{
    // 查找已添加的同类动画，防止时间重叠，自动修改延迟参数
    auto count = ui->animationView->itemCount();
    qreal minDelay = 0;
    for (int i = 0; i < count; ++i) {
        auto data = ui->animationView->getItem(i);
        auto animate = data.params;
        if (animate.getTypeId().compare(param.getTypeId()) == 0) {
            // 发现同类动画
            if (param.getLoopCount() == -1 || animate.getLoopCount() == -1){
                QMessageBox::information(this, tr("提示"),
                    tr("同类动画已经存在且为循环播放，同一时间内同类动画只能有一个。"));
                return false;
            }
            minDelay += animate.getDelay() + animate.getDuration() * animate.getLoopCount();
        }
    }
    AnimationParam newParam(param);
    if (minDelay > 0) {
        minDelay += param.getDelay();
        newParam.setDelay(minDelay);
    }
    // 添加新动画
    // auto actionItem = actionMap[param.getType()];
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    AnimationItem item{type->getIcon(), type->getName(), newParam};
    if (ui->animationView->addItem(item)){
        // 更新图元动画参数
        AnimationFactory::instance()->updateAnimate(graphicItem, ui->animationView->getAllAnimationParams());
    }
    ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);
    return true;
}
