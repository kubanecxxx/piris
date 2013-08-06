#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T14:08:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = piris
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qdisplay.cpp \


HEADERS  += mainwindow.h \
    qdisplay.h \

DEFINES += KDEBUG


FORMS    += mainwindow.ui \
    qdisplay.ui

include (framework/framework.pri)
include (porting/port.pri)
