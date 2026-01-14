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
#ifndef ABSTRACTGOOGLECHART_H
#define ABSTRACTGOOGLECHART_H

#include <QObject>
#include "abstractzoneitem.h"
#include "chartproperty.h"
#include <QWebEngineCertificateError>

class QWebEngineView;
class AbstractGoogleChart : public AbstractZoneItem
{
    Q_OBJECT
public:
    explicit AbstractGoogleChart(QGraphicsItem *parent = nullptr);
    explicit AbstractGoogleChart(const QString &xml, QGraphicsItem *parent = nullptr);
    static QString SHAPE_ID;
    // ICustomGraphic interface
    QString classId() const override;
    QList<CustomMetadata> metadataList() override;
    void setCustomData(const QString &name, const QString &value) override;
    QString getCustomData(const QString &name) override;
    using AbstractItem::attribute;
    ChartProperty *attribute() const;
    // AbstractItem interface
    // void updateAttribute(BaseProperty *attr) override;

Q_SIGNALS:
    void WebCreateEvent();
protected:
    // AbstractItem interface
    void attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr) override;
    void attributeSwitched(int oldIndex, int newIndex) override;
    BaseProperty *newProperty() override;
    QVariant attr2Variant(const BaseProperty &attr) override;
    void copyProperty(QVariant from, BaseProperty *to) override;
    void updateGraphic() override;
    // AbstractZoneItem interface
    QPainterPath shapePath() const override;
    // QGraphicsItem interface
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

protected slots:
    void sizeChanged(QRectF offsetValue) override;
    void adjustEnd(AbstractSelector::AdjustType type) override;
    void onNewWeb();
    void onWebPageLoaded(bool flag);
    void onPageError(const QWebEngineCertificateError &error);
private:
    QWebEngineView *web{nullptr};
    QScopedPointer<QGraphicsProxyWidget> widget;
    void loadWeb();
    void refreshChart();
    /**
     * @brief updateWeb 刷新页面
     */
    void updateWeb();
    /**
     * @brief toJsonObject json 字符串转为json对象
     * @param data json 字符串
     * @return json对象
     */
    QJsonObject toJsonObject(const QString &data);
    /**
     * @brief jsonStringify json对象转为字符串
     * @param object json对象
     * @return json字符串
     */
    QString jsonStringify(const QJsonObject &object);

};

#endif // ABSTRACTGOOGLECHART_H
