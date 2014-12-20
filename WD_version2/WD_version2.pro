#-------------------------------------------------
#
# Project created by QtCreator 2014-11-16T22:54:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WD_version2
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    user.cpp \
    goods.cpp \
    food.cpp \
    dailynecessities.cpp \
    electronics.cpp \
    buyer.cpp \
    seller.cpp \
    member.cpp

HEADERS  += mainwindow.h \
    user.h \
    goods.h \
    food.h \
    dailynecessities.h \
    electronics.h \
    buyer.h \
    seller.h \
    member.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc

RC_FILE = myapp.rc
