#ifndef MEASDATA_H
#define MEASDATA_H

#include <complex>
//#include <QDataStream>
#include <map>
#include "include_/complexdatavector.h"

#include "include_/reftargetclass.h"
using QComplexVector = QVector<std::complex<double>>;
using QDoubleVector = QVector<double>;
//using QComplexVector = std::vector<std::complex<double>>;
//using QDoubleVector = std::vector<double>;

#define LightVel 299792458
/**
 * @brief MeasData class contains parameters and arrays of stored data.
 */
class MeasDataClass
{



public:


    enum class MeasDataType {
        RawTarget,
        RawBcknd,
        RawRsp,

        ProcessedBcknd,
        CalibrationArr,
        PatternArr,

        CurrentAspect,
        CurrentProfRange,
        CurrentGatedProfRange
    };

    struct VNAParams
    {
        QString ip = "192.168.0.83";
        int port = 5025;
        int Pow = 0;
        double StartFreq = 2;
        double StopFreq = 4;
        int NumOfPoi = 1601;
        int IF = 10000;
        QString Datatype = "double";
        QString MeasParameter = "S21";

        void setParameters(const QString& newIp, int newPort, int newPow, \
                           double newStartFreq, double newStopFreq, \
                           int newNumOfPoi, int newIF, const QString& newDatatype,\
                           const QString& newMeasParameter)
        {
            ip = newIp;
            port = newPort;
            Pow = newPow;
            StartFreq = newStartFreq;
            StopFreq = newStopFreq;
            NumOfPoi = newNumOfPoi;
            IF = newIF;
            Datatype = newDatatype;
            MeasParameter = newMeasParameter;
        }

        void CopyTo(VNAParams& Dest) const;

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

        void CopyTo(OPUParams& Dest) const;

        void setParameters(double newStartAzAngl, double newStopAzAngl,\
                           double newStartElAngl, double newStopElAngl, \
                           int newSpeed, int newAzTrigPoints, int newElTrigPoints,\
                           const QString& newMoveMode)
        {
            startAzAngl = newStartAzAngl;
            stopAzAngl = newStopAzAngl;
            startElAngl = newStartElAngl;
            stopElAngl = newStopElAngl;
            Speed = newSpeed;
            AzTrigPoints = newAzTrigPoints;
            ElTrigPoints = newElTrigPoints;
            MoveMode = newMoveMode;
        }


    };

    struct PrimaryProcParams
    {
        int Nfft = 2048;
        int FilterNumTaps = 101;
        bool bUseGate = true;
        QString GateType = "Rect";
        bool bUseBcknd = true;
        bool bUseRspCalibr = true;
        double quietzone_xinit = 38;
        double quietzone_xfin = 48;
        int PatterFreqViewIndx = 0;
        //QComplexVector FilterCoeffs;
        //QComplexVector RefTargetArr;
        void CopyTo(PrimaryProcParams& Dest) const;

        void setParameters(int newFilterNumTaps, bool newBUseGate, \
                               const QString& newGateType, bool newBUseBcknd,\
                               bool newBUseRspCalibr, double newQuietzoneXinit, \
                               double newQuietzoneXfin, int newPatterFreqViewIndx)
        {
            FilterNumTaps = newFilterNumTaps;
            bUseGate = newBUseGate;
            GateType = newGateType;
            bUseBcknd = newBUseBcknd;
            bUseRspCalibr = newBUseRspCalibr;
            quietzone_xinit = newQuietzoneXinit;
            quietzone_xfin = newQuietzoneXfin;
            PatterFreqViewIndx = newPatterFreqViewIndx;
        }

       // void setFilterCoeffs(QComplexVector coeffs){ FilterCoeffs = coeffs; }
       // void setRefTargetArr(QComplexVector RefTargetArr_){ RefTargetArr = RefTargetArr_; }


    };

    enum class DataPrescType{REAL32, REAL}DataType;
    MeasDataClass();
    void SetDefaultParams()
    {
        OPUParams DefaultOPUPars;
        VNAParams DefaulVNAPars;
        PrimaryProcParams DefaultProcPrarams;
        SetAllVNAParamsNoAction(DefaulVNAPars);
        SetAllOPUParamsNoAction(DefaultOPUPars);
        //SetZeroVector(MeasDataType::CurrentGatedProfRange, DefaultProcPrarams.Nfft);
        //SetZeroVector(MeasDataType::CurrentProfRange, DefaultProcPrarams.Nfft);
    }
    ~MeasDataClass();


    void SetAllVNAParamsNoAction(double Pow, \
                                 double StartFreq, \
                                 double StopFreq, \
                                 int NumOfPoi, \
                                 int IF, \
                                 QString Datatype, \
                                 QString MeasParameter)
    {

        SetFreqRangesNoAction(StartFreq, StopFreq, NumOfPoi);
        SetIFNoAction(IF);
        SetPowerNoAction(Pow);
        SetMeasParameterNoAction(MeasParameter);
    }



    void SetAllVNAParamsNoAction( VNAParams &newVNAParameters)
    {
        SetFreqRangesNoAction(newVNAParameters.StartFreq, newVNAParameters.StopFreq, newVNAParameters.NumOfPoi);
        SetIFNoAction(newVNAParameters.IF);
        SetPowerNoAction(newVNAParameters.Pow);
        SetMeasParameterNoAction(newVNAParameters.MeasParameter);

        //VNAParameters.CopyTo(newVNAParameters);
        //int N = VNAParameters.NumOfPoi;
        //SetZeroVector(MeasDataType::RawBcknd, N);
        //SetZeroVector(MeasDataType::RawRsp, N);
        //SetZeroVector(MeasDataType::CalibrationArr, N);
        //SetOnesVector(MeasDataType::CalibrationArr, N);
        //SetZeroVector(MeasDataType::CurrentAspect, N);
        //SetZeroVector(MeasDataType::CurrentGatedProfRange, DataProcParams.Nfft);
        //SetZeroVector(MeasDataType::CurrentProfRange, DataProcParams.Nfft);
        //SetNPointsPerSweep(MeasDataType::RawTarget, N);
        //SetNPointsPerSweep(MeasDataType::PatternArr, N);
    }
    VNAParams getVNAParameters() const;

    void SetAllOPUParamsNoAction(
        double startAzAngl,\
        double stopAzAngl,\
        double startElAngl,\
        double stopElAngl,\
        int Speed,\
        int AzTrigPoints,\
        int ElTrigPoints,\
        QString MoveMode
        )
    {
        SetAzAnglRangesNoAction(startAzAngl,stopAzAngl, AzTrigPoints);
        SetElAnglRangesNoAction(startElAngl, stopElAngl, ElTrigPoints);
        SetMoveModeNoAction(MoveMode);
        SetOPUSpeedNoAction(Speed);
    }

    void SetAllOPUParamsNoAction(const OPUParams &newOPUParameters)
    {
        SetAzAnglRangesNoAction(newOPUParameters.startAzAngl,newOPUParameters.stopAzAngl, newOPUParameters.AzTrigPoints);
        SetElAnglRangesNoAction(newOPUParameters.startElAngl, newOPUParameters.stopElAngl, newOPUParameters.ElTrigPoints);
        SetMoveModeNoAction(newOPUParameters.MoveMode);
        SetOPUSpeedNoAction(newOPUParameters.Speed);
        //OPUParameters = newOPUParameters;
        //SetNAz(MeasDataType::RawTarget, OPUParameters.AzTrigPoints);
        //SetNAz(MeasDataType::PatternArr,  OPUParameters.AzTrigPoints);
        //SetNEl(MeasDataType::RawTarget, OPUParameters.ElTrigPoints);
        //SetNEl(MeasDataType::PatternArr, OPUParameters.ElTrigPoints);
    }
    OPUParams getOPUParameters() const;

    void SetAllProcParamsNoAction(int Nfft = 2048,
                                  int FilterNumTaps = 101,
                                  bool bUseGate = true,
                                  QString GateType = "Rect",
                                  bool bUseBcknd = true,
                                  bool bUseRspCalibr = true,
                                  double quietzone_xinit = 38,
                                  double quietzone_xfin = 48,
                                  int PatterFreqViewIndx = 0)
    {
        setNfft(Nfft);
        setFilterNumTaps(FilterNumTaps);
        setBUseGate(bUseGate);
        setGateType(GateType);
        setQuietZoneParams(quietzone_xinit, quietzone_xfin);
        setBUseRspCal(bUseRspCalibr);
        setBUseBckndCal(bUseBcknd);
        setPatternViewFreq(PatterFreqViewIndx);

    }



    void SetAllProcParamsNoAction( PrimaryProcParams &newProcParameters)
    {
        setNfft(newProcParameters.Nfft);
        setFilterNumTaps(newProcParameters.FilterNumTaps);
        setBUseGate(newProcParameters.bUseGate);
        setGateType(newProcParameters.GateType);
        setBUseRspCal(newProcParameters.bUseRspCalibr);
        setBUseBckndCal(newProcParameters.bUseBcknd);
        setQuietZoneParams(newProcParameters.quietzone_xinit, newProcParameters.quietzone_xfin);
        setPatternViewFreq(newProcParameters.PatterFreqViewIndx);
    }
    PrimaryProcParams getAllProcParamsNoAction() const;

    void SetFreqRangesNoAction(double StartFreq,double StopFreq, int NumOfPoints )
    {
        VNAParameters.StartFreq = StartFreq;
        VNAParameters.StopFreq = StopFreq;
        int N = VNAParameters.NumOfPoi;
        if (N != NumOfPoints) {
            VNAParameters.NumOfPoi = NumOfPoints;
            SetNPointsPerSweep(MeasDataType::RawBcknd, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::RawRsp, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::CalibrationArr, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::ProcessedBcknd, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::RawTarget, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::PatternArr, NumOfPoints);
            SetNPointsPerSweep(MeasDataType::CurrentAspect, NumOfPoints);
            //SetNPointsPerSweep(MeasDataType::CurrentGatedProfRange, DataProcParams.Nfft);
            //SetNPointsPerSweep(MeasDataType::CurrentProfRange, DataProcParams.Nfft);

        }
        //SetZeroVector(MeasDataType::RawBcknd, NumOfPoints);
        //SetZeroVector(MeasDataType::RawRsp, NumOfPoints);
        //SetZeroVector(MeasDataType::CalibrationArr, NumOfPoints);
        //SetOnesVector(MeasDataType::CalibrationArr, NumOfPoints);
        //SetNPointsPerSweep(MeasDataType::RawTarget, NumOfPoints);
        //SetNPointsPerSweep(MeasDataType::PatternArr, NumOfPoints);
        //SetZeroVector(MeasDataType::CurrentAspect, NumOfPoints);
        //SetZeroVector(MeasDataType::CurrentGatedProfRange, DataProcParams.Nfft);
        //SetZeroVector(MeasDataType::CurrentProfRange, DataProcParams.Nfft);

    }

    void SetAzAnglRangesNoAction(double StartAngle, double StopAngle, int NAztrigPoints)
    {
        OPUParameters.startAzAngl = StartAngle;
        OPUParameters.stopAzAngl = StopAngle;
        int N = OPUParameters.AzTrigPoints;

        if( N != NAztrigPoints)
        {
            OPUParameters.AzTrigPoints = NAztrigPoints;
            SetNAz(MeasDataType::RawTarget, NAztrigPoints);
            SetNAz(MeasDataType::PatternArr, NAztrigPoints);
        }

    }
    void SetElAnglRangesNoAction(double StartAngle, double StopAngle, int NElTrigPoints)
    {
        OPUParameters.startElAngl = StartAngle;
        OPUParameters.stopElAngl = StopAngle;

        int N = OPUParameters.ElTrigPoints;

        if( N != NElTrigPoints)
        {
            OPUParameters.ElTrigPoints = NElTrigPoints;
            SetNEl(MeasDataType::RawTarget, NElTrigPoints);
            SetNEl(MeasDataType::PatternArr, NElTrigPoints);
        }
    }




    void SetZeroVector(MeasDataType Type, int Npoints, int NAz = 1, int NEl = 1)
    {
       DataArray[Type].SetZeroVector( Npoints,  NAz,  NEl);
    }

    void SetZeroVector(MeasDataType Type)
    {
        if (Type!= MeasDataType::CurrentGatedProfRange && Type != MeasDataType::CurrentProfRange)
        {
        DataArray[Type].SetZeroVector( GetNFreqPoints(),  GetAzTrigPoints(),  GetElTrigPoints());
        }
        else DataArray[Type].SetZeroVector(DataProcParams.Nfft);
    }


    void setPatternViewFreq(double newPatternViewFreq);
    void setBUseBckndCal(bool newBUseBckndCal);
    void setBUseRspCal(bool newBUseRspCal);
    void setBUseGate(bool boolUseGate);
    void setGateType(QString GateType);
    void setFilterNumTaps(int num_taps);
    void setQuietZoneParams(double x_1, double x_2);
    void setNfft(int newNfft)
    {
        int N = DataProcParams.Nfft;
        if (N != newNfft)
        {
            DataProcParams.Nfft = newNfft;
            SetNPointsPerSweep(MeasDataType::CurrentGatedProfRange, newNfft);
            SetNPointsPerSweep(MeasDataType::CurrentProfRange, newNfft);
        }
    }
    void SetTCPParsNoAction(QString Ip, int Port);
    void SetIFNoAction(int IF);
    void SetDataTypeNoAction(QString Type);
    void SetPowerNoAction(double PowdB);
    void SetMeasParameterNoAction(QString SParameter);
    void SetMoveModeNoAction(QString Movmode);
    void SetOPUSpeedNoAction(int Speed);
    //void SetFilterCoeffs(QComplexVector FilterC);
    //QComplexVector GetFilterCoeffs();
    //QComplexVector GetRefTargetArr();
    int GetTCPPort();
    QString GetIP();
    int GetNFreqPoints();
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
    /**
     * @brief Adds two numbers.
     *
     * This function takes two integers and returns their sum.
     *
     * @param a The first number.
     * @param b The second number.
     * @return The sum of the two numbers.
     */
    int GetOPUSpeed();

/**
* @return Vector of distances for profile range (time-domain).
*/
    QDoubleVector GetDistVector();
    QDoubleVector GetFreqVectorGHz();
    QDoubleVector GetFreqVectorHz();

    QDoubleVector GetAzimuthVector();
    QDoubleVector GetElevationVector ();
    int GetFilterNumTaps();
    double GetXinitQuietZone();
    double GetXfinQuietZone();
    QString GetFilterType();
    int getiPatternViewFreq() const;
    void setPatternViewFreq(int newPatternViewFreqIndex);
    bool GetBUseGate();
    bool GetBUseBcknd();
    bool GetBUseRspCal();

    int FindAzIndex(double AzimuthValue);
    int FindElIndex(double ElevationValue);
    double FindAzValue      (int AzIndex);
    double FindElValue    (int ElIndex);


    void WriteValueAt(MeasDataType Type, const std::complex<double> ComplexVal, int FreqIndx, int AzIndx = 0, int ElIndx = 0);
    int WriteSweepAt(MeasDataType Type, const QComplexVector ComplexSweepData, int AzIndx = 0, int ElIndx = 0);
    void ClearData(MeasDataType Type);
    void ReadSweepFrom(MeasDataType Type, QComplexVector& ComplexSweepDataDest, int AzIndx = 0, int ElIndx = 0);
    QComplexVector ReadSweepFrom(MeasDataType Type, int AzIndx = 0, int ElIndx = 0);
    std::complex<double> ReadValueFrom(MeasDataType Type, int Findx, int AzIndx = 0, int ElIndx = 0);

    void GetAmplVectordB(MeasDataType Type, QDoubleVector &Dest, int AzIndx = 0, int ElIndx = 0);
    void GetAmplVectorSqrt(MeasDataType Type, QDoubleVector &Dest, int AzIndx = 0, int ElIndx = 0);
    QDoubleVector GetAmplVectordB(MeasDataType Type,int AzIndx = 0, int ElIndx = 0);
    QDoubleVector GetAmplVectorSqrt(MeasDataType Type,int AzIndx = 0, int ElIndx = 0);

    void SetRefTarget(QString type, double radius, double height = 0)
    {
        if (type == "Cylinder")
        {
            RefTarget.setObjectType(RefTargetClass::CYLINDER);
            RefTarget.setCylinderParameters(radius, height);
        }
        else if (type == "Sphere")
        {
            RefTarget.setObjectType(RefTargetClass::SPHERE);
            RefTarget.setSphereParameters(radius);
        }
        else {
            throw std::invalid_argument("SetRafTarget: invalid type of target");
        }
    }
    QDoubleVector CalcRefTargetArr(double FStartGHz, double FStopGHz, int NFreqPoints);
    QComplexVector CalcRefTargetArr();

private:

    QDoubleVector RefArr;
    RefTargetClass RefTarget;
    VNAParams VNAParameters;
    OPUParams OPUParameters;
    PrimaryProcParams DataProcParams;
    std::map<MeasDataType, ComplexDataVector> DataArray;

    void SetNPointsPerSweep(MeasDataType Type, int NFreq)
    {
        //setPatternViewFreq((int)(NFreq/2));
        DataArray[Type].SetNPoinPerSweep( NFreq);
    }
    void SetNAz(MeasDataType Type, int NAz)
    {
        DataArray[Type].SetNAz(NAz);
    }
    void SetNEl(MeasDataType Type, int NEl)
    {
        DataArray[Type].SetNEl(NEl);

    }
/*
    ComplexDataVector RawDataTarget;
    ComplexDataVector RawDataResponse;
    ComplexDataVector RawDataBcknd;

    ComplexDataVector CurrentAspectData;
    ComplexDataVector CurrentProfRange;
    ComplexDataVector CurrentGatedProfRange;

    ComplexDataVector ProcessedBcknd;
    ComplexDataVector CalibratedPatternData;
    ComplexDataVector CalibrationData;
*/

    //int iPatternViewFreq;

 };





#endif // MEASDATA_H
