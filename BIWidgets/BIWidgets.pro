CONFIG      += plugin
TARGET      = $$qtLibraryTarget(BIWidgets)
TEMPLATE    = lib

HEADERS     = \
    biwidgets.h
SOURCES += \
    biwidgets.cpp
# RESOURCES   = icons.qrc
LIBS        += -L.

QT += designer core svg xml
CONFIG      += c++17

CONFIG += debug_and_release

DEFINES =  COLOR_PICKER_LIB
QMAKE_CXXFLAGS += /MP

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

INCLUDEPATH += \
    colorpickerwidget \
    linepropertywidget \
    fillpropertywidget\
    pospropertywidget \
    bicomboboxwidget \
    textpropertywidget \
    circleslider \
    gradientcolorpicker \

DEPENDPATH += \
    colorpickerwidget \
    linepropertywidget \
    fillpropertywidget\
    pospropertywidget \
    bicomboboxwidget \
    textpropertywidget \
    circleslider \
    gradientcolorpicker \

include(colorpickerwidget/colorpickerwidget.pri)
include(linepropertywidget/lineproperty.pri)
include(fillpropertywidget/fillproperty.pri)
include(pospropertywidget/posproperty.pri)
include(bicomboboxwidget/bicombobox.pri)
include(textpropertywidget/textproperty.pri)
include(circleslider/circleslider.pri)
include(gradientcolorpicker/gradientcolorpicker.pri)

# win32:CONFIG(debug, debug|release): QMAKE_POST_LINK += xcopy /F /E /Y \"$${PWD}/debug/colorpickerplugind.dll\" \"$${PWD}/dll/\"
# else:win32:CONFIG(release, debug|release): QMAKE_POST_LINK += xcopy /F /E /Y \"$${PWD}/release/colorpickerplugin.dll\" \"$${PWD}/dll/\"


INCLUDEPATH += $$PWD/../common

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../common/debug/ -lcommon
else:unix:!macx: LIBS += -L$$OUT_PWD/../common/ -lcommon

win32:CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../common/release
else:win32:CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../common/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/common.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../common/libcommon.a
