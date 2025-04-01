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

#ifndef SVGHELPERPRIVATE_H
#define SVGHELPERPRIVATE_H
#include <QDomDocument>
#include <QScopedPointer>

class SvgHelper;
class SvgHelperPrivate
{
    Q_DECLARE_PUBLIC(SvgHelper)
public:
    SvgHelperPrivate(SvgHelper *parent);
    ~SvgHelperPrivate();
private:
    /**
     * @brief 获取Dom属性
     * @param nodeName dom节点名称
     * @param property 属性名称
     * @return 属性值
     */
    QString getProperty(const QString &nodeName, const QString property) const;
    /**
     * @brief 设置SVG图片属性
     * @param property key属性名称 value 属性值
     */
    void setProperty(const QMap<QString, QString> property);
    /**
     * @brief 设置Dom 节点属性
     * @param dom dom节点
     * @param property 属性名称
     * @param value 属性值
     * @param deep 递归循环深度， 负数表示完全递归， 1表示该函数只执行1次
     */
    void setNodeProperty(const QDomNode &dom, const QString property, const QString value, qint16 deep);

    SvgHelper *q_ptr;
    // SVG 图片内容
    QDomDocument svgDoc;
};

#endif // SVGHELPERPRIVATE_H
