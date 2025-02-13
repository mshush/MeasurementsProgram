#ifndef MEASURMENTSCONTROL_H
#define MEASURMENTSCONTROL_H

#include <QObject>
#include <QWidget>

#include <QApplication>


#include <QTimer>
#include <QTimerEvent>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "common.h"
#include <errorhandler.h>
#include <03_HardwareConnection/vna.h>
#include "03_HardwareConnection/opu.h"
#include "01_DataProcessing/primarydaraproc.h"
#include "01_DataProcessing/MeasData.h"


class MeasurmentsControl : public QWidget
{
    Q_OBJECT
private:


    static ComplexVector TempTrgtRawDataArr;
    static double* TargetDataTempRe;
    static double* TargetDataTempIm;
    static double CurrentAz;
    static double CurrentEl;

    void MeasureCurrentAspect(MeasDataClass::VNAParams params, double * destReal, double * destIm);
    void MeasureCurrentAspect(MeasDataClass::VNAParams params, ComplexVector &Dest);

    static void MeasureAzTargetThread(MeasDataClass::VNAParams params, MeasDataClass::OPUParams opuParams);

    inline bool IsNewDataAvail();
    inline static void SetbNewDataAvail(bool bNewDataAvailable);
    inline void MainThreadEventsUpdate();
    void ResetAbort();


public:
    MeasurmentsControl(QWidget *parent = nullptr);
    static QString Debug;
    PrimaryDataProc ProcessClass;

    void MeasureAzTarget(MeasDataClass& MeasData);
    void MeasureResponseAtSignleAngl(MeasDataClass& MeasData);
    void MeasureBckgndAtSingleAngl(MeasDataClass& MeasData);
    void Abort();

signals:
   /* void UpdateFreqSweepAmplGraphSignal(DoubleVector SweepAmplArr);
    void UpdateFreqProfRangeAmplGraphSignal(DoubleVector ProfrangeAmplArr);
    void UpdateGatedFreqProfRangeAmplGraphSignal(DoubleVector ProfrangeAmplArr);
    void UpdateRCSGraphRangeAmplSignal(DoubleVector RCSAmplArray);
*/
    void UpdateCurrentAngleSignal(double Angle);

};

#endif // MEASURMENTSCONTROL_H
