#ifndef PROCESSIMITATION_H
#define PROCESSIMITATION_H

#include <random>
#include <QObject>
//#include <complex>
#include <QTimer>
#include <threedimensionalvector.h>
#include <QDebug>
#include <QThread>

class ProcessImitation : public QObject
{
    Q_OBJECT
public:
    explicit ProcessImitation(QObject * parent = nullptr);
    ~ProcessImitation();


    double FrequencyStart = 1;
    double FrequencyStop = 2;
    int FrequencyNumber = 1601;

    double AzimuthStart = 0;
    double AzimuthStop = 359;
    int AzimuthNumber = 360;

    double ElevationStart = 0;
    double ElevationStop = 9;
    int ElevationNumber = 10;

    enum ModeOfMeasurement {Response, Background, Calibration};
    ModeOfMeasurement MeasurementMode = Response; // Calibration; //  Background; //


    ThreeDimensionalVector F; // Переименовать название функции и класса -- ~ 3DVector.

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;

    QTimer * RefreshTimer;

    int BufferSize = 100;

    bool Stopped = false;

signals:
    void MeasurementFinished(ThreeDimensionalVector F_ForSending);
    void ProgressSignal(int CurrentProgressPercent);
    void IterationOfMeasurementFinished(QVector <double> FreqVector);
    void ErrorOccured(QString ErrorText);

public slots:
    void Measure();
    void MeasureContinuously(bool CheckedStatus);

    void SetFrequencyRange (double FreqStart, double FreqStop, double FreqNumber);
    void SetAngleRanges (double AzStart, double AzStop, double AzNumber, double ElStart, double ElStop, double ElNumber);

    void StopEverything();

    void PerformNextMeasurement();
};









#endif // PROCESSIMITATION_H
