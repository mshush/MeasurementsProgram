#include "measurmentscontrol.h"
#include <math.h>
#include <QDir>

//#define OPU_VNA_SIMULATION;
#define OPU_SIMULATION;

QComplexVector MeasurmentsControl::TempTrgtRawDataArr;
double* MeasurmentsControl::TargetDataTempIm;
double* MeasurmentsControl::TargetDataTempRe;
QString MeasurmentsControl::Debug;
std::mutex measMutex;
std::atomic<bool> new_data_available(false); // Атомарный флаг
std::atomic<bool> boolAbort(false);


MeasurmentsControl::MeasurmentsControl(QWidget *parent)
    : QWidget{parent}
{
}

bool readFileAndStoreData1(const QString& filePath, QVector<double>& column1, QVector<std::complex<double>>& column2and3)
{ // function For loading data from C4420 programm to verify filter work
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(", ", Qt::SkipEmptyParts);
        if (parts.size() != 3)
        {
            qWarning() << "Invalid line format:" << line;
            continue;
        }

        bool ok1, ok2, ok3;
        double value1 = parts[0].toDouble(&ok1);
         double amplitudeDB = parts[1].toDouble(&ok2);
        double phase = parts[2].toDouble(&ok3);

        if (!ok1 || !ok2 || !ok3)
        {
            qWarning() << "Failed to parse numbers in line:" << line;
            continue;
        }

        double phaseRadians = phase * M_PI / 180.0;
        double amplitudeLinear = std::pow(10.0, amplitudeDB / 20.0);

        std::complex<double> complexNumber = std::polar(amplitudeLinear, phaseRadians);
        column1.append(value1);
        column2and3.append(complexNumber);

    }

    qDebug() << "all done";

    file.close();
    return true;
}


void MeasurmentsControl::MeasureBckgndAtSingleAngl(MeasDataClass &MeasData)
{
    ResetAbort();
    QComplexVector Bcknd;
    MeasureCurrentAspectInternal(MeasData.getVNAParameters(), Bcknd);
    PrimaryProcessSweep(MeasDataClass::MeasDataType::RawBcknd, Bcknd, MeasData);
}

void MeasurmentsControl::MeasureCurrentAspect(MeasDataClass &MeasData)
{
    ResetAbort();
    QComplexVector CurrentAspectData;
    MeasureCurrentAspectInternal(MeasData.getVNAParameters(), CurrentAspectData);
    PrimaryProcessSweep(MeasDataClass::MeasDataType::CurrentAspect, CurrentAspectData, MeasData);
}

void MeasurmentsControl::MeasureResponseAtSignleAngl(MeasDataClass& MeasData)
{
    ResetAbort();
    QComplexVector Rsp;
    MeasureCurrentAspectInternal(MeasData.getVNAParameters(), Rsp);
    PrimaryProcessSweep(MeasDataClass::MeasDataType::RawRsp, Rsp, MeasData);
}


void MeasurmentsControl::MeasureAzTarget(MeasDataClass& MeasData)
{

    ResetAbort();
    //MeasData.SetFilterCoeffs(Filter.FirWin(MeasData.GetFilterNumTaps(),\
    MeasData.GetXinitQuietZone()/LightVel, MeasData.GetXfinQuietZone()/LightVel,\
    MeasData.GetNFreqPoints(), MeasData.GetFilterType()));

    std::thread MeasThread(MeasureAzTargetThread,MeasData.getVNAParameters(), MeasData.getOPUParameters());
    MeasThread.detach();


    if (bNoError) {
        int iAz = 0;

    while(!(bAbort))
    {
        MainThreadEventsUpdate();


        if(IsNewDataAvail()) {
            {
                std::lock_guard<std::mutex> lk(measMutex);
                MeasData.WriteSweepAt(MeasDataClass::MeasDataType::RawTarget, TempTrgtRawDataArr, iAz);
                 qDebug() << iAz << " iAz prcoessed";
                qDebug() <<  TempTrgtRawDataArr[0].real();

                //new_data_available.store(false, std::memory_order_release);
                SetbNewDataAvail(false);
            }
            QComplexVector TempVector;
            if (!(bAbort)){

                TempVector = MeasData.ReadSweepFrom(MeasDataClass::MeasDataType::RawTarget,iAz);
                PrimaryProcessSweep(MeasDataClass::MeasDataType::RawTarget, TempVector, MeasData, iAz);
                MainThreadEventsUpdate();
                //qDebug() << iAz << " iAz prcoessed";
                updateGraph(iAz, 0);
                //qDebug() <<  TempVector[0].real();
                iAz++;
            }


        }

    }
    }

}

void MeasurmentsControl::MeasureAzTargetThread(MeasDataClass::VNAParams params, MeasDataClass::OPUParams opuParams)
{
    bool bNoError = true;
    TargetDataTempIm = new double[params.NumOfPoi];
    TargetDataTempRe = new double[params.NumOfPoi];
    TempTrgtRawDataArr.resize(params.NumOfPoi);

#ifdef OPU_VNA_SIMULATION

    VNA VNA_;
    OPU opu;
    //VNA_.SimulateTriggerOPU(&opu); // for simulation only
    //opu.MoveAzFromTo();

    for (int i = 0; i < opuParams.AzTrigPoints; i++)
    {
        VNA_.MeasureTestSingleSweep();

        {
            std::lock_guard<std::mutex> lock(measMutex);
            if(IsbAbort()) break;
            VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);
            for(int i =0; i< params.NumOfPoi; i++)
            {TempTrgtRawDataArr[i] = (std::complex(TargetDataTempRe[i],TargetDataTempIm[i]));}
        }

        SetbNewDataAvail(true);
    }
    //opu.StopSimTrig();

#endif

#ifdef OPU_SIMULATION

    VNA VNA_;
    OPU opu;
    //bool IsExtTriggerOn = true;
    bNoError = VNA_.ConnectToSocket(params.ip, params.port);
    //bNoError = opu.ConnectToOPU();
    bool IsExtTriggerOn = false;
    qDebug() << "meas";

    if(bNoError) bNoError = VNA_.SetAllParameters(IsExtTriggerOn,\
                                                 QString::number(params.StartFreq),\
                                                 QString::number(params.StopFreq),\
                                                 QString::number(params.Pow),\
                                                 params.NumOfPoi,\
                                                 params.MeasParameter,\
                                                 params.Datatype,\
                                                 params.IF);

    qDebug() << "params";
      /*
    if (opuParams.MoveMode == "CCW") {
    if (bNoError) bNoError = opu.SetOPUParameters(opuParams.startAzAngl, opuParams.stopAzAngl, \
    opuParams.AzTrigPoints, opuParams.Speed, OPU::MoveMode::CCW);
    }
    else
    {
    if (bNoError) bNoError = opu.SetOPUParameters(opuParams.startAzAngl, opuParams.stopAzAngl, \
        opuParams.AzTrigPoints, opuParams.Speed, OPU::MoveMode::CW);
    }*/

    //VNA_.SimulateTriggerOPU(&opu); // for simulation only

    //opu.MoveAzFromTo();

    //VNA_.NumOfPoi = params.NumOfPoi;

    for (int i = 0; i < opuParams.AzTrigPoints; i++)
    {
                if(IsbAbort()) break;

               VNA_.MeasureSingleSweep();
                _sleep(500);
                {
                std::lock_guard<std::mutex> lock(measMutex);
                VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);

                }
                for(int i =0; i< params.NumOfPoi; i++) TempTrgtRawDataArr[i] = std::complex(TargetDataTempRe[i],TargetDataTempIm[i]);
                qDebug() <<  'TargetDataTempRe = ' << TargetDataTempRe[0];

                SetbNewDataAvail(true);

    }

    VNA_.DisconnectFromSocket();

    //opu.StopSimTrig();

#endif

#ifndef OPU_VNA_SIMULATION
#ifndef OPU_SIMULATION
    VNA VNA_;
    OPU opu;
    bNoError = VNA_.ConnectToSocket(params.ip, params.port);
    //if (bNoError) bNoError = opu.ConnectToOPU();
    bool IsExtTriggerOn = true;
    qDebug() << "meas";

    if(bNoError) bNoError = VNA_.SetAllParameters(IsExtTriggerOn,\
                                                 QString::number(params.StartFreq),\
                                                 QString::number(params.StopFreq),\
                                                 QString::number(params.Pow),\
                                                 params.NumOfPoi,\
                                                 params.MeasParameter,\
                                                 params.Datatype,\
                                                 params.IF);

    //OPU::MoveMode MM;
    //if (opuParams.MoveMode == "CCW") MM = OPU::MoveMode::CCW;
    //else MM = OPU::MoveMode::CW;

   // if (bNoError) bNoError = opu.SetOPUParameters(opuParams.startAzAngl, opuParams.stopAzAngl, \
        opuParams.AzTrigPoints, opuParams.Speed, MM);

   // if (bNoError) opu.SetCurrentAzAngl(opuParams.startAzAngl);
   // if (bNoError) opu.MoveAzFromTo();

    //VNA_.NumOfPoi = params.NumOfPoi;
    if (bNoError) {
        for (int i = 0; i < opuParams.AzTrigPoints; i++)
        {
            VNA_.MeasureSingleSweep();

            {
                std::lock_guard<std::mutex> lock(measMutex);
                if(bAbort || !bNoError) break;
                //CurrentAz = opu.GetCurrentAzAngl();
                VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);
                for(int i =0; i< params.NumOfPoi; i++) TempTrgtRawDataArr[i] = std::complex(TargetDataTempRe[i],TargetDataTempIm[i]);
            }

            SetbNewDataAvail(true);
            //new_data_available.store(true, std::memory_order_release);

        }
    }

#endif
#endif
}

double integrateArray(QDoubleVector V) {
    double sum = 0.0;
    int N = V.size();
    for (int i = 0; i < N; ++i) {
        sum += V[i];
    }

    return sum;
}

void MeasurmentsControl::PrimaryProcessSweep(MeasDataClass::MeasDataType RawDataType, QComplexVector RawData, MeasDataClass &MeasData, int iAz, int iEl)
{     auto start = std::chrono::high_resolution_clock::now();

    using DataType = MeasDataClass::MeasDataType;
    MeasData.WriteSweepAt(DataType::CurrentAspect, RawData);
    qDebug() << "raw data size: " << RawData.size();

    int N = RawData.size();
    double f2 = MeasData.GetStopFreq();
    double f1 = MeasData.GetStartFreq();
    double hf = (f2-f1)/((double)N);

    QComplexVector FilteredData;
    QComplexVector ProfRange;
    QComplexVector GatedProfRange;

 /*   ProcClass.FFT(RawData, ProfRange);
    ProcClass.FFTShift(ProfRange);
    ProcClass.FFTPhaseCorrection(ProfRange, f1, f2, N);
    ProcClass.FFTNorm(ProfRange, hf); //???
*/
    ProfRange = ProcClass.FFTWithPhsCorrectionAndNorm(RawData, f1, f2);

    MeasData.WriteSweepAt(DataType::CurrentProfRange, ProfRange);
    qDebug() << "Profrange written";

    if (MeasData.GetBUseGate()) {
            int s = MeasData.GetDistVector().size();
            double l = MeasData.GetDistVector()[s-1];

            QComplexVector Filter_coeffs = Filter.FirWin(MeasData.GetFilterNumTaps(),\
            MeasData.GetXinitQuietZone() - l*0.5, MeasData.GetXfinQuietZone() - l*0.5,\
             l*0.5, MeasData.GetFilterType());
            FilteredData = Filter.FilterSignalFIR(Filter_coeffs, RawData);
            //MeasData.WriteSweepAt(    DataType::CalibrationArr, FilteredData);
            if (RawDataType == DataType::RawRsp)
            {
            FilteredData;
            int i = 0;
            i++;
            }
           /* ProcClass.FFT(FilteredData, GatedProfRange);
            ProcClass.FFTShift(GatedProfRange);
            ProcClass.FFTPhaseCorrection(GatedProfRange, f1, f2, N);
            ProcClass.FFTNorm(GatedProfRange, hf);
*/
            GatedProfRange = ProcClass.FFTWithPhsCorrectionAndNorm(FilteredData, f1, f2);

            MeasData.WriteSweepAt(DataType::CurrentGatedProfRange, GatedProfRange);
            qDebug() << "Gated Profrange written";

    }

    else {
      FilteredData = RawData;
    }

    if (RawDataType == DataType::RawTarget)
    {

        try {
            if (MeasData.GetBUseBcknd()){
               FilteredData = ProcClass.SubtractVect(FilteredData, MeasData.ReadSweepFrom(DataType::RawBcknd));
            }
          }
          catch(QString mess)
          {
               qDebug() << mess;
               return;
          }
          try{
               //MeasData.ReadSweepFrom(DataType::CalibrationArr);
               if (MeasData.GetBUseRspCal()){
                FilteredData = ProcClass.DivVect(FilteredData, MeasData.ReadSweepFrom(DataType::CalibrationArr));
               }
          }
          catch(QString mess)
          {

               qDebug() << mess;
               return;
          }

           MeasData.WriteSweepAt(DataType::PatternArr, FilteredData, iAz, iEl);
           auto end = std::chrono::high_resolution_clock::now();
           auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
           qDebug() << "processing time: " << duration << "ms";

            return;


    }
    else if(RawDataType == DataType::RawBcknd)
    {
        MeasData.WriteSweepAt(DataType::RawBcknd, RawData);
        MeasData.WriteSweepAt(DataType::ProcessedBcknd, FilteredData);
        QComplexVector b(N) ;

        MeasData.ReadSweepFrom(DataType::ProcessedBcknd, b);

        qDebug() << "bkcnd written";

        return;

    }
    else if (RawDataType == DataType::RawRsp)
    {
        MeasData.WriteSweepAt(DataType::RawRsp, RawData);
        qDebug() << "rawrsp written";
        QComplexVector b(N) ;
        if (MeasData.GetBUseBcknd()){
           MeasData.ReadSweepFrom(DataType::ProcessedBcknd, b);
            try{

                FilteredData = ProcClass.SubtractVect(FilteredData,b);
            }
            catch(QString mess)
            {
                qDebug() << mess;
                return;
            }
         }


        if (MeasData.GetBUseRspCal()){
            try{
                int  i = 0;
                FilteredData = ProcClass.DivVect(FilteredData, MeasData.CalcRefTargetArr());
            }
            catch(QString mess)
            {
                qDebug() << mess;
                return;
            }
         }

        MeasData.WriteSweepAt(    DataType::CalibrationArr, FilteredData);
        qDebug() << "calibration written";

        return;
    }

    return;


}


bool MeasurmentsControl::IsNewDataAvail()
{
    return new_data_available.load();
}

void MeasurmentsControl::SetbNewDataAvail(bool bNewDataAvailable)
{
    //if(NewDataAvailable) new_data_available.store(true, std::memory_order_release);
    new_data_available.store(bNewDataAvailable, std::memory_order_release);

}

void MeasurmentsControl::MainThreadEventsUpdate()
{
    QApplication::processEvents();
}
/*
void MeasurmentsControl::StartAzTargetFIFOMeasure()
{
    //SetParametersNoAction();
    //SetOPUParametersNoAction();

    bAbort = false;
    bNoError = true;
    ResetBinaryBuffer();
    NumOfSweeps = AzTrigPoints;
    ExternalTriggerOn = true;

    TargetFullDataMultDim = new double[NumOfPoi*2*NumOfSweeps];
    TargetDataMinusBcknd = new double[NumOfPoi*2*NumOfSweeps];

    std::thread MeasThread(AzTargetFIFOMeasure ,
                           ip , port, "double", StartFreq,  StopFreq,  Pow, NumOfPoi,
                           MeasParameter, IF, NumOfSweeps, ExternalTriggerOn, startAzAngl, stopAzAngl,
                           Speed, AzTrigPoints, MoveMode);
    MeasThread.detach();
    StartUpdatingGrpah();
}
*/
/*
void MeasurmentsControl::AzTargetFIFOMeasure(QString ip, int port, QString type, double StarFreq, double StopFreq, double Pow, int NumOfPoi, QString MeasParameter, int IF, int NumOfSweeps, bool ExtTrigg, double startAz, double stopAz, int Speed, int AzPoi, int MovMode)
{
    QByteArray data;
    VNA VNA_;
    OPU opu;

    bNoError = VNA_.ConnectToSocket(ip, port);
    bNoError = opu.ConnectToOPU();

/*
    if(bNoError) bNoError = VNA_.SetAllParameters(ExtTrigg, QString::number(StarFreq), QString::number(StopFreq), QString::number(Pow), NumOfPoi, MeasParameter, type, IF);
    if (bNoError) bNoError = opu.SetOPUParameters(startAz, stopAz, AzPoi, Speed, MovMode);
    if(bNoError) bNoError = VNA_.SetFIFOCapacity(NumOfSweeps);
    if(bNoError) bNoError = VNA_.SetFIFOStateOn();

    //VNA_.SimulateTriggerOPU(&opu); // for simulation only
    opu.MoveAzFromTo();


    while(!bAbort || bNoError)
    {
            //VNA_.MeasureTestSingleSweep();
            //VNA_.MeasureSingleSweep();
            int n = VNA_.GetFIFONumOfSweeps() ;
            if (n > 0)
            {
                VNA_.GetFIFOSingleSweep();
                {
                    std::lock_guard<std::mutex> lock(MeasBufferMutex);
                    VNA_.ReadFIFOSingleSweep(TargetFullDataMultDim);
                }
            }
    }

    //opu.StopSimTrig();
    VNA_.DisconnectFromSocket();
}
*/


void MeasurmentsControl::MeasureCurrentAspectInternal(MeasDataClass::VNAParams params, double *destReal, double *destIm)
{


    VNA VNA_;
    bool IsExtTriggerOn = false;
#ifndef OPU_VNA_SIMULATION
    try{
    if(bNoError) bNoError = VNA_.ConnectToSocket(params.ip, params.port);
    }
    catch (QString mess)
    {
        qDebug() << mess;
        return;
    }
    if(bNoError) bNoError = VNA_.Preset();
    if(bNoError) bNoError = VNA_.SetAllParameters(IsExtTriggerOn,\
                                         QString::number(params.StartFreq),\
                                         QString::number(params.StopFreq),\
                                         QString::number(params.Pow),\
                                         params.NumOfPoi,\
                                         params.MeasParameter,\
                                         params.Datatype,\
                                         params.IF);
    //if(bNoError) bNoError = VNA_.SetAllParametersObsolete(IsExtTriggerOn,\
                                         QString::number(params.StartFreq),\
                                         QString::number(params.StopFreq),\
                                         QString::number(params.Pow),\
                                         params.NumOfPoi,\
                                         params.MeasParameter,\
                                         params.Datatype,\
                                         params.IF);
    if(bNoError)
    {
    VNA_.MeasureSingleSweep();
        {
            VNA_.ReadSingleSweep(destReal, destIm);
        }
    VNA_.DisconnectFromSocket();
    }
#else
    if(bNoError) VNA_.MeasureTestSingleSweep();
    {
        if(bNoError) VNA_.ReadSingleSweep(destReal, destIm);
    }
#endif
}


void MeasurmentsControl::MeasureCurrentAspectInternal(MeasDataClass::VNAParams params, QComplexVector &Dest)
{

    double*destReal = new double[params.NumOfPoi];
    double*destIm = new double[params.NumOfPoi];
    Dest.resize(params.NumOfPoi);
    VNA VNA_;
    bool IsExtTriggerOn = false;
#ifndef OPU_VNA_SIMULATION
    qDebug() << "Connect";
    bNoError = VNA_.ConnectToSocket(params.ip, params.port);

    if (bNoError) bNoError = VNA_.Preset();

    if(bNoError) bNoError = VNA_.SetAllParameters(IsExtTriggerOn,\
                                          QString::number(params.StartFreq),\
                                          QString::number(params.StopFreq),\
                                          QString::number(params.Pow),\
                                          params.NumOfPoi,\
                                          params.MeasParameter,\
                                          params.Datatype,\
                                          params.IF);

    if(bNoError)
    {

        VNA_.MeasureSingleSweep();
        VNA_.ReadSingleSweep(destReal, destIm);
        for(int i =0; i< params.NumOfPoi; i++) Dest[i] = std::complex(destReal[i],destIm[i]);
    }
#else
    if(bNoError)
    {

        VNA_.MeasureTestSingleSweepCurrAsp();
        VNA_.ReadSingleSweep(destReal, destIm);
        for(int i =0; i< params.NumOfPoi; i++) Dest[i] = std::complex(destReal[i],destIm[i]);
    }
#endif

}





void MeasurmentsControl::Abort()
{
    {
    std::lock_guard<std::mutex> lock(measMutex);
         bAbort = true;
    }

    boolAbort.store(true);
    qDebug() << "abort";

}

bool MeasurmentsControl::IsbAbort()
{
    return boolAbort.load();
}


void MeasurmentsControl::ResetAbort()
{
    boolAbort.store(false);
    {
    bAbort = false;
    bNoError = true;
    }
}

void MeasurmentsControl::TestFunction(MeasDataClass& ms)
{
    QDoubleVector dist;
    QComplexVector complexvals;
    FilterClass ff;
    readFileAndStoreData1("D:/qt proj/threads_check/DATA_FOR_COMPARISON/TEST_PLANARWCTEMP_NOGATE_SHIFTONW.txt", dist, complexvals);

    qDebug() << "distsize" << dist.size();
    qDebug() << "complexvalssize" << complexvals.size();
    //for(int i =0; i < complexvals.size(); i++) qDebug() << ProcClass.GetAmpl( complexvals[i] );
    ms.WriteSweepAt(MeasDataClass::MeasDataType::CurrentAspect, complexvals);
    complexvals = ms.ReadSweepFrom(MeasDataClass::MeasDataType::CurrentAspect);

    int N = complexvals.size();
    double f2 = ms.GetStopFreq();
    double f1 = ms.GetStartFreq();
    double hf =  (f2-f1)*10e9/((double)N-1);
    qDebug() << f1;
    qDebug() << f2;
    qDebug() << N;
    qDebug() << hf;
    QComplexVector FilteredData(N);

    QComplexVector ProfRange;

    double f11= 34.0/LightVel;
    double f22 =  48.0/LightVel;
    qDebug() << LightVel;
    double fd = ((double)N-1)*10e-9/(f2-f1);
    qDebug() << fd*0.5;
    qDebug() << f11;
    qDebug() << f22;
    if(f11 >= fd*0.5) qDebug("...");
    if(f22 >= fd*0.5) qDebug("...");

    QComplexVector Filter_coeffs = ff.FirWin(101, f11, f22, fd, "Rect");
    FilteredData = ff.FilterSignalFIR(Filter_coeffs, complexvals);
    //FilteredData = complexvals;
   /* ProcClass.IFFT(FilteredData, ProfRange);
    ProcClass.FFTShift(ProfRange);
    ProcClass.FFTPhaseCorrection(ProfRange, f1, f2, N);
    //ProcClass.FFTNorm(ProfRange, hf);
*/
    ProfRange = ProcClass.FFTWithPhsCorrectionAndNorm(FilteredData, f1, f2, FilteredData.size());
    ms.WriteSweepAt(MeasDataClass::MeasDataType::CurrentAspect, ProfRange);

    qDebug() << ( complexvals[0].real() );
}
