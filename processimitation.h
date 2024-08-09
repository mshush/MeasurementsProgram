#ifndef PROCESSIMITATION_H
#define PROCESSIMITATION_H

#include <random>
#include <QObject>
#include <complex>
#include <QTimer>

class ProcessImitation : public QObject {
    Q_OBJECT
public:
    explicit ProcessImitation(QObject * parent = nullptr);
    ~ProcessImitation();

    int NumberOfPoints = 1601;
    QVector <std::complex<double>> f;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution;

    QTimer * RefreshTimer;

signals:
    void MeasurementPerformed(QVector <std::complex<double>> f);

public slots:
    void Measure();
    void MeasureContinuously(bool ContinuousModeIsOn);
    void ChangeParameters(double FreqStart, double FreqStop, double PointsNumber);
    void PerformNextMeasurement();
};









#endif // PROCESSIMITATION_H
