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

#ifndef SVGHELPER_H
#define SVGHELPER_H
#include <QString>
#include <QSize>
#include <QColor>
#include <QPainter>
#include <QMap>

class SvgHelperPrivate;
class SvgHelper
{
public:
    enum ColorGroup{None, Normal, Disabled, Active, Inactive};
    SvgHelper();
    /**
     * @brief 指定 SVG 文件
     * @param filePath SVG 文件路径
     */
    explicit SvgHelper(const QString &filePath);
    /**
     * @brief 指定 SVG 文件
     * @param content SVG 文件内容
     */
    explicit SvgHelper(const QByteArray &content);
    ~SvgHelper();

    qint16 width() const;
    void setWidth(qint16 width);
    qint16 height() const;
    void setHeight(qint16 height);
    QSize size() const;
    void setSize(QSize size);
    void setFillColor(QColor color);
    void setStrokeColor(QColor color);
    void setStrokeWidth(qint16 width);
    /**
     * @brief 使用指定的 painter 绘制 SVG 图
     * @param painter
     * @param bounds 指定绘制位置及大小
     */
    void render(QPainter *painter, const QRectF &bounds);
    /**
     * @brief 获取修改后的 SVG 内容
     * @return  SVG 内容
     */
    QByteArray getContent() const;
    /**
     * @brief SVG 图片转为 pixmap，pixmap 大小为SVG原始大小
     * @param group 主题颜色组别
     * @return pixmap 对象
     */
    QPixmap toPixmap(ColorGroup group = None) const;
    /**
     * @brief SVG 图片转为 pixmap
     * @param size pixmap 大小
     * @param group 主题颜色组别
     * @return pixmap 对象
     */
    QPixmap toPixmap(const QSize &size, ColorGroup group = None) const;
private:

    QScopedPointer<SvgHelperPrivate> d_ptr;

    Q_DISABLE_COPY(SvgHelper)
    Q_DECLARE_PRIVATE(SvgHelper)
};

#endif // SVGHELPER_H
