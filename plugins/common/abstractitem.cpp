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

#include "abstractitem.h"
#include "baseproperty.h"
#include "ipropertyform.h"

#include <QXmlStreamWriter>

AbstractItem::AbstractItem(QGraphicsItem *parent)
    : ICustomGraphic(parent)
{
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setCacheMode(QGraphicsItem::NoCache);
    setAcceptDrops(true);
    setTransformOriginPoint(0,0);
}

AbstractItem::~AbstractItem()
{
    for (int i=0; i<attributes.count(); i++) {
        delete attributes[i];
        attributes[i] = nullptr;
    }
    if (oldAttr) {
        delete oldAttr;
        oldAttr = nullptr;
    }
    if (selector) {
        delete selector;
        selector = nullptr;
    }
}

QString AbstractItem::toXml() const
{
    QString data;
    QScopedPointer<QXmlStreamWriter> xml(new QXmlStreamWriter(&data));
    xml->writeStartElement(QString(classId()));
    xml->writeTextElement("index", QString("%1").arg(attrIndex));
    xml->writeStartElement("data");
    QByteArray array;
    QDataStream stream(&array, QIODeviceBase::WriteOnly);
    int count = attributes.count();
    stream << count;
    foreach (auto attr, attributes) {
        stream << *attr;
    }
    stream << transform();
    xml->writeCDATA(array.toHex());

    xml->writeEndElement();
    xml->writeEndElement();
    return data;
}

void AbstractItem::undo(QVariant undoData)
{
    if (undoData.isNull()){
        return;
    }
    parseUndoAction(undoData);
}


void AbstractItem::redo(QVariant redoData)
{
    if (redoData.isNull()){
        return;
    }
    parseUndoAction(redoData, false);
}

template<class T>
T *AbstractItem::attribute() const
{
    return attributes[attrIndex];
}

QMap<int, QString> AbstractItem::getAttributes()
{
    QMap<int, QString> result;
    foreach (auto i, attributes) {
        result[i->getId()] = i->getName();
    }
    return result;
}

int AbstractItem::addAttribute(const QString &name)
{
    auto keys = attributes.keys();
    int id = *std::max_element(keys.begin(), keys.end());
    id ++;
    auto data = QPair<int, QString>{id, name};
    // 通知改变
    undoTrigger("add attribute", {"newAttr", QVariant::fromValue(data), QVariant::fromValue(data)});

    return id;
}

void AbstractItem::updateAttribute(BaseProperty *attr)
{
    // 通知改变
    undoTrigger("update attribute", {"updateAttr", attr2Variant(*attributes[attrIndex]), attr2Variant(*attr)});
}

void AbstractItem::modifyAttribute(int id, QString name)
{
    QString oldName = attributes[id]->getName();
    // 通知改变
    undoTrigger("Attribute name modified", {"setAttrName", QVariant::fromValue(QPair<int, QString>{id, oldName}),
                                        QVariant::fromValue(QPair<int, QString>{id, name})});
}

bool AbstractItem::removeAttribute(int id)
{
    if (!attributes.contains(id)) {
        return false;
    }
    if (attributes.count() == 1) {
        return false;
    }
    // 通知改变
    undoTrigger("remove attribute", {"removeAttr", attr2Variant(*attributes[id]), QVariant::fromValue(id)});
    return true;
}

void AbstractItem::changeAttribute(int id)
{
    // 通知改变
    undoTrigger("change attribute", {"changeIndex", attrIndex, id});
}

void AbstractItem::setPropertyWidget(QWidget *widget)
{
    auto obj = dynamic_cast<IPropertyForm *>(widget);
    if (obj == nullptr) {
        return;
    }
    propertyForm = obj;
    propertyForm->setGraphicItem(this);
}

QMap<QString, QString> AbstractItem::propertyDescription()
{
    return {{"center", tr("RW|位置")},
            {"angle", tr("RW|旋转角度")},
            {"state", tr("RW|状态")},
            {"stateSet", tr("R|状态集")}};
}

QPointF AbstractItem::center() const
{
    return pos();
}

void AbstractItem::setCenter(QPointF newCenter)
{
    setPos(newCenter);
    updateGraphic();
    updateSelector();
    updateForm();
}

qreal AbstractItem::angle() const
{
    return rotation();
}

void AbstractItem::setAngle(qreal newAngle)
{
    setRotation(newAngle);
    updateGraphic();
    updateSelector();
    updateForm();
}

int AbstractItem::state() const
{
    return attrIndex;
}

void AbstractItem::setState(int index)
{
    auto ids = attributes.keys();
    if (!ids.contains(index)) {
        return;
    }
    attrIndex = index;
    attributeSwitched(attrIndex, index);
    updateGraphic();
    updateSelector();
    updateForm();
}

QMap<int, QString> AbstractItem::stateSet()
{
    return getAttributes();
}

QVariant AbstractItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged){
        if(!value.isNull() && value.toBool()){
            selector = createSelector();
        }else{
            delSelector();
        }
        if (propertyForm) {
            propertyForm->setGraphicItem(this);
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

bool AbstractItem::sceneEvent(QEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneMouseMove) {
        // 拖动图元时，更行图元位置信息;
        updateForm();
    }
    if (event->type() == QEvent::Resize) {
        // 缩放或场景移动; 更新控制点位置
        updateSelector();
    }
    return QGraphicsItem::sceneEvent(event);
}

void AbstractItem::adjustStart(AbstractSelector::AdjustType type)
{
    Q_UNUSED(type);
    oldAttr->copy(*attributes[attrIndex]);
}

void AbstractItem::adjustEnd(AbstractSelector::AdjustType type)
{
    Q_UNUSED(type)
    undoTrigger("attribute changed", {"modifyAttr", attr2Variant(*attributes[attrIndex]), attr2Variant(*oldAttr)});
}

void AbstractItem::parseXML(const QString &xml)
{
    QXmlStreamReader obj(xml);
    obj.readNextStartElement();
    // 该条件不适合使用模板类实现的图元，如 GoogleChart
    // auto id = classId();
    // if (!id.isEmpty() && id.compare(obj.name()) != 0){
    //     return;
    // }
    while (!obj.atEnd()) {
        auto type = obj.readNext();
        if (type == QXmlStreamReader::StartElement && obj.name().compare("index") == 0) {
            attrIndex = obj.readElementText().toInt();
        }
        if (type == QXmlStreamReader::Characters && obj.isCDATA()){
            auto data = obj.text();
            QByteArray array =  QByteArray::fromHex(data.toLocal8Bit());
            QDataStream stream(&array, QIODeviceBase::ReadOnly);
            int count;
            stream >> count;
            for(int i=0; i<count; i++){
                auto attr = newProperty();
                stream >> *attr;
                if(attributes[i]) {
                    delete attributes[i];
                }
                attributes[i] = attr;
            }
            QTransform trans;
            stream >> trans;
            setTransform(trans);
        }
    }
}

void AbstractItem::undoTrigger(QString text, std::initializer_list<QVariant> args)
{
    QList<QPair<QString, QVariant>> undoData;
    QList<QPair<QString, QVariant>> redoData;

    for(auto arg = args.begin(); arg != args.end(); ++arg){
        QString field = arg->toString();
        // oldValue(undoData)
        ++arg;
        undoData.append({field, *arg});
        // newValue(redoData)
        ++arg;
        redoData.append({field, *arg});
    }
    // 判断是否能够处理undo事件
    static const QMetaMethod undoSignal = QMetaMethod::fromSignal(&AbstractItem::undoEvent);
    if (isSignalConnected(undoSignal)) {
        emit undoEvent(text, QVariant::fromValue(undoData), QVariant::fromValue(redoData));
    }else{
        parseUndoAction(QVariant::fromValue(redoData), false);
    }
}

void AbstractItem::commonAction(QString action, QVariant data, bool isUndo)
{
    if (action.compare("newAttr") == 0) {
        auto value = data.value<QPair<int, QString>>();
        if (isUndo) {
            delAttr(value.first);
        }else{
            auto attr = newProperty();
            attr->setId(value.first);
            attr->setName(value.second);
            addAttr(attr);
        }
    } else if (action.compare("setAttrName") == 0){
        auto param = data.value<QPair<int, QString>>();
        attributes[param.first]->setName(param.second);
    } else if (action.compare("removeAttr") == 0){
        if (isUndo) {
            auto value = newProperty();
            copyProperty(data, value);
            addAttr(value);
        } else {
            auto value = data.toInt();
            delAttr(value);
        }
    } else if (action.compare("changeIndex") == 0){
        int oldIndex = attrIndex;
        attrIndex = data.toInt();
        attributeSwitched(oldIndex, attrIndex);
    } else if (action.compare("updateAttr") == 0){
        auto oldAttr = newProperty();
        oldAttr->copy(*attributes[attrIndex]);
        copyProperty(data, attributes[attrIndex]);
        attributeChanged(*oldAttr, *attributes[attrIndex]);
    } else {
        customUndoAction(action, data, isUndo);
    }
}

void AbstractItem::parseUndoAction(QVariant undoData, bool isUndo)
{
    auto data = undoData.value<QList<QPair<QString, QVariant>>>();
    foreach(auto command, data){
        commonAction(command.first, command.second, isUndo);
    }
    prepareGeometryChange();
    updateGraphic();
    updateSelector();
    updateForm();
}

void AbstractItem::updateForm()
{
    if (propertyForm && propertyForm->getGraphicItem() == this) {
        propertyForm->updateData();
    }
}


void AbstractItem::delSelector()
{
    if (selector) {
        selector->remove();
        selector = nullptr;
    }
}

void AbstractItem::delAttr(int id)
{
    attributes.remove(id);
    if (attrIndex == id) {
        attrIndex = attributes.firstKey();
    }
}

void AbstractItem::addAttr(BaseProperty *attr)
{
    int id = attr->getId();
    attributes[id] = attr;
    attrIndex = id;
}
