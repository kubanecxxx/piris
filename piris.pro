#-------------------------------------------------
#
# Project created by QtCreator 2013-08-06T14:08:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = piris
TEMPLATE = app

DEFINES += KDEBUG DRAWING_MODE_CHANGESONLY FALSE=0 TRUE=!FALSE



include (testing_qt/testing.pri)
include (framework/framework.pri)
include (porting/port.pri)
