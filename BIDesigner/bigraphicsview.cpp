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

#include "bigraphicsscene.h"
#include "bigraphicsview.h"
#include "graphicplugingroup.h"
#include "graphicsitemgroup.h"

#include <QWheelEvent>
#include <QTransform>
#include <QMatrix4x4>
#include <QPainterPath>
#include <QLayout>
#include <QScrollBar>
#include <icustomgraphic.h>
#include "igraphicplugin.h"
#include <QStringBuilder>
#include <QXmlStreamWriter>
#include "graphicplugins.h"
#include <QMessageBox>
#include "biundocommand.h"
#include "rectselector.h"
#include <QApplication>
#include <QImageWriter>
#include <QMimeData>
#include <QStyleOptionRubberBand>
#include <QSvgGenerator>
#include <QTime>

BIGraphicsView::BIGraphicsView(QWidget *parent) : QGraphicsView(parent),
    ruler(new RulerWidget(this))
{
    init();
}

BIGraphicsView::BIGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), ruler(new RulerWidget(this))
{
    init();
}

BIGraphicsView::~BIGraphicsView()
{
    // delete layout;
}

bool BIGraphicsView::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        auto p = palette();
        backgroundColor = p.brush(QPalette::Window).color();
        foregroundColor = p.brush(QPalette::WindowText).color();
        fontColor = foregroundColor;
        baseColor = p.brush(QPalette::Button).color();
        ruler->setBackgroundColor(backgroundColor)
            ->setForegroundColor(foregroundColor)
            ->setFontColor(fontColor);
        ruler->update();
        update();
    }
    return QGraphicsView::event(event);
}

QString BIGraphicsView::toXml()
{
    // 添加图元信息
    BIGraphicsScene *localScene = dynamic_cast<BIGraphicsScene *>(scene());
    return localScene->toXml();
}


void BIGraphicsView::loadFromXml(const QString &xml)
{
    // 清除现有图元
    scene()->clear();
    BIGraphicsScene *localScene = dynamic_cast<BIGraphicsScene *>(scene());
    // auto items = localScene->addItems(xml);
    auto items = BIGraphicsScene::toItems(xml);
    localScene->addItems(items);
    // 生成撤销命令
    genUndoCommand(ADD, items);
}

void BIGraphicsView::createGroup()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene == nullptr){
        return;
    }
    auto groupItems = biScene->selectedItems();
    if (groupItems.isEmpty() || groupItems.count() < 2) {
        return;
    }
    // biScene->newGroup(groupItems);
    // 创建可撤销命令
    genUndoCommand(GROUP, groupItems);
    auto group = dynamic_cast<GraphicsItemGroup *>(groupItems.first()->parentItem());
    if (group) {
        connect(group, SIGNAL(undoEvent(QString,QVariant,QVariant)), this, SLOT(undoEventProcessor(QString,QVariant,QVariant)));
    }
}

void BIGraphicsView::destroyGroup()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene == nullptr){
        return;
    }
    auto groupItems = biScene->selectedItems();
    if (groupItems.isEmpty()) {
        return;
    }
    auto item = groupItems.first();
    if (typeid(*item) == typeid(GraphicsItemGroup)) {
        // biScene->ungroup(dynamic_cast<GraphicsItemGroup *>(item));
        // 创建可撤销命令
        genUndoCommand(UNGROUP,{item});
    }
}

void BIGraphicsView::flipGraphic(const QString &actionName)
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene == nullptr) {
        return;
    }
    if (actionName.compare("flipHorizontal") == 0) {
        biScene->flipItem(Qt::Horizontal);
    }else if (actionName.compare("flipVertical") == 0)  {
        biScene->flipItem(Qt::Vertical);
    }
}

void BIGraphicsView::setGraphicZOrder(QString action)
{
    OrderAction itemAction = OrderAction::NONE;
    if (action.compare("toTop") == 0) {
        // 置顶
        itemAction = OrderAction::TOP;
    }
    if (action.compare("toBottom") == 0) {
        // 置底
        itemAction = OrderAction::BOTTOM;
    }
    if (action.compare("toFront") == 0) {
        // 上移
        itemAction = OrderAction::UP;
    }
    if (action.compare("toBack") == 0) {
        // 下移
        itemAction = OrderAction::DOWN;
    }
    if (itemAction == OrderAction::NONE) {
        return;
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene) {
        biScene->setSelectedItemZOrder(itemAction);
    }
}

void BIGraphicsView::setGraphicAlign(QString action)
{
    AlignAction alignAction = AlignAction::NONE;
    if (action.compare("alignLeft") == 0) {
        // 左对齐
        alignAction = AlignAction::LEFT;
    }
    if (action.compare("alignRight") == 0) {
        // 右对齐
        alignAction = AlignAction::RIGHT;
    }
    if (action.compare("alignTop") == 0) {
        // 上对齐
        alignAction = AlignAction::TOP;
    }
    if (action.compare("alignBottom") == 0) {
        // 下对齐
        alignAction = AlignAction::BOTTOM;
    }
    if (action.compare("alignHorizon") == 0) {
        // 水平居中对齐
        alignAction = AlignAction::HORIZON;
    }
    if (action.compare("alignVertical") == 0) {
        // 垂直居中对齐
        alignAction = AlignAction::VERTICAL;
    }
    if (alignAction == AlignAction::NONE) {
        return;
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene) {
        biScene->setItemsAlign(alignAction);
    }
}

void BIGraphicsView::setGraphicDistribute(QString action)
{
    DistributeAction disAction = DistributeAction::NONE;
    if (action.compare("distributeHorizon") == 0) {
        // 水平等距
        disAction = DistributeAction::HORIZON;
    }
    if (action.compare("distributeVertical") == 0) {
        // 左对齐
        disAction = DistributeAction::VERTICAL;
    }
    if (disAction == DistributeAction::NONE) {
        return;
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene) {
        biScene->distributeItems(disAction);
    }
}

void BIGraphicsView::selectAll(bool flag)
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (biScene) {
        biScene->selectAll(flag);
    }
}

void BIGraphicsView::undo()
{
    undoStack.undo();
}

void BIGraphicsView::redo()
{
    undoStack.redo();
}

qreal BIGraphicsView::zoomByStep(qreal step)
{
    qreal multiple = 0.2;
    qreal nextScale = currentScale + step * multiple;
    setCurrentScale(nextScale);
    doZoom();
    return currentScale;
}

qreal BIGraphicsView::zoomByValue(qreal value)
{
    setCurrentScale(value);
    doZoom();
    return currentScale;
}

qreal BIGraphicsView::zoomByType(ZoomType type)
{
    if (type == FITWINDOW) {
        auto ratioW = width() * 0.7 / sceneRect().width();
        auto ratioH = height() * 0.7 / sceneRect().height();
        setCurrentScale(ratioW < ratioH ? ratioW : ratioH);
    }
    if (type == FITWIDTH) {
        setCurrentScale(width() / sceneRect().width());
    }
    doZoom();
    return currentScale;
}

void BIGraphicsView::modifyItemName(QString name)
{
    if (name.isEmpty()) {
        return;
    }
    auto items = scene()->selectedItems();
    if (items.isEmpty() || items.count() > 1){
        return;
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    biScene->setItemName(items.first(), name);
}

PageProperty BIGraphicsView::getPageProperty() const
{
    return pageProperty;
}


void BIGraphicsView::setPageProperty(const PageProperty &newPageProperty)
{
    pageProperty = newPageProperty;
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    biScene->setSceneRect({0, 0, pageProperty.getWidth()*1.0, pageProperty.getHeight()*1.0});
    biScene->setPainter(pageProperty.getBrushProperty(), pageProperty.getPenProperty());
    // 刷新
    setBackgroundBrush(Qt::NoBrush);
}

void BIGraphicsView::setShowGrid(bool flag)
{
    auto pen = pageProperty.getPenProperty();
    if (!flag) {
        lastPenStyle = pen.getStyle();
        pen.setStyle(Qt::NoPen);
        pageProperty.setPenProperty(pen);
    } else {
        pen.setStyle(lastPenStyle);
        pageProperty.setPenProperty(pen);
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    biScene->setPainter(pageProperty.getBrushProperty(), pageProperty.getPenProperty());
    // 刷新
    setBackgroundBrush(Qt::NoBrush);
}

void BIGraphicsView::setShowScale(bool newShowScale)
{
    showScale = newShowScale;
    ruler->show(showScale);
    if (showScale){
        scaleWidth = ruler->getScaleWidth();
    } else {
        scaleWidth = 0;
    }
    updateRuler(size());
}


void BIGraphicsView::setShowRefLine(bool flag)
{
    showRefLine = flag;
}

void BIGraphicsView::setCurrentScale(qreal value)
{
    if (value > maxZoom){
        value = maxZoom;
    }
    if (value < minZoom){
        value = minZoom;
    }
    currentScale = value;
}

QSize BIGraphicsView::selectSize()
{
    auto currentScene = dynamic_cast<BIGraphicsScene*>(scene());
    auto items = currentScene->selectedItems();
    if (items.count() == 0) {
        return QSize{0,0};
    }
    QRectF itemRect{0,0,1,1};
    foreach (auto item, items) {
        itemRect = itemRect.united(item->sceneBoundingRect());
    }
    return itemRect.size().toSize();
}

bool BIGraphicsView::exportToImage(bool selectedScope, const QString &fileName,
                                   const QSize &size, const QColor &bgcolor,
                                   int quality)
{
    QImageWriter writer{fileName};
    writer.setQuality(quality);
    QImage image{size, QImage::Format_ARGB32};
    image.fill(bgcolor);//Qt::transparent);
    QPainter painter{&image};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRect rect{{0,0},size};
    if (selectedScope) {
        // 只保存选中图元
        auto currentScene = dynamic_cast<BIGraphicsScene*>(scene());
        auto items = currentScene->selectedItems();
        if (items.count() <= 0) {
            return false;
        }
        QRectF itemRect{0,0,1,1};
        foreach (auto item, items) {
            itemRect = itemRect.united(item->sceneBoundingRect());
        }
        currentScene->copyItems();
        BIGraphicsScene tempScene;
        tempScene.setSceneRect(0,0,itemRect.width(),itemRect.height());
        tempScene.pastItems({itemRect.width()/2, itemRect.height()/2});
        tempScene.render(&painter, rect, itemRect);
    }else{
        if(scene()->items().count() <= 0){
            return false;
        }
        scene()->clearSelection();
        scene()->render(&painter, rect, sceneRect().toRect());
    }
    return writer.write(image);
}

bool BIGraphicsView::exportToSvg(bool selectedScope, const QString &fileName, const QSize &size)
{
    QSvgGenerator svg;
    svg.setFileName(fileName);
    svg.setSize(size);
    svg.setViewBox(QRect{{0,0}, size});
    QPainter painter{&svg};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    if (selectedScope) {
        // 只导出选中的图形
        auto currentScene = dynamic_cast<BIGraphicsScene*>(scene());
        auto items = currentScene->selectedItems();
        if (items.count() <= 0) {
            return false;
        }
        QRectF itemRect{0,0,1,1};
        foreach (auto item, items) {
            itemRect = itemRect.united(item->sceneBoundingRect());
        }
        currentScene->copyItems();
        BIGraphicsScene tempScene;
        tempScene.setSceneRect(0,0,itemRect.width(),itemRect.height());
        tempScene.pastItems({itemRect.width()/2, itemRect.height()/2});

        tempScene.render(&painter, svg.viewBox(),tempScene.sceneRect());
    } else {
        if(scene()->items().count() <= 0){
            return false;
        }
        scene()->clearSelection();
        scene()->render(&painter, svg.viewBox(),sceneRect().toRect());
    }
    return true;
}

void BIGraphicsView::setDragMode(DragMode mode)
{
    Q_UNUSED(mode)
    // qDebug() << "set drag mode:" << mode;
    // QGraphicsView::setDragMode(mode);
}

void BIGraphicsView::doCopy()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    biScene->copyItems();
}

void BIGraphicsView::doCut()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    biScene->copyItems();
    auto items = biScene->selectedItems();
    biScene->deleteItems(items);
    // 生成撤销命令
    genUndoCommand(DEL, items);
}

void BIGraphicsView::doPast()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    auto items = biScene->pastItems(mapToScene(mapFromGlobal(QCursor::pos()) - QPoint{scaleWidth, scaleWidth}));
    // 生成撤销命令
    genUndoCommand(ADD, items);
}

void BIGraphicsView::doDelete()
{
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    auto items = biScene->selectedItems();
    // 生成撤销命令
    genUndoCommand(DEL, items);
}

void BIGraphicsView::mousePressEvent(QMouseEvent *event)
{    
    QGraphicsView::mousePressEvent(event);
    mousePos = event->position();
    if (currentGraphicItem != nullptr) {
        // 在鼠标点击位置创建图元
        createGraphicsItem(mousePos);
    } else if (!scene()->selectedItems().isEmpty()){
        // 记录可能拖动的图元
        dragItemPos = getItemsPos(scene()->selectedItems());
        if (showRefLine) {
            ruler->setTraceFlag(true);
        }
    }
    if (event->isAccepted()) {
        return;
    }
    mousePressViewPoint = event->position().toPoint();
    mousePressScenePoint = mapToScene(mousePressViewPoint);
    lastMouseMoveScenePoint = mousePressScenePoint;
    if (event->button() == Qt::LeftButton) {
        event->accept();
        rubberBanding = true;
        rubberBandRect = QRect();
        extendSelection = (event->modifiers() & Qt::ControlModifier) != 0;
        auto s = scene();
        if (s && !extendSelection) {
            s->clearSelection();
        }
    }
}

void BIGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (isDrag){
        // 拖动图元结束，生成撤销命令
        BIUndoCommand *command = new BIUndoCommand(dynamic_cast<UndoObject *>(scene()),
           QVariant::fromValue(QPair<QString, QVariant>{"setPos", QVariant::fromValue(dragItemPos)}),
           QVariant::fromValue(QPair<QString, QVariant>{"setPos", QVariant::fromValue(getItemsPos(scene()->selectedItems()))}),
           "pos changed");
        undoStack.push(command);
        isDrag = false;
        if (showRefLine) {
            ruler->setTraceFlag(false);
        }
    }
    if (rubberBanding) {
        auto s = dynamic_cast<BIGraphicsScene*>(scene());
        if (s) {
            QPainterPath selectionArea;
            selectionArea.addPolygon(mapToScene(rubberBandRect));
            selectionArea.closeSubpath();
            s->setSelectionArea(selectionArea,
                                extendSelection?Qt::AddToSelection:Qt::ReplaceSelection,
                                Qt::ContainsItemShape, viewportTransform());
        }
        viewport()->update(rubberBandRegion(viewport(), rubberBandRect));
        rubberBanding = false;
        if (!rubberBandRect.isNull()) {
            rubberBandRect = QRect();
            emit rubberBandChanged(rubberBandRect, QPointF(), QPointF());
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void BIGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMove(event);
    if (event->buttons().testFlag(Qt::MiddleButton) ||
        (event->buttons().testFlag(Qt::LeftButton) && pressKey.contains(Qt::Key_Space))){
        // 鼠标中键按下，或鼠标左键+space键，移动scene
        QPoint pos = event->pos();
        auto vScrollBar = verticalScrollBar();
        if (vScrollBar->isVisible()) {
            vScrollBar->setValue(vScrollBar->value() + mousePos.y() - pos.y());
        }
        auto hScrollBar = horizontalScrollBar();
        if (hScrollBar->isVisible()) {
            hScrollBar->setValue(hScrollBar->value() + mousePos.x() - pos.x());
        }

        mousePos = pos;
        event->accept();
    }
    if (!isDrag && !dragItemPos.isEmpty() && event->buttons().testFlag(Qt::LeftButton)){
        // 测试是否拖动
        auto item = dragItemPos.begin();
        if (item.key() && item.key()->pos() != item.value()) {
            isDrag = true;
        }
    }
    if (isDrag) {
        if (showRefLine) {
            auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
            auto bound = biScene->getUnitBound(biScene->selectedItems());
            ruler->setTraceZone(bound.boundingRect());
        }
    }
    if (event->buttons().testFlag(Qt::LeftButton) && rubberBanding) {
        if ((mousePressViewPoint - event->position().toPoint()).manhattanLength() < QApplication::startDragDistance())
            return;
        viewport()->update(rubberBandRegion(viewport(), rubberBandRect));
        QRect oldRubberband = rubberBandRect;
        const QPoint mp = mapFromScene(mousePressScenePoint);
        const QPoint ep = event->position().toPoint();
        rubberBandRect = QRect(qMin(mp.x(), ep.x()), qMin(mp.y(), ep.y()),
                               qAbs(mp.x() - ep.x()) + 1, qAbs(mp.y() - ep.y()) + 1);
        if (rubberBandRect != oldRubberband || lastRubberbandScenePoint != lastMouseMoveScenePoint) {
            lastRubberbandScenePoint = lastMouseMoveScenePoint;
            emit rubberBandChanged(rubberBandRect, mousePressScenePoint, lastRubberbandScenePoint);
        }
        viewport()->update(rubberBandRegion(viewport(), rubberBandRect));
    }

    if (rubberBanding && !event->buttons()) {
        viewport()->update(rubberBandRegion(viewport(), rubberBandRect));
        rubberBanding = false;
        extendSelection = false;
        if (!rubberBandRect.isNull()) {
            rubberBandRect = QRect();
            emit rubberBandChanged(rubberBandRect, QPointF(), QPointF());
        }
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void BIGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPoint numPixels = event->pixelDelta();
    QPoint numDegrees = event->angleDelta();
    if (pressKey.contains(Qt::Key_Control)) {
        if (!numPixels.isNull()) {
            zoomByStep(numPixels.y() / 120);
        } else if (!numDegrees.isNull()) {
            zoomByStep(numDegrees.y() * 1.0 / 120);
        }
        event->accept();
    }
    if (pressKey.isEmpty()) {
        auto vScrollBar = verticalScrollBar();
        if (vScrollBar->isVisible()) {
            int scrollY = 0;
            if (!numPixels.isNull()) {
                scrollY = numPixels.y();
            } else if (!numDegrees.isNull()) {
                scrollY = numDegrees.y() / 8 / 15;
            }
            int step = vScrollBar->singleStep() * 2;
            scrollY = scrollY > 0 ? step : -step;
            vScrollBar->setValue(vScrollBar->value() + scrollY);
            event->accept();
        }
    }
    QGraphicsView::wheelEvent(event);
}

QRegion BIGraphicsView::rubberBandRegion(const QWidget *widget, const QRect &rect) const
{
    QStyleHintReturnMask mask;
    QStyleOptionRubberBand option;
    option.initFrom(widget);
    option.rect = rect;
    option.opaque = false;
    option.shape = QRubberBand::Rectangle;

    QRegion tmp;
    tmp += rect.adjusted(-1, -1, 1, 1);
    if (widget->style()->styleHint(QStyle::SH_RubberBand_Mask, &option, widget, &mask))
        tmp &= mask.region;
    return tmp;
}

void BIGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    updateRuler(event->size());
}

void BIGraphicsView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    if (event->isAccepted()) {
        return;
    }
    auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
    if (event->modifiers() == Qt::NoModifier) {
        auto items = biScene->selectedItems();
        switch (event->key()) {
        case Qt::Key_Up:
            itemsPos = getItemsPos(items);
            biScene->moveItems(items, {0, -moveStep});
            event->accept();
            break;
        case Qt::Key_Down:
            itemsPos = getItemsPos(items);
            biScene->moveItems(items, {0, moveStep});
            event->accept();
            break;
        case Qt::Key_Left:
            itemsPos = getItemsPos(items);
            biScene->moveItems(items, {-moveStep, 0});
            event->accept();
            break;
        case Qt::Key_Right:
            itemsPos = getItemsPos(items);
            biScene->moveItems(items, {moveStep, 0});
            event->accept();
            break;
        case Qt::Key_Delete:
            doDelete();
            event->accept();
            break;
        default:
            break;
        }
    }else if(event->matches(QKeySequence::SelectAll)){
        biScene->selectAll(true);
        event->accept();
    } else if(event->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier) && event->key() == Qt::Key_A){
        biScene->selectAll(false);
        event->accept();
    } else if(event->matches(QKeySequence::Copy)){
        doCopy();
        event->accept();
    } else if(event->matches(QKeySequence::Paste)){
        doPast();
        event->accept();
    } else if(event->matches(QKeySequence::Cut)){
        doCut();
        event->accept();
    }
    pressKey.insert(event->key());
}

void BIGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    pressKey.remove(event->key());
    if (event->modifiers() == Qt::NoModifier) {
        auto biScene = dynamic_cast<BIGraphicsScene *>(scene());
        auto items = biScene->selectedItems();
        switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
            // 生成撤销命令
            BIUndoCommand *command = new BIUndoCommand(dynamic_cast<UndoObject *>(scene()),
                QVariant::fromValue(QPair<QString, QVariant>{"setPos", QVariant::fromValue(itemsPos)}),
                QVariant::fromValue(QPair<QString, QVariant>{"setPos", QVariant::fromValue(getItemsPos(items))}),
                    "pos changed");
            undoStack.push(command);
            break;
        }
    }
    QGraphicsView::keyReleaseEvent(event);
}


void BIGraphicsView::dragEnterEvent(QDragEnterEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicPluginGroup)) {
        return;
    }
    if (event->mimeData()->hasText()){
        scene()->clearSelection();
        event->acceptProposedAction();
    }
}

void BIGraphicsView::dragMoveEvent(QDragMoveEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicPluginGroup)) {
        return;
    }
    if (event->mimeData()->hasText()){
        event->acceptProposedAction();
    }
}

void BIGraphicsView::dropEvent(QDropEvent *event)
{
    auto obj = event->source();
    if (obj == nullptr || typeid(*obj) != typeid(GraphicPluginGroup)) {
        return;
    }
    const QMimeData *data = event->mimeData();
    if(!data->hasText()){
        return event->ignore();
    }
    auto id = data->text();
    currentGraphicItem = GraphicPlugins::getPluginById(id);
    createByDrop = true;
    createGraphicsItem(event->position());
    event->acceptProposedAction();
}

void BIGraphicsView::drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[])
{
    QGraphicsView::drawItems(painter, numItems, items, options);
}

void BIGraphicsView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());
    if (rubberBanding && !rubberBandRect.isEmpty()) {
        QStyleOptionRubberBand option;
        option.initFrom(viewport());
        option.rect = rubberBandRect;
        option.shape = QRubberBand::Rectangle;

        QStyleHintReturnMask mask;
        if (viewport()->style()->styleHint(QStyle::SH_RubberBand_Mask, &option, viewport(), &mask)) {
            // painter clipping for masked rubberbands
            painter.setClipRegion(mask.region, Qt::IntersectClip);
        }

        viewport()->style()->drawControl(QStyle::CE_RubberBand, &option, &painter, viewport());
    }
}

void BIGraphicsView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx,dy);
    updateRuler(size());
}

void BIGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF paintRect{rect};
    // 扩展绘制区域
    if (horizontalScrollBar()->isVisible()) {
        paintRect.adjust(-contentMargin, 0, contentMargin, 0);
    }
    if (verticalScrollBar()->isVisible()) {
        paintRect.adjust(0, -contentMargin, 0, contentMargin);
    }

    painter->save();
    baseColor.setAlpha(255);
    QBrush brush(baseColor);
    brush.setStyle(Qt::SolidPattern);
    painter->setBrush(brush);
    painter->drawRect(paintRect);
    painter->restore();
    // 场景绘制背景
    try{
        auto biscene = dynamic_cast<BIGraphicsScene*>(scene());
        if (biscene){
            biscene->refreshBackground(this, painter);
            }
    } catch(...){
        qDebug() << "The scene is not subclass of BIGraphicsScene, can not draw scene background.";
    }
}

void BIGraphicsView::graphicItemChangedHandler(IGraphicPlugin *graphicItem)
{
    currentGraphicItem = graphicItem;
    setFocus(Qt::MouseFocusReason);
}

void BIGraphicsView::undoEventProcessor(const QString &text, QVariant undoData, QVariant redoData)
{
    UndoObject *obj = dynamic_cast<UndoObject *>(sender());
    if (obj) {
        BIUndoCommand *command = new BIUndoCommand(obj, undoData, redoData, text);
        undoStack.push(command);
    }

}

void BIGraphicsView::init()
{
    currentGraphicItem = nullptr;
    // 初始化标尺
    ruler->setScaleWidth(scaleWidth)
        ->setScaleStep(scaleStep)
        ->setBackgroundColor(backgroundColor)
        ->setForegroundColor(foregroundColor)
        ->setFontColor(fontColor)
        ->setFontSize(fontSize);
    ruler->show(showScale);
    // 页面属性
    pageProperty.setName(tr("new page"));
    pageProperty.setWidth(sceneRect().width());
    pageProperty.setHeight(sceneRect().height());
    undoStack.setUndoLimit(0);
    // 接受拖放操作
    setAcceptDrops(true);
    // 不使用默认拖动选择动作
    QGraphicsView::setDragMode(QGraphicsView::NoDrag);
}

void BIGraphicsView::updateRuler(const QSize &size)
{
    this->setViewportMargins(scaleWidth,scaleWidth,0,0);
    QRectF rect = sceneRect();
    ruler->setMarkBound({0, qRound(rect.width())}, {0, qRound(rect.height())});
    QPolygonF mapRect = mapFromScene(rect);

    ruler->setViewRect(mapRect.boundingRect().toRect());
    ruler->resize(size + QSize(scaleWidth,scaleWidth));
}

void BIGraphicsView::doZoom()
{
    QTransform transform;
    transform.scale(currentScale, currentScale);
    setTransform(transform);

    QScrollBar *hbar = horizontalScrollBar();
    if (hbar->maximum() > 0) {
        hbar->setRange(hbar->minimum() - contentMargin, hbar->maximum() + contentMargin);
    }
    QScrollBar *vbar = verticalScrollBar();
    if (vbar->maximum() > 0) {
        vbar->setRange(vbar->minimum() - contentMargin, vbar->maximum() + contentMargin);
    }

    updateRuler(size());
    // 通知视图中选中的图元，视图发生改变
    QEvent event(QEvent::Resize);
    for (auto item : scene()->selectedItems()) {
        scene()->sendEvent(item, &event);
    }

    // 缩放消息
    emit zoomEvent(currentScale * 100);
}

void BIGraphicsView::createGraphicsItem(const QPointF &point)
{
    ICustomGraphic *item = currentGraphicItem->createItem();
    if (item == nullptr) {
        return;
    }
    BIGraphicsScene *localScene = dynamic_cast<BIGraphicsScene *>(scene());
    localScene->addEditableItem(item);
    QPointF pos = point;
    if (createByDrop){
        auto itemRect = item->boundingRect();
        auto width = itemRect.width()/2;
        auto height = itemRect.height()/2;
        pos += QPointF{width, height};
        createByDrop = false;
    }
    item->setPos(mapToScene(pos.toPoint()));
    localScene->setItemName(item, currentGraphicItem->name());
    currentGraphicItem = nullptr;
    genUndoCommand(ADD,{item});
    item->setSelected(true);
}


void BIGraphicsView::genUndoCommand(UndoAction action, QList<QGraphicsItem *> items)
{
    QVariant undoData;
    QVariant redoData;
    QString tips;
    auto data = QVariant::fromValue(items);
    if (action == ADD) {
        tips = "add items";
        QPair<QString, QVariant> redoOps{"addItems", data};
        redoData.setValue(redoOps);
        QPair<QString, QVariant> undoOps{"delItems", data};
        undoData.setValue(undoOps);
        // 监听item属性改变事件
        foreach (auto item, items) {
            // QObject *obj = dynamic_cast<QObject *>(item);
            AbstractItem *obj = dynamic_cast<AbstractItem *>(item);
            if (obj) {
                auto rtn = connect(obj, SIGNAL(undoEvent(QString,QVariant,QVariant)),
                       this, SLOT(undoEventProcessor(QString,QVariant,QVariant)));
            }
        }

    } else if (action == DEL){
        tips = "delete items";
        QPair<QString, QVariant> redoOps{"delItems", data};
        redoData.setValue(redoOps);
        QPair<QString, QVariant> undoOps{"addItems", data};
        undoData.setValue(undoOps);
    } else if (action == GROUP){
        tips = "group items";
        QPair<QString, QVariant> redoOps{"newGroup", data};
        redoData.setValue(redoOps);
        QPair<QString, QVariant> undoOps{"ungroup", data};
        undoData.setValue(undoOps);
    } else if (action == UNGROUP){
        tips = "ungroup items";
        QPair<QString, QVariant> redoOps{"ungroup", data};
        redoData.setValue(redoOps);
        auto childs = items[0]->childItems();
        foreach (auto child, childs) {
            //
            if (typeid(*child) == typeid(RectSelector)) {
                childs.removeOne(child);
            }
        }
        QPair<QString, QVariant> undoOps{"newGroup", QVariant::fromValue(childs)};
        undoData.setValue(undoOps);
    }
    BIUndoCommand *command = new BIUndoCommand(dynamic_cast<UndoObject *>(scene()), undoData, redoData, tips);
    undoStack.push(command);
}

QHash<QGraphicsItem *, QPointF> BIGraphicsView::getItemsPos(QList<QGraphicsItem *> items)
{
    QHash<QGraphicsItem *, QPointF> hash;
    foreach (auto item, items) {
        hash[item] = item->pos();
    }
    return hash;
}
