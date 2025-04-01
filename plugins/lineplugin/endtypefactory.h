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

#ifndef ENDTYPEFACTORY_H
#define ENDTYPEFACTORY_H

#include "painterpathex.h"
#include <QMap>
#include <QSharedPointer>
#include <QIcon>
#include <QPainterPath>
#include <QSvgRenderer>
#include "lineendtype.h"

class QString;

class EndType
{
public:
    // ID
    QString id;
    // 文件名
    QString fileName;
    // 画布大小
    QSize size;
    // 对应的图标
    QPixmap thumb;
    // 箭头路径
    QList<PainterPathEx> arrow;
    QSizeF arrowSize;
    // 直线对应的路径
    QList<PainterPathEx> line;
    bool isEmpty(){return id.isEmpty();}
};

class EndTypeFactory
{
public:
    /**
     * @brief instance 获取实例
     * @return EndTypeFactory 对象
     */
    static QSharedPointer<EndTypeFactory>instance();
    /**
     * @brief getEndType 根据ID获取指定类型的端点路径
     * @param typeId 端点类型ID
     * @param category 端点类别
     * @return EndType 对象
     */
    EndType getEndType(const QString &typeId, LineEndType::Category category);
    /**
     * @brief getEndTypeList 获取所有指定类型的端点集合
     * @param category 端点类别
     * @return 端点集合，key 端点ID， value 端点图形
     */
    QMap<QString, QIcon> getEndTypeList(LineEndType::Category category);
private:
    // QMap<QString, QPainterPath> endTypeMap;
    QMap<QString, EndType> endTypeMap;
    qreal screenRatio{1};

    EndTypeFactory();
    Q_DISABLE_COPY(EndTypeFactory)
    /**
     * @brief loadEndType 加载指定路径下的终端类型
     * @param path 路径
     */
    void loadEndType(QString path);
    /**
     * @brief flipPath 水平翻转路径
     * @param path 被翻转路径
     * @return 翻转后路径
     */
    QPainterPath flipPath(QPainterPath path);
    /**
     * @brief createThumb 创建SVG图像
     * @param render SVG 渲染器
     * @param rect svg图像大小
     * @return 图像
     */
    QPixmap createThumb(QSvgRenderer *render, const QRectF &rect = QRectF());
    /**
     * @brief extractPath 从SVG中提取路径
     * @param render SVG 渲染器
     * @param id SVG 图元ID
     * @return 路径信息
     */
    QList<PainterPathEx> extractPath(QSvgRenderer *render, QString id);
};

#endif // ENDTYPEFACTORY_H
