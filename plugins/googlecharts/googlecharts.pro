QT  += core gui xml svg concurrent
QT  += webenginewidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

CONFIG += c++17 plugin

TARGET = $$qtLibraryTarget(googlecharts)

SOURCES += \
        ../common/pointstyle.cpp \
        ../common/adjustpoint.cpp \
        ../common/abstractselector.cpp \
        ../common/rectselector.cpp \
        ../common/abstractitem.cpp \
        ../common/abstractzoneitem.cpp \
        ../common/abstracttextitem.cpp \
        abstractgooglechartplugin.cpp \
        chartfactory.cpp \
        chartpropertyform.cpp \
        chartscollection.cpp\
        abstractgooglechart.cpp

HEADERS += \
        ../common/isubwidget.h \
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
        abstractgooglechartplugin.h \
        chartdef.h \
        chartfactory.h \
        chartobject.h \
        chartproperty.h \
        chartpropertyform.h \
        chartscollection.h\
        abstractgooglechart.h

INCLUDEPATH += \
        ../interface \
        ../common \
        $$PWD/../../BIWidgets/fillpropertywidget \
        $$PWD/../../BIWidgets/linepropertywidget \
        $$PWD/../../BIWidgets/pospropertywidget \
        $$PWD/../../BIWidgets/bicomboboxwidget \
        $$PWD/../../BIWidgets/colorpickerwidget \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../BIWidgets/release/ -lBIWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../BIWidgets/debug/ -lBIWidgetsd
else:unix: LIBS += -L$$OUT_PWD/../../BIWidgets/ -lBIWidgets

win32:CONFIG(release, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/release
else:win32:CONFIG(debug, debug|release): DEPENDPATH += $$OUT_PWD/../../BIWidgets/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/release/libBIWidgets.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/debug/libBIWidgetsd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/release/BIWidgets.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../BIWidgets/debug/BIWidgetsd.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../BIWidgets/libBIWidgets.a

INCLUDEPATH += \
    $$PWD/../../common \

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../common/release -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../common/debug -lcommon
else:unix:!macx: LIBS += -L$$OUT_PWD/../../common/release -lcommon

win32:CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../../common/release
else:win32:CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../../common/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/common.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../../common/libcommon.a

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DESTDIR = $$PWD/../../BIDesigner/plugins

RESOURCES += \
    googleicons.qrc

DISTFILES +=

FORMS += \
    chartpropertyform.ui
