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
#include "webitem.h"
#include "webproperty.h"
#include "zoneproperty.h"
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QGraphicsScene>
#include <QTimer>
#include <QThread>
#include <QApplication>

QString WebItem::SHAPE_ID = "WEB_2024";
WebItem::WebItem(QGraphicsItem *parent)
    :AbstractZoneItem(parent)
{
    WebProperty property;
    property.setDragFlag(true);
    property.setType(PageType::CODE);
    QString content = R"(<html><head>web 控件</head><body style="color:white;">
    <div style="border:solid 1px red;border-radius:5px;padding: 5px;font-size:12pt;">
    input your html code, js code, file or url...
    </div>
    </body></html>)";
    property.setContent(content);
    attribute()->setData(QVariant::fromValue(property));
    setSize({80,60});
    connect(this, SIGNAL(WebCreateEvent()), this, SLOT(onNewWeb()), Qt::QueuedConnection);
}

WebItem::WebItem(const QString &xml, QGraphicsItem *parent)
    : WebItem(parent)
{
    parseXML(xml);
}

WebItem::~WebItem()
{
}

QString WebItem::classId() const
{
    return SHAPE_ID;
}

QPainterPath WebItem::shapePath() const
{
    QPainterPath path;
    auto attr = attribute();
    auto arcSize = 0;
    if (attr->getRound()) {
        arcSize = attr->getArcSize();
    }

    path.addRoundedRect(logicRect, arcSize, arcSize);
    return path;
}

void WebItem::sizeChanged(QRectF offsetValue)
{
    AbstractZoneItem::sizeChanged(offsetValue);
    widget->setPos(logicRect.topLeft());
    web->resize(logicRect.size().toSize());
}

QVariant WebItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    auto res = AbstractZoneItem::itemChange(change, value);
    if (change == QGraphicsItem::ItemSceneHasChanged) {
        if(scene()){
            // 下一个消息循环再处理
            emit WebCreateEvent();
        }
    }else if(change == ItemSelectedChange){
        setFlag(QGraphicsItem::ItemClipsChildrenToShape, !value.toBool());
    }
    return res;
}

void WebItem::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    widget->setPos(logicRect.topLeft());
}

void WebItem::onNewWeb()
{
    web = new QWebEngineView();
    web->setWindowFlags(web->windowFlags() | Qt::FramelessWindowHint);
    web->setAttribute(Qt::WA_TranslucentBackground);
    web->setStyleSheet("background:transparent;");
    connect(web, &QWebEngineView::loadFinished, this, [&]{web->show();});

    // 用独立渲染进程 隔离崩溃风险并提升稳定性
    auto settings = web->settings();
    // 禁用插件
    settings->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    // 关本地存储
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, false);
    settings->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, false);
    settings->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, false);
    settings->setAttribute(QWebEngineSettings::WebGLEnabled, false);
    settings->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);
    auto profile = web->page()->profile();
    profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    profile->setCachePath("");
    profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
    // 20M缓存
    profile->setHttpCacheMaximumSize(20*1024*1024);
    web->page()->setBackgroundColor(Qt::transparent);
    web->setAttribute(Qt::WA_OpaquePaintEvent, false);
    // 加载web数据
    auto data = attribute()->getData();
    bool dragMode{true};
    if (!data.isNull()) {
        auto webAttr = data.value<WebProperty>();
        loadWeb(webAttr.getType(), webAttr.getContent());
        dragMode = webAttr.getDragFlag();
    }
    web->resize(logicRect.size().toSize());

    auto webWidget = new QGraphicsProxyWidget(this);
    webWidget->setAttribute(Qt::WA_OpaquePaintEvent);
    webWidget->setWindowFlags(webWidget->windowFlags() | Qt::FramelessWindowHint);
    webWidget->installEventFilter(this);
    webWidget->setWidget(web);
    webWidget->setAcceptedMouseButtons(Qt::LeftButton);
    webWidget->setFlag(QGraphicsItem::ItemIsMovable, false);
    webWidget->setFlag(QGraphicsItem::ItemIsSelectable, false);
    widget.reset(webWidget);
    webWidget->setPos(logicRect.topLeft());
    setDragMode(dragMode);

}

void WebItem::loadWeb(PageType type, const QString &content)
{
    switch (type) {
    case PageType::URL:
    case PageType::FILE:
        web->load(QUrl(content));
        break;
    case PageType::CODE:
        web->setHtml(content);
        break;
    }
}

void WebItem::setDragMode(bool flag)
{
    // 设置 webWidget 下移一层，这样可以拖动控件，但是鼠标消息不会传递给web控件
    widget->setFlag(QGraphicsItem::ItemStacksBehindParent, flag);
    if (flag) {
        setCursor(QCursor(Qt::SizeAllCursor));
    }
}

void WebItem::updateWeb()
{
    // 更新web控件
    auto data = attribute()->getData();
    if (data.isNull()) {
        return;
    }
    auto webAttr = data.value<WebProperty>();
    setDragMode(webAttr.getDragFlag());
    widget->setPos(logicRect.topLeft());
    web->resize(logicRect.size().toSize());
    loadWeb(webAttr.getType(), webAttr.getContent());
}

bool WebItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == widget.data() && event->type() == QEvent::GraphicsSceneMousePress) {
        auto mEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        if (mEvent->button() == Qt::LeftButton){
            auto data = attribute()->getData();
            if (!data.isNull()) {
                auto webAttr = data.value<WebProperty>();
                if (webAttr.getDragFlag()) {
                    setSelected(true);
                }
            }
        }
    }
    return AbstractZoneItem::eventFilter(watched, event);
}

void WebItem::updateAttribute(BaseProperty *attr)
{
    AbstractZoneItem::updateAttribute(attr);
    updateWeb();
}

void WebItem::attributeSwitched(int oldIndex, int newIndex)
{
    web->hide();
    AbstractZoneItem::attributeSwitched(oldIndex, newIndex);
    updateWeb();
}
