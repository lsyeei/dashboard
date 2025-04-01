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

#include "svgpathdevice.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <qdebug.h>
// #include <private/qfont_p.h>

SvgEngine::SvgEngine()
    : QPaintEngine()
{
    gccaps |= QPaintEngine::AllFeatures;
    extended = 0;
}

QList<PainterPathEx> SvgEngine::getSvgPath()
{
    return pathList;
}


bool SvgEngine::begin(QPaintDevice *pdev)
{
    Q_UNUSED(pdev)
    pathList.clear();
    return true;
}

bool SvgEngine::end()
{
    return true;
}

void SvgEngine::updateState(const QPaintEngineState &state)
{
    Q_UNUSED(state)
}

void SvgEngine::drawPath(const QPainterPath &path)
{
    auto pen = painter()->pen();
    auto brush = painter()->brush();
    PainterPathEx pathEx(path);
    pathEx.setPen(pen);
    pathEx.setBrush(brush);
    pathList.append(pathEx);
}

void SvgEngine::drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode)
{
    Q_UNUSED(mode)
    QList<QPointF> pointList;
    for (int i = 0; i < pointCount; ++i) {
        pointList.append(*points);
        points++;
    }
    QPolygonF polygon(pointList);
    PainterPathEx pathEx;
    pathEx.addPolygon(polygon);
    pathEx.setPen(painter()->pen());
    pathEx.setBrush(painter()->brush());
    pathList.append(pathEx);
}

void SvgEngine::drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr)
{
    Q_UNUSED(pm)
    Q_UNUSED(sr)
    PainterPathEx pathEx;
    pathEx.addRect(r);
    pathEx.setPen(painter()->pen());
    pathEx.setBrush(painter()->brush());
    pathList.append(pathEx);
}

void SvgEngine::drawTextItem(const QPointF &p, const QTextItem &textItem)
{
    PainterPathEx pathEx;
    pathEx.addText(p, textItem.font(), textItem.text());
    pathEx.setPen(painter()->pen());
    pathEx.setBrush(painter()->brush());
    pathList.append(pathEx);
}

QPaintEngine::Type SvgEngine::type() const
{
    return QPaintEngine::SVG;
}

SvgPathDevice::SvgPathDevice(int w, int h)
    :SvgPathDevice(QSize{w,h})
{
}

SvgPathDevice::SvgPathDevice(const QSize &size)
    : width(size.width()), height(size.height())
{
    engine = new SvgEngine();
}

SvgPathDevice::~SvgPathDevice()
{
    delete engine;
}

QList<PainterPathEx> SvgPathDevice::getSvgPath()
{
    return engine->getSvgPath();
}

qreal SvgPathDevice::devicePixelRatio() const
{
    return pixelRatio;
}

void SvgPathDevice::setDevicePixelRatio(qreal scaleFactor)
{
    pixelRatio = scaleFactor;
}

QPaintEngine *SvgPathDevice::paintEngine() const
{
    return engine;
}

int SvgPathDevice::devType() const
{
    return QInternal::UnknownDevice;
}

int SvgPathDevice::metric(PaintDeviceMetric metric) const
{
    switch (metric) {
    case QPaintDevice::PdmWidth:
        return width;
    case QPaintDevice::PdmHeight:
        return height;
    case QPaintDevice::PdmWidthMM:
        return qRound(width * 25.4 / qt_defaultDpiX());
    case QPaintDevice::PdmHeightMM:
        return qRound(height * 25.4 / qt_defaultDpiY());
    case QPaintDevice::PdmNumColors:
        return 24;
    case QPaintDevice::PdmDepth:
        return 8;
    case QPaintDevice::PdmDpiX:
        return qt_defaultDpiX();
    case QPaintDevice::PdmPhysicalDpiX:
        return qt_defaultDpiX();
    case QPaintDevice::PdmDpiY:
        return qt_defaultDpiY();
    case QPaintDevice::PdmPhysicalDpiY:
        return qt_defaultDpiY();
    case QPaintDevice::PdmDevicePixelRatio:
        return pixelRatio;
    case QPaintDevice::PdmDevicePixelRatioScaled:
        return pixelRatio * QPaintDevice::devicePixelRatioFScale();

    default:
        qWarning("SvgPathDevice::metric(): Unhandled metric type %d", metric);
        break;
    }

    return 0;
}
int SvgPathDevice::qt_defaultDpiX() const
{
    if (QCoreApplication::instance()->testAttribute(Qt::AA_Use96Dpi))
        return 96;

    // if (qt_is_tty_app)
    //     return 75;

    if (const QScreen *screen = QGuiApplication::primaryScreen())
        return qRound(screen->logicalDotsPerInchX());

    //PI has not been initialised, or it is being initialised. Give a default dpi
    return 100;
}

int SvgPathDevice::qt_defaultDpiY() const
{
    if (QCoreApplication::instance()->testAttribute(Qt::AA_Use96Dpi))
        return 96;

    // if (qt_is_tty_app)
    //     return 75;

    if (const QScreen *screen = QGuiApplication::primaryScreen())
        return qRound(screen->logicalDotsPerInchY());

    //PI has not been initialised, or it is being initialised. Give a default dpi
    return 100;
}
