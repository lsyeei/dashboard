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

/**
 * 实现类通过定义宏 BASE_FOR_GROUP 明确父类。
 * BASE_FOR_GROUP 指定父类为 QGraphicsItemGroup
 * 未定义宏，默认父类为 QGraphicsItem
 */
#ifndef ICUSTOMGRAPHIC_H
#define ICUSTOMGRAPHIC_H

#ifdef BASE_FOR_GROUP
#include <QGraphicsItemGroup>
#else
#include <QGraphicsItem>
#endif

class QXmlStreamWriter;

class ICustomGraphic :
#ifdef BASE_FOR_GROUP
    virtual public QGraphicsItemGroup
#else
    virtual public QGraphicsItem
#endif
{
public:

#ifdef BASE_FOR_GROUP
    ICustomGraphic(QGraphicsItem *parent = nullptr):QGraphicsItemGroup(parent){}
#else
    ICustomGraphic(QGraphicsItem *parent = nullptr):QGraphicsItem(parent){}
#endif
    virtual ~ICustomGraphic() = default;
    /**
     * @brief id 获取子类标识
     * @return 子类标识
     */
    virtual QString classId() const = 0;
    /**
     * @brief 设置大小
     * @param size 大小
     */
    virtual void setSize(const QSizeF &size) = 0;
    /**
     * @brief 设置插件的属性窗口
     * @param widget 属性窗口
     */
    virtual void setPropertyWidget(QWidget *widget) = 0;
    /**
     * @brief 自绘制控件转为XML
     * @return XML 格式字符串
     */
    virtual QString toXml() const = 0;
    /**
     * @brief propertyDescription 获取插件的公开属性信息
     * @return 属性信息集合，key 属性名，value 属性描述，
     * 可以通过QObject的property()方法获取属性值，setProperty()方法设置属性值
     * value 格式：以 | 作为分隔符，至少包括2个字段，字段顺序如下，
     *           第一个字段表示属性的可读（R）和可写（W）特性，
     *           第二个字段为属性的简称
     *           第三个字段为属性的详细描述
     *   例如：属性width，value可表示为：RW|宽度|图像的最大宽度；
     *        属性center，value可表示为：R|中心位置|图形的中心在scene中的坐标位置
     */
    virtual QMap<QString, QString> propertyDescription() = 0;

};
// #define ICustomGraphic_iid "cn.devhome.BIDesigner.ICustomGraphic"
// Q_DECLARE_INTERFACE(ICustomGraphic, ICustomGraphic_iid)

#endif // ICUSTOMGRAPHIC_H
