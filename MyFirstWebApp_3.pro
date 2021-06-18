QT  += core network serialport
QT  -= gui

TARGET = MyFirstWebApp_3

CONFIG   += console

TEMPLATE = app

SOURCES += src/main.cpp \
    src/commandController.cpp \
    src/requestmapper.cpp

HEADERS += \
    src/commandController.h \
    src/requestmapper.h

OTHER_FILES += etc/webapp1.ini

include(QtWebApp/httpserver/httpserver.pri)
