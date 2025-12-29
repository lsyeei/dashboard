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
#ifndef WEBITEM_H
#define WEBITEM_H

#include <QGraphicsProxyWidget>
#include <QPointer>
#include <QScopedPointer>
#include "abstractzoneitem.h"
#include "webproperty.h"

class QWebEngineView;
class WebItem : public AbstractZoneItem
{
    Q_OBJECT

public:
    static QString SHAPE_ID;
    explicit WebItem(QGraphicsItem *parent = nullptr);
    explicit WebItem(const QString &xml, QGraphicsItem *parent = nullptr);
    ~WebItem();
    QString classId() const override;
    // QObject interface
    bool eventFilter(QObject *watched, QEvent *event) override;
    // AbstractItem interface
    void updateAttribute(BaseProperty *attr) override;
Q_SIGNALS:
    void WebCreateEvent();
    // AbstractZoneItem interface
protected:
    QPainterPath shapePath() const override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void attributeSwitched(int oldIndex, int newIndex) override;
    // AbstractZoneItem interface
protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
    void onNewWeb();
private:
    QWebEngineView *web{nullptr};
    QScopedPointer<QGraphicsProxyWidget> widget;
    /**
     * @brief loadWeb 加载页面
     * @param type 页面类型
     * @param content 页面内容
     */
    void loadWeb(PageType type, const QString &content);
    /**
     * @brief setDragMode 设置编辑模式
     * @param flag true 拖动模式，false 编辑模式
     */
    void setDragMode(bool flag);
    /**
     * @brief updateWeb 刷新页面
     */
    void updateWeb();
};


#endif // WEBITEM_H
