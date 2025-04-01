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

#include "cubicline.h"

QString CubicLine::SHAPE_ID = "CUBIC_LINE_2024";
CubicLine::CubicLine(QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
}

CubicLine::CubicLine(const QString &xml, QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    enableEdit(true);
    enablePreview(true);
    parseXML(xml);
}

QString CubicLine::classId() const
{
    return SHAPE_ID;
}

QPainterPath CubicLine::previewPath(QList<QPointF> points, QVariant args) const
{
    QPainterPath path;
    if (points.isEmpty() || points.count() < 2) {
        return path;
    }
    auto attr = attribute();
    // 获取终端类型的path
    auto startAttr = attr->getStart();
    if (!startAttr.isEmpty()) {
        startAttr.setPos(points[0]);
        startAttr.setRotation(calcEndRotation(points, startAttr));
        auto data = getEndTypePath(startAttr);
        path.addPath(data.first);
        points[0] = data.second;
    }
    auto endAttr = attr->getEnd();
    if (!endAttr.isEmpty()) {
        endAttr.setPos(points[points.count() - 1]);
        endAttr.setRotation(calcEndRotation(points, endAttr));
        auto data = getEndTypePath(endAttr);
        path.addPath(data.first);
        points[points.count() - 1] = data.second;
    }
    int j{-1},k{-1};
    if (!args.isNull()){
        auto ids = args.value<QList<int>>();
        if (ids.count() >= 2) {
            // 添加的位置
            j = ids[0];
            // 删除的位置
            k = ids[1];
        }
    }
    if (j < 0 && k < 0) {
        path.addPath(linePath(points));
    } else if (j >= 0){
        // 添加了新点
        path.moveTo(points[0]);
        QLineF l{points[0],points[1]};
        CurveControlParam param1, param2;
        for (qsizetype i = 1; i < points.count(); ++i) {
            if (controlInfo.isEmpty() || controlInfo.count() < 2*i) {
                path.lineTo(points[i]);
                continue;
            }
            if (i == j) {
                param1 = controlInfo[2*i-1];
                QLineF l(points[i+1], points[i-1]);
                param2.setAngle(l.angle());
                l.setP1(points[i]);
                param2.setLen(l.length()/2);
                param2.setAttach(true);
            } else if(i == j+1) {
                QLineF l(points[i-2], points[i]);
                param1.setAngle(l.angle());
                l.setP1(points[i-1]);
                param1.setLen(l.length()/2);
                param1.setAttach(true);
                param2  = controlInfo[2*(i-1)];
            } else if (i < j) {
                param1 = controlInfo[2*i-1];
                param2  = controlInfo[2*i];
            } else {
                param1 = controlInfo[2*(i-1)-1];
                param2  = controlInfo[2*(i-1)];
            }
            l.setPoints(points[i-1], points[i]);
            l.setAngle(param1.getAngle());
            l.setLength(param1.getLen());
            auto p1 = l.p2();
            l.setPoints(points[i], points[i-1]);
            l.setAngle(param2.getAngle());
            l.setLength(param2.getLen());
            path.cubicTo(p1,l.p2(),points[i]);
        }
    } else if (k >= 0){
        // 删除了点
        path.moveTo(points[0]);
        QLineF l{points[0],points[1]};
        CurveControlParam param1, param2;
        for (qsizetype i = 1; i < points.count(); ++i) {
            if (controlInfo.isEmpty() || controlInfo.count() < 2*i) {
                path.lineTo(points[i]);
                continue;
            }

            if (i < k) {
                param1 = controlInfo[2*i-1];
                param2  = controlInfo[2*i];
            }else if (i == k) {
                param1 = controlInfo[2*i-1];
                param2  = controlInfo[2*(i+1)];
            } else {
                param1 = controlInfo[2*(i+1)-1];
                param2  = controlInfo[2*(i+1)];
            }
            l.setPoints(points[i-1], points[i]);
            l.setAngle(param1.getAngle());
            l.setLength(param1.getLen());
            auto p1 = l.p2();
            l.setPoints(points[i], points[i-1]);
            l.setAngle(param2.getAngle());
            l.setLength(param2.getLen());
            path.cubicTo(p1,l.p2(),points[i]);
        }
    }
    return path;
}

QPainterPath CubicLine::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    if (points.isEmpty() || points.count() < 2) {
        return path;
    }
    path.moveTo(points[0]);
    QLineF l{points[0],points[1]};
    for (qsizetype i = 1; i < points.count(); ++i) {
        // QPointF p1 = points.at(i - 1);
        // QPointF p2 = points.at(i);
        // qreal distance = p2.x() - p1.x();

        // path.cubicTo(p1.x() + distance / 2, p1.y(),
        //              p1.x() + distance / 2, p2.y(),
        //              p2.x(), p2.y());
        if (controlInfo.isEmpty() || controlInfo.count() < 2*i+1) {
            path.lineTo(points[i]);
            continue;
        }
        l.setPoints(points[i-1], points[i]);
        l.setAngle(controlInfo[2*i-1].getAngle());
        l.setLength(controlInfo[2*i-1].getLen());
        auto p1 = l.p2();
        l.setPoints(points[i], points[i-1]);
        l.setAngle(controlInfo[2*i].getAngle());
        l.setLength(controlInfo[2*i].getLen());
        path.cubicTo(p1,l.p2(),points[i]);
    }

    return path;
}

void CubicLine::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-50, 50});
    attr->appendPoint({0, 0});
    attr->appendPoint({50, -50});
    setSize({100,100});
}

void CubicLine::afterCreateSelector(LineSelector *s)
{
    s->enableCurveAdjuster(true);
    connect(s, SIGNAL(pointMoveStart(QString)), this, SLOT(onPointSelected(QString)));
    connect(s, SIGNAL(leftCurveParamChanged(CurveControlParam)), this, SLOT(onLeftCurveChanged(CurveControlParam)));
    connect(s, SIGNAL(rightCurveParamChanged(CurveControlParam)), this, SLOT(onRightCurveChanged(CurveControlParam)));
}

qreal CubicLine::calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const
{
    qreal angle = 0;
    auto path = linePath(points);
    auto attr = attribute();
    if (type.getCategory() == LineEndType::Start) {
        auto p1 = path.pointAtPercent(path.percentAtLength(attr->getStart().getSize()));
        auto p2 = path.pointAtPercent(0);
        QLineF l{p1, p2};
        QLineF l2{{0,0}, {-1,0}};
        angle = l.angleTo(l2);
    }else if (type.getCategory() == LineEndType::End){
        auto p1 = path.pointAtPercent(1-path.percentAtLength(attr->getEnd().getSize()));
        auto p2 = path.pointAtPercent(1);
        QLineF l{p1, p2};
        QLineF l2{{0,0}, {1,0}};
        angle = l.angleTo(l2);
    }
    return angle;
}

void CubicLine::afterAddPoint(const QString &id)
{
    auto attr = attribute();
    auto points = attr->getPoints();
    if (points.count() < 2) {
        return;
    }
    int i = indexOfPoint(id);
    if (i < 0) {
        return;
    }
    if (initStatge == DRAWING){
        deduceCurveParam(i, {points[i-1], points[i]});
    }
    if (initStatge == FINISHED){
        deduceCurveParam(i, {points[i-1], points[i], points[i+1]});
        auto s = dynamic_cast<LineSelector*>(selector);
        s->setCurveController(controlInfo[i*2], controlInfo[i*2+1]);
    }
}

void CubicLine::beforeDelPoint(const QString &id)
{
    int i = indexOfPoint(id);
    if (i < 0 || controlInfo.isEmpty()) {
        return;
    }
    controlInfo.remove(i*2);
    controlInfo.remove(i*2);
    if (i == 0) {
        controlInfo[0].setLen(0);
    }
    auto attr = attribute();
    if (i == attr->getPointCount()-1) {
        controlInfo.last().setLen(0);
    }
    attr->setCurveParam(controlInfo);
    auto s = dynamic_cast<LineSelector*>(selector);
    s->setCurveController(CurveControlParam(), CurveControlParam());
}

void CubicLine::afterPointMoved(const QString &id)
{
    auto attr = attribute();
    if (initStatge == CAPTURED && controlInfo.isEmpty()){
        calcControlPoint(attr->getPoints());
    } else if(initStatge == DRAWING){
        int i = indexOfPoint(id);
        if (i < 0) {
            return;
        }
        auto points = attr->getPoints();
        deduceCurveParam(i, {points[i-1], points[i]});
    }
}

void CubicLine::afterInit()
{
    if (controlInfo.isEmpty()) {
        calcControlPoint(attribute()->getPoints());
    }
}

void CubicLine::dragPoint(const NamedPoint &pt, const QPointF &pos)
{
    QLineF l{pt.pt, mapFromScene(pos)};
    auto i = indexOfPoint(pt.id);
    if (controlInfo.count() < 2*i) {
        controlInfo << CurveControlParam() << CurveControlParam();
    }
    controlInfo[2*i].setAngle(l.angle()+180);
    controlInfo[2*i].setLen(l.length());
    controlInfo[2*i+1].setAngle(l.angle());
    controlInfo[2*i+1].setLen(l.length());
    attribute()->setCurveParam(controlInfo);
    auto s = dynamic_cast<LineSelector*>(selector);
    s->setCurveController(controlInfo[i*2], controlInfo[i*2+1]);
    s->setCurrentPoint(pt.id);
    prepareGeometryChange();
    updateGraphic();
}

void CubicLine::onPointSelected(const QString &id)
{
    if (initStatge != FINISHED) {
        return;
    }
    auto i = indexOfPoint(id);
    if (i < 0) {
        return;
    }
    currentIndex = i;
    auto s = dynamic_cast<LineSelector*>(selector);
    s->setCurveController(controlInfo[i*2], controlInfo[i*2+1]);
}

void CubicLine::onLeftCurveChanged(const CurveControlParam &param)
{
    if(currentIndex < 0){
        return;
    }
    updateCurveParam(2*currentIndex, param);
}

void CubicLine::onRightCurveChanged(const CurveControlParam &param)
{
    if(currentIndex < 0){
        return;
    }
    updateCurveParam(2*currentIndex+1, param);
}

void CubicLine::calcControlPoint(const QList<QPointF> &points)
{
    if(points.isEmpty() || points.count() < 2){
        return;
    }
    QPointF prePt{0,0};
    for (int i = 0; i < points.count(); ++i) {
        if (i > 0) {
            prePt = points[i-1];
        }
        deduceCurveParam(i, {prePt,points[i]});
    }
}

int CubicLine::indexOfPoint(const QString &id) const
{
    auto attr = attribute();
    auto list = attr->getPointList();
    int j = -1;
    for (int i = 0; i < list.count(); ++i) {
        if (list[i].id.compare(id) == 0) {
            j = i;
            break;
        }
    }
    return j;
}

void CubicLine::deduceCurveParam(int i, const QList<QPointF> &pts)
{
    qreal angle = 30;
    if (i == 0 && controlInfo.isEmpty()) {
        controlInfo << CurveControlParam();
        controlInfo << CurveControlParam{angle, 0, false};
        return;
    }
    if (pts.count() < 2 || controlInfo.count() < 2*i) {
        return;
    }
    if (pts.count() == 2){
        // 追加模式
        QLineF l{pts[1], pts[0]};
        QLineF l2{pts[0], pts[1]};
        QLineF l3{l2};
        if (i > 1) {
            angle = controlInfo[2*i-2].getAngle()+180;
        } else if(i == 1) {
            angle = l2.angle() + angle;
        }
        angle = fmodf(angle, 360);
        if (controlInfo[2*i-1].isEmpty()) {
            controlInfo[2*i-1].setLen(l.length()/2);
            controlInfo[2*i-1].setAngle(angle);
        }
        if (i > 1) {
            controlInfo[2*i-1].setAttach(true);
        }
        l3.setAngle(angle);
        angle = l2.angleTo(l3);
        angle = l.angle() - angle;
        if(controlInfo.count() == 2*(i+1)) {
            // 最后一个点移动
            controlInfo[2*i].setLen(l.length()/2);
            controlInfo[2*i].setAngle(angle);
        } else if(controlInfo.count() < 2*(i+1)){
            // 添加最后一个点
            controlInfo.insert(2*i,CurveControlParam{angle, l.length()/2, true});
            controlInfo.insert(2*i+1,CurveControlParam());
        }
        // 修正控制点距离
        // l.setAngle(angle);
        // l2.setAngle(controlInfo[2*i-1].getAngle());
        // QPointF intersectPt;
        // if(l.intersects(l2, &intersectPt) == QLineF::BoundedIntersection){
        //     // 正向相交
        //     l.setP2(intersectPt);
        //     l2.setP2(intersectPt);
        //     if (l2.length()/2 < 2*controlInfo[2*i-1].getLen()) {
        //         controlInfo[2*i-1].setLen(l2.length()/2);
        //     }
        //     if (l.length()/2 < 2*controlInfo[2*i].getLen()) {
        //         controlInfo[2*i].setLen(l.length()/2);
        //     }
        // }
    } else if (pts.count() == 3){
        // 插入模式
        QLineF l{pts[2], pts[0]};
        auto angle = l.angle();
        l.setPoints(pts[1], pts[0]);
        controlInfo.insert(2*i, {angle, l.length()/2, true});
        l.setPoints(pts[1], pts[2]);
        controlInfo.insert(2*i+1, {180+angle, l.length()/2, true});
    }
    attribute()->setCurveParam(controlInfo);
}

QList<NamedPoint> CubicLine::createEditPoint()
{
    QList<NamedPoint> editPoints;
    auto points = attribute()->getPointList();
    if (points.isEmpty() || points.count() < 2) {
        return editPoints;
    }
    QPainterPath path;
    QLineF l{points[0].pt,points[1].pt};
    for (qsizetype i = 1; i < points.count(); ++i) {
        path.moveTo(points[i-1].pt);
        if (controlInfo.isEmpty() || controlInfo.count() < 2*i+1) {
            path.lineTo(points[i].pt);
        }else{
            l.setPoints(points[i-1].pt, points[i].pt);
            l.setAngle(controlInfo[2*i-1].getAngle());
            l.setLength(controlInfo[2*i-1].getLen());
            auto p1 = l.p2();
            l.setPoints(points[i].pt, points[i-1].pt);
            l.setAngle(controlInfo[2*i].getAngle());
            l.setLength(controlInfo[2*i].getLen());
            path.cubicTo(p1,l.p2(),points[i].pt);
        }
        editPoints << NamedPoint{points[i].id, path.pointAtPercent(0.5)};
        path.clear();
    }

    return editPoints;
}

void CubicLine::updateCurveParam(int i, const CurveControlParam &param)
{
    controlInfo[i] = param;
    attribute()->setCurveParam(controlInfo);
    auto s = dynamic_cast<LineSelector*>(selector);
    s->updateEditPoint(createEditPoint());
    updateGraphic();
    updateForm();
}


void CubicLine::parseXML(const QString &xml)
{
    AbstractLineItem::parseXML(xml);
    controlInfo = attribute()->getCurveParam();
}
