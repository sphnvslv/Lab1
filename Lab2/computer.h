#ifndef COMPUTER_H
#define COMPUTER_H

#include <QString>

class Computer {
public:
    Computer(const QString &model = "", double hdd = 0, const QString &cpu = "");

    QString model() const;
    double hdd() const;
    QString cpu() const;

    void setModel(const QString &model);
    void setHdd(double hdd);
    void setCpu(const QString &cpu);

private:
    QString m_model;
    double m_hdd;
    QString m_cpu;
};

#endif // COMPUTER_H
