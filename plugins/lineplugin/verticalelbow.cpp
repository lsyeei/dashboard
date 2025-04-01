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

#include "verticalelbow.h"
#include "paintHelper.h"

#include <QGuiApplication>
#include <QToolTip>

QString VerticalElbow::SHAPE_ID = "VERTICAL_ELBOW_2024";
VerticalElbow::VerticalElbow(QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    auto attr = attribute();
    LineEndType start(LineEndType::Start, "");
    start.setFixRotation(-90);
    attr->setStart(start);
    LineEndType end(LineEndType::End, "arcArrow");
    end.setFixRotation(-90);
    attr->setEnd(end);
}

VerticalElbow::VerticalElbow(const QString &xml, QGraphicsItem *parent)
    : AbstractLineItem(parent)
{
    parseXML(xml);
}

QString VerticalElbow::classId() const
{
    return SHAPE_ID;
}

void VerticalElbow::onPointMoveStart(const QString &id)
{
    if (initStatge < 3) {
        // 未初始化完成，不启用
        return;
    }
    auto points = attribute()->getPointList();
    auto globalPoint = QCursor::pos();
    if (id.compare(points.last().getId()) == 0) {
        // 最后一个点移动时，记录移动前的位置
        lastPoint = points.last().getPt();
        QToolTip::showText(globalPoint, tr("按住ctrl键添加控制点"), nullptr, {}, 1000);
    } else if (points.count() >= 5) {
        QToolTip::showText(globalPoint, tr("按住ctrl键自动合并控制点"), nullptr, {}, 1000);
    }
}

void VerticalElbow::onPointMoveEnd(const QString &id)
{
    if (initStatge < 3) {
        return;
    }
    addFlag = false;
    // 自动合并同一直线上的点
    if (QGuiApplication::keyboardModifiers() == Qt::ControlModifier) {
        autoMergePoit(id);
    }
}

QPainterPath VerticalElbow::linePath(QList<QPointF> points) const
{
    QPainterPath path;
    auto attr = attribute();
    bool isRound = attr->getRounded();
    qreal arcSize = attr->getArcSize();
    auto count = points.count();
    path.moveTo(points[0]);
    for (int i = 1; i < count; ++i) {
        if(i%2 == 1){
            if (isRound) {
                PaintHelper::drawRoundCorner(&path,
                                             {{points[i-1].x(), points[i].y()}, points[i-1]},
                                             {{points[i-1].x(), points[i].y()}, points[i]}, arcSize);
            }else{
                path.lineTo({points[i-1].x(), points[i].y()});
                path.lineTo(points[i]);
            }
        }else{
            if (isRound) {
                PaintHelper::drawRoundCorner(&path,
                                             {{points[i].x(), points[i-1].y()}, points[i-1]},
                                             {{points[i].x(), points[i-1].y()}, points[i]}, arcSize);
            }else{
                path.lineTo({points[i].x(), points[i-1].y()});
                path.lineTo(points[i]);
            }
        }
    }
    path.lineTo(points[points.count() - 1]);
    return path;
}

void VerticalElbow::createPredefinedItem()
{
    auto attr = attribute();
    attr->appendPoint({-50, 50});
    attr->appendPoint({0, 0});
    attr->appendPoint({50, -50});
    setSize({100,100});
}

void VerticalElbow::afterCreateSelector(LineSelector *s)
{
    s->connect(s, SIGNAL(pointMoveStart(QString)), this, SLOT(onPointMoveStart(QString)));
    s->connect(s, SIGNAL(pointMoveEnd(QString)), this, SLOT(onPointMoveEnd(QString)));
}

void VerticalElbow::afterInit()
{
}

void VerticalElbow::afterPointMoved(const QString &id)
{
    auto attr = attribute();
    auto list = attr->getPointList();
    auto count = list.count();
    if (count < 3) {
        return;
    }
    auto lastPt = list.last();
    if (initStatge == 3 && id.compare(lastPt.getId()) == 0 &&
        !addFlag /*&& qAbs(lastPt.getPt().x() - lastPoint.x()) > 5*/
        && QGuiApplication::keyboardModifiers() == Qt::ControlModifier){
        // 移动末端节点，垂直方向偏移大于5时，自动增加点
        autoAddPoint();
        return;
    }
    auto end = attr->getEnd();
    for (int i = 0; i < count; ++i) {
        if (list[i].id.compare(id) != 0) {
            continue;
        }
        if (i == 0) {
            attr->updatePoint(list[i+1].id, {(list[i].pt.x() + list[i+2].pt.x())/2, list[i+1].pt.y()});
            updateEndRotaion();
        }else if(i == count - 1){
            if (initStatge < 3) {
                attr->updatePoint(list[i-1].id, (list[i].pt + list[i-2].pt)/2);
                if (count > 3) {
                    attr->updatePoint(list[i-2].id, {list[i-2].pt.x(), (list[i-1].pt.y() + list[i-3].pt.y())/2});
                }
            } else {
                attr->updatePoint(list[i-1].id, {(list[i].pt.x() + list[i-2].pt.x())/2, list[i-1].pt.y()});
            }
            // 改变箭头方向
            updateEndRotaion();
        } else if (i == 1){
            attr->updatePoint(list[i].id, {(list[i-1].pt.x()+list[i+1].pt.x())/2, list[i].pt.y()});
            if(count > 3){
                attr->updatePoint(list[i+1].id, {list[i+1].pt.x(), (list[i].pt.y() + list[i+2].pt.y())/2});
            }
            // 改变箭头方向
            updateEndRotaion();
        } else if (i == count - 2){
            attr->updatePoint(list[i].id, {(list[i-1].pt.x()+list[i+1].pt.x())/2, list[i].pt.y()});
            attr->updatePoint(list[i-1].id, {list[i-1].pt.x(), (list[i].pt.y() + list[i-2].pt.y())/2});
            // 改变箭头方向
            updateEndRotaion();
        } else if(i%2 == 0){
            attr->updatePoint(list[i].id, {list[i].pt.x(), (list[i-1].pt.y()+list[i+1].pt.y())/2});
            attr->updatePoint(list[i+1].id, {(list[i].pt.x() + list[i+2].pt.x())/2, list[i+1].pt.y()});
            attr->updatePoint(list[i-1].id, {(list[i].pt.x() + list[i-2].pt.x())/2, list[i-1].pt.y()});
        } else if(i%2 == 1){
            attr->updatePoint(list[i].id, {(list[i-1].pt.x()+list[i+1].pt.x())/2, list[i].pt.y()});
            attr->updatePoint(list[i+1].id, {list[i+1].pt.x(), (list[i].pt.y() + list[i+2].pt.y())/2});
            attr->updatePoint(list[i-1].id, {list[i-1].pt.x(), (list[i].pt.y() + list[i-2].pt.y())/2});
        }

        break;
    }
}

void VerticalElbow::beforeAddPoint(const QString &id, const QPointF &pos)
{
    auto attr = attribute();
    auto count = attr->getPointCount();
    if (/*count > 2 && */count%2 == 0){
        return;
    }
    // 添加中间点
    auto list = attr->getPointList();
    QPointF pt;
    if (id.isEmpty()) {
        pt = list.last().pt;
    } else {
        for (int i = 0; i < list.count(); ++i) {
            if (list[i].id.compare(id) == 0) {
                pt = list[i - 1].pt;
                break;
            }
        }
    }
    attr->insertPoint((pt + pos)/2, id);
}

void VerticalElbow::beforeDelPoint(const QString &id)
{
    auto attr = attribute();
    auto list = attr->getPointList();
    // 删除中间点
    for (int i = 0; i < list.count(); ++i) {
        if (list[i].id.compare(id) == 0) {
            if(i == 0){
                attr->removePoint(list[1].id);
            } else if(i == list.count() - 1){
                attr->removePoint(list[list.count() - 2].id);
            } else if(i%2==0){
                attr->removePoint(list[i-1].id);
                attr->updatePoint(list[i+1].id, (list[i-2].pt + list[i+2].pt)/2);
            } else if (i%2 == 1){
                attr->removePoint(list[i+1].id);
                attr->updatePoint(list[i+2].id, (list[i-1].pt + list[i+3].pt)/2);
            }
            break;
        }
    }
}

void VerticalElbow::updateEndRotaion()
{
    auto attr = attribute();
    auto list = attr->getPointList();
    auto start = attr->getStart();
    int offset = 0;
    int minOffset = 5;
    if (!start.isEmpty()) {
        minOffset = start.getSize()/2;
        offset = list[0].pt.y() - list[1].pt.y();
        if (offset > minOffset) {
            start.setRotation(-90);
        } else if (offset < -minOffset){
            start.setRotation(90);
        } else {
            if (list[0].pt.x() < list[1].pt.x()){
                start.setRotation(0);
            } else {
                start.setRotation(180);
            }
            attr->updatePoint(list[0].id, {list[0].pt.x(), list[1].pt.y()});
        }
        attr->setStart(start);
    }

    auto end = attr->getEnd();
    if (!end.isEmpty()) {
        minOffset = end.getSize()/2;
        auto count = list.count();
        offset = list[count - 1].pt.y() - list[count - 2].pt.y();
        if (offset > minOffset) {
            end.setRotation(90);
        } else if (offset < -minOffset){
            end.setRotation(-90);
        } else {
            if (list[count - 1].pt.x() > list[count - 2].pt.x()){
                end.setRotation(0);
            } else {
                end.setRotation(180);
            }
            attr->updatePoint(list[count - 1].id, {list[count - 1].pt.x(), list[count - 2].pt.y()});
        }
        attr->setEnd(end);
    }
}

void VerticalElbow::autoAddPoint()
{
    addFlag = true;
    auto attr = LineBaseProperty();
    attr.copy(*attribute());
    auto list = attr.getPointList();
    QString id = list.last().getId();
    auto count = list.count();
    // 添加2个点的位置
    auto x = list[count-1].pt.x();
    auto y = (list[count-2].getPt().y() + list[count-1].getPt().y())/2;
    attr.insertPoint({x,y}, id);
    attr.insertPoint(list[count-1].pt, id);
    updateAttribute(&attr);
}

void VerticalElbow::autoMergePoit(const QString &movedId)
{
    auto count = attribute()->getPointCount();
    if (initStatge < 3 || count < 5) {
        return;
    }
    auto list = attribute()->getPointList();
    int index{-1};
    for (int i = 0; i < count; ++i) {
        if (movedId.compare(list[i].getId()) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1 || index < 1 || index > count-2) {
        return;
    }
    int minGap = 3;
    auto attr = LineBaseProperty();
    attr.copy(*attribute());
    QPointF pt1, pt2;
    auto pt3 = list[index].getPt();
    // 判断前面2点
    if (index >= 2){
        pt1 = list[index-2].getPt();
        pt2 = list[index-1].getPt();
        if (qAbs(pt2.y() - pt1.y()) < minGap && qAbs(pt2.y() - pt3.y()) < minGap) {
            // 同一水平线
            if (index > 2){
                auto x = (list[index-3].pt.x() + list[index+1].pt.x())/2;
                auto y = list[index-2].pt.y();
                attr.updatePoint(list[index-2].id, {x,y});
            }
            attr.removePoint(list[index-1].id);
            attr.removePoint(movedId);
            // updateAttribute(&attr);
            return;
        }
        if (qAbs(pt2.x() - pt1.x()) < minGap && qAbs(pt2.x() - pt3.x()) < minGap) {
            // 同一垂直线
            if (index > 2){
                auto x = list[index-2].pt.x();
                auto y = (list[index-3].pt.y() + list[index+1].pt.y())/2;
                attr.updatePoint(list[index-2].id, {x,y});
            }
            attr.removePoint(list[index-1].id);
            attr.removePoint(movedId);
            // updateAttribute(&attr);
            return;
        }
    }
    // 判断后面2个点
    if (index <= count - 3) {
        pt1 = list[index+2].getPt();
        pt2 = list[index+1].getPt();
        if (qAbs(pt2.y() - pt1.y()) < minGap && qAbs(pt2.y() - pt3.y()) < minGap) {
            // 同一水平线
            if (index < count - 3){
                auto x = (list[index+3].pt.x() + list[index-1].pt.x())/2;
                auto y = list[index+2].pt.y();
                attr.updatePoint(list[index+2].id, {x,y});
            }
            attr.removePoint(list[index+1].id);
            attr.removePoint(movedId);
            // updateAttribute(&attr);
            return;
        }
        if (qAbs(pt2.x() - pt1.x()) < minGap && qAbs(pt2.x() - pt3.x()) < minGap) {
            // 同一垂直线
            if (index < count - 3){
                auto x = list[index+2].pt.x();
                auto y = (list[index+3].pt.y() + list[index-1].pt.y())/2;
                attr.updatePoint(list[index+2].id, {x,y});
            }
            attr.removePoint(list[index+1].id);
            attr.removePoint(movedId);
            // updateAttribute(&attr);
            return;
        }
    }
}


qreal VerticalElbow::calcEndRotation(const QList<QPointF> &points, const LineEndType &type) const
{
    if (type.getCategory() == LineEndType::Start) {
        if (points[0].y() < points[1].y()) {
            return 90;
        } else if(points[0].y() == points[1].y()) {
            if (points[0].x() > points[1].x()) {
                return 180;
            }else{
                return 0;
            }
        }else{
            return -90;
        }
    }
    if (type.getCategory() == LineEndType::End) {
        auto count = points.count();
        if (points[count-1].y() > points[count-2].y()) {
            return 90;
        } else if (points[count-1].y() == points[count-2].y()){
            if (points[count-1].x() > points[count-2].x()) {
                return 0;
            }else{
                return 180;
            }
        }else{
            return -90;
        }
    }
    return 0;
}
