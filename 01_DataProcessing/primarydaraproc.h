#ifndef PRIMARYDARAPROC_H
#define PRIMARYDARAPROC_H

#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include "common.h"
#include "referencetarget.h"
#include <math.h>
#include "../02_SpectralTransforms/fftw3.h"
#include "referencetarget.h"
#include "01_DataProcessing/MeasData.h"
#include "02_SpectralTransforms/spectraltransforms.h"

class PrimaryDataProc : public QObject
{
    Q_OBJECT
private:
    DoubleVector CurrentProfRangeGraphData;
    DoubleVector CurrentGatedProfRanfeGraphData;
    DoubleVector CurrentAngleDiagramGraphData;
    DoubleVector CurrentSweepGraphData;
    SpectralTransformsClass FilterClass;
    void DivVect(ComplexVector& Divisible,ComplexVector Divident);
    void DivVect(ComplexVector& Divisible, DoubleVector Divident);
    void Div(ComplexVector& Dividend, double Number);

    void SubtractVect(ComplexVector& Init,ComplexVector SubtrTerm);
    void SubtractVect(ComplexVector Init,ComplexVector SubtrTerm,ComplexVector& Result);

    void SubtractVect(DoubleVector& Init, DoubleVector SubtrTerm);

    DoubleVector AmplArrVect(ComplexVector ComplexVector);
public:

    PrimaryDataProc();

    void ProcessBckndRawData(ComplexVector RawData, MeasDataClass& MeasData);
    void ProcessResponseRawData(ComplexVector RawData, MeasDataClass& MeasData);
    void ProcessAnglSweepRawData(ComplexVector RawData, MeasDataClass& MeasData);

    void fft(double* source, double *dest, int NumOfPoin);
    void fft(double *source, int NumOfPoin);
    void ifft(double *source, int NumOfPoin);
    void ifft(double *source, double *dest, int NumOfPoin);

signals:
    void UpdateGatedProfileRangeSignal(DoubleVector GatedProfRangeArrayAmpl);
    void UpdateProfRangeSignal(DoubleVector ProfRangeArrayAmpl);
    void UpdateSweepGraphSignal(DoubleVector SweepArrayAmpl);
    void UpdatePatternSignal(DoubleVector DiagAnglArrayAmpl);
    void RedrawAllGraphsSignal();

};

#endif // PRIMARYDARAPROC_H
