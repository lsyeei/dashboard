QT += core gui xml svg
# QT += gui-private
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = lib
DEFINES += LINEPLUGIN_LIBRARY

DEFINES += QT_DEBUG_DRAW

CONFIG += c++17 plugin

 QMAKE_CXXFLAGS += /MP

TARGET = $$qtLibraryTarget(lineplugin)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/abstractitem.cpp \
    ../common/abstractselector.cpp \
    ../common/adjustpoint.cpp \
    ../common/lineselector.cpp \
    ../common/pointstyle.cpp \
    abstractlineitem.cpp \
    bidirectionalline.cpp \
    bidirectionallineplugin.cpp \
    cubicline.cpp \
    cubiclineplugin.cpp \
    curvedline.cpp \
    curvedlineplugin.cpp \
    dashline.cpp \
    dashlineplugin.cpp \
    directionalline.cpp \
    directionallineplugin.cpp \
    dotline.cpp \
    dotlineplugin.cpp \
    endtypefactory.cpp \
    formfactory.cpp \
    horizontalelbow.cpp \
    horizontalelbowplugin.cpp \
    lineplugincollection.cpp \
    linepropertyform.cpp \
    polygonline.cpp \
    polygonlineplugin.cpp \
    solidline.cpp \
    solidlineplugin.cpp \
    verticalelbow.cpp \
    verticalelbowplugin.cpp

HEADERS += \
    ../common/abstractitem.h \
    ../common/abstractselector.h \
    ../common/adjustpoint.h \
    ../common/baseproperty.h \
    ../common/ilinepath.h \
    ../common/ipropertyform.h \
    ../common/lineselector.h \
    ../common/namedpoint.h \
    ../common/pointstyle.h \
    ../common/curvecontrolparam.h \
    abstractlineitem.h \
    bidirectionalline.h \
    bidirectionallineplugin.h \
    cubicline.h \
    cubiclineplugin.h \
    curvedline.h \
    curvedlineplugin.h \
    dashline.h \
    dashlineplugin.h \
    directionalline.h \
    directionallineplugin.h \
    dotline.h \
    dotlineplugin.h \
    endtypefactory.h \
    formfactory.h \
    horizontalelbow.h \
    horizontalelbowplugin.h \
    linebaseproperty.h \
    lineendtype.h \
    lineplugincollection.h \
    linepropertyform.h \
    polygonline.h \
    polygonlineplugin.h \
    solidline.h \
    solidlineplugin.h \
    verticalelbow.h \
    verticalelbowplugin.h

INCLUDEPATH += \
    ../interface \
    ../common \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = $$PWD/../../BIDesigner/plugins

FORMS += \
    linepropertyform.ui

RESOURCES += \
    lineicons.qrc

INCLUDEPATH += \
    $$PWD/../../BIWidgets/linepropertywidget \
    $$PWD/../../BIWidgets/colorpickerwidget \
    $$PWD/../../BIWidgets/bicomboboxwidget \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../BIWidgets/release/ -lBIWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../BIWidgets/debug/ -lBIWidgetsd
else:unix: LIBS += -L$$OUT_PWD/../../BIWidgets/ -lBIWidgets

win32:CONFIG(release, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/release
else:win32:CONFIG(debug, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/release/libBIWidgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/debug/libBIWidgetsd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/release/BIWidgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/debug/BIWidgetsd.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../BIWidgets/libBIWidgets.a

INCLUDEPATH += $$PWD/../../common
DEPENDPATH += $$PWD/../../common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../../common/ -lcommon

win32:CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../../common/release
else:win32:CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../../common/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/common.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../common/libcommon.a
