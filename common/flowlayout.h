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

#ifndef FLOWLAYOUT_H
#define FLOWLAYOUT_H

#include <QtWidgets/QLayout>
#include <QtWidgets/QStyle>

class FlowLayout : public QLayout
{
public:
    explicit FlowLayout(QWidget *parent = nullptr);
    ~FlowLayout() override;

    void addItem(QLayoutItem *item) override;
    Qt::Orientations expandingDirections() const override;
    bool hasHeightForWidth() const override;
    int heightForWidth(int) const override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;
    QSize sizeHint() const override;
    QLayoutItem *takeAt(int index) override;
    int horizontalSpacing() const;
    int verticalSpacing() const;

    // 重新调整水平/垂直方向的间距
    void setHorizontalSpacing(int hSpacing);
    void setVerticalSpacing(int vSpacing);
    // 立即刷新布局（重新设置水平/垂直方向的间距后，如果布局没有变化，可调用此接口显式刷新布局）
    void refreshLayout();

private:
    int doLayout(const QRect &rect, bool testOnly) const;
    int smartSpacing(QStyle::PixelMetric pm) const;

    QList<QLayoutItem *> itemList;
    int m_hSpace{-1};
    int m_vSpace{-1};
};

#endif // FLOWLAYOUT_H
