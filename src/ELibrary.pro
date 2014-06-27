#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T08:29:51
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ELibrary
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    smartlineedit.cpp \
    bookdialog.cpp \
    mngrconnection.cpp \
    mngrquerys.cpp \
    appresources.cpp \
    listwidgetdialog.cpp \
    listwidgetdialogone.cpp \
    checkcombobox.cpp \
    checklineedit.cpp \
    fileutils.cpp

HEADERS  += mainwidget.h \
    smartlineedit.h \
    bookdialog.h \
    mngrconnection.h \
    mngrquerys.h \
    appresources.h \
    listwidgetdialog.h \
    listwidgetdialogone.h \
    checkcombobox.h \
    checklineedit.h \
    fileutils.h

RESOURCES += \
    fileResources.qrc
