#-------------------------------------------------
#
# Project created by QtCreator 2014-01-04T12:05:22
#
#-------------------------------------------------

QT       -= gui

TARGET = logger
TEMPLATE = lib

DEFINES += LOGGER_LIBRARY

SOURCES += logger.cpp

HEADERS += logger.h\
        logger_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
