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

#include <QString>
#ifndef CHARTOBJECT_H
#define CHARTOBJECT_H


struct ChartObject{
    // 图表类型
    QString type;
    // 图表名称
    QString name;
    // 图表
    QString icon;
    // 默认数据
    QString defaultData;
    // 默认配置
    QString defaultOpton;
    // 参考地址
    QString helpUrl;
};

#endif // CHARTOBJECT_H
