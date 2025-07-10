#include "threedimensionalvector.h"

ThreeDimensionalVector::ThreeDimensionalVector()
{

}

void ThreeDimensionalVector::Resize(int FNumber, int ANumber, int ENumber)
{
    VNAParameters.NumOfPoi = FNumber;
    OPUParameters.AzTrigPoints = ANumber;
    OPUParameters.ElTrigPoints = ENumber;

    ObjectMeasurementResult.resize(FNumber*ANumber*ENumber);
    BackgroundMeasurementResult.resize(FNumber);
    ResponseMeasurementResult.resize(FNumber);
}

std::complex<double> ThreeDimensionalVector::ReadFromObjectResult(int f, int a, int e)
{
    return ObjectMeasurementResult[e * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + a * VNAParameters.NumOfPoi + f];
}


void ThreeDimensionalVector::WriteToObjectResult(int f, int a, int e, std::complex<double> NewValue)
{
    ObjectMeasurementResult[e * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + a * VNAParameters.NumOfPoi + f] = NewValue;
}

QVector<std::complex<double>> ThreeDimensionalVector::GetFrequencyVectorAt(int a, int e)
{
    QVector <std::complex<double>> FreqVector(VNAParameters.NumOfPoi);

    for (int f = 0; f < VNAParameters.NumOfPoi; f ++)
    {
        FreqVector[f] = ReadFromObjectResult(f,a,e);
    }
    return FreqVector;
}


ThreeDimensionalVector::~ThreeDimensionalVector()
{

}


int ThreeDimensionalVector::FindAzimuthIndex(double AzimuthValue)
{
    int Result = int( (AzimuthValue - OPUParameters.startAzAngl)/(OPUParameters.stopAzAngl - OPUParameters.startAzAngl) * double(OPUParameters.AzTrigPoints-1) ) ;
    return Result;
}


int ThreeDimensionalVector::FindElevationIndex(double ElevationValue)
{
    int Result = int( (ElevationValue - OPUParameters.startElAngl)/(OPUParameters.stopElAngl - OPUParameters.startElAngl) * double(OPUParameters.ElTrigPoints-1) ) ;
    return Result;
}

void ThreeDimensionalVector::WriteToRowOfObjectResult(int r, int t, QVector <std::complex<double>> FreqVect)
{
    //Добавить проверку размерности

    for(int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        WriteToObjectResult(f,r,t,FreqVect[f]);
    }
}


void ThreeDimensionalVector::SetRanges(double FreqStart,  double FreqStop,    double FreqNumber,
                                 double AzimuthStart,   double AzimuthStop,     double AzimuthNumber,
                                 double ElevationStart,  double ElevationStop,    double ElevationNumber)
{
    ObjectMeasurementResult = QVector<std::complex<double>>(FreqNumber * AzimuthNumber * ElevationNumber, std::complex<double>(0.0,0.0));

    VNAParameters.StartFreq = FreqStart;
    VNAParameters.StopFreq = FreqStop;
    VNAParameters.NumOfPoi =  FreqNumber;

    OPUParameters.startAzAngl = AzimuthStart;
    OPUParameters.stopAzAngl = AzimuthStop;
    OPUParameters.AzTrigPoints =  AzimuthNumber;

    OPUParameters.startElAngl = ElevationStart;
    OPUParameters.stopElAngl = ElevationStop;
    OPUParameters.ElTrigPoints =  ElevationNumber;

}


double ThreeDimensionalVector::FindAzimuthValue(int a)
{
    double Result = OPUParameters.startAzAngl + double(a) * (OPUParameters.stopAzAngl - OPUParameters.startAzAngl) / double(OPUParameters.AzTrigPoints-1)  ;
    return Result;
}


double ThreeDimensionalVector::FindElevationValue (int e)
{
    double Result = OPUParameters.startElAngl + double(e) * (OPUParameters.stopElAngl - OPUParameters.startElAngl) / double(OPUParameters.ElTrigPoints-1)  ;
    return Result;
}

void ThreeDimensionalVector::AddMeasuredRow(QVector <std::complex<double>> FrequencyRow)
{

    int a = CurrentAzimuthIndex;
    int e = CurrentElevationIndex;
    if ( a < OPUParameters.AzTrigPoints)
    {
        this->WriteToRowOfObjectResult(a,e,FrequencyRow);
        a++;
    }
    else
    {
        a=0;
        e++;
        this->WriteToRowOfObjectResult(a,e,FrequencyRow);
    }
}

QVector<std::complex<double>> ThreeDimensionalVector::MakeItScarcer(QVector<std::complex<double>> MyVector)
{
    // Для прореживания background и response: (Не совсем уверен, так ли он делается)
    QVector<std::complex<double>> ResultVector(MyVector.size()/4);
    for (int i=0; i<ResultVector.size(); i++)
    {
        ResultVector[i] = MyVector[4*i];
    }
    return ResultVector;
}












/*
void ThreeDimensionalVector::AddMeasuredObjectValues(QVector <double> VectorToBeAdded) // Для последовательного заполнения массивом элементами double, идущими "Через один"
{
    //qDebug()<< "VECT = " << VectorToBeAdded.mid(0,2);
    for (int i=0;i<VectorToBeAdded.size(); i++)
    {
        if (CurrentIndex % 2 == 0)
        {
            ObjectMeasurementResult[int(CurrentIndex/2)] = std::complex(VectorToBeAdded[i],ObjectMeasurementResult[CurrentIndex/2].real());
            //if (i==0) qDebug()<<"REAL = " << ObjectMeasurementResult[int(CurrentIndex/2)] .real();
            CurrentIndex++;
        }
        else
        {
            ObjectMeasurementResult[int(CurrentIndex/2)] = std::complex(VectorToBeAdded[i],ObjectMeasurementResult[CurrentIndex/2].imag());
            //if (i==1) qDebug()<<"IMAG = " << ObjectMeasurementResult[int(CurrentIndex/2)] .imag();
            CurrentIndex++;
        }
    }

    if (CurrentIndex == ObjectMeasurementResult.size()*2)
    {
        CurrentIndex = 0;
    }

}
*/



void ThreeDimensionalVector::FillComplexVectorWithDoubleValues(QVector<double> ReceivedVector) // для заполнения мнимыми и действительными числами, если они чередуются в поступающем массиве данных
{
    if (ReceivedVector.size() == VNAParameters.NumOfPoi*OPUParameters.AzTrigPoints*OPUParameters.ElTrigPoints*2)
    {
        int index = 0;
        for (int e=0; e<OPUParameters.ElTrigPoints; e++)
        {
            for (int a=0; a<OPUParameters.AzTrigPoints; a++)
            {
                for (int f=0; f<VNAParameters.NumOfPoi; f++)
                {
                    double RealPart = ReceivedVector[index];
                    index++;
                    double ImagPart = ReceivedVector[index];
                    index++;
                    std::complex<double> ComplexValue = std::complex<double> (RealPart, ImagPart);
                    this->WriteToObjectResult(f,a,e, ComplexValue);
                }
            }
        }
    }
    else
    {
        qDebug()<<"Received vector has wrong size";
    }

}




QVector<double> ThreeDimensionalVector::SubstractBackgroundAndCalibrate()
{

    QVector <std::complex<double>> TempVector(this->ObjectMeasurementResult.size()); // Массив того же размера
    QVector <std::complex<double>> ObjectExample(this->VNAParameters.NumOfPoi);


    for (int e=0; e<OPUParameters.ElTrigPoints; e++)
    {
        for (int a=0; a<OPUParameters.AzTrigPoints; a++)
        {
            for (int f=0; f<VNAParameters.NumOfPoi; f++)
            {
                //Вычитание фона:
                std::complex<double>     ObjectValue = this->ReadFromObjectResult(f,a,e);
                std::complex<double> BackgroundValue = BackgroundMeasurementResult[f];
                std::complex<double> ResultValue1 = ObjectValue - BackgroundValue;

                std::complex<double> ResultValue2 = ResultValue1 / ResponseMeasurementResult[f] * ObjectExample[f];

                TempVector[e * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + a * VNAParameters.NumOfPoi + f] = ResultValue2;
            }
        }
    }

    QVector <double> AbsVector(TempVector.size());

    for (int i=0; i<TempVector.size(); i++)
    {
        AbsVector[i] = 20 * log10(abs(TempVector[i]));
    }

    return AbsVector;
}




QDataStream &operator<<(QDataStream &out, const ThreeDimensionalVector &MyMF)
{
    out << MyMF.VNAParameters.NumOfPoi
        << MyMF.OPUParameters.AzTrigPoints
        << MyMF.OPUParameters.ElTrigPoints
        << MyMF.VNAParameters.StartFreq
        << MyMF.OPUParameters.startAzAngl
        << MyMF.OPUParameters.startElAngl
        << MyMF.VNAParameters.StopFreq
        << MyMF.OPUParameters.stopAzAngl
        << MyMF.OPUParameters.stopElAngl;

    QVector<double> RealValuesOfObjectMeasurement(MyMF.ObjectMeasurementResult.size());
    QVector<double> ImagValuesOfObjectMeasurement(MyMF.ObjectMeasurementResult.size());

    for (int i = 0; i < MyMF.ObjectMeasurementResult.size(); ++i)
    {
        RealValuesOfObjectMeasurement[i] = MyMF.ObjectMeasurementResult[i].real();
        ImagValuesOfObjectMeasurement[i] = MyMF.ObjectMeasurementResult[i].imag();
    }

    out << RealValuesOfObjectMeasurement << ImagValuesOfObjectMeasurement;

    QVector<double> RealValuesOfBackgroundMeasurement(MyMF.BackgroundMeasurementResult.size());
    QVector<double> ImagValuesOfBackgroundMeasurement(MyMF.BackgroundMeasurementResult.size());

    for (int i = 0; i < MyMF.BackgroundMeasurementResult.size(); ++i)
    {
        RealValuesOfBackgroundMeasurement[i] = MyMF.BackgroundMeasurementResult[i].real();
        ImagValuesOfBackgroundMeasurement[i] = MyMF.BackgroundMeasurementResult[i].imag();
    }

    out << RealValuesOfBackgroundMeasurement << ImagValuesOfBackgroundMeasurement;

    QVector<double> RealValuesOfResponseMeasurement(MyMF.ResponseMeasurementResult.size());
    QVector<double> ImagValuesOfResponseMeasurement(MyMF.ResponseMeasurementResult.size());

    for (int i = 0; i < MyMF.ObjectMeasurementResult.size(); ++i)
    {
        RealValuesOfResponseMeasurement[i] = MyMF.ResponseMeasurementResult[i].real();
        ImagValuesOfResponseMeasurement[i] = MyMF.ResponseMeasurementResult[i].imag();
    }

    out << RealValuesOfResponseMeasurement << ImagValuesOfResponseMeasurement;

    return out;
}



QDataStream &operator>>(QDataStream &in, ThreeDimensionalVector &MyThreeDimensionalVector)
{
    in >> MyThreeDimensionalVector.VNAParameters.NumOfPoi
        >> MyThreeDimensionalVector.OPUParameters.AzTrigPoints
        >> MyThreeDimensionalVector.OPUParameters.ElTrigPoints
        >> MyThreeDimensionalVector.VNAParameters.StartFreq
        >> MyThreeDimensionalVector.OPUParameters.startAzAngl
        >> MyThreeDimensionalVector.OPUParameters.startElAngl
        >> MyThreeDimensionalVector.VNAParameters.StopFreq
        >> MyThreeDimensionalVector.OPUParameters.stopAzAngl
        >> MyThreeDimensionalVector.OPUParameters.stopElAngl;

    int Size = MyThreeDimensionalVector.VNAParameters.NumOfPoi * MyThreeDimensionalVector.OPUParameters.AzTrigPoints *  MyThreeDimensionalVector.OPUParameters.ElTrigPoints; // Размер массива по углам и частотам

    QVector<double> RealValuesOfObjectMeasurement(Size);
    QVector<double> ImagValuesOfObjectMeasurement(Size);

    in >> RealValuesOfObjectMeasurement >> ImagValuesOfObjectMeasurement;

    MyThreeDimensionalVector.ObjectMeasurementResult.resize(Size);
    for (int i = 0; i < Size; ++i)
    {
        MyThreeDimensionalVector.ObjectMeasurementResult[i] = std::complex<double>(RealValuesOfObjectMeasurement[i], ImagValuesOfObjectMeasurement[i]);
    }


    int FNum = MyThreeDimensionalVector.VNAParameters.NumOfPoi;

    QVector<double> RealValuesOfBackgroundMeasurement(FNum);
    QVector<double> ImagValuesOfBackgroundMeasurement(FNum);

    in >> RealValuesOfBackgroundMeasurement >> ImagValuesOfBackgroundMeasurement;

    MyThreeDimensionalVector.BackgroundMeasurementResult.resize(FNum);
    for (int i = 0; i < FNum; ++i)
    {
        MyThreeDimensionalVector.BackgroundMeasurementResult[i] = std::complex<double>(RealValuesOfBackgroundMeasurement[i], ImagValuesOfBackgroundMeasurement[i]);
    }


    QVector<double> RealValuesOfResponseMeasurement(FNum);
    QVector<double> ImagValuesOfResponseMeasurement(FNum);

    in >> RealValuesOfResponseMeasurement >> ImagValuesOfResponseMeasurement;

    MyThreeDimensionalVector.ResponseMeasurementResult.resize(FNum);
    for (int i = 0; i < FNum; ++i)
    {
        MyThreeDimensionalVector.ResponseMeasurementResult[i] = std::complex<double>(RealValuesOfResponseMeasurement[i], ImagValuesOfResponseMeasurement[i]);
    }




    return in;
}




QVector <double> ThreeDimensionalVector::FreqVector()
{
    QVector <double> FreqVector(VNAParameters.NumOfPoi);

    for (int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        FreqVector[f] = VNAParameters.StartFreq + f * (VNAParameters.StopFreq-VNAParameters.StartFreq)/(VNAParameters.NumOfPoi-1);
    }

    return FreqVector;
}

QVector <double> ThreeDimensionalVector::AzimuthVector()
{
    QVector <double> AzimuthVector(OPUParameters.AzTrigPoints);

    for (int a=0; a<OPUParameters.AzTrigPoints; a++)
    {
        AzimuthVector[a] = OPUParameters.startAzAngl + a * (OPUParameters.stopAzAngl-OPUParameters.startAzAngl)/(OPUParameters.AzTrigPoints-1);
    }

    return AzimuthVector;
}


QVector <double> ThreeDimensionalVector::ElevationVector()
{
    QVector <double> ElevationVector(OPUParameters.ElTrigPoints);

    for (int e=0; e<OPUParameters.ElTrigPoints; e++)
    {
        ElevationVector[e] = OPUParameters.startElAngl + e * (OPUParameters.stopElAngl-OPUParameters.startElAngl)/(OPUParameters.ElTrigPoints-1);
    }
    return ElevationVector;
}


// Для подключения как слотов:
void ThreeDimensionalVector::ReceiveBackgroundVector(QVector<std::complex<double>> MeasuredBackground)
{
    this->BackgroundMeasurementResult = MeasuredBackground;
}


void ThreeDimensionalVector::ReceiveResponseVector(QVector<std::complex<double>> MeasuredResponse)
{
    this->ResponseMeasurementResult = MeasuredResponse;
}












// Вектор амплитуды при заданных углах
QVector <double> ThreeDimensionalVector::AmplitudeVectorAtAngles (int a, int e)
{
    QVector <double> YVector(VNAParameters.NumOfPoi);

    for (int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        YVector[f] = 20 * log10(abs(ReadFromObjectResult(f,a,e)));
    }

    return YVector;
}




// Далее устаревшие куски программы


QVector <double> ThreeDimensionalVector::AmplitudeVectorAtFrequencyElevation(int f, int e)
{
    QVector <double> YVector(VNAParameters.NumOfPoi);
    for (int a=0; a<OPUParameters.AzTrigPoints; a++)
    {
        YVector[a] = 20 * log10(abs(ReadFromObjectResult(f,a,e)));
    }
    return YVector;
}


bool ThreeDimensionalVector::CheckBackgroundForSuitability(ThreeDimensionalVector BG)
{
    bool FreqRangeSuitable      = (VNAParameters.StartFreq == BG.VNAParameters.StartFreq &&  VNAParameters.StopFreq == BG.VNAParameters.StopFreq &&  VNAParameters.StartFreq == BG.VNAParameters.StartFreq);
    bool AzimuthRangeSuitable   = (OPUParameters.startAzAngl == BG.OPUParameters.startAzAngl &&  OPUParameters.stopAzAngl == BG.OPUParameters.stopAzAngl &&  OPUParameters.startAzAngl == BG.OPUParameters.startAzAngl);
    bool ElevationRangeSuitable = (OPUParameters.startElAngl == BG.OPUParameters.startElAngl &&  OPUParameters.stopElAngl == BG.OPUParameters.stopElAngl &&  OPUParameters.startElAngl == BG.OPUParameters.startElAngl);

    bool Result = FreqRangeSuitable && AzimuthRangeSuitable && ElevationRangeSuitable;

    return Result;
}




void ThreeDimensionalVector::ClearFunction()
{
    Resize(0,0,0);

    VNAParameters.NumOfPoi = 0;
    OPUParameters.AzTrigPoints = 0;
    OPUParameters.ElTrigPoints = 0;

    VNAParameters.StartFreq = 0;
    OPUParameters.startAzAngl = 0;
    OPUParameters.startElAngl = 0;

    VNAParameters.StopFreq = 0;
    OPUParameters.stopAzAngl = 0;
    OPUParameters.stopElAngl = 0;
}




void ThreeDimensionalVector::Calibrate(ThreeDimensionalVector C, int SampleType)
{
    //Добавить проверку размерности
    for (int t = 0; t < OPUParameters.ElTrigPoints; t++)
    {
        for (int r = 0; r < OPUParameters.AzTrigPoints; r++)
        {
            for (int f=0; f < VNAParameters.NumOfPoi; f++)
            {
                std::complex<double> Multiplier = C.ReadFromObjectResult(f,r,t) * pow(std::complex<double>(f,0), SampleType+1);
                std::complex<double> ValueAtPoint = ReadFromObjectResult(f,r,t)  * Multiplier;
                this->WriteToObjectResult(f,r,t,ValueAtPoint);
            }
        }
    }
}



// Должна возвращать массив расстояний -- как его правильно пересчитать пока не знаю сейчас просто индексы выдаёт
QVector <double> ThreeDimensionalVector::DistVector()
{
    QVector <double> Result(VNAParameters.NumOfPoi);
    for (int d=0; d<VNAParameters.NumOfPoi; d++)
    {
        Result[d] = d; // Как правильно считать я не знаю пока
    }
    return Result;
}




QVector <double> ThreeDimensionalVector::FourierAmplVectorAtAngles (int a, int e)
{

    QVector <std::complex<double>> F = GetFrequencyVectorAt(a,e);
    QVector <std::complex<double>> Transform(VNAParameters.NumOfPoi);


    for (int d=0; d<VNAParameters.NumOfPoi; d++)
    {
        Transform[d] = 0;
        for (int f=0; f<VNAParameters.NumOfPoi; f++)
        {
            Transform[d] += F[f] * exp( - std::complex<double>(0, 2 * M_PI * f * d / VNAParameters.NumOfPoi));
        }
        Transform[d]/=VNAParameters.NumOfPoi;
    }

    QVector <double> y(VNAParameters.NumOfPoi);

    for (int d=0; d<VNAParameters.NumOfPoi; d++)
    {
        y[d] = 20 * log10(abs(Transform[d]));
    }

    return y;
}



//Убираю, так как не нужно -- и так простые функции.
/*
std::complex<double> ThreeDimensionalVector::ReadFromBackgroundResult(int f)
{
    return ObjectMeasurementResult[f];
}

std::complex<double> ThreeDimensionalVector::ReadFromResponseResult(int f)
{
    return ObjectMeasurementResult[f];
}
*/





void ThreeDimensionalVector::SubstractBackground(ThreeDimensionalVector BG)
{
    for (int e = 0; e < OPUParameters.ElTrigPoints; e++)
    {
        for (int a = 0; a < OPUParameters.AzTrigPoints; a++)
        {
            for (int f=0; f < VNAParameters.NumOfPoi; f++)
            {
                std::complex<double> ValueAtPoint =ReadFromObjectResult(f,a,e) - BG.ReadFromObjectResult(f,a,e);
                this->WriteToObjectResult(f,a,e,ValueAtPoint);
            }
        }
    }
    // Добавить вывод ошибки при несовпадении параметров
}











