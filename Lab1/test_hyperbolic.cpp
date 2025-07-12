#include "test_hyperbolic.h"
#include "mainwindow.h"
#include <QTest>
#include <cmath>
#include <QDateTime>
#include <QDir>

TestHyperbolic::TestHyperbolic(QObject *parent) : QObject(parent) {}

void TestHyperbolic::testSinhCalculation()
{
    MainWindow window;
    qreal result = window.calculateHyperbolicFunc("sinh", 1.0);
    QCOMPARE(result, sinh(1.0));
}

void TestHyperbolic::testCothZeroDivision()
{
    MainWindow window;
    try {
        window.calculateHyperbolicFunc("coth", 0.0);
        QFAIL("Должно было вызвать исключение");
    } catch (...) {
        QVERIFY(true);
    }
}
void TestHyperbolic::testFileLogging()
{
    QString testLogPath = "test_hyperbolic_log_" +
                          QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") +
                          ".txt";

    MainWindow window;
    QString originalLogPath = window.logFileName;
    window.logFileName = testLogPath;
    window.toggleFileOperations(true);

    if (QFile::exists(testLogPath)) {
        QVERIFY(QFile::remove(testLogPath));
    }

    window.calculateAndLog("sinh", 1.0);

    QFile logFile(testLogPath);
    QVERIFY2(logFile.exists(), qPrintable(
                                   QString("Файл лога не найден по пути: %1").arg(testLogPath)));

    QVERIFY(logFile.open(QIODevice::ReadOnly));
    QString content = logFile.readAll();
    logFile.close();
    А
    QVERIFY2(content.contains("sinh(1"), "В логе не найдена ожидаемая запись");

    window.logFileName = originalLogPath;
    QFile::remove(testLogPath);
}

