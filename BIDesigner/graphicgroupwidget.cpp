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

#include "graphicgroupwidget.h"
#include "customgraphic/userpluginmanageform.h"
#include "flowlayout.h"
#include "graphicrootwidget.h"
#include "svghelper.h"
#include <QApplication>
#include <QCryptographicHash>
#include <QDrag>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QMimeData>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyle>
#include <QToolButton>
#include <igraphicplugin.h>

GraphicGroupWidget::GraphicGroupWidget(QString groupName, qint32 index, QWidget *parent)
    : QWidget{parent}, groupName(groupName)
{
    setParent(parent);
    widgetId = createId(groupName, index);
    setObjectName(widgetId);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    layout = new QVBoxLayout (this);
    layout->setObjectName("layout");
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    titleWidget = new QWidget(this);
    titleWidget->installEventFilter(this);
    layout->addWidget(titleWidget);
    contentWidget = new QWidget(this);
    layout->addWidget(contentWidget);

    // 分组标题
    titleWidget->setObjectName("titlePanel");
    titleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    titleLayout = new QHBoxLayout(titleWidget);
    titleLayout->setContentsMargins(5,6,5,6);
    icon = new QLabel(titleWidget);
    icon->setObjectName("icon");
    icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}
                        .toPixmap(SvgHelper::Normal));
    icon->setScaledContents(true);
    icon->setFixedSize({18,18});
    titleLayout->addWidget(icon);
    title = new QLabel(groupName, titleWidget);
    title->setObjectName("title");
    title->setAlignment(Qt::AlignLeft);
    titleLayout->addWidget(title);
    titleLayout->setAlignment(Qt::AlignLeft);
    titleLayout->setProperty("layoutLeftMargin", 5);

    // 控件集合
    contentWidget->setObjectName("contentPanel");
    contentWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
    contentLayout = new FlowLayout(contentWidget);
    contentLayout->setSizeConstraint(QLayout::SetMinimumSize);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->setVerticalSpacing(6);
    contentLayout->setHorizontalSpacing(6);

    paletteChanged();
}

bool GraphicGroupWidget::addPlugin(IGraphicPlugin *plugin)
{
    if (plugin->name().isEmpty() || plugin->icon().isNull()){
        return false;
    }
    QToolButton * button = new QToolButton(contentWidget);
    contentLayout->addWidget(button);
    int btnWidth = 28;
    button->setFixedWidth(btnWidth);
    button->setFixedHeight(btnWidth);
    button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    button->setPopupMode(QToolButton::DelayedPopup);
    QIcon icon = plugin->icon();
    button->setIcon(icon);
    button->setIconSize({btnWidth, btnWidth});
    button->setText(plugin->name());
    button->setToolTip(plugin->toolTip());
    button->setObjectName("shape_" + plugin->id());

    pluginMap[plugin->id()] = button;

    button->setAcceptDrops(false);
    button->installEventFilter(this);
    return true;
}

void GraphicGroupWidget::itemClicked(QToolButton * button)
{
    auto name = button->objectName();
    if (name.startsWith("shape_")) {
        emit graphicItemClicked(name.right(name.length() - 6));
    }
}

void GraphicGroupWidget::createEditBtns()
{
    if (!editBtn.isNull()) {
        return;
    }

    titleEditor = new QLineEdit();
    titleLayout->addWidget(titleEditor);
    titleEditor->hide();
    connect(titleEditor.data(), SIGNAL(editingFinished()), this, SLOT(onNameEditEnd()));

    titleLayout->addStretch();

    QIcon menuIcon(SvgHelper{QString{":/icons/icons/more-line.svg"}}.toPixmap(SvgHelper::Normal));
    editBtn = new QPushButton(menuIcon, tr(""));
    editBtn->setIconSize({12,12});
    editBtn->setFlat(true);
    editBtn->setMinimumSize({20, 18});
    connect(editBtn.data(), &QPushButton::clicked,
            this, [&](){popMenu->popup(QCursor::pos());});

    titleLayout->addWidget(editBtn);

    popMenu = new QMenu(tr("编辑"),editBtn);
    renameAct = popMenu->addAction(SvgHelper{QString{":/icons/icons/edit-box.svg"}}
                                       .toPixmap(SvgHelper::Normal), tr("修改组名"));
    connect(renameAct.data(), SIGNAL(triggered(bool)), this, SLOT(onEditClicked()));
    delAct = popMenu->addAction(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete), tr("删除组"));
    connect(delAct.data(), SIGNAL(triggered(bool)), this, SLOT(onDeleteClicked()));
    importAct = popMenu->addAction(SvgHelper{QString{":/icons/icons/bottom.svg"}}
                                       .toPixmap(SvgHelper::Normal), tr("导入图元"));
    connect(importAct.data(), SIGNAL(triggered(bool)), this, SLOT(onImportClicked()));
    manageAct = popMenu->addAction(SvgHelper{QString{":/icons/icons/manage.svg"}}
                                       .toPixmap(SvgHelper::Normal), tr("管理图元"));
    connect(manageAct.data(), SIGNAL(triggered(bool)), this, SLOT(onManageClicked()));
}

void GraphicGroupWidget::showEditBtns(bool showFlag)
{
    if (!editBtn.isNull()) {
        return;
    }
    editBtn->setVisible(showFlag);
}

void GraphicGroupWidget::onTitleclicked()
{
    if (contentWidget->isHidden()) {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal));
        contentWidget->show();
    } else {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-right.svg"}}.toPixmap(SvgHelper::Normal));
        contentWidget->hide();
    }
}

void GraphicGroupWidget::onEditClicked()
{
    title->hide();
    titleEditor->setText(groupName);
    titleEditor->show();
    titleEditor->setFocus(Qt::MouseFocusReason);
    titleEditor->selectAll();
}

void GraphicGroupWidget::onDeleteClicked()
{
    if (QMessageBox::question(this, tr("提示"), "确定要删除吗？") == QMessageBox::No){
        return;
    }
    GraphicsManager::instance()->removeGroup(userGroupId);
}

void GraphicGroupWidget::onImportClicked()
{
    auto files = QFileDialog::getOpenFileNames(this, tr("导入图元"), QDir::currentPath(),
                                               "Images (*.svg *.png *.jpg *.bmp *.gif *.jpeg)");
    if (files.isEmpty()) {
        return;
    }
    auto graphics = GraphicsManager::instance()->importGraphics(userGroupId, files);
    // 添加控件
    foreach(auto graphic, graphics){
        addPlugin(graphic);
    }
}

void GraphicGroupWidget::onManageClicked()
{
    if (form == nullptr) {
        form = new UserPluginManageForm(userGroupId, this);
        connect(form, SIGNAL(importEvent(qint32)), this, SLOT(onImportClicked()));
        connect(form, &UserPluginManageForm::dataChanged,
                this, &GraphicGroupWidget::onItemChanged);
        connect(form, &UserPluginManageForm::remove,
                this, &GraphicGroupWidget::onItemRemoved);
    }else{
        form->setGroup(userGroupId);
    }

    form->show();
}

void GraphicGroupWidget::onNameEditEnd()
{
    auto newName = titleEditor->text().trimmed();
    if (newName.isEmpty()) {
        return;
    }
    title->setText(newName);
    auto oldName = groupName;
    groupName = newName;
    titleEditor->hide();
    title->show();
    // 图元管理类更新组名称
    bool flag = GraphicsManager::instance()->updateGroupName(userGroupId, newName);
    if (!flag) {
        setGroupName(oldName);
    }
}

void GraphicGroupWidget::onItemChanged(const UserPluginDO &data)
{
    auto graphic = GraphicsManager::instance()->updateGraphic(data);
    updatePlugin(graphic);
}

void GraphicGroupWidget::onItemRemoved(const UserPluginDO &data)
{
    auto graphicId = GraphicsManager::instance()->removeGraphic(data);
    removePlugin(graphicId);
}

QString GraphicGroupWidget::getWidgetId() const
{
    return widgetId;
}

qint32 GraphicGroupWidget::getUserGroupId() const
{
    return userGroupId;
}

void GraphicGroupWidget::setUserGroupId(qint32 id)
{
    userGroupId = id;
}

void GraphicGroupWidget::setEditable(bool flag)
{
    if (editBtn.isNull() && flag) {
        createEditBtns();
        return;
    }
    editBtn->setVisible(flag);
}

void GraphicGroupWidget::clearGroup()
{
    foreach (auto btn, pluginMap) {
        delete btn;
        btn = nullptr;
    }
    pluginMap.clear();
}

bool GraphicGroupWidget::removePlugin(const QString &graphicId)
{
    auto btn = pluginMap[graphicId];
    if (btn) {
        delete btn;
    }else{
        return false;
    }
    pluginMap.remove(graphicId);
    return true;
}

void GraphicGroupWidget::updatePlugin(IGraphicPlugin *plugin)
{
    auto btn = pluginMap[plugin->id()];
    if (btn) {
        btn->setText(plugin->name());
        btn->setToolTip(plugin->toolTip());
        btn->setIcon(plugin->icon());
    }
}

QString GraphicGroupWidget::createId(QString name, qint32 index)
{
    Q_UNUSED(name)
    // QCryptographicHash hash(QCryptographicHash::Md5);
    // hash.addData(name.toUtf8());
    // return hash.result().toHex();
    return QString::asprintf("group-%d", index);
}

void GraphicGroupWidget::paletteChanged()
{
    auto p = palette();
    auto textColor = p.color(QPalette::Active, QPalette::WindowText).name();//p.brush(QPalette::Text).color().name();
    auto windowColor = p.color(QPalette::Active, QPalette::Window).name();//p.brush(QPalette::Window).color().name();
    auto windowLightColor = p.color(QPalette::Inactive, QPalette::Window).name();//p.brush(QPalette::Light).color().name();
    auto buttonColor = p.brush(QPalette::Button).color().name();
    auto baseColor = p.brush(QPalette::Base).color().name();
    if (windowColor.compare("#000000") == 0) {
        windowColor = "Silver";
    }
    if (windowLightColor.compare("#000000") == 0) {
        windowLightColor = "gray";
    }
    if (buttonColor.compare("#000000") == 0) {
        buttonColor = "gray";
    }
    titleWidget->setStyleSheet("#titlePanel{border-bottom: 1px solid "+buttonColor+
                               "; background:"+windowColor+";} #titlePanel:hover{ background:"+windowLightColor+";}");
    title->setStyleSheet("#title{font-size:10pt; color:"+textColor+";}");

    auto buttonLightColor = p.brush(QPalette::Light).color().name();
    contentWidget->setStyleSheet("#contentPanel{ background-color:"+baseColor+";} QToolButton{border:none;padding:3px;border-radius:5px;}"
                                 "QToolButton:hover{background-color:"+buttonLightColor+"}");
    // 修改图标
    for (const auto &[id,btn]:pluginMap.asKeyValueRange())
    {
        auto plugin = GraphicsManager::instance()->getPluginById(id);
        btn->setIcon(plugin->icon());
    }

    if (contentWidget->isHidden()) {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-right.svg"}}.toPixmap(SvgHelper::Normal));
    } else {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal));
    }
}

QString GraphicGroupWidget::getGroupName() const
{
    return groupName;
}

void GraphicGroupWidget::setGroupName(const QString &name)
{
    title->setText(name);
    groupName = name;
}

bool GraphicGroupWidget::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteChanged();
        event->accept();
        return true;
    }
    return QWidget::event(event);
}

bool GraphicGroupWidget::eventFilter(QObject *watched, QEvent *event)
{
    auto name = watched->objectName();
    if (watched == titleWidget) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto mEvent = dynamic_cast<QMouseEvent*>(event);
            if (mEvent->buttons() & Qt::LeftButton) {
                onTitleclicked();
            }
        }
    } else if (name.startsWith("shape_")) {
        if (event->type() == QEvent::MouseButtonPress) {
            auto mEvent = dynamic_cast<QMouseEvent*>(event);
            if (mEvent->buttons() & Qt::LeftButton) {
                dragStartPosition = mEvent->pos();
                itemClicked(dynamic_cast<QToolButton*>(watched));
                return true;
            }
        } else if(event->type() == QEvent::MouseMove){
            auto mEvent = dynamic_cast<QMouseEvent*>(event);
            if (mEvent->buttons() & Qt::LeftButton) {
                if ((mEvent->pos() - dragStartPosition).manhattanLength()
                    >= QApplication::startDragDistance()){
                    QDrag *drag = new QDrag(this);
                    QMimeData *mimeData = new QMimeData;

                    mimeData->setText(name.right(name.length() - 6));
                    drag->setMimeData(mimeData);
                    auto obj = dynamic_cast<QToolButton*>(watched);
                    QCursor cursor(Qt::ArrowCursor);
                    drag->setDragCursor(cursor.pixmap(), Qt::CopyAction);
                    drag->setPixmap(obj->icon().pixmap(64,64));
                    drag->exec(Qt::CopyAction);
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

