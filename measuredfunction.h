#ifndef MEASUREDFUNCTION_H
#define MEASUREDFUNCTION_H



#include <complex>
#include <QVector>

class MeasuredFunction
{
public:
    MeasuredFunction();

    ~MeasuredFunction();

    int FNum;
    int RNum;
    int TNum;

    QVector <std::complex<double>> Function;

    void Resize(int FNum, int RNum, int TNum);
    void WriteTo(int f, int r, int t, std::complex<double> NewValue);
    std::complex<double> ReadFrom(int f, int r, int t);

    QVector <std::complex<double>> GetFrequencyVectorAt(int r, int t);


};

#endif // MEASUREDFUNCTION_H
