#include <QApplication>
#include "mainwindow.h"


 #define RUN_TESTS

#ifdef RUN_TESTS
#include "test_hyperbolic.h"
#include <QTest>

int runTests(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestHyperbolic tests;
    return QTest::qExec(&tests, argc, argv);
}
#endif

int main(int argc, char *argv[])
{
#ifdef RUN_TESTS
    return runTests(argc, argv);
#else
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
#endif
}
