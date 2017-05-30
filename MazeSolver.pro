#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T10:33:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeSolver
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/src
INCLUDEPATH += $$PWD/headers

SOURCES += src/main.cpp \
        src/mainwindow.cpp \
    src/mazeline.cpp \
    src/mazefield.cpp \
    src/labiryntview.cpp \
    src/abstractalgorithm.cpp \
    src/dfsearch.cpp \
    src/randomfirst.cpp \
    src/bfsearch.cpp

HEADERS  += headers/mainwindow.h \
    headers/mazeline.h \
    headers/mazefield.h \
    headers/graf.h \
    headers/labiryntview.h \
    headers/abstractalgorithm.h \
    headers/dfsearch.h \
    headers/randomfirst.h \
    headers/bfsearch.h

FORMS    += forms/mainwindow.ui
