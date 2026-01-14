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

#include "abstractzoneitem.h"
#include "rectselector.h"
#include "zoneproperty.h"
#include <QGraphicsItem>

AbstractZoneItem::AbstractZoneItem(QGraphicsItem *parent, bool init)
    : AbstractItem(parent)
{
    if (!init) return;
    attributes[0] = newProperty();
    attributes[0]->setId(0);
    attributes[0]->setName("default");
    attrIndex = 0;
    oldAttr = newProperty();
}

QRectF AbstractZoneItem::boundingRect() const
{
    qreal border = 0;
    if (attribute()->hasBorder()) {
        border = attribute()->getPen().getWidth();
    }
    qreal offset = border * 0.5;
    return logicRect.adjusted(-offset, -offset, offset, offset);
}

QPainterPath AbstractZoneItem::shape() const
{
    return shapePath();
}

QSizeF AbstractZoneItem::size()
{
    auto attr = attribute();
    return {attr->getWidth(), attr->getHeight()};
}

void AbstractZoneItem::setSize(const QSizeF &size)
{
    auto attr = attribute();
    attr->setWidth(size.width());
    attr->setHeight(size.height());
    syncLogicRect();
}

void AbstractZoneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    auto attr = attribute();
    painter->setPen(attr->getPen().getPen());
    painter->setBrush(attr->getBrush().getBrush(boundingRect().toRect()));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setRenderHint(QPainter::VerticalSubpixelPositioning);
    auto path = shapePath();
    if (attr->getBrush().getStyle() == Qt::TexturePattern){
        painter->setBrushOrigin(path.boundingRect().topLeft());
    }
    painter->drawPath(path);

    painter->restore();
}

QList<CustomMetadata> AbstractZoneItem::metadataList()
{
    auto result = AbstractItem::metadataList();
    result << CustomMetadata{"width", tr("宽度"), DataType::DOUBLE, OperateMode::ReadWrite, "15.5"}
           << CustomMetadata{"height", tr("高度"), DataType::DOUBLE, OperateMode::ReadWrite, "15.5"}
           << CustomMetadata{"size", tr("大小"), DataType::SIZE, OperateMode::ReadWrite, "[15.5,12.2]"}
           << CustomMetadata{"color", tr("背景颜色"), DataType::STRING, OperateMode::ReadWrite, "#00FF00"};
    return result;
}

void AbstractZoneItem::setCustomData(const QString &name, const QString &value)
{
    if (name.isEmpty() || value.isEmpty()) {
        return;
    }
    bool ok{false};
    if (name.compare("width") == 0) {
        auto width = value.trimmed().toDouble(&ok);
        if (ok) {
            setWidth(width);
        }
    }else if (name.compare("height") == 0) {
        auto height = value.trimmed().toDouble(&ok);
        if (ok) {
            setHeight(height);
        }
    }else if (name.compare("size") == 0) {
        auto values = value.split(",");
        if (values.count() < 2) {
            return;
        }
        bool xOk{false}, yOk{false};
        auto xStr = values[0].trimmed().mid(1);
        auto yStr = values[1].trimmed();
        yStr = yStr.left(yStr.length() - 1);
        auto x = xStr.toDouble(&xOk);
        auto y = yStr.toDouble(&yOk);
        if (xOk && yOk){
            setSize({x, y});
        }
    }else if (name.compare("color") == 0) {
        QColor color{value};
        if (!color.isValid()) {
            return;
        }
        setColor(color);
    }else{
        AbstractItem::setCustomData(name, value);
    }
}

QString AbstractZoneItem::getCustomData(const QString &name)
{
    if (name.isEmpty()) {
        return "";
    }
    if (name.compare("width") == 0) {
        return QString("%1").arg(attribute()->getWidth());
    }else if (name.compare("height") == 0) {
        return QString("%1").arg(attribute()->getHeight());
    }else if (name.compare("size") == 0) {
        auto attr = attribute();
        return QString("[%1,%2]").arg(attr->getWidth()).arg(attr->getHeight());
    }else if (name.compare("color") == 0) {
        return attribute()->getBrush().getColor().name();
    }else{
        return AbstractItem::getCustomData(name);
    }
}

ZoneProperty *AbstractZoneItem::attribute() const
{
    auto attr = attributes[attrIndex];
    return dynamic_cast<ZoneProperty*>(attr);
}

// qreal AbstractZoneItem::width() const
// {
//     return attribute()->getWidth();
// }

void AbstractZoneItem::setWidth(qreal newWidth)
{
    auto attr = attribute();
    attr->setWidth(newWidth);
    logicRect = attr->getLogicRect();
    updateItem();
}


// qreal AbstractZoneItem::height() const
// {
//     return attribute()->getHeight();
// }


void AbstractZoneItem::setHeight(qreal newHeight)
{
    auto attr = attribute();
    attr->setHeight(newHeight);
    logicRect = attr->getLogicRect();
    updateItem();
}

// QColor AbstractZoneItem::color() const
// {
//     return attribute()->getBrush().getColor();
// }

void AbstractZoneItem::setColor(const QColor &newColor)
{
    auto attr = attribute();
    auto brush = attr->getBrush();
    brush.setColor(newColor);
    attr->setBrush(brush);
    updateItem();
}

// Qt::BrushStyle AbstractZoneItem::brushStyle() const
// {
//     return attribute()->getBrush().getStyle();
// }

// void AbstractZoneItem::setBrushStyle(Qt::BrushStyle newBrushStyle)
// {
//     auto attr = attribute();
//     auto brush = attr->getBrush();
//     brush.setStyle(newBrushStyle);
//     attr->setBrush(brush);
//     updateItem();
// }

void AbstractZoneItem::sizeChanged(QRectF offsetValue)
{
    // 通知 scene item 大小即将改变
    prepareGeometryChange();
    auto attr = attribute();
    attr->setWidth(attr->getWidth() + offsetValue.right() - offsetValue.left());
    attr->setHeight(attr->getHeight() + offsetValue.bottom() - offsetValue.top());
    // 计算本坐标系下矩形变化
    logicRect.adjust(offsetValue.left(), offsetValue.top(),
                   offsetValue.right(), offsetValue.bottom());
    // 限制现有圆角大小
    auto arcSize = attr->getArcSize();
    qreal maxArc = qMin(logicRect.width() / 2, logicRect.height() / 2);
    if (arcSize > maxArc) {
        attr->setArcSize(maxArc);
        attributes[attrIndex] = attr;
        updateSelector();
    }
    // 计算矩形中心位置偏移
    centerOffset = mapToParent(logicRect.center()) - attr->getPos();
    // 更新属性数据
    updateForm();
}

void AbstractZoneItem::cornerChanged(qreal newValue)
{
    auto attr = attribute();
    if (!attr->getRound()) {
        return;
    }
    attr->setArcSize(newValue);
    update();
    // 更新属性数据
    updateForm();
}

void AbstractZoneItem::rotateChanged(qreal offsetValue)
{
    qreal oldAngle = rotation();
    qreal angle = fmodf(oldAngle + offsetValue, 360);
    auto attr = attribute();
    attr->setRotate(angle);

    this->prepareGeometryChange();
    this->setRotation(angle);
    // 更新属性数据
    this->updateForm();
}

void AbstractZoneItem::adjustStart(AbstractSelector::AdjustType type)
{
    Q_UNUSED(type)
    // 记录调整前矩形属性
    oldAttr->copy(*attributes[attrIndex]);
}

void AbstractZoneItem::adjustEnd(AbstractSelector::AdjustType type)
{
    auto attr = dynamic_cast<ZoneProperty*>(oldAttr);
    switch (type) {
    case RectSelector::SIZE:
        if(centerOffset.x() != 0 || centerOffset.y() != 0){
            // 调整中心点位置
            auto newPos = centerOffset + attribute()->getPos();
            attribute()->setPos(newPos);
            setPos(newPos);
            syncLogicRect();
            updateSelector();
            // 偏移量置空
            centerOffset.setX(0);
            centerOffset.setY(0);
        }
        // 通知可撤销操作
        undoTrigger("size changed", {"size", attr2Variant(*oldAttr), attr2Variant(*attributes[attrIndex])});
        break;
    case RectSelector::ROATATE:
        // 通知可撤销操作
        undoTrigger("rotate changed", {"rotate", attr->getRotate(), rotation()});
        break;
    case RectSelector::CORNER:
        undoTrigger("corner changed", {"arcSize", attr->getArcSize(), attribute()->getArcSize()});
        break;
    default:
        break;
    }
}

void AbstractZoneItem::customUndoAction(QString action, QVariant data, bool isUndo)
{
    Q_UNUSED(isUndo)
    if (action.compare("size") == 0) {
        copyProperty(data, attributes[attrIndex]);
    } else if (action.compare("rotate") == 0) {
        qreal rotation = data.toReal();
        attribute()->setRotate(rotation);
    } else if (action.compare("arcSize") == 0) {
        qreal arc = data.toReal();
        attribute()->setArcSize(arc);
    }
}

AbstractSelector *AbstractZoneItem::createSelector()
{
    auto attr = attribute();
    auto width = attr->getWidth();
    auto height = attr->getHeight();
    auto rounded = attr->getRound();
    auto arcSize = attr->getArcSize();
    this->prepareGeometryChange();
    auto s = new RectSelector({-width/2,-height/2,width,height}, this);
    connect(s, SIGNAL(rectSizeChanged(QRectF)), this, SLOT(sizeChanged(QRectF)));
    s->keepRatio(attr->getAspectRatio());
    s->setRadius(arcSize);
    connect(s, SIGNAL(rectCornerChanged(qreal)), this, SLOT(cornerChanged(qreal)));

    if (rounded){
        s->showCornerAdjuster(true);
    } else {
        s->showCornerAdjuster(false);
    }
    connect(s, SIGNAL(rectRotateChanged(qreal)), this, SLOT(rotateChanged(qreal)));
    connect(s, SIGNAL(adjustStart(AbstractSelector::AdjustType)), this, SLOT(adjustStart(AbstractSelector::AdjustType)));
    connect(s, SIGNAL(adjustEnd(AbstractSelector::AdjustType)), this, SLOT(adjustEnd(AbstractSelector::AdjustType)));
    return s;
}

void AbstractZoneItem::updateSelector()
{
    if(selector == nullptr){
        return;
    }
    auto s = dynamic_cast<RectSelector *>(selector);
    if (s == nullptr) {
        return;
    }

    auto attr = attribute();
    auto rounded = attr->getRound();
    auto arcSize = attr->getArcSize();
    auto border = attr->getPen().getWidth();
    if (!attr->hasBorder()) {
        border = 0;
    }
    s->keepRatio(attr->getAspectRatio());
    s->setRectBorder(border);
    s->setRadius(arcSize);
    s->showCornerAdjuster(rounded);
    border /= 2;
    s->updateRect(boundingRect().marginsAdded({-border, -border, -border, -border}));
}

void AbstractZoneItem::updateGraphic()
{
    auto attr = attribute();
    setPos(attr->getPos());
    logicRect = attr->getLogicRect();
    setRotation(attr->getRotate());
    update();
}

BaseProperty *AbstractZoneItem::newProperty()
{
    auto attr = new ZoneProperty();
    if (attrIndex >= 0 && attributes[attrIndex] != nullptr) {
        attr->copy(*attributes[attrIndex]);
        attr->setId(-1);
        attr->setName("");
    }
    return attr;
}

QVariant AbstractZoneItem::attr2Variant(const BaseProperty &attr)
{
    auto data = dynamic_cast<const ZoneProperty *>(&attr);
    if (data == nullptr) {
        return QVariant::fromValue(attr);
    }
    return QVariant::fromValue(*data);
}

void AbstractZoneItem::copyProperty(QVariant from, BaseProperty *to)
{
    if (!from.canConvert<ZoneProperty>()) {
        return;
    }
    auto f =from.value<ZoneProperty>();
    auto t = dynamic_cast<ZoneProperty*>(to);
    if (t == nullptr) {
        return;
    }
    t->copy(f);
}

void AbstractZoneItem::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    Q_UNUSED(oldAttr)
    attribute()->copy(newAttr);
    logicRect = attribute()->getLogicRect();
    setPos(attribute()->getPos());
    updateSelector();
}

void AbstractZoneItem::attributeSwitched(int oldIndex, int newIndex)
{
    Q_UNUSED(oldIndex)
    Q_UNUSED(newIndex)
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    setPos(attr->getPos());
}

void AbstractZoneItem::parseXML(const QString &xml)
{
    AbstractItem::parseXML(xml);
    auto attr = attribute();
    setPos(attr->getPos());
    setRotation(attr->getRotate());
    syncLogicRect();
}

QVariant AbstractZoneItem:: itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionHasChanged) {
        attribute()->setPos(pos());
    } else if(change == ItemRotationHasChanged){
        auto attr = dynamic_cast<ZoneProperty*>(attributes[attrIndex]);
        attr->setRotate(rotation());
    } else if (change ==QGraphicsItem::ItemTransformHasChanged){
        updateSelector();
    }
    return AbstractItem::itemChange(change, value);
}

void AbstractZoneItem::updateItem()
{
    updateGraphic();
    updateSelector();
    updateForm();
}

void AbstractZoneItem::syncLogicRect()
{
    auto attr = attribute();
    logicRect = attr->getLogicRect();
    updateSelector();
}
