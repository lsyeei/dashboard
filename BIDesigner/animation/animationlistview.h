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

#ifndef ANIMATELISTVIEW_H
#define ANIMATELISTVIEW_H

#include "animationParam.h"

#include <QWidget>
struct AnimationItem{
    bool isEmpty(){return name.isEmpty();}
    QIcon icon;
    QString name;
    AnimationParam params;
};

class AnimationListView : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowHeight READ rowHeight WRITE setRowHeight FINAL)
    Q_PROPERTY(int iconSize READ iconSize WRITE setIconSize FINAL)
    Q_PROPERTY(int textWidth READ textWidth WRITE setTextWidth FINAL)
public:
    explicit AnimationListView(QWidget *parent = nullptr);
    void clear();
    bool addItem(const AnimationItem &item);
    void removeItem(int index);
    void setCurrentItemIndex(int index);
    int currentItemIndex();
    AnimationItem getItem(int index);
    bool setAnimationParam(int index, const AnimationParam &params);
    int itemCount();
    QList<AnimationParam> getAllAnimationParams();

    int rowHeight() const;
    void setRowHeight(int newRowHeight);

    int iconSize() const;
    void setIconSize(int newIconSize);

    int textWidth() const;
    void setTextWidth(int newTextWidth);

signals:
    void itemSelectionChanged(int oldIndex, int newIndex);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QList<AnimationItem> animations;
    int currentIndex{-1};
    int m_rowHeight{24};
    int m_iconSize{18};
    int m_textWidth{60};
    int m_rowSpace{3};
    int m_colSpace{3};
    // 动画总时长
    qreal totalTime{0};
    // 循环播放的动画数量
    int infiniteCount{0};
    /**
     * @brief checkItem 检查指定索引的项目
     * @param index 指定的索引
     * @return true 参数可用，false 参数有误
     */
    bool checkItem(int index);
    /**
     * @brief createTimeLine 根据参数创建时间线
     * @param param 动画参数
     * @return 时间线图像
     */
    QImage createTimeLine(const AnimationParam &param);
    /**
     * @brief statistics 统计总时长等信息
     * @param param 动画参数
     */
    void statistics(const AnimationParam &param);
};

#endif // ANIMATELISTVIEW_H
