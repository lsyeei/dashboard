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

#ifndef PATHPLUGINHELPER_H
#define PATHPLUGINHELPER_H

#define PLUGIN_INTERFACE \
public:\
QString id() const override;\
QString name() const override;\
QString group() const override;\
QIcon icon() const override;\
IMovePath *createPath() override;\
IMovePath *createPath(const QString &xml) override;\


#define PLUGIN_DEFINE(PATHITEM, NAME, GROUP, ICON)\
QString PATHITEM##Plugin::id() const\
{\
    return PATHITEM::PATH_ID;\
}\
\
QString PATHITEM##Plugin::name() const\
{\
    return tr(u8##NAME);\
}\
\
QString PATHITEM##Plugin::group() const\
{\
    return tr(u8##GROUP);\
}\
\
QIcon PATHITEM##Plugin::icon() const\
{\
    SvgHelper svg(QString(#ICON));\
    QWidget widget;\
    auto color = widget.palette().brush(QPalette::Text).color();\
    svg.setStrokeColor(color);\
    svg.setFillColor(color);\
    return QIcon(svg.toPixmap());\
}\
\
IMovePath *PATHITEM##Plugin::createPath()\
{\
    return new PATHITEM();\
}\
\
IMovePath *PATHITEM##Plugin::createPath(const QString &xml)\
{\
    return new PATHITEM(xml);\
}\


#define PATH_INTERFACE(CLASS) \
public:\
    static QString PATH_ID;\
    explicit CLASS(QGraphicsItem *parent = nullptr);\
    explicit CLASS(const QString &xml, QGraphicsItem *parent = nullptr);\
\
    QString classId() const override;\
protected:\
    QPainterPath linePath(QList<QPointF> points) const override;\
    void createPredefinedItem() override;\
    void afterCreateSelector(LineSelector *s) override;\


#define PATH_DEFINE(CLASS, ID) \
QString CLASS::PATH_ID = ID;\
CLASS::CLASS(QGraphicsItem *parent)\
    : AbstractLinePath(parent)\
{\
}\
\
CLASS::CLASS(const QString &xml, QGraphicsItem *parent)\
    : AbstractLinePath(parent)\
{\
    parseXML(xml);\
}\
\
QString CLASS::classId() const\
{\
    return PATH_ID;\
}\
\
QPainterPath CLASS::linePath(QList<QPointF> points) const\
{\
    QPainterPath path;\
    return path;\
}\
\
void CLASS::createPredefinedItem()\
{\
}\
\
void CLASS::afterCreateSelector(LineSelector *s)\
{\
}\


#endif // PATHPLUGINHELPER_H
