QT += core gui widgets testlib
QT += core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Основное приложение
SOURCES += main.cpp \
           mainwindow.cpp \
           settingsdialog.cpp \
           test_hyperbolic.cpp  # Добавлено

HEADERS += mainwindow.h \
           settingsdialog.h \
           test_hyperbolic.h    # Добавлено

FORMS += mainwindow.ui

# Настройки для тестов
CONFIG += testcase

DISTFILES += \
    .gitignore
