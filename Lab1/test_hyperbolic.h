#ifndef TEST_HYPERBOLIC_H
#define TEST_HYPERBOLIC_H

#include <QObject>
#include <QTest>

class TestHyperbolic : public QObject
{
    Q_OBJECT
public:
    explicit TestHyperbolic(QObject *parent = nullptr);

private slots:
    void testSinhCalculation();
    void testCothZeroDivision();
    void testFileLogging();
};

#endif // TEST_HYPERBOLIC_H
