QT += core gui widgets testlib
QT += core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += main.cpp \
           mainwindow.cpp \
           settingsdialog.cpp \
           test_hyperbolic.cpp

HEADERS += mainwindow.h \
           settingsdialog.h \
           test_hyperbolic.h

FORMS += mainwindow.ui

CONFIG += testcase

DISTFILES += \
    .gitignore
