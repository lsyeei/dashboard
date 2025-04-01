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

#ifndef VARIANTUTIL_H
#define VARIANTUTIL_H

#include "qcolor.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QLine>
#include <QPoint>
#include <QRect>
#include <QSize>
#include <QVariant>


class VariantUtil{
public:
    /**
     * @brief 将QVariant对象转为json值对象
     * @param var QVariant对象
     * @return json值对象
     */
    static QJsonValue toJsonValue(const QVariant &var);
    /**
     * @brief 将json对象解析为指定的数据类型
     * @param val json对象
     * @param type 数据类型
     * @return type类型的QVariant对象
     */
    static QVariant fromJsonValue(const QJsonValue &val, QMetaType type);
    /**
     * @brief 将QVariant转为字符串，并去掉类型信息
     * @param var QVariant 对象
     * @return 不含类型信息的字符串
     */
    static QString toString(const QVariant &var);
};

inline QJsonValue VariantUtil::toJsonValue(const QVariant &var)
{
    auto type = var.metaType();
    switch (type.id()) {
    case QMetaType::QPoint:
        return QJsonArray{var.toPoint().x(), var.toPoint().y()};
        break;
    case QMetaType::QPointF:
        return QJsonArray{var.toPointF().x(), var.toPointF().y()};
        break;
    case QMetaType::QSize:
        return QJsonArray{var.toSize().width(), var.toSize().height()};
        break;
    case QMetaType::QSizeF:
        return QJsonArray{var.toSizeF().width(), var.toSizeF().height()};
        break;
    case QMetaType::QRect:
        return QJsonArray{var.toRect().x(), var.toRect().y(),
                        var.toRect().width(), var.toRect().height()};
        break;
    case QMetaType::QRectF:
        return QJsonArray{var.toRectF().x(), var.toRectF().y(),
                        var.toRectF().width(), var.toRectF().height()};
        break;
    case QMetaType::QLine:
        return [=]{
            QLine line(var.value<QLine>());
            QPoint p1 = line.p1();
            QPoint p2 = line.p2();
            return QJsonArray{QJsonArray{p1.x(), p1.y()}, QJsonArray{p2.x(), p2.y()}};
        }();
        break;
    case QMetaType::QLineF:
        return [=]{
            QLineF line(var.value<QLineF>());
            QPointF p1 = line.p1();
            QPointF p2 = line.p2();
            return QJsonArray{QJsonArray{p1.x(), p1.y()}, QJsonArray{p2.x(), p2.y()}};
        }();
        break;
    case QMetaType::QColor:
        return QColor(var.value<QColor>()).name();
        break;
    default:
        if (type.flags().testFlag(QMetaType::IsEnumeration)) {
            return var.toInt();
        } else {
            return QJsonValue::fromVariant(var);
        }
        break;
    }
}

inline QVariant VariantUtil::fromJsonValue(const QJsonValue &val, QMetaType type)
{
    switch (type.id()) {
    case QMetaType::QPoint:
        return [=]{
            QJsonArray array(val.toArray());
            QPoint pt(array[0].toInt(), array[1].toInt());
            return QVariant(pt);}();
        break;
    case QMetaType::QPointF:
        return [=]{
            QJsonArray array(val.toArray());
            QPointF pt(array[0].toDouble(), array[1].toDouble());
            return QVariant(pt);}();
        break;
    case QMetaType::QSize:
        return [=]{
            QJsonArray array(val.toArray());
            QSize sz(array[0].toInt(), array[1].toInt());
            return QVariant(sz);}();
        break;
    case QMetaType::QSizeF:
        return [=]{
            QJsonArray array(val.toArray());
            QSizeF sz(array[0].toDouble(), array[1].toDouble());
            return QVariant(sz);}();
        break;
    case QMetaType::QRect:
        return [=]{
            QJsonArray array(val.toArray());
            QRect rect(array[0].toInt(), array[1].toInt(),
                       array[2].toInt(), array[3].toInt());
            return QVariant(rect);}();
        break;
    case QMetaType::QRectF:
        return [=]{
            QJsonArray array(val.toArray());
            QRectF rect(array[0].toDouble(), array[1].toDouble(),
                        array[2].toDouble(), array[3].toDouble());
            return QVariant(rect);}();
        break;
    case QMetaType::QLine:
        return [=]{
            QJsonArray array(val.toArray());
            QPoint p1{array[0][0].toInt(), array[0][1].toInt()};
            QPoint p2{array[1][0].toInt(), array[1][1].toInt()};
            QLine line(p1, p2);
            return QVariant(line);}();
        break;
    case QMetaType::QLineF:
        return [=]{
            QJsonArray array(val.toArray());
            QPointF p1{array[0][0].toDouble(), array[0][1].toDouble()};
            QPointF p2{array[1][0].toDouble(), array[1][1].toDouble()};
            QLineF line(p1, p2);
            return QVariant(line);}();
        break;
    case QMetaType::QColor:
        return QColor{val.toString()};
        break;
    default:
        return val.toVariant();
        break;
    }
}

inline QString VariantUtil::toString(const QVariant &var)
{
    QString str = QDebug::toString(var);
    str = str.replace(QRegularExpression("QVariant\\([^,]+, (.+)\\)$"), "\\1");
    int len = str.length();
    do{
        str = str.replace(QRegularExpression("\\w+\\(([^())]+)\\)"), "[\\1]");
        if (len == str.length()) {
            break;
        }
        len = str.length();
    }while(1);
    return str;
}

#endif // VARIANTUTIL_H
