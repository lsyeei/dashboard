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

#include "ilinepath.h"
#include "lineselector.h"
#include <QGuiApplication>
#include <QToolTip>

LineSelector::LineSelector(QList<NamedPoint> points, QGraphicsItem *parent)
    : AbstractSelector(parent)
{
    updatePoints(points);
}

LineSelector::~LineSelector()
{
}

void LineSelector::updatePoints(QList<NamedPoint> points)
{
    if (editing) {
        return;
    }
    setPos(0,0);
    syncTransfrom();
    pointIds.clear();
    foreach (auto item, points) {
        pointIds << item.id;
        if(adjuster[item.id]){
            adjuster[item.id]->setPos(mapToView(item.pt));
            adjuster[item.id]->update();
        }else{
            auto adjustor = addAdjustPoint(item.id, AbstractSelector::POS);
            adjustor->setPos(mapToView(item.pt));
        }
    }
    // 删除不使用的控制点
    adjuster.removeIf([&](QMap<QString, AdjustPoint*>::iterator item){
        if(item.value() && !pointIds.contains(item.key())
            && getAdjustType(item.value()) == AbstractSelector::POS){
            item.value()->disconnect();
            item.value()->deleteLater();
            return true;
        }
        return false;
    });
    update();
}

void LineSelector::updateEditPoint(const QList<NamedPoint> &points)
{
    if (!editable){
        return;
    }
    QSet<QString> idSet;
    foreach (auto item, points) {
            QString id = "edit-" + item.id;
            idSet << id;
            if(adjuster[id]){
                adjuster[id]->setPos(mapToView(item.pt));
                adjuster[id]->update();
            }else{
                auto adjustor = addAdjustPoint(id, AbstractSelector::CUSTOM);
                adjustor->setStyle(PointStyle{PointStyle::Circle, {8,8},
                                              Qt::NoPen,
                                              {"#6029B6F2"}});
                adjustor->setCursor(Qt::CrossCursor);
                adjustor->setPos(mapToView(item.pt));
            }
    }
    // 删除不使用的控制点
    adjuster.removeIf([&](QMap<QString, AdjustPoint*>::iterator item){
        if(item.value() && !idSet.contains(item.key())
            && getAdjustType(item.value()) == AbstractSelector::CUSTOM){
            item.value()->disconnect();
            item.value()->deleteLater();
            return true;
        }
        return false;
    });
    update();
}

QRectF LineSelector::boundingRect() const
{
    auto path = getParentPath();
    if (curveAdjustable && !currentAdjusterId.isEmpty()) {
        path.moveTo(adjuster[currentAdjusterId]->pos());
        if (adjuster[lCurve]) {
            path.lineTo(adjuster[lCurve]->pos());
        }
        if (adjuster[rCurve]) {
            path.lineTo(adjuster[rCurve]->pos());
        }
    }
    return path.boundingRect();
}

void LineSelector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    if (curveAdjustable) {
        paintCurveControl(painter);
    }

    painter->save();
    QPen pen;
    pen.setColor(0x0066aa);
    pen.setWidthF(0.5);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    painter->strokePath(getParentPath(), pen);

    painter->restore();
}

void LineSelector::enableEdit(bool flag)
{
    editable = flag;
}

void LineSelector::onAdjusterMove(const QPointF &from, const QPointF &to)
{
    Q_UNUSED(from)
    auto obj = sender();
    auto adjustor = dynamic_cast<AdjustPoint*>(obj);
    if (adjustor == nullptr) {
        return;
    }
    bool delFlag{false};
    auto type = getAdjustType(adjustor);
    auto id = adjustor->getId();
    if (type == AbstractSelector::POS) {
        // 更改光标样式
        auto pos = mapToView(parentItem()->mapFromScene(to));
        auto index = pointIds.indexOf(id);
        auto pointCount = pointIds.count();
        if (editable) {
            // 判断是否处于删除位置
            QLineF l1{{0,0},{minEditLen+1.0,0}}, l2{{0,0},{minEditLen+1.0,0}};
            if (index == 0) {
                l1.setPoints(pos, adjuster[pointIds[index+1]]->pos());
            } else if(index == pointCount - 1){
                l2.setPoints(pos, adjuster[pointIds[index-1]]->pos());
            }else{
                l1.setPoints(pos, adjuster[pointIds[index+1]]->pos());
                l2.setPoints(pos, adjuster[pointIds[index-1]]->pos());
            }
            auto style = adjustor->style();
            bool mergeFlag{false};
            if (l1.length() <= minEditLen){
                mergeFlag = true;
                mergeId = adjuster[pointIds[index+1]]->getId();
            }else if(l2.length() <= minEditLen){
                mergeFlag = true;
                mergeId = adjuster[pointIds[index-1]]->getId();
            }

            if (mergeFlag){
                // 移动到临近点上
                style.setPen(Qt::NoPen);
                style.setBrush({Qt::red, Qt::SolidPattern});
                adjustor->setOpacity(0.6);
                adjustor->setData(-2, true);
                adjustor->setZValue(1);
                delFlag = true;
            }else{
                style.setPen({Qt::white, 1});
                style.setBrush({"#29B6F2"});
                adjustor->setOpacity(1);
                adjustor->setData(-2, false);
                adjustor->setZValue(0);
                mergeId = "";
            }
            adjustor->setStyle(style);
        }
        adjustor->setPos(pos);
        if (!previewMode) {
            emit pointMoved(id, to);
        }else{
            update();
            prepareGeometryChange();
        }
        // 更新曲线控制点
        updateCurveControl(lCurve, lParam);
        updateCurveControl(rCurve, rParam);
    } else if (type == AbstractSelector::CUSTOM) {
        movedAdjustor.id = adjustor->getId();
        movedAdjustor.pt = mapToView(parentItem()->mapFromScene(to));
        prepareGeometryChange();
        adjustor->setPos(movedAdjustor.pt);
        update();
    } else if(type == CORNER) {
        prepareGeometryChange();
        adjustor->setPos(mapToView(parentItem()->mapFromScene(to)));
        // 取消左右弧度的关联
        if (QGuiApplication::keyboardModifiers() == Qt::AltModifier) {
            if (!lParam.isEmpty()){
                lParam.setAttach(false);
            }
            if (!rParam.isEmpty()){
                rParam.setAttach(false);
            }
        }
        // 弧度调整
        if (!lParam.isEmpty() && lCurve.compare(id) == 0 && !currentAdjusterId.isEmpty()){
            QLineF l{mapFromView(adjuster[currentAdjusterId]->pos()),
                     mapFromView(adjuster[lCurve]->pos())};
            lParam.setAngle(l.angle());
            lParam.setLen(l.length());
            if (lParam.getAttach() && !rParam.isEmpty()) {
                rParam.setAngle(lParam.getAngle() - 180);
                l.setAngle(rParam.getAngle());
                l.setLength(rParam.getLen());
                adjuster[rCurve]->setPos(mapToView(l.p2()));
                emit rightCurveParamChanged(rParam);
            }
            emit leftCurveParamChanged(lParam);
            update();
        } else if (!rParam.isEmpty() && rCurve.compare(id) == 0 && !currentAdjusterId.isEmpty()){
            QLineF l{mapFromView(adjuster[currentAdjusterId]->pos()),
                     mapFromView(adjuster[rCurve]->pos())};
            rParam.setAngle(l.angle());
            rParam.setLen(l.length());
            if (rParam.getAttach() && !lParam.isEmpty()) {
                lParam.setAngle(rParam.getAngle() + 180);
                l.setAngle(lParam.getAngle());
                l.setLength(lParam.getLen());
                adjuster[lCurve]->setPos(mapToView(l.p2()));
                emit leftCurveParamChanged(lParam);
            }
            emit rightCurveParamChanged(rParam);
            update();
        }
    }
    // 显示位置提示
    auto tips = QString("%1, %2").arg(int(to.x())).arg(int(to.y()));
    if (delFlag) {
        tips = tr("合并该点");
    }
    QToolTip::showText(QCursor::pos(), tips);
}

void LineSelector::onAdjusterMoveStart()
{
    auto obj = sender();
    auto adjustor = dynamic_cast<AdjustPoint*>(obj);
    if (adjustor == nullptr) {
        return;
    }
    startPos = adjustor->pos();
    auto type = getAdjustType(adjustor);
    if (type == CORNER) {
        return;
    }
    if (type == POS) {
        removeCurveControl();
        if (curveAdjustable) {
            currentAdjusterId = adjustor->getId();
        }
    }
    if (editable) {
        editing = true;
    }
    emit pointMoveStart(adjustor->getId());
}

void LineSelector::onAdjusterMoveEnd()
{
    movedAdjustor.id = "";
    auto obj = sender();
    auto adjustor = dynamic_cast<AdjustPoint*>(obj);
    if (adjustor == nullptr) {
        return;
    }    
    if (editable) {
        editing = false;
    }
    auto id = adjustor->getId();
    auto type = getAdjustType(adjustor);
    if (previewMode && type == AbstractSelector::POS) {
        emit pointMoved(id, parentItem()->mapToScene(mapFromView(adjustor->pos())));
    }
    if (!editable) {
        emit pointMoveEnd(id);
        return;
    }
    if (type == AbstractSelector::POS) {
        if (adjustor->data(-2).toBool()) {
            // currentAdjusterId = mergeId;
            removeCurveControl();
            mergeId = "";
            // 删除该点
            emit delPoint(id);
        }
    }else if (type == AbstractSelector::CUSTOM) {
        QLineF l{startPos,adjustor->pos()};
        if (l.length() < minEditLen){
            adjustor->setPos(startPos);
            return;
        }

        auto ids = id.split("-");
        emit addPoint(ids[1], mapFromView(movedAdjustor.pt));
        removeCurveControl();
    }
}

void LineSelector::setPreviewMode(bool flag)
{
    previewMode = flag;
}

void LineSelector::enableCurveAdjuster(bool flag)
{
    curveAdjustable = flag;
    if (!flag) {
        currentAdjusterId = "";
    }
}

void LineSelector::setCurveController(const CurveControlParam &left, const CurveControlParam &right)
{
    lParam = left;
    rParam = right;
    updateCurveControl(lCurve, left);
    updateCurveControl(rCurve, right);
}

void LineSelector::setCurrentPoint(const QString &id)
{
    currentAdjusterId = id;
}

QPainterPath LineSelector::getParentPath() const
{
    auto parent = dynamic_cast<ILinePath*>(parentItem());
    // 不使用以下代码，shape()方法可能包含了线宽，selector 不需要线宽
    // if (!previewMode){
    //     return mapToView(parentItem()->shape());
    // }
    QList<QPointF> points;
    int j=-1,k=-1;
    QString insertId{""};
    if (editable && getAdjustType(adjuster[movedAdjustor.id]) == CUSTOM) {
        auto seg = movedAdjustor.id.split("-");
        insertId = seg[1];
    }

    foreach (auto id, pointIds) {
        auto item = adjuster[id];
        auto type = getAdjustType(item);
        if (type == POS) {
            if (item->data(-2).toBool()) {
                // 排除将要删除的点
                k = points.count();
                continue;
            }
            if (editable && !insertId.isEmpty() && item->getId().compare(insertId) == 0) {
                j = points.count();
                points.append(mapFromView(adjuster[movedAdjustor.id]->pos()));
            }
            points.append(mapFromView(item->pos()));
        }
    }
    return mapToView(parent->previewPath(points, QVariant::fromValue(QList<int>({j,k}))));
}

void LineSelector::updateCurveControl(const QString &id, const CurveControlParam &param)
{
    PointStyle style{PointStyle::Rectangle, {8,8}, {Qt::white}, {Qt::lightGray}};
    AdjustPoint *curveControl;
    if (!param.isEmpty()) {
        if (adjuster[id] == nullptr) {
            curveControl = addAdjustPoint(id, CORNER);
            curveControl->setStyle(style);
        }
        curveControl = adjuster[id];
        if (!currentAdjusterId.isEmpty()) {
            // 有调整点被选中，更新曲线控制点的位置
            auto pos = mapFromView(adjuster[currentAdjusterId]->pos());
            QLineF l{pos, pos+QPointF{1,1}};
            l.setLength(param.getLen());
            l.setAngle(param.getAngle());
            curveControl->setPos(mapToView(l.p2()));
            update();
        }
    } else {
        if (adjuster[id]) {
            adjuster[id]->disconnect();
            delete adjuster[id];
            adjuster.remove(id);
        }
    }
}

void LineSelector::removeCurveControl()
{
    prepareGeometryChange();
    if (adjuster[lCurve]) {
        adjuster[lCurve]->disconnect();
        delete adjuster[lCurve];
        adjuster.remove(lCurve);
    }
    if (adjuster[rCurve]) {
        adjuster[rCurve]->disconnect();
        delete adjuster[rCurve];
        adjuster.remove(rCurve);
    }
    currentAdjusterId = "";
}

void LineSelector::paintCurveControl(QPainter *painter)
{
    if (currentAdjusterId.isEmpty()) {
        return;
    }
    painter->save();
    painter->setPen(Qt::lightGray);
    if (adjuster[lCurve]) {
        painter->drawLine(mapToView(adjuster[lCurve]->pos()),
                          mapToView(adjuster[currentAdjusterId]->pos()));
    }
    if (adjuster[rCurve]) {
        painter->drawLine(mapToView(adjuster[rCurve]->pos()),
                          mapToView(adjuster[currentAdjusterId]->pos()));
    }
    painter->restore();
}
