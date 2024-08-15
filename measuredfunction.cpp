#include "measuredfunction.h"

MeasuredFunction::MeasuredFunction()
{
    FNum = 0;
    RNum = 0;
    TNum = 0;
}


void MeasuredFunction::Resize(int FNumber, int RNumber, int TNumber)
{
    FNum = FNumber;
    RNum = RNumber;
    TNum = TNumber;

    Function.resize(FNum*RNum*TNum);
}

std::complex<double> MeasuredFunction::ReadFrom(int f, int r, int t)
{
    return Function[t * (RNum * FNum)  + r * FNum + f];
}

void MeasuredFunction::WriteTo(int f, int r, int t, std::complex<double> NewValue)
{
    Function[t * (RNum * FNum)  + r * FNum + f] = NewValue;
}

QVector<std::complex<double>> MeasuredFunction::GetFrequencyVectorAt(int r, int t)
{
    QVector <std::complex<double>> FreqVector(FNum);

    for (int f=0; f<FNum; f++)
    {
        FreqVector[f] = ReadFrom(f,r,t);
    }

    return FreqVector;
}


MeasuredFunction::~MeasuredFunction()
{

}



