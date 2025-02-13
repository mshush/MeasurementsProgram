#include "MeasData.h"

MeasDataClass::MeasDataClass()
{

}

std::complex<double> MeasDataClass::ReadFromRawDataTrgtArr(int FreqIndex, int AzIndex, int ElIndex)
{
    return RawDataTargetArray[ElIndex * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + AzIndex * VNAParameters.NumOfPoi + FreqIndex];
}

ComplexVector MeasDataClass::GetRawSweepDataAt(int AzIndex, int ElIndex)
{
    ComplexVector FreqVector(VNAParameters.NumOfPoi);

    for (int f = 0; f < VNAParameters.NumOfPoi; f ++)
    {
        FreqVector[f] = ReadFromRawDataTrgtArr(f,AzIndex,ElIndex);
    }
    return FreqVector;
}


MeasDataClass::~MeasDataClass()
{

}




int MeasDataClass::FindAzimuthIndex(double AzimuthValue)
{
    int Result = int( (AzimuthValue - OPUParameters.startAzAngl)/(OPUParameters.stopAzAngl - OPUParameters.startAzAngl) * double(OPUParameters.AzTrigPoints-1) ) ;
    return Result;
}


int MeasDataClass::FindElevationIndex(double ElevationValue)
{
    int Result = int( (ElevationValue - OPUParameters.startElAngl)/(OPUParameters.stopElAngl - OPUParameters.startElAngl) * double(OPUParameters.ElTrigPoints-1) ) ;
    return Result;
}




void MeasDataClass::SetValueTargetRawDataArr(int FreqIndex, int AzIndex, int ElIndex, std::complex<double> NewValue)
{
    RawDataTargetArray[ElIndex * (OPUParameters.AzTrigPoints * VNAParameters.NumOfPoi)  + AzIndex * VNAParameters.NumOfPoi + FreqIndex] = NewValue;
}

void MeasDataClass::setBUseBckndCal(bool newBUseBckndCal)
{
    bUseBckndCal = newBUseBckndCal;
}

void MeasDataClass::setBUseRspCal(bool newBUseRspCal)
{
    bUseRspCal = newBUseRspCal;
}

DoubleVector& MeasDataClass::GetVectorAmplitudeIndB(ComplexVector Vector)
{
    DoubleVector AmplVector(Vector.size());
    std::complex<double> c;
    for(int i =0; i < Vector.size(); i++)
    {
        c = Vector[i];
        AmplVector[i] = log10((c.imag()*c.imag()) + c.real()*c.real()) * 10;
    }

    return AmplVector;
}


void MeasDataClass::GetVectorAmplitudeIndB(ComplexVector SourceVector, DoubleVector &DestVector)
{
    std::complex<double> c;
    for(int i =0; i < DestVector.size(); i++)
    {
        c = SourceVector[i];
        DestVector[i] = log10((c.imag()*c.imag()) + c.real()*c.real()) * 10;
    }

}

int MeasDataClass::getPatternViewFreq() const
{
    return PatternViewFreq;
}

void MeasDataClass::setPatternViewFreq(int newPatternViewFreq)
{
    PatternViewFreq = newPatternViewFreq;
}


void MeasDataClass::SetSweepAtAngl(ComplexVector FreqVect, int AzIndex, int ElIndex)
{

   for(int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        SetValueTargetRawDataArr(f,AzIndex,ElIndex,FreqVect[f]);
    }


}

void MeasDataClass::SetSweepAtAngl(double *FreqVectRe, double *FreqVectIm, int AzIndex, int ElIndex)
{
    for(int f=0; f<VNAParameters.NumOfPoi; f++)
    {

        SetValueTargetRawDataArr(f,AzIndex,ElIndex,std::complex<double>(FreqVectRe[f], FreqVectIm[f]));
    }

}


void MeasDataClass::AppendSweepToTargetRawDataArr(ComplexVector FreqSweep)
{
    RawDataTargetArray.append(FreqSweep);
}

void MeasDataClass::AppendSingleAngleSweepToDiag(ComplexVector ProcessedAngleSweep)
{
    PatternAtAllFreqsArray.append(ProcessedAngleSweep);
}

void MeasDataClass::SetAllVNAParamsNoAction(int Pow, double StartFreq, double StopFreq, int NumOfPoi, int IF, QString Datatype, QString MeasParameter)
{
    /*
    VNAParameters.Pow = Pow;
    VNAParameters.StartFreq = StartFreq;
    VNAParameters.StopFreq = StopFreq;
    VNAParameters.NumOfPoi = NumOfPoi;
    VNAParameters.IF = IF;
    VNAParameters.Datatype = Datatype;
    VNAParameters.MeasParameter = MeasParameter;
*/
    SetFreqRangesNoAction(StartFreq, StopFreq, NumOfPoi);
    SetIFNoAction(IF);
    SetDataTypeNoAction(Datatype);
    SetMeasParameterNoAction(MeasParameter);
 }

void MeasDataClass::SetAllOPUParamsNoAction(double startAzAngl, double stopAzAngl, double startElAngl, double stopElAngl, int Speed, int AzTrigPoints, int ElTrigPoints, QString MoveMode)
{
    /*
    OPUParameters.startAzAngl = startAzAngl;
    OPUParameters.stopAzAngl = stopAzAngl;
    OPUParameters.startElAngl = startElAngl;
    OPUParameters.stopElAngl = stopElAngl;
    OPUParameters.Speed = Speed;
    OPUParameters.AzTrigPoints = AzTrigPoints;
    OPUParameters.ElTrigPoints = ElTrigPoints;
    OPUParameters.MoveMode = MoveMode;
*/
    SetAzAnglRangesNoAction(startAzAngl,stopAzAngl, AzTrigPoints);
    SetElAnglRangesNoAction(startElAngl, stopElAngl, ElTrigPoints);
    SetMoveModeNoAction(MoveMode);
    SetOPUSpeed(Speed);
}



MeasDataClass::OPUParams MeasDataClass::getOPUParameters() const
{
    return OPUParameters;
}

void MeasDataClass::SetAllOPUParametersNoAction(const OPUParams &newOPUParameters)
{
    OPUParameters = newOPUParameters;
}

MeasDataClass::VNAParams MeasDataClass::getVNAParameters() const
{
    return VNAParameters;
}

void MeasDataClass::SetAllVNAParametersNoAction(const VNAParams &newVNAParameters)
{
    VNAParameters = newVNAParameters;
}

void MeasDataClass::SetTCPParsNoAction(QString Ip, int Port)
{
    VNAParameters.ip = Ip;
    VNAParameters.port = Port;
}


void MeasDataClass::SetFreqRangesNoAction(double StartFreq, double StopFreq, int NumOfPoints)
{
    VNAParameters.StartFreq = StartFreq;
    VNAParameters.StopFreq = StopFreq;
    VNAParameters.NumOfPoi = NumOfPoints;
}


void MeasDataClass::SetIFNoAction(int IF)
{
    VNAParameters.IF = IF;
}

void MeasDataClass::SetDataTypeNoAction(QString Type)
{
    VNAParameters.Datatype = Type;
}

void MeasDataClass::SetPower(double PowdB)
{
    VNAParameters.Pow = PowdB;
}

void MeasDataClass::SetMeasParameterNoAction(QString SParameter)
{
    VNAParameters.MeasParameter = SParameter;
}

void MeasDataClass::SetAzAnglRangesNoAction(double StartAngle, double StopAngle, int NAztrigPoints)
{
    OPUParameters.startAzAngl = StartAngle;
    OPUParameters.stopAzAngl = StopAngle;
    OPUParameters.AzTrigPoints = NAztrigPoints;
}


void MeasDataClass::SetElAnglRangesNoAction(double StartAngle, double StopAngle, int NElTrigPoints)
{
    OPUParameters.startElAngl = StartAngle;
    OPUParameters.stopElAngl = StopAngle;
    OPUParameters.ElTrigPoints = NElTrigPoints;
}

void MeasDataClass::SetMoveModeNoAction(QString Movmode)
{
    OPUParameters.MoveMode = Movmode;
}

void MeasDataClass::SetOPUSpeed(int Speed)
{
    OPUParameters.Speed = Speed;
}

int MeasDataClass::GetTCPPort()
{
    return VNAParameters.port;
}

QString MeasDataClass::GetIP()
{
    return VNAParameters.ip;
}

int MeasDataClass::GetNumOfFreqSweepPoints() {
    return VNAParameters.NumOfPoi;
}

double MeasDataClass::GetStartFreq() {
    return VNAParameters.StartFreq;
}

double MeasDataClass::GetStopFreq() {
    return VNAParameters.StopFreq;
}

int MeasDataClass::GetIF() {
    return VNAParameters.IF;
}

QString MeasDataClass::GetDataType() {
    return VNAParameters.Datatype;
}

QString MeasDataClass::GetMeasParameter() {
    return VNAParameters.MeasParameter;
}

double MeasDataClass::GetStartAzAngl()
{

}

double MeasDataClass::GetStopAzAngl()
{

}

double MeasDataClass::GetStartElAngl()
{

}

double MeasDataClass::GetStopElAngl()
{

}

double MeasDataClass::GetPower()
{

}

int MeasDataClass::GetAzTrigPoints()
{

}

int MeasDataClass::GetElTrigPoints()
{

}

QString MeasDataClass::GetMoveMode()
{

}

int MeasDataClass::GetOPUSpeed()
{

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




ComplexVector MeasDataClass::DownSample(ComplexVector MyVector)
{
    // Для прореживания background и response: (Не совсем уверен, так ли он делается)
   ComplexVector ResultVector(MyVector.size()/4);
    for (int i=0; i<ResultVector.size(); i++)
    {
        ResultVector[i] = MyVector[4*i];
    }
    return ResultVector;
}






DoubleVector MeasDataClass::GetFreqVector()
{
    QVector <double> FreqVector(VNAParameters.NumOfPoi);

    for (int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        FreqVector[f] = VNAParameters.StartFreq + f * (VNAParameters.StopFreq-VNAParameters.StartFreq)/(VNAParameters.NumOfPoi-1);
    }

    return FreqVector;
}

DoubleVector MeasDataClass::GetAzimuthVector()
{
    DoubleVector AzimuthVector(OPUParameters.AzTrigPoints);

    for (int a=0; a<OPUParameters.AzTrigPoints; a++)
    {
        AzimuthVector[a] = OPUParameters.startAzAngl + a * (OPUParameters.stopAzAngl-OPUParameters.startAzAngl)/(OPUParameters.AzTrigPoints-1);
    }

    return AzimuthVector;
}


DoubleVector MeasDataClass::GetElevationVector()
{
    DoubleVector ElevationVector(OPUParameters.ElTrigPoints);

    for (int e=0; e<OPUParameters.ElTrigPoints; e++)
    {
        ElevationVector[e] = OPUParameters.startElAngl + e * (OPUParameters.stopElAngl-OPUParameters.startElAngl)/(OPUParameters.ElTrigPoints-1);
    }
    return ElevationVector;
}


// Для подключения как слотов:
void MeasDataClass::SetRawBcknd(ComplexVector MeasuredBackground)
{

    RawDataBackgroundArray = MeasuredBackground;
    qDebug() << RawDataBackgroundArray.at(0).imag();
}


void MeasDataClass::SetRawResponse(ComplexVector MeasuredResponse)
{
   RawDataResponseArray = MeasuredResponse;
}

void MeasDataClass::SetRawBcknd(double *MeasuredBackgroundRe, double *MeasuredBackgroundIm)
{
   qDebug() << "Hello";

   for (int i = 0; i < VNAParameters.NumOfPoi; i++)
   {

        RawDataBackgroundArray.append( std::complex<double>(MeasuredBackgroundRe[i], MeasuredBackgroundIm[i]) );
   }
}

void MeasDataClass::SetRawResponse(double *MeasuredResponseRe, double *MeasuredResponseIm)
{
   for (int i = 0; i < VNAParameters.NumOfPoi; i++)
   {
        RawDataResponseArray.append( std::complex<double>(MeasuredResponseRe[i], MeasuredResponseRe[i]) );
   }
}

void MeasDataClass::SetProcessedResponse(ComplexVector MeasuredResponse)
{

}












// Вектор амплитуды при заданных углах
DoubleVector MeasDataClass::GetPatternSweepAtAngles(int AzIndex, int ElIndex)
{
   /// !!! ADD

    DoubleVector YVector(VNAParameters.NumOfPoi);
/*
    for (int f=0; f<VNAParameters.NumOfPoi; f++)
    {
        YVector[f] = 20 * log10(abs(ReadFromRawDataTrgtArr(f,AzIndex,ElIndex)));
    }
*/
    return YVector;

}




// Далее устаревшие куски программы


DoubleVector MeasDataClass::GetPatternDataAt(int FreqIndex, int ElIndex)
{
    /// !!! ADD

   DoubleVector YVector(VNAParameters.NumOfPoi);
/*
    for (int a=0; a<OPUParameters.AzTrigPoints; a++)
    {
        YVector[a] = 20 * log10(a(ReadFromRawDataTrgtArr(FreqIndex,a,ElIndex)));
    }
*/
    return YVector;
}

QVector<std::complex<double>> MeasDataClass::GetBcknd()
{
   // return GetVectorAmplitudeIndB( RawDataBackgroundArray );
    return RawDataBackgroundArray;
}

QVector<std::complex<double> > MeasDataClass::GetResponseRawData()
{
   // return GetVectorAmplitudeIndB (RawDataResponseArray );
    return RawDataResponseArray;

}

void MeasDataClass::GetResponseRawData(QVector<std::complex<double>> &Dest)
{
   // GetVectorAmplitudeIndB(RawDataResponseArray, Dest);
    Dest = RawDataResponseArray;
}

void MeasDataClass::GetBcknd(QVector<std::complex<double>> &Dest)
{
   // GetVectorAmplitudeIndB(RawDataBackgroundArray, Dest);
    for(int i=0; i<Dest.size(); i++) Dest[i] = RawDataBackgroundArray[i];

}

QVector<std::complex<double>> MeasDataClass::GetCalibrArray()
{
    return CalibrationArray;
}





void MeasDataClass::ClearBackgroundData()
{
    /*Resize(0,0,0);

    VNAParameters.NumOfPoi = 0;
    OPUParameters.AzTrigPoints = 0;
    OPUParameters.ElTrigPoints = 0;

    VNAParameters.StartFreq = 0;
    OPUParameters.startAzAngl = 0;
    OPUParameters.startElAngl = 0;

    VNAParameters.StopFreq = 0;
    OPUParameters.stopAzAngl = 0;
    OPUParameters.stopElAngl = 0;
*/

    RawDataBackgroundArray.clear();
}

void MeasDataClass::ClearTargetMeasData()
{
    RawDataTargetArray.clear();
}

void MeasDataClass::ClearResponseData()
{
    RawDataResponseArray.clear();
}

void MeasDataClass::ClearAllMeasData()
{
    RawDataBackgroundArray.clear();
    RawDataTargetArray.clear();
    RawDataResponseArray.clear();
}

void MeasDataClass::SetDefaultParams()
{
    OPUParams DefaultOPUPars;
    VNAParams DefaulVNAPars;

}


DoubleVector MeasDataClass::GetDistVector()
{
    DoubleVector Result(VNAParameters.NumOfPoi);
    for (int d=0; d<VNAParameters.NumOfPoi; d++)
    {
        Result[d] = d; // Как правильно считать я не знаю пока
    }
    return Result;
}



void MeasDataClass::SetRefTarget(QString type, double radius, double height)
{
    RefTarget.SetRefTargetType(type);

    if (type == "Sphere") RefTarget.Sphere.SetSphereParams(radius);

    else if (type == "Cylinder") RefTarget.Cylinder.SetCylinderParams(radius, height);

}

