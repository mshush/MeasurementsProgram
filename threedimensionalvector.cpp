#include "threedimensionalvector.h"

ThreeDimensionalVector::ThreeDimensionalVector()
{
    FNum = 0;
    ANum = 0;
    ENum = 0;

}

void ThreeDimensionalVector::Resize(int FNumber, int ANumber, int ENumber)
{
    FNum = FNumber;
    ANum = ANumber;
    ENum = ENumber;

    Function.resize(FNum*ANum*ENum);
}

std::complex<double> ThreeDimensionalVector::ReadFrom(int f, int r, int t)
{
    return Function[t * (ANum * FNum)  + r * FNum + f];
}

void ThreeDimensionalVector::WriteTo(int f, int r, int t, std::complex<double> NewValue)
{
    Function[t * (ANum * FNum)  + r * FNum + f] = NewValue;
}

QVector<std::complex<double>> ThreeDimensionalVector::GetFrequencyVectorAt(int r, int t)
{
    QVector <std::complex<double>> FreqVector(FNum);

    for (int f = 0; f < FNum; f ++)
    {
        FreqVector[f] = ReadFrom(f,r,t);
    }

    return FreqVector;
}


ThreeDimensionalVector::~ThreeDimensionalVector()
{

}




int ThreeDimensionalVector::FindAzimuthIndex(double AzimuthValue)
{
    int Result = int( (AzimuthValue - AStart)/(AStop - AStart) * double(ANum-1) ) ;
    return Result;
}


int ThreeDimensionalVector::FindElevationIndex(double ElevationValue)
{
    int Result = int( (ElevationValue - EStart)/(EStop - EStart) * double(ENum-1) ) ;
    return Result;
}


QDataStream &operator<<(QDataStream &out, const ThreeDimensionalVector &MyMF)
{
    out << MyMF.FNum
        << MyMF.ANum
        << MyMF.ENum
        << MyMF.FStart
        << MyMF.AStart
        << MyMF.EStart
        << MyMF.FStop
        << MyMF.AStop
        << MyMF.EStop;

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



QDataStream &operator>>(QDataStream &in, ThreeDimensionalVector &MyThreeDimensionalVector)
{
    in >> MyThreeDimensionalVector.FNum
        >> MyThreeDimensionalVector.ANum
        >> MyThreeDimensionalVector.ENum
        >> MyThreeDimensionalVector.FStart
        >> MyThreeDimensionalVector.AStart
        >> MyThreeDimensionalVector.EStart
        >> MyThreeDimensionalVector.FStop
        >> MyThreeDimensionalVector.AStop
        >> MyThreeDimensionalVector.EStop;


    QVector<double> RealValuesOfFunction;
    QVector<double> ImagValuesOfFunction;

    in >> RealValuesOfFunction >> ImagValuesOfFunction;

    MyThreeDimensionalVector.Function.resize(RealValuesOfFunction.size());
    for (int i = 0; i < RealValuesOfFunction.size(); ++i)
    {
        MyThreeDimensionalVector.Function[i] = std::complex<double>(RealValuesOfFunction[i], ImagValuesOfFunction[i]);
    }
    return in;
}




void ThreeDimensionalVector::SubstractBackground(ThreeDimensionalVector BG)
{
    for (int t = 0; t < ENum; t++)
    {
        for (int r = 0; r < ANum; r++)
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




QVector <double> ThreeDimensionalVector::FreqVector()
{
    QVector <double> FreqVector(FNum);

    for (int f=0; f<FNum; f++)
    {
        FreqVector[f] = FStart + f * (FStop-FStart)/(FNum-1);
    }

    return FreqVector;
}

QVector <double> ThreeDimensionalVector::AzimuthVector()
{
    QVector <double> AzimuthVector(ANum);

    for (int r=0; r<ANum; r++)
    {
        AzimuthVector[r] = AStart + r * (AStop-AStart)/(ANum-1);
    }

    return AzimuthVector;
}


QVector <double> ThreeDimensionalVector::ElevationVector()
{
    QVector <double> ElevationVector(ENum);

    for (int t=0; t<ENum; t++)
    {
        ElevationVector[t] = EStart + t * (EStop-EStart)/(ENum-1);
    }

    return ElevationVector;
}



QVector <double> ThreeDimensionalVector::AmplitudeVectorAtAngles (int r, int t)
{
    QVector <double> YVector(FNum);

    for (int f=0; f<FNum; f++)
    {
        YVector[f] = abs(ReadFrom(f,r,t));
    }

    return YVector;
}


QVector <double> ThreeDimensionalVector::AmplitudeVectorAtFrequencyElevation(int f, int t)
{
    {
        QVector <double> YVector(FNum);

        for (int r=0; f<ANum; r++)
        {
            YVector[f] = abs(ReadFrom(f,r,t));
        }
        return YVector;
    }
}


bool ThreeDimensionalVector::CheckBackgroundForSuitability(ThreeDimensionalVector BG)
{
    bool FreqRangeSuitable = (FStart == BG.FStart &&  FStop == BG.FStop &&  FStart == BG.FStart);
    bool AzimuthRangeSuitable = (AStart == BG.AStart &&  AStop == BG.AStop &&  AStart == BG.AStart);
    bool ElevationRangeSuitable = (EStart == BG.EStart &&  EStop == BG.EStop &&  EStart == BG.EStart);

    bool Result = FreqRangeSuitable && AzimuthRangeSuitable && ElevationRangeSuitable;

    return Result;
}




void ThreeDimensionalVector::ClearFunction()
{
    Resize(0,0,0);

    FNum = 0;
    ANum = 0;
    ENum = 0;

    FStart = 0;
    AStart = 0;
    EStart = 0;

    FStop = 0;
    AStop = 0;
    EStop = 0;
}



void ThreeDimensionalVector::Calibrate(ThreeDimensionalVector C, int SampleType)
{
    //Добавить проверку размерности
    for (int t = 0; t < ENum; t++)
    {
        for (int r = 0; r < ANum; r++)
        {
            for (int f=0; f < FNum; f++)
            {
                std::complex<double> Multiplier = C.ReadFrom(f,r,t) * pow(std::complex<double>(f,0), SampleType+1);
                std::complex<double> ValueAtPoint = ReadFrom(f,r,t)  * Multiplier;
                this->WriteTo(f,r,t,ValueAtPoint);
            }
        }
    }
}





QVector <double> ThreeDimensionalVector::DistVector ()
{
    QVector <double> Result(FNum);
    for (int d=0; d<FNum; d++)
    {
        Result[d] = d;
    }
    return Result;
}


QVector <double> ThreeDimensionalVector::FourierAmplVectorAtAngles (int r, int t)
{

    QVector <std::complex<double>> F = GetFrequencyVectorAt(r,t);
    QVector <std::complex<double>> Transform(FNum);


    for (int d=0; d<FNum; d++)
    {
        Transform[d] = 0;
        for (int f=0; f<FNum; f++)
        {
            Transform[d] += F[f] * exp( - std::complex<double>(0, 2 * M_PI * f * d / FNum));
        }
        Transform[d]/=FNum;
    }

    QVector <double> y(FNum);

    for (int d=0; d<FNum; d++)
    {
        y[d] = abs(Transform[d]);
    }

    return y;
}



void ThreeDimensionalVector::WriteToRow(int r, int t, QVector <std::complex<double>> FreqVect)
{
    //Добавить проверку размерности

    for(int f=0; f<FNum; f++)
    {
        WriteTo(f,r,t,FreqVect[f]);
    }
}


void ThreeDimensionalVector::SetRanges(double FreqStart,  double FreqStop,    double FreqNumber,
                                 double AzimuthStart,   double AzimuthStop,     double AzimuthNumber,
                                 double ElevationStart,  double ElevationStop,    double ElevationNumber)
{
    Function = QVector<std::complex<double>>(FreqNumber * AzimuthNumber * ElevationNumber, std::complex<double>(0.0,0.0));

    FStart = FreqStart;
    FStop = FreqStop;
    FNum =  FreqNumber;

    AStart = AzimuthStart;
    AStop = AzimuthStop;
    ANum =  AzimuthNumber;

    EStart = ElevationStart;
    EStop = ElevationStop;
    ENum =  ElevationNumber;

}


double ThreeDimensionalVector::FindAzimuthValue(int r)
{
    double Result = AStart + double(r) * (AStop - AStart) / double(ANum-1)  ;
    return Result;
}




double ThreeDimensionalVector::FindElevationValue (int t)
{
    double Result = EStart + double(t) * (EStop - EStart) / double(ENum-1)  ;
    return Result;
}



void ThreeDimensionalVector::AddMeasuredValues(QVector <double> VectorToBeAdded)
{
    //qDebug()<< "VECT = " << VectorToBeAdded.mid(0,2);



    for (int i=0;i<VectorToBeAdded.size(); i++)
    {
        if (CurrentIndex % 2 == 0)
        {
            Function[int(CurrentIndex/2)] = std::complex(VectorToBeAdded[i],Function[CurrentIndex/2].real());
            //if (i==0) qDebug()<<"REAL = " << Function[int(CurrentIndex/2)] .real();
            CurrentIndex++;
        }
        else
        {
            Function[int(CurrentIndex/2)] = std::complex(VectorToBeAdded[i],Function[CurrentIndex/2].imag());
            //if (i==1) qDebug()<<"IMAG = " << Function[int(CurrentIndex/2)] .imag();
            CurrentIndex++;
        }
    }

    if (CurrentIndex == Function.size()*2)
    {
        CurrentIndex = 0;
    }

}




void ThreeDimensionalVector::FillComplexVectorWithDoubleValues(QVector<double> ReceivedVector)
{
    if (ReceivedVector.size() == FNum*ANum*ENum*2)
    {
        int index = 0;
        for (int t=0; t<ENum; t++)
        {
            for (int r=0; r<ANum; r++)
            {
                for (int f=0; f<FNum; f++)
                {
                    double RealPart = ReceivedVector[index];
                    index++;
                    double ImagPart = ReceivedVector[index];
                    index++;
                    std::complex<double> ComplexValue = std::complex<double> (RealPart, ImagPart);
                    this->WriteTo(f,r,t, ComplexValue);
                }
            }
        }
    }
    else
    {
        qDebug()<<"Received vector has wrong size";
    }

}




