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

#include "abstracttextitem.h"
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include "zoneproperty.h"

AbstractTextItem::AbstractTextItem(QGraphicsItem *parent)
    : AbstractZoneItem(parent)
{
    textItem = new QGraphicsTextItem(this);
    textItem->setPlainText(tr("Text"));
    QFont font;
    font.setFamily("Arial");
    font.setPointSize(16);
    font.setBold(true);
    textItem->setFont(font);
    textItem->setDefaultTextColor(Qt::lightGray);
    textItem->setObjectName("textObject");
    // 计算边框大小
    textItem->setTextWidth(100);
    setSize(textItem->boundingRect().size());
    // 监控文本框大小改变信号
    auto doc = textItem->document();
    doc->setIndentWidth(12);
    auto docLayout = doc->documentLayout();
    connect(docLayout, SIGNAL(documentSizeChanged(QSizeF)), this, SLOT(docSizeChanged(QSizeF)));
    // 设置边框不可见
    auto attr = attribute();
    auto pen = attr->getPen();
    pen.setStyle(Qt::NoPen);
    attr->setPen(pen);
    attr->setData("Text");
}

AbstractTextItem::AbstractTextItem(const QString &xml, QGraphicsItem *parent)
    :AbstractTextItem(parent)
{
    parseXML(xml);
}

AbstractTextItem::~AbstractTextItem()
{
    if (textItem) {
        textItem->disconnect();
        textItem->deleteLater();
        delete textItem;
    }
}

QString AbstractTextItem::toXml() const
{
    auto data = textItem->toHtml();
    attribute()->setData(data);
    return AbstractZoneItem::toXml();
}

void AbstractTextItem::setSize(const QSizeF &size)
{
    auto attr = attribute();
    auto ratioX = size.width() / attr->getWidth();
    auto ratioY = size.height() / attr->getHeight();
    AbstractZoneItem::setSize(size);
    if (ratioX <= 0 || ratioY <= 0 || std::isnan(ratioX) || std::isnan(ratioY)) {
        return;
    }
    textItem->setPos(logicRect.topLeft());
    auto trans = textItem->transform();
    trans.scale(ratioX, ratioY);
    textItem->setTransform(trans);
}

void AbstractTextItem::setWidth(qreal newWidth)
{
    auto attr = attribute();
    auto ratioX = newWidth / attr->getWidth();
    AbstractZoneItem::setWidth(newWidth);
    if (ratioX <= 0 || std::isnan(ratioX)) {
        return;
    }
    textItem->setPos(logicRect.topLeft());
    auto trans = textItem->transform();
    trans.scale(ratioX, 1);
    textItem->setTransform(trans);
}

void AbstractTextItem::setHeight(qreal newHeight)
{
    auto attr = attribute();
    auto ratioY = newHeight / attr->getHeight();
    AbstractZoneItem::setHeight(newHeight);
    if (ratioY <= 0 || std::isnan(ratioY)) {
        return;
    }
    textItem->setPos(logicRect.topLeft());
    auto trans = textItem->transform();
    trans.scale(1, ratioY);
    textItem->setTransform(trans);
}

// void AbstractTextItem::setColor(const QColor &newColor)
// {
//     textItem->setDefaultTextColor(newColor);
//     updateItem();
// }

QPainterPath AbstractTextItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = 0;
    if (attr->getRound()) {
        arcSize = attr->getArcSize();
    }

    path.addRoundedRect(logicRect, arcSize, arcSize);
    return path;
}

QVariant AbstractTextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (textItem && change == QGraphicsItem::ItemPositionHasChanged) {
        textItem->setPos(logicRect.topLeft());
    }
    return AbstractZoneItem::itemChange(change, value);
}

AbstractSelector *AbstractTextItem::createSelector()
{
    auto s = AbstractZoneItem::createSelector();
    s->stackBefore(textItem);
    return s;
}

void AbstractTextItem::parseXML(const QString &xml)
{
    AbstractZoneItem::parseXML(xml);
    auto data = attribute()->getData();
    auto width = attribute()->getWidth();
    if (data.isValid()) {
        textItem->setHtml(data.toString());
        textItem->setTextWidth(width);
    }
}

void AbstractTextItem::sizeChanged(QRectF offsetValue)
{
    adjustFlag = true;
    // 调整文本块的宽度
    textItem->setTextWidth(logicRect.width()+offsetValue.right() - offsetValue.left());
    // 获取文本块宽度调整后的大小
    auto textRect = textItem->boundingRect();
    auto dy = logicRect.height() - textRect.height();
    if (qAbs(offsetValue.top()) > 0) {
        offsetValue.setTop(dy);
    }else{
        offsetValue.setBottom(-dy);
    }
    AbstractZoneItem::sizeChanged(offsetValue);
    textItem->setPos(logicRect.topLeft());
    if (qAbs(dy) > 0) {
        updateSelector();
    }
    adjustFlag = false;
}

void AbstractTextItem::adjustStart(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustStart(type);
    // 开始调整时取消文本缩放
    auto trans = textItem->transform();
    trans.reset();
    textItem->setTransform(trans);
}

void AbstractTextItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    if (type == AbstractSelector::SIZE) {
        textItem->setPos(logicRect.topLeft());
    }
}

void AbstractTextItem::docSizeChanged(QSizeF size)
{
    if (adjustFlag ||
        (size.height() == logicRect.height() &&
         size.width() == logicRect.width())) {
        return;
    }
    QRectF offset{0,0,0,0};
    offset.setBottom(size.height() - logicRect.height());
    offset.setRight(size.width() - logicRect.width());
    sizeChanged(offset);
    adjustEnd(AbstractSelector::SIZE);
}
