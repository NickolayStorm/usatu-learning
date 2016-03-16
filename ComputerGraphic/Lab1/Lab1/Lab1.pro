#-------------------------------------------------
#
# Project created by QtCreator 2015-09-16T22:10:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app

CONFIG+=C++14

SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    dimensional.cpp \
    complex.cpp

HEADERS  += mainwindow.h \
    controller.h \
    dimensional.h \
    complex.h

FORMS    += mainwindow.ui
