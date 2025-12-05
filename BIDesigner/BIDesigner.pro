QT       += core gui concurrent svg xml sql
QT += core-private
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += /MP
QT += webenginewidgets
QT += network
#webenginecore

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
# disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../plugins/common/pointstyle.cpp \
    ../plugins/common/adjustpoint.cpp \
    ../plugins/common/abstractselector.cpp \
    ../plugins/common/lineselector.cpp \
    ../plugins/common/rectselector.cpp \
    ../plugins/common/abstractitem.cpp \
    ../plugins/common/abstractzoneitem.cpp \
    animation/abstractparamwidget.cpp \
    animation/animateType.cpp \
    animation/animationfactory.cpp \
    animation/animationform.cpp \
    animation/animationlistview.cpp \
    animation/opacityanimation.cpp \
    animation/paramwidget/blinkparamwidget.cpp \
    animation/paramwidget/moveparamwidget.cpp \
    animation/paramwidget/rotateparamwidget.cpp \
    animation/paramwidget/scaleparamwidget.cpp \
    animation/path/abstractlinepath.cpp \
    animation/path/curvedpath.cpp \
    animation/path/curvedpathplugin.cpp \
    animation/path/linepath.cpp \
    animation/path/linepathplugin.cpp \
    animation/path/movepathfactory.cpp \
    animation/path/polygonpath.cpp \
    animation/path/polygonpathplugin.cpp \
    animation/qgraphicstranslation.cpp \
    animation/tranfromanimation.cpp \
    bigraphicsscene.cpp \
    bigraphicsview.cpp \
    biundocommand.cpp \
    configmaster.cpp \
    customgraphic/abstractusergraphic.cpp \
    customgraphic/userimageitem.cpp \
    customgraphic/userplugingroupdialog.cpp \
    customgraphic/userpluginmanageform.cpp \
    customgraphic/userpluginpropertyform.cpp \
    customgraphic/usersvgitem.cpp \
    datasource/customtreewidget.cpp \
    datasource/datadirdialog.cpp \
    datasource/datasourceform.cpp \
    exportdialog.cpp \
    graphicgroupwidget.cpp \
    graphiclistform.cpp \
    graphicpropertyform.cpp \
    graphicrootwidget.cpp \
    graphicsitemgroup.cpp \
    graphicsmanager.cpp \
    grouppropertyform.cpp \
    main.cpp \
    mainwindow.cpp \
    projectpropertyform.cpp \
    rulerwidget.cpp

HEADERS += \
    ../plugins/common/pointstyle.cpp \
    ../plugins/common/adjustpoint.h \
    ../plugins/common/abstractselector.h \
    ../plugins/common/ilinepath.h \
    ../plugins/common/lineselector.h \
    ../plugins/common/namedpoint.h \
    ../plugins/common/rectselector.h \
    ../plugins/common/baseproperty.h \
    ../plugins/common/zoneproperty.h \
    ../plugins/common/abstractitem.h \
    ../plugins/common/abstractzoneitem.h \
    ../plugins/common/curvecontrolparam.h \
    $$PWD/../common/xmlHelper.h \
    animation/abstractparamwidget.h \
    animation/animateType.h \
    animation/animationParam.h \
    animation/animationfactory.h \
    animation/animationform.h \
    animation/animationlistview.h \
    animation/graphicsrotationex.h \
    animation/opacityanimation.h \
    animation/paramwidget/blinkparamwidget.h \
    animation/paramwidget/moveparamwidget.h \
    animation/paramwidget/rotateparamwidget.h \
    animation/paramwidget/scaleparamwidget.h \
    animation/path/abstractlinepath.h \
    animation/path/curvedpath.h \
    animation/path/curvedpathplugin.h \
    animation/path/imovepath.h \
    animation/path/imovepathplugin.h \
    animation/path/linepath.h \
    animation/path/linepathplugin.h \
    animation/path/linepathproperty.h \
    animation/path/movepathfactory.h \
    animation/path/pathpluginhelper.h \
    animation/path/polygonpath.h \
    animation/path/polygonpathplugin.h \
    animation/qgraphicstranslation.h \
    animation/tranfromanimation.h \
    bigraphicsscene.h \
    bigraphicsview.h \
    biundocommand.h \
    configmaster.h \
    configs.h \
    customgraphic/abstractusergraphic.h \
    customgraphic/userimageitem.h \
    customgraphic/userplugindo.h \
    customgraphic/userplugingroupdialog.h \
    customgraphic/userplugingroupdo.h \
    customgraphic/userplugingroupservice.h \
    customgraphic/userpluginmanageform.h \
    customgraphic/userpluginpropertyform.h \
    customgraphic/userpluginservice.h \
    customgraphic/userplugintype.h \
    customgraphic/usersvgitem.h \
    datasource/customtreewidget.h \
    datasource/datadirdialog.h \
    datasource/datadirdo.h \
    datasource/datadirservice.h \
    datasource/datamarketdo.h \
    datasource/datamarketservice.h \
    datasource/datasourcedo.h \
    datasource/datasourceform.h \
    datasource/datasourceservice.h \
    dbutil/basemapper.h \
    dbutil/baseservice.h \
    dbutil/entity.h \
    dbutil/entitytablemodel.h \
    dbutil/imagedelegate.h \
    dbutil/tablemodelevent.h \
    dbutil/transactionmanager.h \
    exportdialog.h \
    filetemplate.h \
    graphicgroupwidget.h \
    graphiclistform.h \
    graphicpropertyform.h \
    graphicrootwidget.h \
    graphicsitemgroup.h \
    graphicsmanager.h \
    grouppropertyform.h \
    igraphicsscene.h \
    mainwindow.h \
    pageproperty.h \
    projectProperty.h \
    projectpropertyform.h \
    rulerwidget.h

FORMS += \
    animation/animationform.ui \
    customgraphic/userplugingroupdialog.ui \
    customgraphic/userpluginmanageform.ui \
    customgraphic/userpluginpropertyform.ui \
    datasource/datadirdialog.ui \
    datasource/datasourceform.ui \
    exportdialog.ui \
    graphiclistform.ui \
    graphicproperty.ui \
    grouppropertyform.ui \
    mainwindow.ui \
    projectpropertyform.ui

RESOURCES += \
    icons.qrc

INCLUDEPATH += $$PWD/../plugins/interface \
    $$PWD/../common \
    $$PWD/../plugins/common

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../BIWidgets/release/ -lBIWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../BIWidgets/debug/ -lBIWidgetsd
else:unix: LIBS += -L$$OUT_PWD/../BIWidgets/ -lBIWidgets

INCLUDEPATH += \
    $$PWD/../BIWidgets/colorpickerwidget \
    $$PWD/../BIWidgets/fillpropertywidget \
    $$PWD/../BIWidgets/linepropertywidget \
    $$PWD/../BIWidgets/pospropertywidget \
    $$PWD/../BIWidgets/bicomboboxwidget

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../common/release/ -lcommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../common/debug/ -lcommon
else:unix: LIBS += -L$$OUT_PWD/../common/ -lcommon

# INCLUDEPATH += $$PWD/../common
DEPENDPATH += $$PWD/../common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/libcommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/libcommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/release/common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../common/debug/common.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../common/libcommon.a

DISTFILES +=
