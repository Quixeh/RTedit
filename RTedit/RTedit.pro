#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T21:50:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTedit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DCMFile.cpp \
    DCMHeader.cpp \
    DCMElement.cpp \
    DCMImage.cpp \
    SlotTransfer.cpp

HEADERS  += mainwindow.h \
    DCMFile.h \
    DCMHeader.h \
    DCMElement.h \
    DCMImage.h \
    SlotTransfer.h

FORMS    += mainwindow.ui
