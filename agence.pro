QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT       += sql
QT       -= gui
QT       += charts
QT       += printsupport

TARGET = oracleconnect
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# Uncomment this line to disable deprecated APIs before Qt 6.0.0.
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    calculator.cpp \
    connexion.cpp \
    employe.cpp \
    formation.cpp \
    gestion_employe.cpp \
    gestion_formation.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    stati.cpp \
    stati2.cpp

HEADERS += \
    calculator.h \
    connexion.h \
    employe.h \
    formation.h \
    gestion_employe.h \
    gestion_formation.h \
    login.h \
    mainwindow.h \
    stati.h \
    stati2.h

FORMS += \
    calculator.ui \
    gestion_employe.ui \
    gestion_formation.ui \
    login.ui \
    mainwindow.ui \
    stati.ui \
    stati2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Include the Oracle OCI library for SQL Developer

DISTFILES += \
    2.png \
    logo.png

RESOURCES += \
    image.qrc \
    img.qrc \
    tt.qrc
