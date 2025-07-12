#include "testmainwindow.h"
#include "mainwindow.h"
#include <QtTest/QtTest>

TestMainWindow::TestMainWindow(QObject *parent) : QObject(parent) {}

void TestMainWindow::testAddComputerWithoutImage() {
    MainWindow window;
    int initialRows = window.tableWidget->rowCount();

    window.addComputerToViews("Model", 512, "i7", "");

    QCOMPARE(window.tableWidget->rowCount(), initialRows + 1);
    QCOMPARE(window.listViewModel->rowCount(), initialRows + 1);
    QCOMPARE(window.listWidget->count(), initialRows + 1);

    QTableWidgetItem *item = window.tableWidget->item(initialRows, 0);
    QVERIFY(item);
    QCOMPARE(item->text(), QString("Model"));
}

void TestMainWindow::testDeleteComputer() {
    MainWindow window;
    window.addComputerToViews("Mod", 256, "i5", "");

    int lastRow = window.tableWidget->rowCount() - 1;

    window.tableWidget->selectRow(lastRow);
    window.listView->setCurrentIndex(window.listViewModel->index(lastRow, 0));
    window.listWidget->setCurrentRow(lastRow);

    window.deleteSelectedComputer();

    QCOMPARE(window.tableWidget->rowCount(), lastRow);
    QCOMPARE(window.listViewModel->rowCount(), lastRow);
    QCOMPARE(window.listWidget->count(), lastRow);
}

void TestMainWindow::testSearchComputer() {
    MainWindow window;
    window.addComputerToViews("HP", 1024, "Intel i5", "");
    window.addComputerToViews("Asus", 2048, "Intel i9", "");

    window.searchEdit->setText("Asus");
    window.searchComputer();

    QVERIFY(window.tableWidget->isRowHidden(0));
    QVERIFY(!window.tableWidget->isRowHidden(1));
}

