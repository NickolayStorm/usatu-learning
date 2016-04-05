#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T09:06:47
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chees
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cpp\
        mainwindow.cpp \
    piece.cpp \
    allmessages.cpp \
    allocpiece.cpp \
    authorization.cpp \
    database.cpp \
    registration.cpp \
    selectgame.cpp \
    unfinishedgames.cpp \ #\
    newgame.cpp \
    controlwidget.cpp \
    chat.cpp \
    message.cpp \

HEADERS  += mainwindow.h \
    piece.h \
    allocpiece.h \
    allmessages.h \
    authorization.h \
    database.h \
    registration.h \
    selectgame.h \
    unfinishedgames.h \ #\
    newgame.h \
    controlwidget.h \
    chat.h \
    message.h \

FORMS    += mainwindow.ui \
    authorization.ui \
    allmessages.ui \
    registration.ui \
    selectgame.ui \
    unfinishedgames.ui \ #\
    newgame.ui \
    controlwidget.ui \
    chat.ui

RESOURCES += \
    icons.qrc
