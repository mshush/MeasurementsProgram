#include "MeasDataClass.h"

MeasDataClass::MeasDataClass()
{

}

void MeasDataClass::SetOPUParameters(OPUParams OPUPars)
{
    OPUParameters = OPUPars;
}

void MeasDataClass::SetOPUParameters(double AzimuthStart, double AzimuthStop, double AzimuthNumber, double ElevationStart, double ElevationStop, double ElevationNumber, int Speed, int MoveMode)
{
    OPUParameters.startAzAngl = AzimuthStart;
    OPUParameters.stopAzAngl = AzimuthStop;
    OPUParameters.AzTrigPoints =  AzimuthNumber;

    OPUParameters.startElAngl = ElevationStart;
    OPUParameters.stopElAngl = ElevationStop;
    OPUParameters.ElTrigPoints =  ElevationNumber;
    OPUParameters.MoveMode = MoveMode;
    OPUParameters.Speed = Speed;

    TargetMeasArray = QVector<std::complex<double>>(VNAParameters.NumOfPoi * AzimuthNumber * ElevationNumber, std::complex<double>(0.0,0.0));

}

void MeasDataClass::SetVNAParameters(int Pow, double StartFreq, double StopFreq, int NumOfPoi, int NumOfSweeps, int IF, QString Datatype, QString MeasParameter, bool ExternalTriggerOn)
{
    {
        //VNAParameters.ip = ip;
        //VNAParameters.port = port;
        VNAParameters.Pow = Pow;
        VNAParameters.StartFreq = StartFreq;
        VNAParameters.StopFreq = StopFreq;
        VNAParameters.NumOfPoi = NumOfPoi;
        VNAParameters.NumOfSweeps  = NumOfSweeps;
        VNAParameters.IF = IF;
        VNAParameters.Datatype = Datatype;
        VNAParameters.MeasParameter = MeasParameter;
        VNAParameters.ExternalTriggerOn = ExternalTriggerOn;
    };

}

void MeasDataClass::SetVNAParameters(VNAParams VNAPars)
{
    VNAParameters = VNAPars;
}

void MeasDataClass::SetReferenceCylinderPars(double height, double radius)
{

    RefCylinder.SetCylinderParams(radius, height);

}

void MeasDataClass::CopyVNAParams(VNAParams dest)
{
    dest = VNAParameters;
}

void MeasDataClass::CopyOPUParams(OPUParams dest)
{
    dest = OPUParameters;
}

void MeasDataClass::Resize(int FreqNum, int AzNum, int ElNum)
{
    VNAParameters.NumOfPoi = FreqNum;
    OPUParameters.AzTrigPoints = AzNum;
    OPUParameters.ElTrigPoints = ElNum;

    TargetMeasArray.resize(FreqNum*AzNum*ElNum);
    BackgroundMeasArray.resize(FreqNum);
    ResponseMeasArray.resize(FreqNum);

}

std::complex<double> MeasDataClass::ReadFromTargetMeasArray(int FreqIndex, int AzIndex, int ElIndex)
{
    // index out of range?
    return TargetMeasArray[ElIndex * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + AzIndex * VNAParameters.NumOfPoi + FreqIndex];
}

void MeasDataClass::WriteValueToTargetArray(int f, int a, int ElIndex, std::complex<double> NewValue)
{
    // index out of range?
    TargetMeasArray[ElIndex * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + a * VNAParameters.NumOfPoi + f] = NewValue;
}

QVector<std::complex<double>> MeasDataClass::GetSweepAt(int AzIndex, int ElIndex)
{
    QVector <std::complex<double>> SingleSweep(VNAParameters.NumOfPoi);

    for (int f = 0; f < VNAParameters.NumOfPoi; f ++)
    {
        SingleSweep[f] = ReadFromTargetMeasArray(f,AzIndex,ElIndex);
    }
    return SingleSweep;
}


MeasDataClass::~MeasDataClass()
{

}




int MeasDataClass::FindAzimuthIndex(double AzimuthValue)
{
    // wtf is it
    int Result = int( (AzimuthValue - OPUParameters.startAzAngl)/(OPUParameters.stopAzAngl - OPUParameters.startAzAngl) * double(OPUParameters.AzTrigPoints-1) ) ;
    return Result;
}


int MeasDataClass::FindElevationIndex(double ElevationValue)
{
    // wtf is it
    int Result = int( (ElevationValue - OPUParameters.startElAngl)/(OPUParameters.stopElAngl - OPUParameters.startElAngl) * double(OPUParameters.ElTrigPoints-1) ) ;
    return Result;
}





void MeasDataClass::WriteSweepToTargetArray(int TargetMeasArray, int ElIndex, QVector <std::complex<double>> SingleSweep)
{
    //Добавить проверку размерности

    for(int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        WriteValueToTargetArray(f,TargetMeasArray,ElIndex,SingleSweep[f]);
    }
}


double MeasDataClass::FindAzimuthValue(int AzIndex)
{
    double Result = OPUParameters.startAzAngl + double(AzIndex) * (OPUParameters.stopAzAngl - OPUParameters.startAzAngl) / double(OPUParameters.AzTrigPoints-1)  ;
    return Result;
}


double MeasDataClass::FindElevationValue (int ElIndex)
{
    double Result = OPUParameters.startElAngl + double(ElIndex) * (OPUParameters.stopElAngl - OPUParameters.startElAngl) / double(OPUParameters.ElTrigPoints-1)  ;
    return Result;
}



QVector<std::complex<double>> MeasDataClass::DownSample(QVector<std::complex<double>> MyVector)
{
    // Для прореживания background и response: (Не совсем уверен, так ли он делается)
    QVector<std::complex<double>> ResultVector(MyVector.size()/4);
    for (int i=0; i<ResultVector.size(); i++)
    {
        ResultVector[i] =  MyVector[4*i];
    }
    return ResultVector;
}


void MeasDataClass::Calibrate()
{

}

QDataStream &operator<<(QDataStream &out, const MeasDataClass &MyMF)
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

    QVector<double> RealValuesOfObjectMeasurement(MyMF.TargetMeasArray.size());
    QVector<double> ImagValuesOfObjectMeasurement(MyMF.TargetMeasArray.size());

    for (int i = 0; i < MyMF.TargetMeasArray.size(); ++i)
    {
        RealValuesOfObjectMeasurement[i] = MyMF.TargetMeasArray[i].real();
        ImagValuesOfObjectMeasurement[i] = MyMF.TargetMeasArray[i].imag();
    }

    out << RealValuesOfObjectMeasurement << ImagValuesOfObjectMeasurement;

    QVector<double> RealValuesOfBackgroundMeasurement(MyMF.BackgroundMeasArray.size());
    QVector<double> ImagValuesOfBackgroundMeasurement(MyMF.BackgroundMeasArray.size());

    for (int i = 0; i < MyMF.BackgroundMeasArray.size(); ++i)
    {
        RealValuesOfBackgroundMeasurement[i] = MyMF.BackgroundMeasArray[i].real();
        ImagValuesOfBackgroundMeasurement[i] = MyMF.BackgroundMeasArray[i].imag();
    }

    out << RealValuesOfBackgroundMeasurement << ImagValuesOfBackgroundMeasurement;

    QVector<double> RealValuesOfResponseMeasurement(MyMF.ResponseMeasArray.size());
    QVector<double> ImagValuesOfResponseMeasurement(MyMF.ResponseMeasArray.size());

    for (int i = 0; i < MyMF.TargetMeasArray.size(); ++i)
    {
        RealValuesOfResponseMeasurement[i] = MyMF.ResponseMeasArray[i].real();
        ImagValuesOfResponseMeasurement[i] = MyMF.ResponseMeasArray[i].imag();
    }

    out << RealValuesOfResponseMeasurement << ImagValuesOfResponseMeasurement;

    return out;
}



QDataStream &operator>>(QDataStream &in, MeasDataClass &MyMeasDataClass)
{
    in >> MyMeasDataClass.VNAParameters.NumOfPoi
        >> MyMeasDataClass.OPUParameters.AzTrigPoints
        >> MyMeasDataClass.OPUParameters.ElTrigPoints
        >> MyMeasDataClass.VNAParameters.StartFreq
        >> MyMeasDataClass.OPUParameters.startAzAngl
        >> MyMeasDataClass.OPUParameters.startElAngl
        >> MyMeasDataClass.VNAParameters.StopFreq
        >> MyMeasDataClass.OPUParameters.stopAzAngl
        >> MyMeasDataClass.OPUParameters.stopElAngl;

    int Size = MyMeasDataClass.VNAParameters.NumOfPoi * MyMeasDataClass.OPUParameters.AzTrigPoints *  MyMeasDataClass.OPUParameters.ElTrigPoints; // Размер массива по углам и частотам

    QVector<double> RealValuesOfObjectMeasurement(Size);
    QVector<double> ImagValuesOfObjectMeasurement(Size);

    in >> RealValuesOfObjectMeasurement >> ImagValuesOfObjectMeasurement;

    MyMeasDataClass.TargetMeasArray.resize(Size);
    for (int i = 0; i < Size; ++i)
    {
        MyMeasDataClass.TargetMeasArray[i] = std::complex<double>(RealValuesOfObjectMeasurement[i], ImagValuesOfObjectMeasurement[i]);
    }


    int FNum = MyMeasDataClass.VNAParameters.NumOfPoi;

    QVector<double> RealValuesOfBackgroundMeasurement(FNum);
    QVector<double> ImagValuesOfBackgroundMeasurement(FNum);

    in >> RealValuesOfBackgroundMeasurement >> ImagValuesOfBackgroundMeasurement;

    MyMeasDataClass.BackgroundMeasArray.resize(FNum);
    for (int i = 0; i < FNum; ++i)
    {
        MyMeasDataClass.BackgroundMeasArray[i] = std::complex<double>(RealValuesOfBackgroundMeasurement[i], ImagValuesOfBackgroundMeasurement[i]);
    }


    QVector<double> RealValuesOfResponseMeasurement(FNum);
    QVector<double> ImagValuesOfResponseMeasurement(FNum);

    in >> RealValuesOfResponseMeasurement >> ImagValuesOfResponseMeasurement;

    MyMeasDataClass.ResponseMeasArray.resize(FNum);
    for (int i = 0; i < FNum; ++i)
    {
        MyMeasDataClass.ResponseMeasArray[i] = std::complex<double>(RealValuesOfResponseMeasurement[i], ImagValuesOfResponseMeasurement[i]);
    }




    return in;
}




QVector <double> MeasDataClass::GetFreqVector()
{
    QVector <double> FreqVector(VNAParameters.NumOfPoi);

    for (int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        FreqVector[f] = VNAParameters.StartFreq + f * (VNAParameters.StopFreq-VNAParameters.StartFreq)/(VNAParameters.NumOfPoi-1);
    }

    return FreqVector;
}

QVector <double> MeasDataClass::GetAzimuthVector()
{
    QVector <double> AzimuthVector(OPUParameters.AzTrigPoints);

    for (int a=0; a<OPUParameters.AzTrigPoints; a++)
    {
        AzimuthVector[a] = OPUParameters.startAzAngl + a * (OPUParameters.stopAzAngl-OPUParameters.startAzAngl)/(OPUParameters.AzTrigPoints-1);
    }

    return AzimuthVector;
}


QVector <double> MeasDataClass::GetElevationVector()
{
    QVector <double> ElevationVector(OPUParameters.ElTrigPoints);

    for (int e=0; e<OPUParameters.ElTrigPoints; e++)
    {
        ElevationVector[e] = OPUParameters.startElAngl + e * (OPUParameters.stopElAngl-OPUParameters.startElAngl)/(OPUParameters.ElTrigPoints-1);
    }
    return ElevationVector;
}


// Для подключения как слотов:
void MeasDataClass::SetBackgroundVector(QVector<std::complex<double>> MeasuredBackground)
{
    BackgroundMeasArray = MeasuredBackground;
}


void MeasDataClass::SetResponseVector(QVector<std::complex<double>> MeasuredResponse)
{
    ResponseMeasArray = MeasuredResponse;
}

void MeasDataClass::SetBackgroundVector(double *ReBcknd, double *ImBcknd)
{

}

void MeasDataClass::SetResponseVector(double *ReRsp, double *ImRsp)
{

}

void MeasDataClass::SetBackgroundVector(double *Bcknd)
{

}

void MeasDataClass::SetResponseVector(double *Rsp)
{

}


// что добавть : 1) запись в массив по double значениями, 2) изменить функции приема Respone, Background или перегрузить их ??



