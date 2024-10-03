#ifndef PROCESSIMITATION_H
#define PROCESSIMITATION_H

#include <random>
#include <QObject>
#include <complex>
#include <QTimer>
#include <measuredfunction.h>
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

    double RotationAngleStart = 0;
    double RotationAngleStop = 359;
    int RotationAngleNumber = 360;

    double TiltAngleStart = 0;
    double TiltAngleStop = 9;
    int TiltAngleNumber = 10;

    enum ModeOfMeasurement {Response, Background, Calibration};
    ModeOfMeasurement MeasurementMode = Response; // Calibration; //  Background; //


    MeasuredFunction F;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;

    QTimer * RefreshTimer;

    int BufferSize = 100;

    bool Stopped = false;

signals:
    void MeasurementFinished(MeasuredFunction F_ForSending);
    void ProgressSignal(int CurrentProgressPercent);
    void IterationOfMeasurementFinished(QVector <double> FreqVector);
    void ErrorOccured(QString ErrorText);

public slots:
    void Measure();
    void MeasureContinuously(bool CheckedStatus);

    void SetFrequencyRange (double FreqStart, double FreqStop, double FreqNumber);
    void SetAngleRanges (double RotStart, double RotStop, double RotNumber, double TiltStart, double TiltStop, double TiltNumber);

    void StopEverything();

    void PerformNextMeasurement();
};









#endif // PROCESSIMITATION_H
