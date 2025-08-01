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
 * 当存在 QObject 多路继承时，定义 EXIST_QOBJECT 避免 AbstractItem 继承 QObject
 */
#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include "icustomgraphic.h"
#include "abstractselector.h"
#include "baseproperty.h"
#include "undoobject.h"
#include <QObject>

class IPropertyForm;
class AbstractItem : public QObject, public ICustomGraphic, public UndoObject
{
    Q_OBJECT
    // Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(QPointF center READ center WRITE setCenter STORED false FINAL)
    Q_PROPERTY(qreal angle READ angle WRITE setAngle STORED false FINAL)
    Q_PROPERTY(int state READ state WRITE setState STORED false FINAL)
    Q_PROPERTY(QMap<int, QString> stateSet READ stateSet STORED false)
public:
    AbstractItem(QGraphicsItem *parent = nullptr);
    ~AbstractItem();
    /**
     * @brief 将图形转换为XML
     * @return xml字符串
     */
    QString toXml() const override;
    void undo(QVariant undoData) override;
    void redo(QVariant redoData) override;
    /**
     * @brief 获取当前属性
     * @return 当前属性
     */
    template<class T>
    T *attribute() const;
    /**
     * 获取图元属性集合，key 状态索引， value 状态名称
     */
    QMap<int, QString> getAttributes();
    /**
     * @brief 新建一个属性
     * @param name 属性名
     * @return  属性ID
     */
    int addAttribute(const QString &name);
    /**
     * @brief 更新当前属性
     * @param attr 属性对象
     */
    void updateAttribute(BaseProperty *attr);
    /**
     * @brief 修改属性名称
     * @param id 属性ID
     * @param name 属性名称
     */
    void modifyAttribute(int id, QString name);
    /**
     * @brief 删除属性
     * @param id 属性id
     */
    bool removeAttribute(int id);
    /**
     * @brief 切换属性
     * @param id 属性id
     */
    void changeAttribute(int id);
    void setPropertyWidget(QWidget *widget) Q_DECL_OVERRIDE;

    QMap<QString, QString> propertyDescription() Q_DECL_OVERRIDE;


    QPointF center() const;
    void setCenter(QPointF newCenter);

    qreal angle() const;
    void setAngle(qreal newAngle);

    int state() const;
    void setState(int index);
    QMap<int, QString> stateSet();

Q_SIGNALS:
    void stateChanged();
    void undoEvent(const QString &text, QVariant undoData, QVariant redoData) override;

protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    bool sceneEvent(QEvent *event) override;
    virtual void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) = 0;
    virtual void attributeSwitched(int oldIndex, int newIndex) = 0;

protected Q_SLOTS:
    void adjustStart(AbstractSelector::AdjustType type);
    void adjustEnd(AbstractSelector::AdjustType type);

protected:
    // 属性集合，key 属性ID， value 属性集
    QMap<int, BaseProperty*> attributes;
    // 当前属性索引
    qint32 attrIndex{-1};
    // 记录属性变动前的值
    BaseProperty *oldAttr;
    // 控制框
    AbstractSelector *selector{nullptr};
    // 属性设置窗口
    IPropertyForm *propertyForm{nullptr};

    /**
     * @brief 从XML中解析图形参数
     * @param xml xml字符串
     */
    virtual void parseXML(const QString &xml);
    /**
     * @brief 触发可撤销操作，一次可设置多个属性名和对应的属性值
     * @param text 操作名称
     * @param args field属性名, undoData(oldValue原属性值), redoData(newValue新属性值) 序列
     */
    void undoTrigger(QString text, std::initializer_list<QVariant> args);
    /**
     * @brief 普通的撤销命令
     * @param action 命令动作名词
     * @param data 数据
     * @param isUndo true 执行撤销，false 执行redo
     */
    void commonAction(QString action, QVariant data, bool isUndo = true);
    /**
     * @brief 自定义撤销命令
     * @param action 命令名称
     * @param data 数据
     * @param isUndo true 执行撤销，false 执行redo
     */
    virtual void customUndoAction(QString action, QVariant data, bool isUndo = true) = 0;
    /**
     * @brief 解析撤销命令
     * @param undoData 撤销命令数据
     * @param isUndo true 执行撤销，false 执行redo
     */
    void parseUndoAction(QVariant undoData, bool isUndo = true);
    /**
     * @brief 更新widget数据
     */
    virtual void updateForm();

    /**
     * @brief 创建选择框
     */
    virtual AbstractSelector *createSelector() = 0;
    /**
     * @brief 创建属性对象
     * @return  属性对象
     */
    virtual BaseProperty *newProperty() = 0;
    /**
     * @brief 将属性转换为 QVariant 对象
     * @param attr 属性对象
     * @return  QVariant 对象
     */
    virtual QVariant attr2Variant(const BaseProperty &attr) = 0;
    /**
     * @brief 从Qvariant对象中拷贝数据
     * @param from Qvariant对象
     * @param to 赋值对象
     */
    virtual void copyProperty(QVariant from, BaseProperty *to) = 0;
    /**
     * @brief 删除选择框
     */
    virtual void delSelector();
    /**
     * @brief 刷新选择框
     */
    virtual void updateSelector() = 0;
    /**
     * @brief 刷新图像
     */
    virtual void updateGraphic() = 0;
    /**
     * @brief 删除指定属性
     * @param id 属性ID
     */
    void delAttr(int id);
    /**
     * @brief 添加属性
     * @param att 属性对象r
     */
    void addAttr(BaseProperty *attr);
};

#endif // ABSTRACTITEM_H
