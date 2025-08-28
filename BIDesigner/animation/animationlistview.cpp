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

#include "animationlistview.h"

#include <QPaintEvent>
#include <QPainter>

AnimationListView::AnimationListView(QWidget *parent)
    : QWidget{parent}
{setFocusPolicy(Qt::ClickFocus);}

void AnimationListView::clear()
{
    animations.clear();
    update();
}

bool AnimationListView::addItem(const AnimationItem &item)
{
    animations << item;
    if (!checkItem(animations.count() - 1)){
        animations.removeLast();
        return false;
    }
    int old = currentIndex;
    currentIndex = animations.count() - 1;
    emit itemSelectionChanged(old, currentIndex);
    statistics(item.params);

    update();
    return true;
}

void AnimationListView::removeItem(int index)
{
    if (index < 0 || index >= animations.count()) {
        return;
    }
    animations.removeAt(index);
    if (currentIndex == index) {
        int old = currentIndex;
        if (currentIndex > animations.count() - 1) {
            currentIndex --;
        }
        emit itemSelectionChanged(old, currentIndex);
    }
    if (currentIndex > index) {
        currentIndex --;
        emit itemSelectionChanged(currentIndex, currentIndex);
    }
    update();
}

void AnimationListView::setCurrentItemIndex(int index)
{
    if (index < animations.count()) {
        int old = currentIndex;
        currentIndex = index;
        emit itemSelectionChanged(old, currentIndex);
    }
}

int AnimationListView::currentItemIndex()
{
    return currentIndex;
}

AnimationItem AnimationListView::getItem(int index)
{
    if (index < 0 || index >= animations.count()) {
        return AnimationItem();
    }
    return animations[index];
}

bool AnimationListView::setAnimationParam(int index, const AnimationParam &params)
{
    if (index < 0 || index >= animations.count()) {
        return false;
    }
    auto oldValue =animations[index].params;
    animations[index].params = params;
    if (!checkItem(index)) {
        animations[index].params = oldValue;
        return false;
    }
    statistics(params);
    update();
    return true;
}

int AnimationListView::itemCount()
{
    return animations.count();
}

QList<AnimationParam> AnimationListView::getAllAnimationParams()
{
    QList<AnimationParam> result;
    foreach (auto item, animations) {
        result << item.params;
    }
    return result;
}

void AnimationListView::mousePressEvent(QMouseEvent *event)
{
    auto y = event->position().y();
    int index = qFloor(y / (m_rowHeight + m_rowSpace));
    if (index != currentIndex && index < animations.count()) {
        int old = currentIndex;
        currentIndex = index;
        emit itemSelectionChanged(old, currentIndex);
        update();
    }
    QWidget::mousePressEvent(event);
}

void AnimationListView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up) {
        if (currentIndex > 0) {
            int old = currentIndex;
            currentIndex --;
            emit itemSelectionChanged(old, currentIndex);
            update();
        }
    }
    if (event->key() == Qt::Key_Down) {
        if (currentIndex < animations.count() - 1) {
            int old = currentIndex;
            currentIndex ++;
            emit itemSelectionChanged(old, currentIndex);
            update();
        }
    }
    QWidget::keyPressEvent(event);
}

void AnimationListView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto rect = event->rect();
    int width = rect.width();
    int lineX = m_iconSize+m_textWidth+m_colSpace*3;
    if (animations.count() > 0) {
        // 绘制一条时间起点参考线
        painter.save();
        painter.setPen(QPen(Qt::lightGray, 0.5, Qt::DashLine));
        painter.drawLine(lineX,0,lineX,rect.height());
        painter.restore();
    }
    for (int i = 0; i < animations.count(); ++i) {
        auto item = animations[i];
        int x = 0;
        int y = i*(m_rowHeight + m_rowSpace);
        if (i == currentIndex) {
            // 绘制选中背景
            painter.save();
            QBrush brush(QColor(0xB83B1D));
            painter.setBrush(brush);
            painter.setPen(QPen(Qt::NoPen));
            painter.drawRect(0, y, width, m_rowHeight);
            painter.restore();
        }
        // 绘制图标
        x += m_colSpace;
        painter.drawImage(QRect{x, y + (m_rowHeight - m_iconSize)/2,
                                m_iconSize, m_iconSize},
                          item.icon.pixmap(m_iconSize, m_iconSize).toImage());
        // 绘制文字
        QTextOption option;
        option.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        x += m_iconSize + m_colSpace;
        painter.drawText(QRect{x, y, m_textWidth, m_rowHeight},
                         item.name, option);
        // 绘制时间线
        auto img = createTimeLine(item.params);
        x += m_textWidth + m_colSpace;
        painter.drawImage(QRect{x, y + (m_rowHeight - img.height())/2,
                                img.width(), img.height()}, img);
    }
    painter.end();
}

bool AnimationListView::checkItem(int index)
{
    auto param = animations[index].params;
    auto start = param.getDelay();
    auto end = start + param.getDuration() * param.getLoopCount();
    for (int i = 0; i < animations.count(); ++i) {
        auto item = animations[i];
        if (i == index) {
            continue;
        }
        auto animate = item.params;
        if (animate.getTypeId().compare(param.getTypeId()) == 0) {
            // 发现同类动画
            if (param.getLoopCount() == -1 || animate.getLoopCount() == -1){
                QMessageBox::information(this, tr("提示"),
                                         tr("同类动画已经存在且为循环播放，同一时间内同类动画只能有一个。"));
                return false;
            }
            auto s = animate.getDelay();
            auto e = s + animate.getDuration() * animate.getLoopCount();
            if ((s >= start && s < end) || (e > start && e <= end)) {
                QMessageBox::information(this, tr("提示"),
                                         tr("同类动画已经存在, 播放时间重叠，同一时间内同类动画只能有一个。"));
                return false;
            }
        }
    }
    return true;
}

QImage AnimationListView::createTimeLine(const AnimationParam &param)
{
    auto maxWidth = this->rect().width() - m_iconSize - m_textWidth - m_colSpace*4;
    int width = 0,height = 8;
    auto maxTime = totalTime;
    if (infiniteCount > 0) {
        // 有无限循环播放时，总时长加5
        maxTime += 5;
    }
    if (param.getLoopCount() < 0) {
        width = maxWidth;
    }else{
        width = (param.getDelay() + param.getDuration()*param.getLoopCount()) * maxWidth / maxTime;
    }
    int blankWidth = param.getDelay() * maxWidth / maxTime;
    QPixmap image(width, height);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    QBrush brush(QColor(0xA3C7D8));
    QPen pen(Qt::NoPen);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(QRect{blankWidth, 0, width - blankWidth, height});
    painter.end();
    return image.toImage();
}

void AnimationListView::statistics(const AnimationParam &param)
{
    if (param.getLoopCount() == -1){
        infiniteCount ++;
    } else {
        auto time = param.getDelay() + param.getDuration() * param.getLoopCount();
        if (time > totalTime) {
            totalTime = time;
        }
    }
}

int AnimationListView::rowHeight() const
{
    return m_rowHeight;
}

void AnimationListView::setRowHeight(int newRowHeight)
{
    m_rowHeight = newRowHeight;
}

int AnimationListView::iconSize() const
{
    return m_iconSize;
}

void AnimationListView::setIconSize(int newIconSize)
{
    m_iconSize = newIconSize;
}

int AnimationListView::textWidth() const
{
    return m_textWidth;
}

void AnimationListView::setTextWidth(int newTextWidth)
{
    m_textWidth = newTextWidth;
}
