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

#include <QWidget>
#ifndef ABSTRACTSUBFORM_H
#define ABSTRACTSUBFORM_H

class AbstractSubForm : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractSubForm(QWidget *parent = nullptr):QWidget(parent){};
    ~AbstractSubForm(){};
    /**
     * @brief setData 设置数据
     * @param data 新数据
     */
    virtual void setData(const QVariant &data) = 0;
    /**
     * @brief getData 获取数据
     * @return 当前数据
     */
    virtual QVariant getData() const = 0;
Q_SIGNALS:
    /**
     * @brief dataChangedEvent 数据改变消息
     * @param data 改变后的数据
     */
    void dataChangedEvent(const QVariant &data);
};

#endif // ABSTRACTSUBFORM_H
