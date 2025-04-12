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

#include "rectpropertyform.h"
#include "textitem.h"

#include <QTextList>
#include <QAbstractTextDocumentLayout>

QString TextItem::SHAPE_ID = "TEXT_2024";

TextItem::TextItem(QGraphicsItem *parent)
    : AbstractTextItem(parent)
{
    // textItem->installEventFilter(this);
}

TextItem::TextItem(const QString &xml, QGraphicsItem *parent)
    : TextItem(parent)
{
    parseXML(xml);
}

TextItem::~TextItem()
{
}

QString TextItem::classId() const
{
    return SHAPE_ID;
}

QVariant TextItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged) {
        if (!isSelected()) {
            // 取消可编辑状态
            textItem->setTextInteractionFlags(Qt::NoTextInteraction);
        }
    }
    return AbstractTextItem::itemChange(change, value);
}

void TextItem::cursorSelectChanged()
{
    auto cursor = textItem->textCursor();
    auto form = dynamic_cast<RectPropertyForm*>(propertyForm);
    // 获取文字格式
    auto charFormat = cursor.charFormat();
    auto blockFormat = cursor.blockFormat();
    form->setTextFormat(charFormat);
    form->setTextFormat(blockFormat);
    auto list = cursor.currentList();

    QTextListFormat listFormat;
    if (list) {
        listFormat = list->format();
    }
    form->setTextFormat(listFormat);
}

void TextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setFocus(Qt::MouseFocusReason);
    }
    AbstractZoneItem::mouseDoubleClickEvent(event);
}

void TextItem::setTextFormat(const QTextFormat &format)
{
    auto cursor = textItem->textCursor();
    cursor.beginEditBlock();
    if (format.isCharFormat()) {
        cursor.mergeCharFormat(format.toCharFormat());
    }
    if (format.isBlockFormat()) {
        cursor.mergeBlockFormat(format.toBlockFormat());
    }
    if (format.isListFormat()) {
        auto list = cursor.currentList();
        auto listFormat = format.toListFormat();

        if (list){
            if (listFormat.style() == 0){
                list->remove(cursor.block());
                auto blockFormat = cursor.blockFormat();
                blockFormat.setIndent(0);
                cursor.setBlockFormat(blockFormat);
            } else {
                list->setFormat(listFormat);
            }
        }else{
            // 获取选中的block索引区间
            int start=-1,end=-1;
            QTextDocument *doc = cursor.document();
            if (cursor.hasSelection()) {
                start = cursor.selectionStart();
                end = cursor.selectionEnd();
                start = doc->findBlock(start).blockNumber();
                end = doc->findBlock(end).blockNumber();
            }else{
                start = cursor.blockNumber();
                end = start;
            }
            cursor.movePosition(QTextCursor::StartOfBlock);
            // 判断前一个block是否为list, 如果是，且类型相同，加入前一个list，否则新建list
            QTextCursor preCursor(cursor);
            preCursor.movePosition(QTextCursor::PreviousBlock, QTextCursor::MoveAnchor);
            auto preList = preCursor.currentList();
            if (preList) {
                if(preList->format().style() == listFormat.style()){
                    if (start >= 0) {
                        for(int i=start; i<=end; i++){
                            preList->add(doc->findBlockByNumber(i));
                        }
                    }
                    cursor.endEditBlock();
                    return;
                }
            }
            // 新建list
            list = cursor.createList(listFormat);
            if (start >= 0) {
                for(int i=start; i<=end; i++){
                    list->add(doc->findBlockByNumber(i));
                }
            }
        }
    }
    cursor.endEditBlock();
}

bool TextItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == textItem) {
        if (event->type() == QEvent::GraphicsSceneMouseRelease) {
            auto mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
            if (mEvent->button() == Qt::LeftButton) {
                if (textItem->textInteractionFlags() & Qt::TextEditable) {
                    cursorSelectChanged();
                }
            }
        }
        if (event->type() == QEvent::FocusOut) {
            textItem->textCursor().clearSelection();
        }
    }
    return QObject::eventFilter(watched, event);
}

QColor TextItem::textColor() const
{
    QTextCursor cursor = textItem->textCursor();
    cursor.select(QTextCursor::Document);
    auto color = cursor.charFormat().foreground().color();
    cursor.clearSelection();
    return color;
}

void TextItem::setTextColor(const QColor &newTextColor)
{
    QTextCursor cursor = textItem->textCursor();
    cursor.select(QTextCursor::Document);

    auto format = cursor.charFormat();
    format.setForeground(QBrush(newTextColor, Qt::SolidPattern));
    cursor.mergeCharFormat(format);
    cursor.clearSelection();
    updateItem();
}
