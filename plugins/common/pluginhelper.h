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

#ifndef PLUGINHELPER_H
#define PLUGINHELPER_H

#define PLUGIN_INTERFACE \
QString id() const override;\
QString name() const override;\
QString group() const override;\
QString toolTip() const override;\
QString whatsThis() const override;\
QIcon icon() const override;\
ICustomGraphic *createItem() override;\
ICustomGraphic *createItem(const QString &xml) override;\
QWidget *propertyWidget() override;\

#ifdef PROPERTY_WIDGET_IMPL
#define PROPERTY_WIDGET(CLASS_NAME, FORM)
#else
#define PROPERTY_WIDGET(CLASS_NAME, FORM) \
    QWidget *CLASS_NAME::propertyWidget()\
    {\
            return new FORM();\
    }
#endif

#define METHOD_DEFINE(CLASS_NAME, NAME, GROUP, TIP, WHATE, ICON, GRAPHIC, FORM)\
QString CLASS_NAME::id() const\
{\
    return GRAPHIC::SHAPE_ID;\
}\
\
QString CLASS_NAME::name() const\
{\
    return tr(u8##NAME);\
}\
\
QString CLASS_NAME::group() const\
{\
    return tr(u8##GROUP);\
}\
\
QString CLASS_NAME::toolTip() const\
{\
    return tr(u8##TIP);\
}\
\
QString CLASS_NAME::whatsThis() const\
{\
    return tr(u8##WHATE);\
}\
\
QIcon CLASS_NAME::icon() const\
{\
    return QIcon(SvgHelper(QString(#ICON)).toPixmap(SvgHelper::Normal));\
}\
\
ICustomGraphic *CLASS_NAME::createItem()\
{\
    return new GRAPHIC();\
}\
\
ICustomGraphic *CLASS_NAME::createItem(const QString &xml)\
{\
    return new GRAPHIC(xml);\
}\
PROPERTY_WIDGET(CLASS_NAME, FORM)\

#define GRAPHIC_INTERFACE(CLASS) \
public:\
    static QString SHAPE_ID;\
    explicit CLASS(QGraphicsItem *parent = nullptr);\
    explicit CLASS(const QString &xml, QGraphicsItem *parent = nullptr);\
\
    QString classId() const override;\
\
protected:\
    QPainterPath shapePath() const override;\


#endif // PLUGINHELPER_H
