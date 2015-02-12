#-------------------------------------------------
#
# Project created by QtCreator 2015-02-06T08:35:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SquaSSH
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    account.cpp \
    accountentry.cpp \
    accountlistmodel.cpp

HEADERS  += mainwindow.h \
    account.h \
    accountentry.h \
    accountlistmodel.h

FORMS    += mainwindow.ui \
    account.ui \
    accountlist.ui

LIBS     += -L/usr/lib64 -lqtermwidget5 -L/usr/local/lib -lqtreetabs-qt5

INCLUDEPATH += /usr/include/qtermwidget5 /usr/local/include/qtreetabs-qt5/
