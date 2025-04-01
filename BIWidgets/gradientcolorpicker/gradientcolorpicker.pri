HEADERS += \
    $$PWD/colorindicator.h \
    $$PWD/gradientcolorpicker.h \
    $$PWD/gradientcolorpickerform.h \
    $$PWD/gradientcolorpickerplugin.h
SOURCES += \
    $$PWD/colorindicator.cpp \
    $$PWD/gradientcolorpicker.cpp \
    $$PWD/gradientcolorpickerform.cpp \
    $$PWD/gradientcolorpickerplugin.cpp

RESOURCES += \
    $$PWD/gradienticons.qrc

FORMS += \
    $$PWD/gradientcolorpickerform.ui

QT += widgets
