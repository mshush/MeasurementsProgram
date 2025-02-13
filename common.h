#ifndef COMMON_H
#define COMMON_H
#include <QByteArray>
#include <thread>
#include <mutex>
#include <errorhandler.h>
#include <cstdlib>
#include <QVector>
#include <complex>

using ComplexVector = QVector<std::complex<double>>;
using DoubleVector = QVector<double>;

extern QByteArray BinaryDataArr;
extern std::mutex MeasBufferMutex;
extern bool bNoError;
extern bool bAbort;
extern int SweepsReadGlobal;
extern int SweepsAvailableGlobal;

extern int SimChangeNum;

extern QString DebugStr;
#endif // COMMON_H
