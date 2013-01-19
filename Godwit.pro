#-------------------------------------------------
#
# Project created by QtCreator 2013-01-19T14:00:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Godwit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    point.cpp \
    track.cpp

HEADERS  += mainwindow.h \
    point.h \
    track.h

FORMS    += mainwindow.ui

CONFIG += c++11
