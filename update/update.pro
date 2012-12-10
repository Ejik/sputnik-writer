#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T13:06:22
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = update
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    worker.cpp \
    ../common/httprequestclass.cpp

HEADERS += \
    worker.h \
    ../common/httprequestclass.h
