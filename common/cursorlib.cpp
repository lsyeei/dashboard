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

#include "cursorlib.h"

#include "pathimage.h"

#include <QMap>
class CursorLibPrivate : public QSharedData{
public:
    CursorLibPrivate(){};
    QMap<CursorLib::CustomShape, PathImage> definedShape;
};

CursorLib *CursorLib::lib{nullptr};
CursorLib *CursorLib::instance()
{
    if (lib == nullptr) {
        lib = new CursorLib();
    }
    return lib;
}

QCursor CursorLib::getShape(CustomShape shape, qreal angle, const QSize &size)
{
    auto pixmap = d->definedShape[shape].toPixMap(angle, size);
    return QCursor(pixmap);
}

PathImage CursorLib::createSizeHorCursor()
{
    QSize imgSize{32,32};
    TintedPath tPath;
    tPath.pen = Qt::NoPen;
    tPath.brush = Qt::white;
    qreal winWidth{20}, winHeight{8};
    qreal x1 = -winWidth / 2;
    qreal x2 = x1 + winHeight / 2;
    qreal x3 = -x2;
    qreal x4 = -x1;
    qreal y1 = -winHeight / 2;
    qreal y2 = -winHeight * 1 /8;
    qreal y3 = -y2;
    qreal y4 = -y1;
    tPath.path.moveTo(x1, 0);
    tPath.path.lineTo(x2,y1);
    tPath.path.lineTo(x2, y2);
    tPath.path.lineTo(x3, y2);
    tPath.path.lineTo(x3,y1);
    tPath.path.lineTo(x4, 0);
    tPath.path.lineTo(x3, y4);
    tPath.path.lineTo(x3, y3);
    tPath.path.lineTo(x2, y3);
    tPath.path.lineTo(x2, y4);
    tPath.path.lineTo(x1, 0);

    tPath.path.closeSubpath();

    PathImage image(imgSize, tPath);
    return image;
}

CursorLib::CursorLib()
{
    d = new CursorLibPrivate();
    d->definedShape[SizeHorCursor] = createSizeHorCursor();
}
