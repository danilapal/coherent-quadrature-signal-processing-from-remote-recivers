#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T19:26:02
#
#-------------------------------------------------

QT       += core gui widgets network

TARGET = GWAPP_1
TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwidget.cpp \
    radiotools.cpp \
    radio.cpp \
    controller.cpp \
    qcustomplot.cpp \
    application.cpp \
    state.cpp \
    painter.cpp \
    groupbox.cpp \
    radioviewer.cpp \
    client.cpp \
    clientpart.cpp

HEADERS += \
        mainwidget.h \
    G35DDCAPI.h \
    radiotools.h \
    radio.h \
    controller.h \
    qcustomplot.h \
    application.h \
    state.h \
    painter.h \
    groupbox.h \
    radioviewer.h \
    client.h \
    clientpart.h

FORMS += \
        mainwidget.ui \
    groupbox.ui \
    radioviewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
