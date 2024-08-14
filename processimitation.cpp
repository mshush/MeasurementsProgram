#include "processimitation.h"



ProcessImitation::ProcessImitation(QObject * parent) : QObject(parent)
{
    RefreshTimer = new QTimer;
    generator = std::default_random_engine (time(0));
    distribution = std::normal_distribution<double> (0.0, 1.0);
}


void ProcessImitation::Measure()
{
    f = QVector <std::complex<double>> (NumberOfPoints);

    f[0] = std::complex<double>(0,0);

    for (int i=1; i<NumberOfPoints; ++i)
    {
        f[i] = f[i-1] + std::complex<double> (distribution(generator),distribution(generator)) ;
    }

    emit MeasurementPerformed(f);
}


void ProcessImitation::MeasureContinuously(bool ContinuousModeIsOn)
{
    if (ContinuousModeIsOn)
    {
        Measure();
        connect(RefreshTimer, &QTimer::timeout, this, &ProcessImitation::PerformNextMeasurement);
        RefreshTimer->start(100);
    }
    else
    {
        disconnect(RefreshTimer, &QTimer::timeout, this, &ProcessImitation::PerformNextMeasurement);
    }
}


void ProcessImitation::ChangeParameters(double FreqStart, double FreqStop, double PointsNumber)
{
    NumberOfPoints = PointsNumber;
}




void ProcessImitation::PerformNextMeasurement()
{
    for (int i=0; i< NumberOfPoints-1; ++i)
    {
        f[i] = f[i+1];
    }
    f[NumberOfPoints-1] = f[NumberOfPoints-2]+ std::complex<double> (distribution(generator),distribution(generator));

    emit MeasurementPerformed(f);
}


ProcessImitation::~ProcessImitation()
{

}




