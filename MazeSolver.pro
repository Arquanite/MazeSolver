#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T10:33:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeSolver
TEMPLATE = app

win32:RC_ICONS += res/icon_128.ico

INCLUDEPATH += $$PWD/headers

TARGET = MazeSolver

isEmpty(PREFIX) {
    PREFIX = /usr/local
}

target.path = $$PREFIX/bin
INSTALLS += target

shortcutfiles.files = res/mazesolver.desktop
shortcutfiles.path = $$PREFIX/share/applications/
INSTALLS += shortcutfiles

iconfile.files = res/mazesolver.png
iconfile.path = $$PREFIX/share/icons/hicolor/48x48/apps/
INSTALLS += iconfile


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

RESOURCES += \
    res/resources.qrc
