QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chatserver
TEMPLATE = app


SOURCES += main.cpp\
        chatserverwindow.cpp

HEADERS  += chatserverwindow.h

FORMS    += chatserverwindow.ui
