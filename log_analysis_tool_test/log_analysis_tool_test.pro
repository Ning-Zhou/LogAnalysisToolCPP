#-------------------------------------------------
#
# Project created by QtCreator 2013-06-22T20:09:12
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = log_analysis_tool_test
CONFIG   += console
CONFIG   -= app_bundle
QT   += testlib
CONFIG   += debug

TEMPLATE = app

INCLUDEPATH += "../"
SOURCES += log_analysis_tool_test.cpp

SOURCES += "../log_analysis_tool.cpp"

#INCLUDEPATH += /usr/local/boost_1_54_0
LIBS += /usr/local/lib/libboost_regex.a


