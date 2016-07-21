INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
VPATH += $$PWD

HEADERS += pportingabstract.h \
    pkeyevent.h \
    ptouchevent.h \
    ptypes.h \
    passert.h \
    pcolor.h \
    pwidget.h \
    pmaster.h \
    pscreen.h \
    qdebugprint.h \
    pbutton.h \
    pfont.h \
    plabel.h \
    pcheckbox.h \
    pspecialspinbox.h \
    chsprintf.h \
    utils/touch_calibration.h

SOURCES += \
    pkeyevent.cpp \
    ptouchevent.cpp \
    pcolor.cpp \
    pwidget.cpp \
    pmaster.cpp \
    pscreen.cpp \
    qdebugprint.cpp \
    pbutton.cpp \
    pportingabstract.cpp \
    pfont.cpp \
    plabel.cpp \
    pcheckbox.cpp \
    pspecialspinbox.cpp \
    chsprintf.cpp \
    utils/touch_calibration.cpp

DEFINES += PIRIS_USE_CALIBRATOR
