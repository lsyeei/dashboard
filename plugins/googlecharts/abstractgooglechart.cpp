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
#include "abstractgooglechart.h"
#include "chartfactory.h"
#include "chartproperty.h"
#include "qgraphicsproxywidget.h"
#include "qwebengineprofile.h"
#include "qwebenginesettings.h"
#include "qwebengineview.h"

#include <QJsonDocument>

AbstractGoogleChart::AbstractGoogleChart(QGraphicsItem *parent)
    : AbstractZoneItem(parent, false)
{
    attributes[0] = newProperty();
    attributes[0]->setId(0);
    attributes[0]->setName("default");
    attrIndex = 0;
    oldAttr = newProperty();
    setSize({80,60});
    connect(this, SIGNAL(WebCreateEvent()), this, SLOT(onNewWeb()), Qt::QueuedConnection);
}

AbstractGoogleChart::AbstractGoogleChart(const QString &xml, QGraphicsItem *parent)
    : AbstractGoogleChart(parent)
{
    parseXML(xml);
}

QString AbstractGoogleChart::classId() const
{
    return ChartFactory::chartClassId(attribute()->getChartType());
}

ChartProperty *AbstractGoogleChart::attribute() const
{
    auto attr = attributes[attrIndex];
    return dynamic_cast<ChartProperty*>(attr);
}

// void AbstractGoogleChart::updateAttribute(BaseProperty *attr)
// {
//     AbstractZoneItem::updateAttribute(attr);
// }

void AbstractGoogleChart::attributeChanged(const BaseProperty &oldAttr, const BaseProperty &newAttr)
{
    AbstractZoneItem::attributeChanged(oldAttr, newAttr);
    updateWeb();
}

void AbstractGoogleChart::attributeSwitched(int oldIndex, int newIndex)
{
    web->hide();
    AbstractZoneItem::attributeSwitched(oldIndex, newIndex);
    updateWeb();
}

BaseProperty *AbstractGoogleChart::newProperty()
{
    auto attr = new ChartProperty();
    auto pen = attr->getPen();
    pen.setStyle(Qt::NoPen);
    attr->setPen(pen);
    if (attrIndex >= 0 && attributes[attrIndex] != nullptr) {
        attr->copy(*attributes[attrIndex]);
        attr->setId(-1);
        attr->setName("");
    }
    return attr;
}

QVariant AbstractGoogleChart::attr2Variant(const BaseProperty &attr)
{
    auto data = dynamic_cast<const ChartProperty *>(&attr);
    if (data == nullptr) {
        return QVariant::fromValue(attr);
    }
    return QVariant::fromValue(*data);
}

void AbstractGoogleChart::copyProperty(QVariant from, BaseProperty *to)
{
    if (!from.canConvert<ChartProperty>()) {
        return;
    }
    auto f =from.value<ChartProperty>();
    auto t = dynamic_cast<ChartProperty*>(to);
    if (t == nullptr) {
        return;
    }
    t->copy(f);
}

void AbstractGoogleChart::updateGraphic()
{
    AbstractZoneItem::updateGraphic();
    refreshChart();
}

QPainterPath AbstractGoogleChart::shapePath() const
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

QVariant AbstractGoogleChart::itemChange(GraphicsItemChange change, const QVariant &value)
{
    auto res = AbstractZoneItem::itemChange(change, value);
    if (change == QGraphicsItem::ItemSceneHasChanged) {
        if(scene()){
            // 下一个消息循环再处理
            emit WebCreateEvent();
        }
    }
    return res;
}

void AbstractGoogleChart::sizeChanged(QRectF offsetValue)
{
    AbstractZoneItem::sizeChanged(offsetValue);
    widget->setPos(logicRect.topLeft());
    web->resize(logicRect.size().toSize());
}

void AbstractGoogleChart::adjustEnd(AbstractSelector::AdjustType type)
{
    AbstractZoneItem::adjustEnd(type);
    widget->setPos(logicRect.topLeft());
}

void AbstractGoogleChart::onNewWeb()
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
    // 隐藏滚动条
    settings->setAttribute(QWebEngineSettings::ShowScrollBars, false);
    auto profile = web->page()->profile();
    profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
    profile->setCachePath("");
    profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
    // 20M缓存
    profile->setHttpCacheMaximumSize(20*1024*1024);
    web->page()->setBackgroundColor(Qt::transparent);
    web->setAttribute(Qt::WA_OpaquePaintEvent, false);
    // 加载web数据
    auto data = attribute()->getChartType();
    if (!data.isEmpty()) {
        loadWeb();
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
    // 设置 webWidget 下移一层，这样可以拖动控件，但是鼠标消息不会传递给web控件
    widget->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    setCursor(QCursor(Qt::SizeAllCursor));

}

void AbstractGoogleChart::onWebPageLoaded(bool flag)
{
    if (!flag){
        qWarning() << tr("google chart页面加载失败");
        return;
    }
    auto attr = attribute();
    auto page = web->page();
    QString script{R"(
      google.charts.load('51');
      var wrapper;
      function drawChart() {
        // Draw chart
        var chartOptions = JSON.parse('%3');
        wrapper = new google.visualization.ChartWrapper({
          chartType: '%1',
          dataTable: %2,
          options: chartOptions,
          containerId: 'chart_div'
        });
        wrapper.draw();
      }
      // Set a callback to run when the Google Visualization API is loaded.
      google.charts.setOnLoadCallback(drawChart);
    )"};
    auto options = toJsonObject(attr->getOptions());
    options["width"] = attr->getWidth();
    options["height"] = attr->getHeight();
    script = script.arg(attr->getChartType(),
                        attr->getDataTable(),
                        jsonStringify(options));
    page->runJavaScript(script);
}

void AbstractGoogleChart::onPageError(const QWebEngineCertificateError &error)
{
    qWarning() << "页面错误" << error.description();
}

void AbstractGoogleChart::loadWeb()
{
    auto attr = attribute();
    auto chartType = attr->getChartType();
    if (chartType.isEmpty()) {
        return;
    }

    // 启用开发者工具
    // auto devView = new QWebEngineView(web);
    // web->page()->setDevToolsPage(devView->page());
    // devView->resize({800,800});
    // devView->show();

    connect(web, SIGNAL(loadFinished(bool)), this, SLOT(onWebPageLoaded(bool)));
    connect(web->page(), SIGNAL(certificateError(QWebEngineCertificateError)),
            this, SLOT(onPageError(QWebEngineCertificateError)));
    web->setUrl(QUrl("qrc:/html/chart.html"));

    // QFile f(":/html/chart.html");
    // f.open(QIODeviceBase::ReadOnly|QIODeviceBase::Text);
    // auto data = f.readAll();
    // f.close();
    // QString html = QString::fromUtf8(data);
    // auto options = toJsonObject(attr->getOptions());
    // options["width"] = attr->getWidth();
    // options["height"] = attr->getHeight();
    // html = html.arg(attr->getChartType(),
    //                     attr->getDataTable(),
    //                     jsonStringify(options));
    // web->setHtml(html, QUrl("qrc:/html/"));
}


void AbstractGoogleChart::refreshChart()
{
    auto attr = attribute();
    auto page = web->page();
    auto options = toJsonObject(attr->getOptions());
    options["width"] = attr->getWidth();
    options["height"] = attr->getHeight();
    QString script{R"(
  wrapper.setDataTable(%1);
  var options = JSON.parse('%2');
  wrapper.setOptions(options);
  wrapper.draw();
    )"};
    script = script.arg(attr->getDataTable(), jsonStringify(options));
    page->runJavaScript(script);
}

void AbstractGoogleChart::updateWeb()
{
    auto attr = attribute();
    auto chartType = attr->getChartType();
    if (chartType.isEmpty()) {
        return;
    }
    // 更新web控件
    widget->setPos(logicRect.topLeft());
    web->resize(logicRect.size().toSize());
    refreshChart();
}

QJsonObject AbstractGoogleChart::toJsonObject(const QString &data)
{
    auto jsonData = data.toUtf8().trimmed();
    if (jsonData.startsWith("\xEF\xBB\xBF")) {
        jsonData = jsonData.mid(3);
    }
    QJsonParseError parser;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &parser);
    if (parser.error == QJsonParseError::NoError){
        return doc.object();
    }
    qWarning() << "google chart json 解析错误：" << parser.errorString();
    return QJsonObject();
}


QString AbstractGoogleChart::jsonStringify(const QJsonObject &object)
{
    QJsonDocument doc{object};
    return QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
}
