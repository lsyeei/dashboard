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
#pragma once
#ifndef ABSTRACTTEXTITEM_H
#define ABSTRACTTEXTITEM_H

#include <QObject>
#include "abstractzoneitem.h"

class AbstractTextItem : public AbstractZoneItem
{
    Q_OBJECT
public:
    explicit AbstractTextItem(QGraphicsItem *parent = nullptr);
    explicit AbstractTextItem(const QString &xml, QGraphicsItem *parent = nullptr);
    ~AbstractTextItem();
    // ICustomGraphic interface
    QString toXml() const override;

    void setSize(const QSizeF &size) override;
    void setWidth(qreal newWidth) override;
    void setHeight(qreal newHeight) override;
    // void setColor(const QColor &newColor) override;

protected:
    QPainterPath shapePath() const override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    // AbstractItem interface
    AbstractSelector *createSelector() override;
    void parseXML(const QString &xml) override;

    // AbstractZoneItem interface
protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustStart(AbstractSelector::AdjustType type) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
    void docSizeChanged(QSizeF size);
protected:
    QGraphicsTextItem *textItem{nullptr};
    // 手动调整大小标记
    bool adjustFlag{false};
};

#endif // ABSTRACTTEXTITEM_H
