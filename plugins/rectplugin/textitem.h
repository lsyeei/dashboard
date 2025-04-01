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

#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "itextobject.h"
#include "abstracttextitem.h"
#include <QGraphicsWidget>
#include <QObject>
#include <abstractzoneitem.h>

class QGraphicsProxyWidget;
class QTextEdit;

class TextItem : public AbstractTextItem, public ITextObject
{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor FINAL)

public:
    static QString SHAPE_ID;
    explicit TextItem(QGraphicsItem *parent = nullptr);
    explicit TextItem(const QString &xml, QGraphicsItem *parent = nullptr);
    ~TextItem();
    QString classId() const override;
    // ITextObject interface
    void setTextFormat(const QTextFormat &format) override;
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;

    QColor textColor() const;
    void setTextColor(const QColor &newTextColor);

protected:
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    // AbstractItem interface
    void cursorSelectChanged();
};

#endif // TEXTITEM_H
