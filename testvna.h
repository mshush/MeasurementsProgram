#ifndef TESTVNA_H
#define TESTVNA_H

#include <QObject>
#include <QCoreApplication>
#include <QTCPSocket>
#include <complex>

using QComplexVector = QVector<std::complex<double>>;
using QDoubleVector = QVector<double>;


class TestVNA
{
public:
    TestVNA();

};

#endif // TESTVNA_H
