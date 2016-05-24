#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT       += widgets

TARGET = kxmob
TEMPLATE = lib

DEFINES += KXMOB_LIBRARY

SOURCES += kxmob.cpp

HEADERS += kxmob.h\
        kxmob_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
