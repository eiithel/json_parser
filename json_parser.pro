QT += core
QT -= gui
QT += network


CONFIG += c++11

TARGET = json_parser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Mains.cpp

DISTFILES += \
    montreal.json \
    googlemap.json \
    test.txt

HEADERS += \
    Mains.h
