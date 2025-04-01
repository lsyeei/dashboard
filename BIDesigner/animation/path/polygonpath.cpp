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

#include "polygonpath.h"
#include "animation/path/linepathproperty.h"

#include <lineselector.h>

QString PolygonPath ::PATH_ID = "PLOYGON_PATH";
PolygonPath ::PolygonPath(QGraphicsItem *parent) : AbstractLinePath(parent) {
    enableEdit(true);
    enablePreview(true);

}
PolygonPath ::PolygonPath(const QString &xml, QGraphicsItem *parent)
    : AbstractLinePath(parent) {
    parseXML(xml);
    enableEdit(true);
    enablePreview(true);
}

QString PolygonPath ::classId() const { return PATH_ID; }

QPainterPath PolygonPath ::linePath(QList<QPointF> points) const {
    QPainterPath path;
    path.addPolygon(points);
    return path;
}

void PolygonPath ::createPredefinedItem() {}


void PolygonPath::afterCreateSelector(LineSelector *s)
{}
