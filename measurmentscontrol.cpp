#include "measurmentscontrol.h"
#include "common.h"
#include <math.h>

//#define OPU_VNA_SIMULATION;

ComplexVector MeasurmentsControl::TempTrgtRawDataArr;

double* MeasurmentsControl::TargetDataTempIm;
double* MeasurmentsControl::TargetDataTempRe;
double MeasurmentsControl::CurrentAz;
double MeasurmentsControl::CurrentEl;

QString MeasurmentsControl::Debug;
std::mutex measMutex;
std::atomic<bool> new_data_available(false); // Атомарный флаг
std::atomic<bool> boolAbort(false); // Атомарный флаг

MeasurmentsControl::MeasurmentsControl(QWidget *parent)
    : QWidget{parent}
{


}


void MeasurmentsControl::MeasureBckgndAtSingleAngl(MeasDataClass &MeasData)
{
    ResetAbort();
    int N = MeasData.GetNumOfFreqSweepPoints();
   ComplexVector Bcknd;
    if (bNoError) MeasureCurrentAspect(MeasData.getVNAParameters(), Bcknd);
    if (bNoError) ProcessClass.ProcessBckndRawData(Bcknd, MeasData);
}

void MeasurmentsControl::MeasureResponseAtSignleAngl(MeasDataClass& MeasData)
{
    ResetAbort();
   ComplexVector Rsp;
    if (bNoError) MeasureCurrentAspect(MeasData.getVNAParameters(), Rsp);
    if (bNoError)  ProcessClass.ProcessResponseRawData(Rsp, MeasData);
}


void MeasurmentsControl::MeasureAzTarget(MeasDataClass& MeasData)
{

    ResetAbort();
    //TargetDataTempIm = new double[MeasData.GetNumOfFreqSweepPoints()];
    //TargetDataTempRe = new double[MeasData.GetNumOfFreqSweepPoints()];
    double AnglTemp;
    std::thread MeasThread(MeasureAzTargetThread ,
    MeasData.getVNAParameters(), MeasData.getOPUParameters());
    MeasThread.detach();
    if (bNoError) {
    for(int i = 0; i < MeasData.getOPUParameters().AzTrigPoints; i++)
    {
        if(!bNoError) break;
        MainThreadEventsUpdate();
        if(IsNewDataAvail()) {
        {
            std::lock_guard<std::mutex> lk(measMutex);
            if(bAbort) break;
            MeasData.SetSweepAtAngl(TempTrgtRawDataArr, i);
            AnglTemp = CurrentAz;
        }

        UpdateCurrentAngleSignal(AnglTemp);
        SetbNewDataAvail(false);
        ProcessClass.ProcessAnglSweepRawData(MeasData.GetRawSweepDataAt(i,0), MeasData);
        MainThreadEventsUpdate();

        }

    }
    }

}

void MeasurmentsControl::MeasureAzTargetThread(MeasDataClass::VNAParams params, MeasDataClass::OPUParams opuParams)
{
#ifdef OPU_VNA_SIMULATION

    VNA VNA_;
    OPU opu;
    bool IsExternalTriggerOn = true;
    bool IsExtTriggerOn = false;

    qDebug() << "simulate";

    VNA_.SimulateTriggerOPU(&opu); // for simulation only
    qDebug() << "move";

    opu.MoveAzFromTo();

    VNA_.NumOfPoi = params.NumOfPoi;

    for (int i = 0; i < opuParams.AzTrigPoints; i++)
    {

        VNA_.MeasureTestSingleSweep();

        {
        std::lock_guard<std::mutex> lock(measMutex);

        if(bAbort) break;

        VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);

        }

        //new_data_available.store(true, std::memory_order_release);
        SetbNewDataAvail(true);

        qDebug() << "read";
    }
    opu.StopSimTrig();
#endif

#ifdef OPU_SIMULATION

    VNA VNA_;
    OPU opu;
    bool IsExternalTriggerOn = true;
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
    qDebug() << "simulate";

    VNA_.SimulateTriggerOPU(&opu); // for simulation only
    qDebug() << "move";

    opu.MoveAzFromTo();

    VNA_.NumOfPoi = params.NumOfPoi;

    for (int i = 0; i < opuParams.AzTrigPoints; i++)
    {

                //VNA_.MeasureTestSingleSweep();
               VNA_.MeasureSingleSweep();

                {
                std::lock_guard<std::mutex> lock(measMutex);

                if(bAbort) break;

                VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);

                }

                //new_data_available.store(true, std::memory_order_release);
                SetbNewDataAvail(true);

                qDebug() << "read";
    }
    VNA_.DisconnectFromSocket();

    Abort();
    opu.StopSimTrig();

#endif

#ifndef OPU_VNA_SIMULATION
#ifndef OPU_SIMULATION
    VNA VNA_;
    OPU opu;
    bNoError = VNA_.ConnectToSocket(params.ip, params.port);
    if (bNoError) bNoError = opu.ConnectToOPU();
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

    OPU::MoveMode MM;
    if (opuParams.MoveMode == "CCW") MM = OPU::MoveMode::CCW;
    else MM = OPU::MoveMode::CW;

    if (bNoError) bNoError = opu.SetOPUParameters(opuParams.startAzAngl, opuParams.stopAzAngl, \
        opuParams.AzTrigPoints, opuParams.Speed, MM);

    if (bNoError) opu.SetCurrentAzAngl(opuParams.startAzAngl);
    if (bNoError) opu.MoveAzFromTo();

    VNA_.NumOfPoi = params.NumOfPoi;
    if (bNoError) {
        for (int i = 0; i < opuParams.AzTrigPoints; i++)
        {
            VNA_.MeasureSingleSweep();

            {
                std::lock_guard<std::mutex> lock(measMutex);
                if(bAbort || !bNoError) break;
                CurrentAz = opu.GetCurrentAzAngl();
                VNA_.ReadSingleSweep(TargetDataTempRe, TargetDataTempIm);
                for(int i =0; i< params.NumOfPoi; i++) TempTrgtRawDataArr[i] = std::complex(TargetDataTempRe[i],TargetDataTempIm[i]);
            }

            SetbNewDataAvail(true);
        }
    }

#endif
#endif

}


bool MeasurmentsControl::IsNewDataAvail()
{
    return new_data_available.load();
}

void MeasurmentsControl::SetbNewDataAvail(bool bNewDataAvailable)
{
    //if(NewDataAvailable) new_data_available.store(true, std::memory_order_release);
    new_data_available.store(bNewDataAvailable);

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


void MeasurmentsControl::MeasureCurrentAspect(MeasDataClass::VNAParams params, double *destReal, double *destIm)
{


    VNA VNA_;
    bool IsExtTriggerOn = false;

    bNoError = VNA_.ConnectToSocket(params.ip, params.port);
    VNA_.Preset();
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
    {
         VNA_.ReadSingleSweep(destReal, destIm);
    }
   // VNA_.DisconnectFromSocket();
    }

}


void MeasurmentsControl::MeasureCurrentAspect(MeasDataClass::VNAParams params, ComplexVector &Dest)
{

    double*destReal = new double[params.NumOfPoi];
    double*destIm = new double[params.NumOfPoi];

    VNA VNA_;
    bool IsExtTriggerOn = false;

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

    if(bNoError){
    VNA_.MeasureSingleSweep();
    {
         VNA_.ReadSingleSweep(destReal, destIm);
         for(int i =0; i< params.NumOfPoi; i++)
         {
                Dest[i] = std::complex(destReal[i],destIm[i]);
         }
    }
    }

}





void MeasurmentsControl::Abort()
{
    {
    std::lock_guard<std::mutex> lock(measMutex);
         bAbort = true;
    }
    boolAbort.store(true, std::memory_order_release);
    qDebug() << "abort";

}


void MeasurmentsControl::ResetAbort()
{
    {
    bAbort = false;
    bNoError = true;
    }
}
