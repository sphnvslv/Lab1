#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QObject>
#include "mainwindow.h"

class TestMainWindow : public QObject
{
    Q_OBJECT
public:
    explicit TestMainWindow(QObject *parent = nullptr);

private slots:
    void testAddComputerWithoutImage();
    void testDeleteComputer();
    void testSearchComputer();
};

#endif // TESTMAINWINDOW_H
