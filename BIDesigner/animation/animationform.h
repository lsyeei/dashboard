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

#ifndef ANIMATIONFORM_H
#define ANIMATIONFORM_H

#include "animationParam.h"
#include "undoobject.h"
#include <QWidget>
#include <QAbstractAnimation>
#include <QPointer>

class ICustomGraphic;
class IMovePath;
namespace Ui {
class AnimationForm;
}

class AnimationForm : public QWidget, public UndoObject
{
    Q_OBJECT

public:
    explicit AnimationForm(QWidget *parent = nullptr);
    ~AnimationForm();
    void setGraphicItem(ICustomGraphic *item);
    
    // UndoObject 接口实现
    void undo(QVariant undoData) override;
    void redo(QVariant redoData) override;

Q_SIGNALS:
    void undoEvent(const QString &text, QVariant undoData, QVariant redoData) override;
    void playEvent(bool playing);
protected Q_SLOTS:
    void onAnimationMenuSelected();
    void onRemoveAnimate();
    void onPlay();
    void onPlayEnd();
    void onAnimateSelectChanged(int oldIndex, int newIndex);
    void onAnimateParamChanged();
    // 响应分组事件
    void onAddGroup(int index);
    void onRemoveGroup(const QString &name, QVariant data);
    void onModifyGroup(int index);
    void onGroupChanged(int index);

    // QWidget interface
protected:
    void hideEvent(QHideEvent *event);
private:
    Ui::AnimationForm *ui;
    QMenu *actionMenu;
    // 当前图元对象
    ICustomGraphic *graphicItem;
    QPointer<QAbstractAnimation> player;
    // 播放动画前前编辑的动画索引
    int editItemIndex{-1};
    // 动画播放标记
    bool playFlag{false};

    void initUI();
    /**
     * @brief addAnimateItem 向列表中添加动画项目
     * @param param 动画参数
     * @return true 成功，false 失败
     */
    bool addAnimateItem(const AnimationParam &param);
    /**
     * @brief showProperty 显示属性
     * @param widget 指定的属性
     */
    void showProperty(QWidget *widget);
    AbstractParamWidget* currentPropertyWidget();
    
    // UndoObject 辅助方法
    void undoTrigger(QString text, QList<UndoAction> actions);
    void parseUndoAction(QVariant undoData, bool isUndo);
    /**
     * @brief 普通的撤销命令
     * @param action 命令动作名词
     * @param data 数据
     * @param isUndo true 执行撤销，false 执行redo
     */
    void commonAction(QString action, QVariant data, bool isUndo = true);
    int groupId2ComboIndex(int groupId);
};

#endif // ANIMATIONFORM_H
