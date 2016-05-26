#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += core gui
QT += widgets

TARGET = kxmob
TEMPLATE = lib

DEFINES += KXFW_LIB

PRECOMPILED_HEADER = stable.h
SOURCES += kxmob.cpp \
    kwidget.cpp

HEADERS += kxmob.h\
        kxmob_global.h \
    kdatadef.h \
    kwidget.h \
    kwidget_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
