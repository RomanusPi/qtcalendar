#-------------------------------------------------
#
# Project created by QtCreator 2021-03-05T11:58:16
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = telepor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    file.h \
    data.h\
   sms.h\
 database.h

FORMS    += mainwindow.ui
