QT += core gui widgets testlib
CONFIG += c++11 testcase

QT += testlib
CONFIG += testcase

CONFIG += console
CONFIG(debug, debug|release) {
    DEFINES += RUN_TESTS
}


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    computer.cpp \
    testmainwindow.cpp

HEADERS += \
    mainwindow.h \
    computer.h \
    testmainwindow.h

# Убедитесь, что нет дублирования moc файлов
MOC_DIR = $$PWD/build/moc
OBJECTS_DIR = $$PWD/build/obj
