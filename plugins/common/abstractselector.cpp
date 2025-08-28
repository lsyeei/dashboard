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

#include "abstractselector.h"
#include <QGraphicsScene>
#include <QGraphicsView>

AbstractSelector::AbstractSelector(QGraphicsItem *parent)
    : QGraphicsItem{parent}
{
    setAcceptHoverEvents(true);
    // 不使用父节点的转换，防止graphicvie缩放时控制点一起缩放
    setFlag(QGraphicsItem::ItemIgnoresTransformations,true);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    setObjectName("AbstractSelector");
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    if (parent) {
        setPos(parent->boundingRect().center());
    }

    setTransformOriginPoint({0, 0});
}

AbstractSelector::~AbstractSelector()
{
    disconnect();
}

void AbstractSelector::remove()
{
    disconnect();
    removeAdjusters();
    hide();
    deleteLater();
}

AdjustPoint *AbstractSelector::addAdjustPoint(QString id, AdjustType type)
{
    AdjustPoint *item= new AdjustPoint(id, this);
    item->setData(-1, type);
    adjuster[id] = item;
    connect(item,SIGNAL(moveEvent(QPointF,QPointF)),this,SLOT(onAdjusterMove(QPointF,QPointF)));
    connect(item,SIGNAL(captureEvent()),this,SLOT(onAdjusterMoveStart()));
    connect(item,SIGNAL(releaseEvent()),this,SLOT(onAdjusterMoveEnd()));
    return item;
}

AbstractSelector::AdjustType AbstractSelector::getAdjustType(AdjustPoint *item) const
{
    return AdjustType(item->data(-1).toInt());
}

void AbstractSelector::onAdjusterMoveStart()
{
    auto obj = dynamic_cast<QGraphicsItem *>(sender());
    if (obj == nullptr) {
        return;
    }
    auto data = obj->data(-1);
    if (data.isNull()) {
        return;
    }
    syncTransfrom();
    emit adjustStart(AdjustType(data.toInt()));
}

void AbstractSelector::onAdjusterMoveEnd()
{
    auto obj = dynamic_cast<QGraphicsItem *>(sender());
    if (obj == nullptr) {
        return;
    }
    auto data = obj->data(-1);
    if (data.isNull()) {
        return;
    }
    emit adjustEnd(AdjustType(data.toInt()));
}

void AbstractSelector::removeAdjusters()
{
    prepareGeometryChange();
    foreach (auto item, adjuster) {
        if (item){
            item->setPos({0,0});
            item->hide();
            item->deleteLater();
        }
    }
}

void AbstractSelector::syncTransfrom()
{
    auto parent = parentItem();
    if (parent == nullptr) {
        return;
    }
    auto parentTrans = parent->sceneTransform();
    QTransform trans{parentTrans.m11(), parentTrans.m12(), parentTrans.m13(),
                     parentTrans.m21(), parentTrans.m22(), parentTrans.m23(),
                     0, 0, parentTrans.m33()};
    setTransform(trans);
}

QTransform AbstractSelector::viewTransform() const
{
    QTransform trans;
    if (scene() == nullptr) {
        return trans;
    }
    QList<QGraphicsView *> list = scene()->views();
    if (list.isEmpty()) {
        return trans;
    }
    QGraphicsView *view = nullptr;
    if (list.length() == 1) {
        view = list.first();
    }else{
        for (QGraphicsView *item : list){
            if (item->hasFocus()/*item->underMouse()*/) {
                view = item;
                break;
            }
        }
    }
    if (view != nullptr){
        trans = view->transform();
    }
    return trans;
}

QPointF AbstractSelector::mapToView(const QPointF &pt) const
{
    return viewTransform().map(pt);
}

QPointF AbstractSelector::mapFromView(const QPointF &pt) const
{
    return viewTransform().inverted().map(pt);
}

QRectF AbstractSelector::mapToView(const QRectF &rect) const
{
    return viewTransform().mapRect(rect);
}

QPainterPath AbstractSelector::mapToView(const QPainterPath &path) const
{
    return viewTransform().map(path);
}
