#include "testmainwindow.h"
#include "mainwindow.h"
#include <QtTest/QtTest>

TestMainWindow::TestMainWindow(QObject *parent) : QObject(parent) {}

void TestMainWindow::testAddComputerWithoutImage() {
    MainWindow window;
    int initialRows = window.tableWidget->rowCount();

    window.addComputerToViews("ASUS", 512, "Intel i7", "");

    QCOMPARE(window.tableWidget->rowCount(), initialRows + 1);
    QCOMPARE(window.listViewModel->rowCount(), initialRows + 1);
    QCOMPARE(window.listWidget->count(), initialRows + 1);

    QTableWidgetItem *item = window.tableWidget->item(initialRows, 0);
    QVERIFY(item);
    QCOMPARE(item->text(), QString("ASUS"));
}

void TestMainWindow::testDeleteComputer() {
    MainWindow window;
    window.addComputerToViews("Dell", 256, "AMD Ryzen", "");

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
    window.addComputerToViews("Lenovo", 2048, "Intel i9", "");

    window.searchEdit->setText("lenovo");
    window.searchComputer();

    QVERIFY(window.tableWidget->isRowHidden(0));  // HP
    QVERIFY(!window.tableWidget->isRowHidden(1)); // Lenovo
}

