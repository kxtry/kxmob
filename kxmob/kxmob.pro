#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += widgets xml

TARGET = kxmob
TEMPLATE = lib

DEFINES += KXFW_LIB

SOURCES += kxmob.cpp \
    kwidget.cpp \
    kwindow.cpp \
    kspacer.cpp \
    kxmlui.cpp \
    kresource.cpp \
    kutility.cpp \
    khelper.cpp

PRECOMPILED_HEADER = stable.h

HEADERS += kxmob.h\
    kwidget.h \
    kwidget_p.h \
    stable.h \
    kxapi.h \
    kxglobal.h \
    kwindow.h \
    kspacer.h \
    kxmlui.h \
    kresource.h \
    kutility.h \
    khelper.h \
    khelper_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
