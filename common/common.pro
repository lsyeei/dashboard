QT       += core svg xml
QT       -= gui

TEMPLATE = lib
DEFINES += SVG_HELPER_LIBRARY
DEFINES += EASY_JSON_DEFAULT

CONFIG += c++17
CONFIG += staticlib
QMAKE_CXXFLAGS += /MP

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS     = \
    svghelper.h \
    brushproperty.h \
    cursorlib.h \
    easyjson.h \
    PropertyHelper.h \
    easyjsonimpl.h \
    flowlayout.h \
    ksyntaxhighlighting/include/abstracthighlighter.h \
    ksyntaxhighlighting/include/abstracthighlighter_p.h \
    ksyntaxhighlighting/include/ansihighlighter.h \
    ksyntaxhighlighting/include/context_p.h \
    ksyntaxhighlighting/include/contextswitch_p.h \
    ksyntaxhighlighting/include/definition.h \
    ksyntaxhighlighting/include/definition_p.h \
    ksyntaxhighlighting/include/dynamicregexpcache_p.h \
    ksyntaxhighlighting/include/foldingregion.h \
    ksyntaxhighlighting/include/format.h \
    ksyntaxhighlighting/include/format_p.h \
    ksyntaxhighlighting/include/highlightingdata_p.hpp \
    ksyntaxhighlighting/include/htmlhighlighter.h \
    ksyntaxhighlighting/include/keywordlist_p.h \
    ksyntaxhighlighting/include/ksyntaxhighlighting_export.h \
    ksyntaxhighlighting/include/ksyntaxhighlighting_logging.h \
    ksyntaxhighlighting/include/ksyntaxhighlighting_version.h \
    ksyntaxhighlighting/include/matchresult_p.h \
    ksyntaxhighlighting/include/repository.h \
    ksyntaxhighlighting/include/repository_p.h \
    ksyntaxhighlighting/include/rule_p.h \
    ksyntaxhighlighting/include/state.h \
    ksyntaxhighlighting/include/state_p.h \
    ksyntaxhighlighting/include/syntaxhighlighter.h \
    ksyntaxhighlighting/include/textstyledata_p.h \
    ksyntaxhighlighting/include/theme.h \
    ksyntaxhighlighting/include/themedata_p.h \
    ksyntaxhighlighting/include/wildcardmatcher.h \
    ksyntaxhighlighting/include/worddelimiters_p.h \
    ksyntaxhighlighting/include/xml_p.h \
    paintHelper.h \
    pathimage.h \
    penproperty.h \
    serializable.h \
    snowflake.h \
    svghelperprivate.h \
    svgparser.h \
    syntaxfactory.h \
    textproperty.h \
    variantutil.h \
    xmlHelper.h \
    undoobject.h \
    painterpathex.h \
    svgpathdevice.h \

SOURCES     = svghelper.cpp \
    cursorlib.cpp \
    easyjsonimpl.cpp \
    flowlayout.cpp \
    ksyntaxhighlighting/include/abstracthighlighter.cpp \
    ksyntaxhighlighting/include/ansihighlighter.cpp \
    ksyntaxhighlighting/include/context.cpp \
    ksyntaxhighlighting/include/contextswitch.cpp \
    ksyntaxhighlighting/include/definition.cpp \
    ksyntaxhighlighting/include/foldingregion.cpp \
    ksyntaxhighlighting/include/format.cpp \
    ksyntaxhighlighting/include/highlightingdata.cpp \
    ksyntaxhighlighting/include/htmlhighlighter.cpp \
    ksyntaxhighlighting/include/keywordlist.cpp \
    ksyntaxhighlighting/include/ksyntaxhighlighting_logging.cpp \
    ksyntaxhighlighting/include/repository.cpp \
    ksyntaxhighlighting/include/rule.cpp \
    ksyntaxhighlighting/include/state.cpp \
    ksyntaxhighlighting/include/syntaxhighlighter.cpp \
    ksyntaxhighlighting/include/theme.cpp \
    ksyntaxhighlighting/include/themedata.cpp \
    ksyntaxhighlighting/include/wildcardmatcher.cpp \
    ksyntaxhighlighting/include/worddelimiters.cpp \
    pathimage.cpp \
    serializable.cpp \
    snowflake.cpp \
    svgparser.cpp \
    painterpathex.cpp \
    svgpathdevice.cpp \
    syntaxfactory.cpp

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# DISTFILES += \
#     ksyntaxhighlighting/CMakeLists.txt

RESOURCES += \
    syntax.qrc
