QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += HTTPPLUGIN_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apikeyform.cpp \
    authform.cpp \
    basicauthform.cpp \
    bearertokenform.cpp \
    bodyform.cpp \
    connectform.cpp \
    headerform.cpp \
    httpclient.cpp \
    httpconfig.cpp \
    httpplugin.cpp \
    keyvalueform.cpp \
    oauth2form.cpp \
    queryconfig.cpp \
    queryform.cpp \
    settingform.cpp

HEADERS += \
    abstractsubform.h \
    apikeyform.h \
    auth2config.h \
    authdef.h \
    authform.h \
    basicauthform.h \
    bearertokenform.h \
    bodyform.h \
    connectform.h \
    headerform.h \
    httpbody.h \
    httpclient.h \
    httpconfig.h \
    httpheader.h \
    httpplugin.h \
    keyvalue.h \
    keyvalueform.h \
    oauth2form.h \
    queryconfig.h \
    queryform.h \
    settingform.h

INCLUDEPATH += \
    ../common \
    ../interface \
    ../../common \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

FORMS += \
    apikeyform.ui \
    authform.ui \
    basicauthform.ui \
    bearertokenform.ui \
    bodyform.ui \
    connectform.ui \
    headerform.ui \
    keyvalueform.ui \
    oauth2form.ui \
    queryform.ui \
    settingform.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../../common/ -lcommon

win32:CONFIG(release, debug|release):DEPENDPATH += $$OUT_PWD/../../common/release
else:win32:CONFIG(debug, debug|release):DEPENDPATH += $$OUT_PWD/../../common/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../common/debug/common.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../common/libcommon.a

win32:CONFIG(release, debug|release): DESTDIR = $$PWD/../../BIDesigner/release/dataplugins
else:win32:CONFIG(debug, debug|release): DESTDIR = $$PWD/../../BIDesigner/debug/dataplugins
else:unix: DESTDIR = $$PWD/../../BIDesigner/dataplugins

RESOURCES += \
    httpicons.qrc
