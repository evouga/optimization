#-------------------------------------------------
#
# Project created by QtCreator 2013-09-12T10:16:28
#
#-------------------------------------------------

QT       -= core gui

TARGET = optimization
TEMPLATE = lib

DEFINES += OPTIMIZATION_LIBRARY

SOURCES += \
    augmentedlagrangian.cpp

HEADERS += \
    augmentedlagrangian.h \
    optimization.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH += ../ext/eigen
