#-------------------------------------------------
#
# Project created by QtCreator 2017-06-16T09:00:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankSever
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    message.cpp

HEADERS  += mainwindow.h \
    ApiEx.h \
    userdata.h \
    message.h

FORMS    += mainwindow.ui
FORMS    +=

win32: LIBS += -L$$PWD/./ -lApiEx

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
PRE_TARGETDEPS += $$PWD/./ApiEx.lib

