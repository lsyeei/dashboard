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

#include "graphicplugingroup.h"
#include "flowlayout.h"
#include "graphicplugins.h"
#include "svghelper.h"
#include <QApplication>
#include <QCryptographicHash>
#include <QDrag>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyle>
#include <QToolButton>
#include <igraphicplugin.h>

GraphicPluginGroup::GraphicPluginGroup(QString groupName, qint32 index, QWidget *parent)
    : QWidget{parent}, groupName(groupName)
{
    widgetId = createId(groupName, index);
    setObjectName(widgetId);
    QSizePolicy policy;
    policy.setHorizontalPolicy(QSizePolicy::Expanding);
    policy.setVerticalPolicy(QSizePolicy::Minimum);
    setSizePolicy(policy);

    layout = new QVBoxLayout (this);
    layout->setObjectName("layout");
    layout->setSizeConstraint(QLayout::SetDefaultConstraint);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    titleWidget = new QWidget(this);
    titleWidget->installEventFilter(this);
    layout->addWidget(titleWidget);
    contentWidget = new QWidget(this);
    layout->addWidget(contentWidget);

    // 分组标题
    titleWidget->setObjectName("titlePanel");
    QSizePolicy titlePolicy;
    titlePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    titlePolicy.setVerticalPolicy(QSizePolicy::Preferred);
    titleWidget->setSizePolicy(titlePolicy);
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
    QSizePolicy contentPolicy;
    contentPolicy.setHorizontalPolicy(QSizePolicy::Expanding);
    contentPolicy.setVerticalPolicy(QSizePolicy::Fixed);
    contentWidget->setSizePolicy(contentPolicy);
    contentLayout = new FlowLayout(contentWidget);
    contentLayout->setSizeConstraint(QLayout::SetMinimumSize);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->setVerticalSpacing(6);
    contentLayout->setHorizontalSpacing(6);

    paletteChanged();
}

bool GraphicPluginGroup::addPlugin(IGraphicPlugin *plugin)
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

    itemWidgetMap[plugin->id()] = button;

    button->setAcceptDrops(false);
    button->installEventFilter(this);
    return true;
}

void GraphicPluginGroup::itemClicked(QToolButton * button)
{
    auto name = button->objectName();
    if (name.startsWith("shape_")) {
        emit graphicItemClicked(name.right(name.length() - 6));
    }
}

void GraphicPluginGroup::createEditBtns()
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
    editBtn->setIconSize({18,18});
    editBtn->setFlat(true);
    editBtn->setMaximumWidth(20);
    editBtn->setMaximumHeight(18);
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
}

void GraphicPluginGroup::showEditBtns(bool showFlag)
{
    if (!editBtn.isNull()) {
        return;
    }
    editBtn->setVisible(showFlag);
}

void GraphicPluginGroup::onTitleclicked()
{
    if (contentWidget->isHidden()) {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal));
        contentWidget->show();
    } else {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-right.svg"}}.toPixmap(SvgHelper::Normal));
        contentWidget->hide();
    }
}

void GraphicPluginGroup::onEditClicked()
{
    title->hide();
    titleEditor->setText(groupName);
    titleEditor->show();
    titleEditor->setFocus(Qt::MouseFocusReason);
    titleEditor->selectAll();
}

void GraphicPluginGroup::onDeleteClicked()
{
    emit removeGroup();
}

void GraphicPluginGroup::onImportClicked()
{
    emit importGraphic(userGroupId);
}

void GraphicPluginGroup::onNameEditEnd()
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
    emit nameChanged(oldName, newName);
}

QString GraphicPluginGroup::getGroupId() const
{
    return widgetId;
}

void GraphicPluginGroup::setUserGroupId(qint32 id)
{
    userGroupId = id;
}

void GraphicPluginGroup::setEditable(bool flag)
{
    if (editBtn.isNull() && flag) {
        createEditBtns();
        return;
    }
    editBtn->setVisible(flag);
}

QString GraphicPluginGroup::createId(QString name, qint32 index)
{
    // QCryptographicHash hash(QCryptographicHash::Md5);
    // hash.addData(name.toUtf8());
    // return hash.result().toHex();
    return QString::asprintf("group-%d", index);
}

void GraphicPluginGroup::paletteChanged()
{
    auto p = palette();
    auto textColor = p.brush(QPalette::Text).color().name();
    auto windowColor = p.brush(QPalette::Window).color().name();
    auto windowLightColor = p.brush(QPalette::Light).color().name();
    auto buttonColor = p.brush(QPalette::Button).color().name();
    auto baseColor = p.brush(QPalette::Base).color().name();
    titleWidget->setStyleSheet("#titlePanel{border-bottom: 1px solid "+buttonColor+
                               "; background:"+windowColor+";} #titlePanel:hover{ background:"+windowLightColor+";}");
    title->setStyleSheet("#title{font-size:10pt; color:"+textColor+";}");

    auto buttonLightColor = p.brush(QPalette::Light).color().name();
    contentWidget->setStyleSheet("#contentPanel{ background-color:"+baseColor+";} QToolButton{border:none;padding:3px;border-radius:5px;}"
                                 "QToolButton:hover{background-color:"+buttonLightColor+"}");
    // 修改图标
    for (auto item = itemWidgetMap.cbegin(); item != itemWidgetMap.cend(); item++)
    {
        auto plugin = GraphicPlugins::getPluginById(item.key());
        item.value()->setIcon(plugin->icon());
    }

    if (contentWidget->isHidden()) {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-right.svg"}}.toPixmap(SvgHelper::Normal));
    } else {
        icon->setPixmap(SvgHelper{QString{":/icons/icons/arrow-down.svg"}}.toPixmap(SvgHelper::Normal));
    }
}

QString GraphicPluginGroup::getGroupName() const
{
    return groupName;
}

void GraphicPluginGroup::setGroupName(const QString &name)
{
    title->setText(name);
    groupName = name;
}

bool GraphicPluginGroup::event(QEvent *event)
{
    if (event->type() == QEvent::PaletteChange) {
        paletteChanged();
        event->accept();
        return true;
    }
    return QWidget::event(event);
}

bool GraphicPluginGroup::eventFilter(QObject *watched, QEvent *event)
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
