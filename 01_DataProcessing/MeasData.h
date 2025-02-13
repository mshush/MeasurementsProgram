#ifndef MEASDATA_H
#define MEASDATA_H

#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>
#include <referencetarget.h>
#include "common.h"

class MeasDataClass
{

public:
    enum class DataPrescType{REAL32, REAL}DataType;

    struct VNAParams
    {
        QString ip = "192.168.0.83";
        int port = 5025;
        int Pow = 0;
        double StartFreq = 1;
        double StopFreq = 20;
        int NumOfPoi = 1601;
        int IF = 10000;
        QString Datatype = "double";
        QString MeasParameter = "S21";

        void CopyTo(VNAParams Dest)
        {
            Dest.ip = ip;
            Dest.port = port;
            Dest.Pow = Pow;
            Dest.StartFreq = StartFreq;
            Dest.StopFreq = StopFreq;
            Dest.NumOfPoi = NumOfPoi;
            Dest.IF = IF;
            Dest.Datatype = Datatype;
            Dest.MeasParameter = MeasParameter;
        }

    };

    struct OPUParams
    {
        double startAzAngl = 0;
        double stopAzAngl = 360;
        double startElAngl = 0;
        double stopElAngl = 0;
        int Speed = 1;
        int AzTrigPoints = 3600;
        int ElTrigPoints = 1;
        QString MoveMode = "CCW";
    };
    MeasDataClass();
    ~MeasDataClass();

    void SetRawBcknd(ComplexVector MeasuredBackground);
    void SetRawResponse  (ComplexVector MeasuredResponse);
    void SetRawBcknd(double* MeasuredBackgroundRe, double* MeasuredBackgroundIm);
    void SetRawResponse  (double* MeasuredResponseRe, double* MeasuredResponseIm);
    void SetProcessedResponse  (ComplexVector MeasuredResponse);


    void SetAllVNAParamsNoAction(int Pow, \
    double StartFreq, \
    double StopFreq, \
    int NumOfPoi, \
    int IF, \
    QString Datatype, \
    QString MeasParameter);

    void SetAllOPUParamsNoAction(
    double startAzAngl,\
    double stopAzAngl,\
    double startElAngl,\
    double stopElAngl,\
    int Speed,\
    int AzTrigPoints,\
    int ElTrigPoints,\
    QString MoveMode
        );

    OPUParams getOPUParameters() const;
    void SetAllOPUParametersNoAction(const OPUParams &newOPUParameters);
    VNAParams getVNAParameters() const;
    void SetAllVNAParametersNoAction(const VNAParams &newVNAParameters);
    void SetRefTarget(QString type,double radius, double height = 0);

    void SetTCPParsNoAction(QString Ip, int Port);
    void SetFreqRangesNoAction(double StartFreq,double StopFreq, int NumOfPoints );
    void SetIFNoAction(int IF);
    void SetDataTypeNoAction(QString Type);
    void SetPower(double PowdB);

    void SetMeasParameterNoAction(QString SParameter);
    void SetAzAnglRangesNoAction(double StartAngle, double StopAngle, int NAztrigPoints);
    void SetElAnglRangesNoAction(double StartAngle, double StopAngle, int NElTrigPoints);
    void SetMoveModeNoAction(QString Movmode);
    void SetOPUSpeed(int Speed);

    int GetTCPPort();
    QString GetIP();
    int GetNumOfFreqSweepPoints();
    double GetStartFreq();
    double GetStopFreq();
    int GetIF();
    QString GetDataType();
    QString GetMeasParameter();
    double GetStartAzAngl();
    double GetStopAzAngl();
    double GetStartElAngl();
    double GetStopElAngl();
    double GetPower();
    int GetAzTrigPoints();
    int GetElTrigPoints();
    QString GetMoveMode();
    int GetOPUSpeed();

    DoubleVector GetDistVector();
    DoubleVector GetFreqVector ();
    DoubleVector GetAzimuthVector();
    DoubleVector GetElevationVector ();


    DoubleVector GetPatternSweepAtAngles            (int AzIndex, int ElIndex);
    DoubleVector GetPatternDataAt(int FreqIndex, int ElIndex = 0);
    ComplexVector GetRawSweepDataAt(int AzIndex, int ElIndex);
    ComplexVector GetBcknd();
   ComplexVector GetResponseRawData();
    void GetResponseRawData(ComplexVector &Dest);
    void GetBcknd(ComplexVector &Dest);
    ComplexVector GetCalibrArray();

    void ClearBackgroundData();
    void ClearTargetMeasData();
    void ClearResponseData();
    void ClearAllMeasData();
    void SetDefaultParams();

   ComplexVector DownSample(ComplexVector MyVector);

    int FindAzimuthIndex(double AzimuthValue);
    int FindElevationIndex(double ElevationValue);
    double FindAzimuthValue      (int AzIndex);
    double FindElevationValue    (int ElIndex);
    std::complex<double> ReadFromRawDataTrgtArr (int FreqIndex, int AzIndex, int ElIndex);

    void SetSweepAtAngl(ComplexVector FreqVect, int AzIndex, int ElIndex = 0);
    void SetSweepAtAngl( double* FreqVectRe, double* FreqVectIm, int AzIndex, int ElIndex = 0);
    void AppendSweepToTargetRawDataArr(ComplexVector FreqSweep);
    void AppendSingleAngleSweepToDiag(ComplexVector ProcessedAngleSweep);

    void SetValueTargetRawDataArr(int FreqIndex, int AzIndex, int ElIndex, std::complex<double> NewValue);
    void setBUseBckndCal(bool newBUseBckndCal);
    void setBUseRspCal(bool newBUseRspCal);

    int getPatternViewFreq() const;
    void setPatternViewFreq(int newPatternViewFreq);

private:

    DoubleVector &GetVectorAmplitudeIndB(ComplexVector Vector);
    void GetVectorAmplitudeIndB(ComplexVector SourceVector, DoubleVector& DestVector);

    bool bUseBckndCal;
    bool bUseRspCal;

    int PatternViewFreq;
    ComplexVector RawDataTargetArray;
    ComplexVector RawDataBackgroundArray;
    ComplexVector RawDataResponseArray;

    ComplexVector CalibrationArray;
    ComplexVector PatternAtAllFreqsArray;

    VNAParams VNAParameters;
    OPUParams OPUParameters;

    ReferenceTarget RefTarget;

    int CurrentAzimuthIndex = 0;
    int CurrentElevationIndex = 0;
    int CurrentIndex = 0;


 };





#endif // MEASDATA_H
