QT += core network serialport
QT -= gui

TARGET = IOController
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mainclass.cpp \
    tcpoutputclass.cpp \
    tcpinputclass.cpp

HEADERS += \
    mainclass.h \
    tcpoutputclass.h \
    tcpinputclass.h

INCLUDEPATH += /usr/lib/arm-linux-gnueabihf
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local
INCLUDEPATH += /usr/include/mysql

win32:CONFIG(release, debug|release): LIBS += -L$$/usr/local/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/local/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$/usr/local/lib/ -lwiringPi

INCLUDEPATH += $$/usr/local/include
DEPENDPATH += $$/usr/local/include

