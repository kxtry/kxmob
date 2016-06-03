#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:06:24
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uishower
TEMPLATE = app

PRECOMPILED_HEADER =

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

RESOURCES += \
    uishower.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../kxmob/release/ -lkxmob
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../kxmob/debug/ -lkxmob
else:unix: LIBS += -L$$OUT_PWD/../kxmob/ -lkxmob

INCLUDEPATH += $$PWD/../kxmob
DEPENDPATH += $$PWD/../kxmob
