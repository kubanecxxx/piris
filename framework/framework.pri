INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += pportingabstract.h \
    pkeyevent.h \
    ptouchevent.h \
    ptypes.h \
    passert.h \
    pcolor.h \
    framework/pwidget.h \
    framework/pmaster.h \
    pscreen.h \
    qdebugprint.h \
    pbutton.h \
    pfont.h \
    framework/plabel.h

SOURCES += \
    pkeyevent.cpp \
    ptouchevent.cpp \
    framework/pcolor.cpp \
    framework/pwidget.cpp \
    framework/pmaster.cpp \
    pscreen.cpp \
    framework/qdebugprint.cpp \
    framework/pbutton.cpp \
    framework/pportingabstract.cpp \
    framework/pfont.cpp \
    framework/plabel.cpp

