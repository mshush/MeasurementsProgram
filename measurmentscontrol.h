#ifndef MEASURMENTSCONTROL_H
#define MEASURMENTSCONTROL_H

#include <QWidget>
#include <QObject>
#include <QApplication>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "vna.h"
#include "include_/vectortransforms.h"
#include "include_/measdata.h"
#include "include_/opu.h"

class MeasurmentsControl : public QWidget
{
    Q_OBJECT
private:
    SpectralTransformsClass ProcClass;
    FilterClass Filter;
    bool bAbort;
    bool bNoError;
    static QComplexVector TempTrgtRawDataArr;
    static double* TargetDataTempRe;
    static double* TargetDataTempIm;

    void MeasureCurrentAspectInternal(MeasDataClass::VNAParams params, double * destReal, double * destIm);
    void MeasureCurrentAspectInternal(MeasDataClass::VNAParams params, QComplexVector &Dest);
    static void MeasureAzTargetThread(MeasDataClass::VNAParams params,MeasDataClass::OPUParams opuParams);
    void PrimaryProcessSweep(MeasDataClass::MeasDataType RawDataType, QComplexVector RawData, MeasDataClass& MeasData, int iAz = 0, int iEl = 0);

    inline bool IsNewDataAvail();
    inline static void SetbNewDataAvail(bool bNewDataAvailable);
    inline static bool IsbAbort();
    inline void MainThreadEventsUpdate();
    void ResetAbort();

public:
    void TestFunction(MeasDataClass &ms);
    MeasurmentsControl(QWidget *parent = nullptr);
    static QString Debug;

    void MeasureAzTarget(MeasDataClass& MeasData);
    void MeasureResponseAtSignleAngl(MeasDataClass& MeasData);
    void MeasureBckgndAtSingleAngl(MeasDataClass& MeasData);
    void MeasureCurrentAspect(MeasDataClass& MeasData);
    void Abort();
signals:
    void updateGraph(int iAz, int iEl);
};

#endif // MEASURMENTSCONTROL_H
