QT       += core gui xml svg
# QT  += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

CONFIG += c++17 plugin

TARGET = $$qtLibraryTarget(rectplugin)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../common/pointstyle.cpp \
    ../common/adjustpoint.cpp \
    ../common/abstractselector.cpp \
    ../common/rectselector.cpp \
    ../common/abstractitem.cpp \
    ../common/abstractzoneitem.cpp \
    ../common/abstracttextitem.cpp \
    circleitem.cpp \
    circleplugin.cpp \
    diamonditem.cpp \
    diamondplugin.cpp \
    hexagonitem.cpp \
    hexagonplugin.cpp \
    # htmleditorform.cpp \
    obtusetriangleitem.cpp \
    obtusetriangleplugin.cpp \
    octagonitem.cpp \
    octagonplugin.cpp \
    parallelogramitem.cpp \
    parallelogramplugin.cpp \
    pentagonitem.cpp \
    pentagonplugin.cpp \
    pieitem.cpp \
    pieplugin.cpp \
    quadrangleitem.cpp \
    quadrangleplugin.cpp \
    rectitem.cpp \
    rectplugin.cpp \
    rectplugincollection.cpp \
    rectproperty.cpp \
    rectpropertyform.cpp \
    righttrapezoiditem.cpp \
    righttrapezoidplugin.cpp \
    righttriangleplugin.cpp \
    rightttriangleitem.cpp \
    sectoritem.cpp \
    sectorplugin.cpp \
    star4item.cpp \
    star4plugin.cpp \
    star5item.cpp \
    star5plugin.cpp \
    star6item.cpp \
    star6plugin.cpp \
    star8item.cpp \
    star8plugin.cpp \
    trapeziumitem.cpp \
    trapeziumplugin.cpp \
    triangleitem.cpp \
    triangleplugin.cpp \
    textitem.cpp \
    textplugin.cpp \
    textpropertyform.cpp \
    htmlitem.cpp \
    htmlitemplugin.cpp \
    htmlpropertyform.cpp \

HEADERS += \
    ../common/pointstyle.h \
    ../common/adjustpoint.h \
    ../common/abstractselector.h \
    ../common/rectselector.h \
    ../common/abstractitem.h \
    ../common/abstractzoneitem.h \
    ../common/baseproperty.h \
    ../common/zoneproperty.h \
    ../common/abstracttextitem.h \
    ../common/namedpoint.h \
    circleitem.h \
    circleplugin.h \
    diamonditem.h \
    diamondplugin.h \
    hexagonitem.h \
    hexagonplugin.h \
    # htmleditorform.h \
    obtusetriangleitem.h \
    obtusetriangleplugin.h \
    octagonitem.h \
    octagonplugin.h \
    parallelogramitem.h \
    parallelogramplugin.h \
    pentagonitem.h \
    pentagonplugin.h \
    pieitem.h \
    pieplugin.h \
    quadrangleitem.h \
    quadrangleplugin.h \
    rectitem.h \
    rectplugin.h \
    rectplugincollection.h \
    rectproperty.h \
    rectpropertyform.h \
    righttrapezoiditem.h \
    righttrapezoidplugin.h \
    righttriangleplugin.h \
    rightttriangleitem.h \
    sectoritem.h \
    sectorplugin.h \
    star4item.h \
    star4plugin.h \
    star5item.h \
    star5plugin.h \
    star6item.h \
    star6plugin.h \
    star8item.h \
    star8plugin.h \
    trapeziumitem.h \
    trapeziumplugin.h \
    triangleitem.h \
    triangleplugin.h \
    textitem.h \
    textplugin.h \
    textpropertyform.h \
    htmlitem.h \
    htmlitemplugin.h \
    htmlpropertyform.h \

INCLUDEPATH += \
    ../interface \
    ../common \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    # htmleditorform.ui \
    rectpropertyform.ui \
    textpropertyform.ui \
    htmlpropertyform.ui \

RESOURCES += \
    icons.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BIWidgets/release/ -lBIWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BIWidgets/debug/ -lBIWidgetsd
else:unix: LIBS += -L$$OUT_PWD/../../BIWidgets/ -lBIWidgets

INCLUDEPATH += \
    $$PWD/../../BIWidgets/fillpropertywidget \
    $$PWD/../../BIWidgets/linepropertywidget \
    $$PWD/../../BIWidgets/pospropertywidget \
    $$PWD/../../BIWidgets/bicomboboxwidget \
    $$PWD/../../BIWidgets/colorpickerwidget \
    # $$PWD/../../BIWidgets/textpropertywidget \

win32:CONFIG(release, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/release
else:win32:CONFIG(debug, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/debug

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../common/release -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../common/debug -lcommon
else:unix:!macx: LIBS += -L$$OUT_PWD/../../common/release -lcommon

INCLUDEPATH += \
    $$PWD/../../common

win32:CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../../common/release
else:win32:CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../../common/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/common.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../common/release/libcommon.a


# win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += xcopy /F /E /Y \"$${OUT_PWD}/debug/rectplugind.dll\" \"$${PWD}/../../BIDesigner/plugins/\"
# else:win32:CONFIG(release, debug|release): QMAKE_POST_LINK += xcopy /F /E /Y \"$${OUT_PWD}/release/rectplugin.dll\" \"$${PWD}/../../BIDesigner/plugins/\"

# DLLDESTDIR = $$PWD/../../BIDesigner/plugins
DESTDIR = $$PWD/../../BIDesigner/plugins
