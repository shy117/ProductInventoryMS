#-------------------------------------------------
#
# Project created by QtCreator 2022-12-16T01:34:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProductInventoryMS
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

CONFIG += c++11

SOURCES += \
    main.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    sqlserver.cpp \
    stockpage.cpp \
    homepage.cpp \
    userpage.cpp \
    addstockdialog.cpp \
    modifystockdialog.cpp \
    instockpage.cpp \
    outstockpage.cpp \
    addinstockdialog.cpp \
    modifyinstockdialog.cpp \
    addoutstockdialog.cpp \
    modifyoutstockdialog.cpp

HEADERS += \
    loginwindow.h \
    mainwindow.h \
    sqlserver.h \
    stockpage.h \
    homepage.h \
    userpage.h \
    addstockdialog.h \
    modifystockdialog.h \
    instockpage.h \
    outstockpage.h \
    addinstockdialog.h \
    modifyinstockdialog.h \
    addoutstockdialog.h \
    modifyoutstockdialog.h

FORMS += \
    loginwindow.ui \
    mainwindow.ui \
    stockpage.ui \
    homepage.ui \
    userpage.ui \
    instockpage.ui \
    outstockpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
