#-------------------------------------------------
#
# Project created by QtCreator 2013-06-12T00:05:23
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = logAnalysisToolCPP
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    log_analysis_tool.cpp

HEADERS += \
    log_analysis_tool.h




#INCLUDEPATH += /usr/local/boost_1_54_0
LIBS += /usr/local/lib/libboost_regex.a
