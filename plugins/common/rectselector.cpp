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

#include "rectselector.h"
#include "qgraphicsscene.h"

#include <QGraphicsView>
#include <QToolTip>
#include <cursorlib.h>


RectSelector::RectSelector(const QRectF &rect, qreal rectBorder, QGraphicsItem *parent)
    :AbstractSelector(parent), rect(rect), parentBorder(rectBorder)
{
    setObjectName("RectSelector");

    radius = 0;
    hasCorner = false;
    sizeOffsetTotal.setX(0);
    sizeOffsetTotal.setY(0);
    syncTransfrom();
    // 创建控制点
    createAdjuster();
    // 初始控制点
    initAdjuster();
}

RectSelector::RectSelector(const QRectF &rect, QGraphicsItem *parent)
    : AbstractSelector(parent), rect(rect)
{
    if (parent) {
        parentBorder = parent->boundingRect().width() - rect.width();
    }
    radius = 0;
    hasCorner = false;
    setObjectName("RectSelector");
    sizeOffsetTotal.setX(0);
    sizeOffsetTotal.setY(0);
    // 创建控制点
    createAdjuster();
    syncTransfrom();
    setPos(rect.center());
    // 初始控制点
    initAdjuster();
}

qreal RectSelector::parentRotation()
{
    qreal angle = 0;
    auto parent = parentItem();
    if (parent == nullptr) {
        return angle;
    }
    QTransform trans = parent->sceneTransform();
    if (trans.isRotating() || trans.isScaling()){
        QLineF line1{{0,0},{1,0}};
        QLineF line2 = trans.map(line1);
        // rectselector 为被调整图元的子项目，父项目旋转时rectselector也设置了旋转角度，
        // 此时sceneTransform为叠加的角度，该角度的一半为父项目的旋转角度
        angle = line2.angleTo(line1);
    }
    return angle;
}

void RectSelector::createAdjuster()
{
    QString sizeAdjuster[] = {"topLeft", "topMid", "topRight",
                              "left", "right",
                              "bottomLeft", "bottomMid", "bottomRight"};
    int cursorAngle[] = {45, 90, -45, 0, 0, -45, 90, 45};
    auto cursor = CursorLib::instance();
    for (int i = 0; i < sizeof(sizeAdjuster) / sizeof(sizeAdjuster[0]); i++) {
        auto id = sizeAdjuster[i];
        addAdjustPoint(id, SIZE)->setCursor(
            cursor->getShape(CursorLib::SizeHorCursor, cursorAngle[i]), true);
    }
    addAdjustPoint("corner", CORNER)->setCursor(Qt::ArrowCursor);
    adjuster["corner"]->setStyle(PointStyle{PointStyle::Rectangle, {8,8},
                                            {Qt::white, 1},{0xFCA000}, 45});

    addAdjustPoint("rotate", ROATATE)->setCursor(Qt::OpenHandCursor, true);
    adjuster["rotate"]->setStyle(PointStyle{PointStyle::Recycle, {13,13},
                                            {QColor(0x29B6F2), 2}, Qt::NoBrush});
}

void RectSelector::initAdjuster()
{
    auto viewRect = mapToView(rect);
    qreal margin = (parentBorder + borderWidth) / 2 + adjuster["topLeft"]->boundingRect().width() / 2;
    QRectF adjusterRect = viewRect.marginsAdded({margin,margin,margin,margin});
    adjuster["topLeft"]->setPos(adjusterRect.topLeft());
    adjuster["topMid"]->setPos(adjusterRect.left() + adjusterRect.width() / 2, adjusterRect.top());
    adjuster["topRight"]->setPos(adjusterRect.topRight());
    adjuster["left"]->setPos(adjusterRect.left(), adjusterRect.top() + adjusterRect.height() / 2);
    adjuster["right"]->setPos(adjusterRect.right(), adjusterRect.top() + adjusterRect.height() / 2);
    adjuster["bottomLeft"]->setPos(adjusterRect.bottomLeft());
    adjuster["bottomMid"]->setPos(adjusterRect.left() + adjusterRect.width() / 2, adjusterRect.bottom());
    adjuster["bottomRight"]->setPos(adjusterRect.bottomRight());

    updateCorner();

    qreal offset = adjuster["topRight"]->boundingRect().width() + adjuster["rotate"]->boundingRect().width() / 2;
    adjuster["rotate"]->setPos(viewRect.topRight() + QPointF(offset, -offset));
}

void RectSelector::updateCorner()
{
    if (hasCorner) {
        auto topRight = mapToView(rect).topRight() + QPointF(-radius, borderWidth + 10);
        adjuster["corner"]->setPos(topRight);
        adjuster["corner"]->show();
    } else {
        adjuster["corner"]->hide();
    }
}

void RectSelector::calcSize(AdjustPoint *obj, const QPointF &from, const QPointF &to)
{

    QPointF moveOffset = to - from;
    // 累计偏移量
    sizeOffsetTotal += moveOffset;
    if(abs(sizeOffsetTotal.x()) < 1 && abs(sizeOffsetTotal.y()) < 1){
        return;
    }
    moveOffset = sizeOffsetTotal;

    QRectF offset(0,0,0,0);
    if (obj == adjuster["topLeft"]) {
        offset.setTopLeft(moveOffset);
    } else if(obj == adjuster["topMid"]){
        offset.setTop(moveOffset.y());
    } else if(obj == adjuster["topRight"]){
        offset.setTopRight(moveOffset);
    } else if(obj == adjuster["left"]){
        offset.setLeft(moveOffset.x());
    } else if(obj == adjuster["right"]){
        offset.setRight(moveOffset.x());
    } else if(obj == adjuster["bottomLeft"]){
        offset.setBottomLeft(moveOffset);
    } else if(obj == adjuster["bottomMid"]){
        offset.setBottom(moveOffset.y());
    } else if(obj == adjuster["bottomRight"]){
        offset.setBottomRight(moveOffset);
    }
    offset = recalcSize(offset);
    // 更新选中框大小
    QRectF newRect = rect.adjusted(offset.left(), offset.top(), offset.right(), offset.bottom());
    if (newRect.width() <= 0 || newRect.height() <= 0){
        return;
    }
    updateRect(newRect);

    // 发出大小改变信号
    emit rectSizeChanged(offset);
    // 清空累计信息
    sizeOffsetTotal.setX(0);
    sizeOffsetTotal.setY(0);
    // 提示宽高
    auto tips = QString("%1, %2").arg(int(newRect.width())).arg(int(newRect.height()));
    QToolTip::showText(QCursor::pos(), tips);
}

QRectF RectSelector::recalcSize(QRectF offset)
{
    if (ratio <= 0) {
        return offset;
    }
    qreal left = offset.left();
    qreal top = offset.top();
    qreal right = offset.right();
    qreal bottom = offset.bottom();
    if (qAbs(left) < qAbs(top)) {
        left = top * ratio;
    } else {
        top = left / ratio;
    }
    if (qAbs(right) < qAbs(bottom)) {
        right = bottom * ratio;
    } else {
        bottom = right / ratio;
    }
    QRectF result{0,0,0,0};
    return result.adjusted(left, top, right, bottom);
}

void RectSelector::calcCorner(const QPointF &from, const QPointF &to)
{
    // 转换为控制框内的坐标，保证只在x轴有位移时调整圆角
    QPointF offset = to - from;
    qreal cornerOffset = offset.x();
    qreal xPos = adjuster["corner"]->x() + cornerOffset;
    qreal newRadius = radius - offset.x();
    if ((offset.x() < 0 && (xPos < 0 || newRadius > rect.height()/2)) ||
        (offset.x() > 0 && newRadius < 0) || offset.x() == 0){
        return;
    }
    // 改变控制点位置
    adjuster["corner"]->setPos(xPos, adjuster["corner"]->y());
    radius = newRadius;
    if (newRadius < 1){
        // 角度过小时直接置为0，保证能绘出直角
        newRadius = 0;
    }
    // 发出信号
    emit rectCornerChanged(newRadius);
    auto tips = QString::asprintf("%.0f",radius);
    QToolTip::showText(QCursor::pos(), tips);
}

void RectSelector::calacRotation(const QPointF &from, const QPointF &to)
{
    // 找到原点
    QPointF origin = parentItem()->transformOriginPoint();
    qreal angle = QLineF(origin, to).angleTo(QLineF(origin, from));
    setRotation(std::fmodf(rotation() + angle, 360));
    foreach (auto item, adjuster) {
        item->setRotation(std::fmodf(item->rotation() + angle, 360));
    }

    emit rectRotateChanged(angle);

    // 提示角度
    qreal value = std::fmodf(parentItem()->rotation(), 360);
    value = value > 180? value-360:value;
    auto tips = QString::asprintf("%.1f°",value);
    QToolTip::showText(QCursor::pos(), tips);
}

QRectF RectSelector::boundingRect() const
{
    qreal margin = borderWidth / 2;
    QRectF mRect = mapToView(rect).marginsAdded(QMarginsF(margin,margin,margin,margin));
    return mRect;
}

void RectSelector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->save();

    QPen pen;
    pen.setWidth(borderWidth);
    pen.setStyle(Qt::DashLine);
    pen.setColor(QColor(borderColor));

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->setPen(pen);
    painter->setBrush(QBrush());
    auto drawRect = mapToView(rect);
    painter->drawRect(drawRect);

    painter->restore();
}

void RectSelector::updateRect(const QRectF &newRect)
{
    prepareGeometryChange();
    rect = newRect;

    setRotation(0);
    syncTransfrom();

    initAdjuster();
    update();
}

void RectSelector::setRadius(const qreal newRadius)
{
    radius = newRadius;
    updateCorner();
}

void RectSelector::showCornerAdjuster(bool show)
{
    hasCorner = show;
    updateCorner();
}

bool RectSelector::keepRatio(bool flag)
{
    if (rect.width() <= 0 || rect.height() <= 0) {
        return false;
    }
    if (flag) {
        ratio = rect.width() / rect.height();
    } else {
        ratio = 0;
    }
    return true;
}

void RectSelector::onAdjusterMove(const QPointF &from, const QPointF &to)
{
    auto point = dynamic_cast<AdjustPoint *>(sender());
    if (point == nullptr) {
        return;
    }
    auto data = point->data(-1);
    if (data.isNull()) {
        return;
    }
    auto parent = parentItem();
    QPointF itemFrom = parent->mapFromScene(from);
    QPointF itemTo = parent->mapFromScene(to);
    if (AdjustType(data.toInt()) == SIZE) {
        calcSize(point, itemFrom, itemTo);
    } else if (AdjustType(data.toInt()) == CORNER) {
        calcCorner(itemFrom, itemTo);
    } else if (AdjustType(data.toInt()) == ROATATE) {
        calacRotation(itemFrom, itemTo);
    }
}

void RectSelector::syncTransfrom()
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
    auto rotation = parentRotation();
    foreach (auto item, adjuster) {
        item->setRotation(rotation);
    }
    // 处理翻转情况
    QString sizeAdjuster[] = {"topLeft", "topMid", "topRight",
                              "left", "right",
                              "bottomLeft", "bottomMid", "bottomRight"};
    QList<qreal> cursorAngle = {45, 90, -45, 0, 0, -45, 90, 45};
    auto m11 = parentTrans.m11();
    auto m22 = parentTrans.m22();
    if ((m11 < 0 && m22 >= 0) || (m22 < 0 && m11 >= 0)) {
        // 翻转
        cursorAngle = {-45, 90, 45, 0, 0, 45, 90, -45};
    }
    auto cursor = CursorLib::instance();
    for (int i = 0; i < sizeof(sizeAdjuster) / sizeof(sizeAdjuster[0]); i++) {
        adjuster[sizeAdjuster[i]]->setCursor(
            cursor->getShape(CursorLib::SizeHorCursor, cursorAngle[i]), true);
    }
}

void RectSelector::setRectBorder(qreal border)
{
    parentBorder = border;
}
