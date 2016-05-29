#-------------------------------------------------
#
# Project created by QtCreator 2016-05-24T23:06:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uishower
TEMPLATE = app

PRECOMPILED_HEADER =

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../kxmob/release/ -lkxmob
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../kxmob/debug/ -lkxmob
else:unix:!macx: LIBS += -L$$OUT_PWD/../kxmob/ -lkxmob

INCLUDEPATH += $$PWD/../kxmob
DEPENDPATH += $$PWD/../kxmob

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../kxmob/release/libkxmob.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../kxmob/debug/libkxmob.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../kxmob/release/kxmob.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../kxmob/debug/kxmob.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../kxmob/libkxmob.a

RESOURCES += \
    uishower.qrc
