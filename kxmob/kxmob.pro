#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += widgets

TARGET = kxmob
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += KXFW_LIB

PRECOMPILED_HEADER = stable.h

SOURCES += kxmob.cpp \
    kwidget.cpp \
    widget.cpp

HEADERS += kxmob.h\
        kxmob_global.h \
    kdatadef.h \
    kwidget.h \
    kwidget_p.h \
    widget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
