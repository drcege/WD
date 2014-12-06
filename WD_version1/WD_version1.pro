#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T22:54:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WD_version1
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    goods.cpp

HEADERS  += mainwindow.h \
    user.h \
    goods.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
