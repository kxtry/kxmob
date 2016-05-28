#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += widgets

TARGET = kxmob
TEMPLATE = lib

CONFIG += staticlib

SOURCES += kxmob.cpp \
    kwidget.cpp

PRECOMPILED_HEADER = stable.h

HEADERS += kxmob.h\
    kwidget.h \
    kwidget_p.h \
    kxmob_global.h \
    stable.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
