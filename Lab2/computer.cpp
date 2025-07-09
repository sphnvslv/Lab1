#include "computer.h"

Computer::Computer(const QString &model, double hdd, const QString &cpu)
    : m_model(model), m_hdd(hdd), m_cpu(cpu) {}

QString Computer::model() const { return m_model; }
double Computer::hdd() const { return m_hdd; }
QString Computer::cpu() const { return m_cpu; }

void Computer::setModel(const QString &model) { m_model = model; }
void Computer::setHdd(double hdd) { m_hdd = hdd; }
void Computer::setCpu(const QString &cpu) { m_cpu = cpu; }
