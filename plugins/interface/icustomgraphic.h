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

#include <QString>
enum class OperateMode{ReadOnly, ReadWrite, WriteOnly};
enum class DataType{BOOL, INT, DOUBLE, STRING, POINT, SIZE, JSON};
struct CustomMetadata{
    // 属性名
    QString name;
    // 属性别名，可读的名称
    QString alias;
    // 数据类型
    DataType dataType;
    // 操作模式
    OperateMode mode;
    // 数据示例
    QString dataExample;
    QString dataTypeName(){
        switch (dataType) {
        case DataType::BOOL:
            return "布尔"; break;
        case DataType::INT:
            return "整形"; break;
        case DataType::DOUBLE:
            return "小数"; break;
        case DataType::STRING:
            return "字符串"; break;
        case DataType::POINT:
            return "坐标"; break;
        case DataType::SIZE:
            return "大小"; break;
        case DataType::JSON:
            return "json 字符串"; break;
        default:
            return "未知";break;
        }
    }
};

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
     * @brief metadataList 获取插件的元数据信息
     * @return 元数据信息列表
     */
    virtual QList<CustomMetadata> metadataList() = 0;
    /**
     * @brief setCustomData 给数据赋值
     * @param name 数据名称
     * @param value 值
     */
    virtual void setCustomData(const QString &name, const QString &value) = 0;
    /**
     * @brief getCustomData 获取指定数据的值
     * @param name 数据名称
     * @return 数据的值
     */
    virtual QString getCustomData(const QString &name) = 0;

};
// #define ICustomGraphic_iid "cn.devhome.BIDesigner.ICustomGraphic"
// Q_DECLARE_INTERFACE(ICustomGraphic, ICustomGraphic_iid)

#endif // ICUSTOMGRAPHIC_H
