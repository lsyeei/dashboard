QT       += core svg xml
QT       -= gui

TEMPLATE = lib
DEFINES += SVG_HELPER_LIBRARY
DEFINES += EASY_JSON_DEFAULT

CONFIG += c++17
CONFIG += staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS     = svghelper.h \
    brushproperty.h \
    cursorlib.h \
    easyjson.h \
    PropertyHelper.h \
    easyjsonimpl.h \
    flowlayout.h \
    ksyntaxhighlighting/abstracthighlighter.h \
    ksyntaxhighlighting/abstracthighlighter_p.h \
    ksyntaxhighlighting/ansihighlighter.h \
    ksyntaxhighlighting/context_p.h \
    ksyntaxhighlighting/contextswitch_p.h \
    ksyntaxhighlighting/definition.h \
    ksyntaxhighlighting/definition_p.h \
    ksyntaxhighlighting/dynamicregexpcache_p.h \
    ksyntaxhighlighting/foldingregion.h \
    ksyntaxhighlighting/format.h \
    ksyntaxhighlighting/format_p.h \
    ksyntaxhighlighting/highlightingdata_p.hpp \
    ksyntaxhighlighting/htmlhighlighter.h \
    ksyntaxhighlighting/keywordlist_p.h \
    ksyntaxhighlighting/ksyntaxhighlighting_export.h \
    ksyntaxhighlighting/ksyntaxhighlighting_logging.h \
    ksyntaxhighlighting/ksyntaxhighlighting_version.h \
    ksyntaxhighlighting/matchresult_p.h \
    ksyntaxhighlighting/repository.h \
    ksyntaxhighlighting/repository_p.h \
    ksyntaxhighlighting/rule_p.h \
    ksyntaxhighlighting/state.h \
    ksyntaxhighlighting/state_p.h \
    ksyntaxhighlighting/syntaxhighlighter.h \
    ksyntaxhighlighting/textstyledata_p.h \
    ksyntaxhighlighting/theme.h \
    ksyntaxhighlighting/themedata_p.h \
    ksyntaxhighlighting/wildcardmatcher.h \
    ksyntaxhighlighting/worddelimiters_p.h \
    ksyntaxhighlighting/xml_p.h \
    paintHelper.h \
    pathimage.h \
    penproperty.h \
    serializable.h \
    snowflake.h \
    svghelperprivate.h \
    svgparser.h \
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
    ksyntaxhighlighting/abstracthighlighter.cpp \
    ksyntaxhighlighting/ansihighlighter.cpp \
    ksyntaxhighlighting/context.cpp \
    ksyntaxhighlighting/contextswitch.cpp \
    ksyntaxhighlighting/definition.cpp \
    ksyntaxhighlighting/foldingregion.cpp \
    ksyntaxhighlighting/format.cpp \
    ksyntaxhighlighting/highlightingdata.cpp \
    ksyntaxhighlighting/htmlhighlighter.cpp \
    ksyntaxhighlighting/keywordlist.cpp \
    ksyntaxhighlighting/ksyntaxhighlighting_logging.cpp \
    ksyntaxhighlighting/repository.cpp \
    ksyntaxhighlighting/rule.cpp \
    ksyntaxhighlighting/state.cpp \
    ksyntaxhighlighting/syntaxhighlighter.cpp \
    ksyntaxhighlighting/theme.cpp \
    ksyntaxhighlighting/themedata.cpp \
    ksyntaxhighlighting/wildcardmatcher.cpp \
    ksyntaxhighlighting/worddelimiters.cpp \
    pathimage.cpp \
    serializable.cpp \
    snowflake.cpp \
    svgparser.cpp \
    painterpathex.cpp \
    svgpathdevice.cpp \

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ksyntaxhighlighting/CMakeLists.txt
