#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T18:30:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#PYTHON_LIB = python3.6m
PYTHON_LIB = python2.7
PYTHON_INC = /usr/include/$$PYTHON_LIB

TARGET = control
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    run_thread.cpp

HEADERS += \
        mainwindow.h \
    run_thread.h

FORMS += \
        mainwindow.ui

LIBS += -lqscintilla2_qt5 -l$$PYTHON_LIB
#LIBS += -lPythonQt-Qt5-Python3
LIBS += -lQt5Python27

INCLUDEPATH += $$PYTHON_INC

INCLUDEPATH += /usr/include/Qt5Python27
