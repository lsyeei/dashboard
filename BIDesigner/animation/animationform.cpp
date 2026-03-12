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
#include "undoobject.h"
#include "bigraphicsscene.h"
#include "bigraphicsview.h"
#include "graphicrootwidget.h"
#include "ui_animationform.h"

#include <QCborMap>
#include <QMenu>
#include <QSignalBlocker>
#include <QTabWidget>
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

void AnimationForm::undoTrigger(QString text, QList<UndoAction> actions)
{
    QList<QPair<QString, QVariant>> undoAction;
    QList<QPair<QString, QVariant>> redoAction;

    auto count = actions.count();
    for(int i = 0; i<count; ++i){
        undoAction.append({actions[count - i - 1].id, actions[count - i - 1].undoData});
        redoAction.append({actions[i].id, actions[i].redoData});
    }

    // 统一携带graphic
    QVariantList undoObj, redoObj;
    undoObj << QVariant::fromValue(graphicItem) << QVariant::fromValue(undoAction);
    redoObj << QVariant::fromValue(graphicItem) << QVariant::fromValue(redoAction);
    static const QMetaMethod undoSignal = QMetaMethod::fromSignal(&AnimationForm::undoEvent);
    if (isSignalConnected(undoSignal)) {
        emit undoEvent(text, undoObj, redoObj);
    } else {
        parseUndoAction(redoObj, false);
    }
}

int AnimationForm::groupId2ComboIndex(int groupId)
{
    for (int i = 0; i < ui->groupCombo->count(); ++i) {
        if (ui->groupCombo->itemData(i).toInt() == groupId) {
            return i;
        }
    }
    return -1;
}

void AnimationForm::parseUndoAction(QVariant undoData, bool isUndo)
{
    auto list = undoData.toList();
    if (list.count() < 2) {
        return;
    }
    auto item = list[0].value<ICustomGraphic*>();
    if (item == nullptr) {
        return;  // 安全检查
    }
    graphicItem = item;
    item->setSelected(true);
    // 切换到本窗口
    auto parent = parentWidget()->parentWidget();
    if (parent) {
        auto tab = dynamic_cast<QTabWidget*>(parent);
        if (tab) {
            tab->setTabVisible(tab->indexOf(this), true);
            tab->setCurrentWidget(this);
        }
    }

    auto data = list[1].value<QList<QPair<QString, QVariant>>>();

    foreach (auto command, data) {
        commonAction(command.first, command.second, isUndo);
    }
}

void AnimationForm::commonAction(QString action, QVariant data, bool isUndo)
{
    if (action == "addGroup") {
        auto list = data.toList();
        if (list.count() < 2) {
            return;
        }
        int groupId = list[0].toInt();
        QString groupName = list[1].toString();
        int index{-1};
        ui->groupCombo->blockSignals(true);
        if (isUndo) {
            // undo: 数据层 + UI 层
            AnimationFactory::instance()->removeGroup(graphicItem, groupId);

            // UI 操作：找到并删除 groupCombo 中的项
            int comboIndex = groupId2ComboIndex(groupId);
            if (comboIndex >= 0) {
                ui->groupCombo->removeItem(comboIndex);
            }
        } else {
            // redo: 数据层 + UI 层
            AnimationFactory::instance()->addGroup(graphicItem, groupId, groupName);

            // UI 操作：重新添加到 groupCombo
            ui->groupCombo->addItem(groupName, groupId);
        }
        // 选中最后一项
        index = ui->groupCombo->count() - 1;
        ui->groupCombo->setCurrentItem(index);
        ui->groupCombo->blockSignals(false);
        onGroupChanged(index);

    } else if (action == "removeGroup") {
        ui->groupCombo->blockSignals(true);
        if (isUndo) {
            // undo: 数据层 + UI 层
            auto group = data.value<AnimationGroup>();
            AnimationFactory::instance()->addGroup(graphicItem, group.getId(), group.getName());
            AnimationFactory::instance()->updateAnimate(graphicItem, group.getId(),
                                                        group.getAnimationList());
            AnimationFactory::instance()->enableGroup(graphicItem, group.getId(), group.getEnable());

            // UI 操作：重新添加到 groupCombo
            ui->groupCombo->addItem(group.getName(), group.getId());
            ui->groupCombo->setCurrentItem(ui->groupCombo->count() - 1);

        } else {
            // redo: 数据层 + UI 层
            auto groupId = data.toInt();
            AnimationFactory::instance()->removeGroup(graphicItem, groupId);

            // UI 操作：从 groupCombo 删除
            int comboIndex = groupId2ComboIndex(groupId);
            if (comboIndex >= 0) {
                ui->groupCombo->removeItem(comboIndex);
                // 清空动画列表
                ui->animationView->clear();
            }
            ui->groupCombo->setCurrentItem(ui->groupCombo->count() - 1);
        }
        ui->groupCombo->blockSignals(false);
        onGroupChanged(ui->groupCombo->currentIndex());

    } else if (action == "modifyGroup") {
        auto list = data.toList();
        if (list.count() < 3) {
            return;
        }
        int groupId = list[0].toInt();
        QString name = list[1].toString();
        bool enable = list[2].toBool();

        // 数据层
        AnimationFactory::instance()->modifyGroupName(graphicItem, groupId, name);
        AnimationFactory::instance()->enableGroup(graphicItem, groupId, enable);

        // UI 操作：修改 groupCombo 的文本
        QSignalBlocker radio1(ui->enableRadio);
        QSignalBlocker radio2(ui->disableRadio);
        ui->enableRadio->setChecked(enable);
        ui->disableRadio->setChecked(!enable);
        int comboIndex = groupId2ComboIndex(groupId);
        if (comboIndex >= 0) {
            QSignalBlocker blocker(ui->groupCombo);
            ui->groupCombo->setCurrentItem(comboIndex);
            ui->groupCombo->setItemText(comboIndex, name);
        }

    } else if (action == "addAnimate") {
        auto list = data.toList();
        if (list.count() < 2) {
            return;
        }
        auto group = list[0].value<AnimationGroup>();
        auto index = list[1].toInt();
        AnimationFactory::instance()->updateAnimate(graphicItem, group.getId(), group.getAnimationList());

        ui->animationView->blockSignals(true);
        ui->animationView->clear();
        auto actions = group.getAnimationList();
        foreach (auto act, actions) {
            addAnimateItem(act);
        }
        if (!isUndo) {
            index = ui->animationView->itemCount() - 1;
        }
        ui->animationView->blockSignals(false);
        ui->animationView->setCurrentItemIndex(index);
        ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);

    } else if (action == "removeAnimate") {
        auto list = data.toList();
        if (list.count() < 2) {
            return;
        }
        auto group = list[0].value<AnimationGroup>();
        auto index = list[1].toInt();

        // 数据层
        AnimationFactory::instance()->updateAnimate(graphicItem, group.getId(), group.getAnimationList());

        // UI 操作
        ui->animationView->blockSignals(true);
        ui->animationView->clear();
        auto actions = group.getAnimationList();
        foreach (auto act, actions) {
            addAnimateItem(act);
        }
        ui->animationView->blockSignals(false);
        ui->animationView->setCurrentItemIndex(index);
        ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);

    } else if (action == "updateAnimateParam") {
        auto list = data.toList();
        if (list.count() < 3) {
            return;
        }
        int groupId = list[0].toInt();
        auto index = list[1].toInt();
        auto param = list[2].value<AnimationParam>();

        // 数据层
        AnimationFactory::instance()->updateAnimateParam(graphicItem, groupId, index, param);

        // UI 操作：更新 animationView
        ui->animationView->setAnimationParam(index, param);
        ui->animationView->setCurrentItemIndex(index);
        onAnimateSelectChanged(-1, index);
    }
}

void AnimationForm::undo(QVariant undoData)
{
    parseUndoAction(undoData, true);
}

void AnimationForm::redo(QVariant redoData)
{
    parseUndoAction(redoData, false);
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
    bool firstGroup{false};
    if (ui->groupCombo->count() <= 0) {
        // 首次添加动画，自动添加一个分组
        QString groupName{tr("默认")};
        auto groupId = AnimationFactory::instance()->addGroup(graphicItem, groupName);
        if (groupId < 0) {
            return;
        }
        QSignalBlocker blocker(ui->groupCombo);
        ui->groupCombo->addItem(groupName, groupId);
        firstGroup = true;
    }
    graphicItem->setSelected(true);
    QSignalBlocker blocker(ui->groupCombo);
    auto groupId = ui->groupCombo->currentData().toInt();
    auto typeId = obj->property("id").toString();
    auto type = AnimationFactory::instance()->getAnimateType(typeId);
    if (type) {
        auto widget = type->paramWidget();
        widget->initWidget();
        // record undo
        auto oldIndex = ui->animationView->currentItemIndex();
        auto oldGroup = AnimationFactory::instance()->getGroup(graphicItem, groupId);
        auto list = oldGroup.getAnimationList();
        auto newParam = widget->getParam();
        list << newParam;
        AnimationGroup newGroup{groupId, oldGroup.getName(), oldGroup.getEnable()};
        newGroup.setAnimationList(list);
        QVariantList undoObj, redoObj;
        undoObj << QVariant::fromValue(oldGroup) << oldIndex;
        redoObj << QVariant::fromValue(newGroup) << -1;
        if (firstGroup) {
            ui->groupCombo->removeItem(ui->groupCombo->currentIndex());
            QVariantList groupObj;
            groupObj << groupId << oldGroup.getName();
            undoTrigger(tr("添加动画"), {{"addGroup", groupObj, groupObj},
                                         {"addAnimate", undoObj, redoObj}});
        }else{
            undoTrigger(tr("添加动画"), {{"addAnimate", undoObj, redoObj}});
        }
    }else if (firstGroup) {
        ui->groupCombo->removeItem(ui->groupCombo->currentIndex());
        QVariantList groupObj;
        groupObj << groupId << ui->groupCombo->itemText(ui->groupCombo->currentIndex());
        undoTrigger(tr("添加组"), {{"addGroup", groupObj, groupObj}});
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
    // auto param = ui->animationView->getItem(index).params;
    // auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    // if (type) {
    //     type->paramWidget()->hide();
    // }

    // undoTrigger 前调用 getGroup 获取旧数据
    QVariantList undoObj, redoObj;
    auto group = AnimationFactory::instance()->getGroup(graphicItem, groupId);
    AnimationGroup newGroup{groupId, group.getName(), group.getEnable()};
    ui->animationView->removeItem(index);
    newGroup.setAnimationList(ui->animationView->getAllAnimationParams());
    undoObj << QVariant::fromValue(group) << index;
    redoObj << QVariant::fromValue(newGroup) << -1;

    // 触发 undo 事件（只保存数据层）
    undoTrigger("删除动画", {{"removeAnimate", undoObj, redoObj}});

    // ui->playBtn->setEnabled(ui->animationView->itemCount() > 0);
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
    Q_UNUSED(oldIndex)
    // 使能移除按钮
    ui->removeBtn->setEnabled(newIndex >= 0);
    showProperty(nullptr);
    if (newIndex < 0 || ui->animationView->itemCount() <= 0) {
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
    auto oldParams = ui->animationView->getItem(index).params;
    if (ui->animationView->setAnimationParam(index, param)){

        // undoTrigger 前调用 getGroup 获取旧数据
        QVariantList undoObj, redoObj;
        undoObj << groupId << index << QVariant::fromValue(oldParams);
        redoObj << groupId << index << QVariant::fromValue(param);

        // 触发 undo 事件（只保存数据层）
        undoTrigger("更新动画", {{"updateAnimateParam", undoObj, redoObj}});
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
        return;
    }

    // 先调用 addGroup 获取 groupId
    int id = AnimationFactory::instance()->addGroup(graphicItem, groupName);
    if (id < 0) {
        QMessageBox::information(this, tr("提示"), tr("新建组失败！"));
        ui->groupCombo->setFocus();
        return;
    }

    // ui->groupCombo->setItemData(index, id);
    QSignalBlocker blocker(ui->groupCombo);
    ui->groupCombo->removeItem(ui->groupCombo->currentIndex());
    QVariantList redoObj;
    redoObj << id << groupName;
    // 触发 undo 事件（只保存数据层）
    undoTrigger("添加动画组", {{"addGroup", redoObj, redoObj}});
}

void AnimationForm::onRemoveGroup(const QString &name, QVariant data)
{
    if (!data.isValid() || !data.canConvert<int>()){
        QMessageBox::information(this, tr("提示"), name + tr("删除失败！"));
        return;
    }

    int groupId = data.toInt();

    QSignalBlocker bolcker(ui->groupCombo);
    ui->groupCombo->addItem(name, groupId);
    ui->groupCombo->setCurrentItem(ui->groupCombo->count() - 1);
    onGroupChanged(ui->groupCombo->currentIndex());
    auto btn = QMessageBox::question(this, tr("提示"),
                QString(tr("确定要删除[%1]么，该组下的所有动画将同时删除").arg(name)));
    if (btn == QMessageBox::No) {
        return;
    }

    // undoTrigger 前获取完整数据
    auto group = AnimationFactory::instance()->getGroup(graphicItem, groupId);

    // 触发 undo 事件（只保存数据层：完整 AnimationGroup + groupId）
    undoTrigger(tr("删除动画组"), {{"removeGroup",
        QVariant::fromValue(group), groupId}});
}

void AnimationForm::onModifyGroup(int index)
{
    if (index < 0){
        return;
    }
    auto groupName = ui->groupCombo->itemText(index).trimmed();
    auto groupId = ui->groupCombo->itemData(index).toInt();
    bool flag = ui->enableRadio->isChecked();

    // undoTrigger 前调用 getGroup 获取旧数据
    QVariantList undoObj, redoObj;
    auto group = AnimationFactory::instance()->getGroup(graphicItem, groupId);
    undoObj << groupId << group.getName() << group.getEnable();
    redoObj << groupId << groupName << flag;
    // 触发 undo 事件
    undoTrigger("修改组", {{"modifyGroup", undoObj, redoObj}});
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
            this, &AnimationForm::onRemoveGroup);
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
    // 添加动画到视图
    auto type = AnimationFactory::instance()->getAnimateType(param.getTypeId());
    AnimationItem item{type->getIcon(), type->getName(), newParam};
    ui->animationView->addItem(item);
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

AbstractParamWidget* AnimationForm::currentPropertyWidget(){
    AbstractParamWidget *widget{nullptr};
    auto layout = ui->property->layout();
    auto count = layout->count();
    for (int i = 0; i < count; ++i) {
        auto item = layout->itemAt(i)->widget();
        if (item->isVisible()) {
            widget = dynamic_cast<AbstractParamWidget*>(item);
            break;
        }
    }
    return widget;
}
