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




int MeasuredFunction::FindRotationIndex(double RotationValue)
{
    int Result = int( (RotationValue - RStart)/(RStop - RStart) * double(RNum-1) ) ;
    return Result;
}


int MeasuredFunction::FindTiltIndex(double TiltValue)
{
    int Result = int( (TiltValue - TStart)/(TStop - TStart) * double(TNum-1) ) ;
    //qDebug() <<Result << " " << TiltValue << " " << TStop;
    return Result;
}








QDataStream &operator<<(QDataStream &out, const MeasuredFunction &MyMF)
{
    out << MyMF.FNum
        << MyMF.RNum
        << MyMF.TNum
        << MyMF.FStart
        << MyMF.RStart
        << MyMF.TStart
        << MyMF.FStop
        << MyMF.RStop
        << MyMF.TStop;

    QVector<double> RealValuesOfFunction(MyMF.Function.size());
    QVector<double> ImagValuesOfFunction(MyMF.Function.size());

    for (int i = 0; i < MyMF.Function.size(); ++i)
    {
        RealValuesOfFunction[i] = MyMF.Function[i].real();
        ImagValuesOfFunction[i] = MyMF.Function[i].imag();
    }

    out << RealValuesOfFunction << ImagValuesOfFunction;
    return out;
}



QDataStream &operator>>(QDataStream &in, MeasuredFunction &MyMeasuredFunction)
{
    in >> MyMeasuredFunction.FNum
        >> MyMeasuredFunction.RNum
        >> MyMeasuredFunction.TNum
        >> MyMeasuredFunction.FStart
        >> MyMeasuredFunction.RStart
        >> MyMeasuredFunction.TStart
        >> MyMeasuredFunction.FStop
        >> MyMeasuredFunction.RStop
        >> MyMeasuredFunction.TStop;


    QVector<double> RealValuesOfFunction;
    QVector<double> ImagValuesOfFunction;

    in >> RealValuesOfFunction >> ImagValuesOfFunction;

    MyMeasuredFunction.Function.resize(RealValuesOfFunction.size());
    for (int i = 0; i < RealValuesOfFunction.size(); ++i)
    {
        MyMeasuredFunction.Function[i] = std::complex<double>(RealValuesOfFunction[i], ImagValuesOfFunction[i]);
    }
    return in;
}



QVector <double> MeasuredFunction::XVector()
{
    QVector <double> x(FNum);

    for (int i=0;i<FNum;i++)
    {
        x[i] = FStart + i* (FStop-FStart)/(FNum-1);
    }
    return x;
}



void MeasuredFunction::SubstractBackground(MeasuredFunction BG)
{
    for (int t = 0; t < TNum; t++)
    {
        for (int r = 0; r < RNum; r++)
        {
            for (int f=0; f < FNum; f++)
            {
                std::complex<double> ValueAtPoint = this->ReadFrom(f,r,t) - BG.ReadFrom(f,r,t);
                this->WriteTo(f,r,t,ValueAtPoint);
            }
        }
    }
    // Добавить вывод ошибки при несовпадении параметров
}



QVector <double> MeasuredFunction::YVectorAtAngles (int r, int t)
{
    QVector <double> YVector(FNum);

    for (int f=0; f<FNum; f++)
    {
        YVector[f] = abs(ReadFrom(f,r,t));
    }

    return YVector;
}


