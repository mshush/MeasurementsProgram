#ifndef PROCESSIMITATION_H
#define PROCESSIMITATION_H

#include <random>
#include <QObject>
#include <complex>
#include <QTimer>
#include <measuredfunction.h>
#include <QDebug>

class ProcessImitation : public QObject {
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

    enum ModeOfMeasurement {Object, Background, Calibration};
    ModeOfMeasurement MeasurementMode = Object; // Background; // Calibration; //


    MeasuredFunction F;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;

    QTimer * RefreshTimer;


signals:
    void MeasurementFinished(MeasuredFunction F_ForSending);

public slots:
    void Measure();
    void MeasureContinuously(bool ContinuousModeIsOn);

    void SetFrequencyRange (double FreqStart, double FreqStop, double PointsNumber);
    void SetAngleRanges (double RotStart, double RotStop, double RotNumber, double TiltStart, double TiltStop, double TiltNumber);

    //void ChangeRotationAngleRange (double RotStart, double RotStop, double RotNumber);
    //void ChangeTiltAngleRange (double TiltStart, double TiltStop, double TiltNumber);

    void PerformNextMeasurement();
};









#endif // PROCESSIMITATION_H
