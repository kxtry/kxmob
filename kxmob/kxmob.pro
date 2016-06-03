#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:02:20
#
#-------------------------------------------------

QT += widgets xml

TARGET = kxmob
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += KXFW_LIB
DEFINES += KXFW_STATICLIBA

SOURCES += kxmob.cpp \
    kwidget.cpp \
    kwindow.cpp \
    kspacer.cpp \
    kxmlui.cpp \
    kresource.cpp \
    kutility.cpp \
    khelper.cpp \
    ktheme.cpp \
    colorspace.cpp \
    kimageitem.cpp \
    klabel.cpp \
    klineedit.cpp \
    qlineeditex.cpp \
    kframeitem.cpp \
    ktextitem.cpp

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
    khelper_p.h \
    ktheme.h \
    colorspace.h \
    kimageitem.h \
    klabel.h \
    klineedit.h \
    qlineeditex.h \
    kframeitem.h \
    ktextitem.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
