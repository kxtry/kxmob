#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += widgets

TARGET = kxmob
TEMPLATE = lib

DEFINES += KXFW_LIB

SOURCES += kxmob.cpp \
    kwidget.cpp

PRECOMPILED_HEADER = stable.h

HEADERS += kxmob.h\
    kwidget.h \
    kwidget_p.h \
    stable.h \
    kxapi.h \
    kxglobal.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
