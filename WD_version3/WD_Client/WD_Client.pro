#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T22:54:23
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WD_version3
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

RC_FILE = myapp.rc
