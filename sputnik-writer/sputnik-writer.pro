#-------------------------------------------------
#
# Project created by QtCreator 2012-11-17T01:09:54
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sputnik-writer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../common/httprequestclass.cpp

HEADERS  += mainwindow.h \
    ../common/httprequestclass.h

FORMS    += mainwindow.ui
