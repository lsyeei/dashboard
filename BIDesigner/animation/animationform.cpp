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
    auto groupList = factory->graphicAnimation(id);
    ui->groupCombo->blockSignals(true);
    ui->groupCombo->clear();
    if (groupList.isEmpty()) {
        ui->groupCombo->blockSignals(false);
        return;
    }
    // 初始化组数据
    foreach (auto group, groupList) {
        ui->groupCombo->addItem(group.getName(), group.getId());
    }
    ui->groupCombo->blockSignals(false);
    if (groupList.count() > 0) {
        ui->groupCombo->setCurrentItem(0);
        onGroupChanged(0);
    }
}

void AnimationForm::onAnimationMenuSelected()
{
    auto obj = sender();
    if (obj == nullptr) {
        return;
    }
    if (ui->groupCombo->count() <= 0) {
        // 首次添加动画，自动添加一个分组
        QSignalBlocker blocker{ui->groupCombo};
        QString groupName{tr("默认")};
        auto groupId = AnimationFactory::instance()->addGroup(graphicItem, groupName);
        if (groupId < 0) {
            return;
        }
        ui->groupCombo->addItem(groupName, groupId);
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
    auto i = ui->groupCombo->currentIndex();
    if (i < 0) {
        return;
    }
    auto groupId = ui->groupCombo->itemData(i).toInt();
    auto param = ui->animationView->getItem(index).params;
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    if (type) {
        type->paramWidget()->hide();
    }
    ui->animationView->removeItem(index);
    // 删除动画数据
    AnimationFactory::instance()->updateAnimate(graphicItem, groupId,
                                                ui->animationView->getAllAnimationParams());
    ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);
}

void AnimationForm::onPlay()
{
    if (player.isNull()){
        auto groupId = ui->groupCombo->itemData(ui->groupCombo->currentIndex()).toInt();
        player = AnimationFactory::instance()->play(graphicItem, groupId);
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
    showProperty(nullptr);
    if (newIndex < 0) {
        return;
    }
    auto param = ui->animationView->getItem(newIndex).params;
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
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
    auto i = ui->groupCombo->currentIndex();
    if (i < 0) {
        return;
    }
    auto groupId = ui->groupCombo->itemData(i).toInt();
    auto obj = sender();
    auto widget = dynamic_cast<AbstractParamWidget*>(obj);
    if (widget == nullptr) {
        return;
    }
    auto param = widget->getParam();

    if (ui->animationView->setAnimationParam(index, param)){
        // 更新图元动画参数
        AnimationFactory::instance()->updateAnimate(graphicItem, groupId, ui->animationView->getAllAnimationParams());
    }else{
        // 重新显示原参数
        onAnimateSelectChanged(index, index);
    }
}

void AnimationForm::onAddGroup(int index)
{
    auto groupName = ui->groupCombo->itemText(index).trimmed();
    if (groupName.isEmpty()) {
        QMessageBox::information(this, tr("提示"), tr("组名称不能为空！"));
        ui->groupCombo->setFocus();
    }
    auto id = AnimationFactory::instance()->addGroup(graphicItem, groupName);
    if (id >= 0) {
        ui->groupCombo->setItemData(index, id);
        ui->animationView->clear();
    }else{
        QMessageBox::information(this, tr("提示"), tr("新建组失败！"));
        ui->groupCombo->setFocus();
    }
}

void AnimationForm::onRemoveGroup(const QString &name, QVariant data)
{
    if (!data.isValid() || !data.canConvert<int>()){
        QMessageBox::information(this, tr("提示"), name + tr("删除失败！"));
        return;
    }
     auto btn = QMessageBox::question(this, tr("提示"),
                QString(tr("确定要删除[%1]么，该组下的所有动画将同时删除").arg(name)));
    if (btn == QMessageBox::Cancel) {
         return;
    }
    int groupId = data.toInt();
    if (AnimationFactory::instance()->removeGroup(graphicItem, groupId)){
        ui->animationView->clear();
    }else{
        QMessageBox::information(this, tr("提示"), name + tr("删除失败！"));
    }
}

void AnimationForm::onModifyGroup(int index)
{
    if (index < 0){
        return;
    }
    auto groupName = ui->groupCombo->itemText(index).trimmed();
    auto groupId = ui->groupCombo->itemData(index).toInt();
    bool flag = ui->enableRadio->isChecked();
    AnimationFactory::instance()->modifyGroupName(graphicItem, groupId, groupName);
    AnimationFactory::instance()->enableGroup(graphicItem, groupId, flag);
}

void AnimationForm::onGroupChanged(int index)
{
    if (index < 0){
        ui->animationView->clear();
        return;
    }
    // 获取组信息
    auto groupId = ui->groupCombo->itemData(index).toInt();
    auto group = AnimationFactory::instance()->getGroup(graphicItem, groupId);
    auto flag = group.getEnable();
    ui->enableRadio->setChecked(flag);
    ui->disableRadio->setChecked(!flag);
    // 显示已配置的动画
    ui->animationView->clear();
    auto actions = group.getAnimationList();
    if (actions.isEmpty()) {
        return;
    }
    foreach (auto act, actions) {
        addAnimateItem(act);
    }
    ui->animationView->setCurrentItemIndex(-1);
}

void AnimationForm::hideEvent(QHideEvent *event)
{
    // 隐藏当前路径
    ui->animationView->setCurrentItemIndex(-1);
    QWidget::hideEvent(event);
}

void AnimationForm::initUI()
{
    ui->property->hide();
    // 初始化分组
    ui->groupCombo->addItem(tr("默认"), 0);
    ui->groupCombo->setCurrentItem(0);
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
    connect(ui->animationView, SIGNAL(itemSelectionChanged(int,int)),
            this, SLOT(onAnimateSelectChanged(int,int)));
    // 按钮事件
    connect(ui->removeBtn, SIGNAL(clicked(bool)), this, SLOT(onRemoveAnimate()));
    connect(ui->playBtn, SIGNAL(clicked(bool)), this, SLOT(onPlay()));
    // 分组
    connect(ui->groupCombo, &BIComboBox::itemAdded,
            this, &AnimationForm::onAddGroup);
    connect(ui->groupCombo, &BIComboBox::itemRemoved,
            this, &AnimationForm::onRemoveAnimate);
    connect(ui->groupCombo, &BIComboBox::itemModified,
            this, &AnimationForm::onModifyGroup);
    connect(ui->groupCombo, &BIComboBox::currentIndexChanged,
            this, &AnimationForm::onGroupChanged);
    connect(ui->enableRadio, &QRadioButton::clicked,
            this, [&]{onModifyGroup(ui->groupCombo->currentIndex());});
    connect(ui->disableRadio, &QRadioButton::clicked,
            this, [&]{onModifyGroup(ui->groupCombo->currentIndex());});
}

bool AnimationForm::addAnimateItem(const AnimationParam &param)
{
    auto i = ui->groupCombo->currentIndex();
    if (i < 0) {
        return false;
    }
    auto groupId = ui->groupCombo->itemData(i).toInt();
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
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    AnimationItem item{type->getIcon(), type->getName(), newParam};
    if (ui->animationView->addItem(item)){
        // 更新图元动画参数
        AnimationFactory::instance()->updateAnimate(graphicItem, groupId,
                                                    ui->animationView->getAllAnimationParams());
    }
    ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);
    return true;
}

void AnimationForm::showProperty(QWidget *widget)
{
    auto layout = ui->property->layout();
    auto count = layout->count();
    for (int i = 0; i < count; ++i) {
        auto item = layout->itemAt(i)->widget();
        if (item) {
            item->hide();
        }
    }
    if (widget){
        widget->show();
    }
}
