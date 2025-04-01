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

#ifndef SVGPATHDEVICE_H
#define SVGPATHDEVICE_H

#include "painterpathex.h"
#include <QPaintEngine>
#include <QPainterPath>

class SvgEngine : public QPaintEngine
{
public:
    SvgEngine();
    QList<PainterPathEx> getSvgPath();
    // QPaintEngine interface
    bool begin(QPaintDevice *pdev) override;
    bool end() override;
    void updateState(const QPaintEngineState &state) override;
    void drawPath(const QPainterPath &path) override;
    void drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode) override;
    void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr) override;
    void drawTextItem(const QPointF &p, const QTextItem &textItem) override;
    QPaintEngine::Type type() const override;
private:
    QList<PainterPathEx> pathList;

};

class SvgPathDevice : public QPaintDevice
{
public:

    SvgPathDevice(int w, int h);
    SvgPathDevice(const QSize &size);
    ~SvgPathDevice();
    QList<PainterPathEx> getSvgPath();

    qreal devicePixelRatio() const;
    void setDevicePixelRatio(qreal scaleFactor);
    // QPaintDevice interface
    QPaintEngine *paintEngine() const override;
    int devType() const override;

protected:
    int metric(PaintDeviceMetric metric) const override;
private:
    SvgEngine *engine;
    qreal pixelRatio{1};
    int width;
    int height;
    int qt_defaultDpiX() const;
    int qt_defaultDpiY() const;
};
#endif // SVGPATHDEVICE_H
