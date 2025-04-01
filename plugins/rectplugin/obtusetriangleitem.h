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

#ifndef OBTUSETRIANGLEITEM_H
#define OBTUSETRIANGLEITEM_H

#include <QObject>
#include <abstractzoneitem.h>

class ObtuseTriangleItem : public AbstractZoneItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit ObtuseTriangleItem(QGraphicsItem *parent = nullptr);
    explicit ObtuseTriangleItem(const QString &xml,
                                QGraphicsItem *parent = nullptr);
    QString classId() const override;

protected:
    QPainterPath shapePath() const override;
    ;

    // AbstractItem interface
    AbstractSelector *createSelector() override;
    void delSelector() override;

    // AbstractZoneItem interface
protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
    void onTiltMove(const QPointF &from, const QPointF &to);
private:
    /**
     * @brief updateTiltAdjuster 更新调整点
     */
    void updateTiltAdjuster();
    // 倾斜度调整
    AdjustPoint *tiltAdjuster{nullptr};
};

#endif // OBTUSETRIANGLEITEM_H
