#include "processimitation.h"



ProcessImitation::ProcessImitation(QObject * parent) : QObject(parent)
{
    RefreshTimer = new QTimer;
    generator = std::default_random_engine (time(0));
    distribution = std::normal_distribution<double> (0.0, 1.0);
}


void ProcessImitation::Measure()
{
    QVector <std::complex<double>> FOffset(FrequencyNumber);
    QVector <std::complex<double>> ROffset(RotationAngleNumber);
    QVector <std::complex<double>> TOffset(TiltAngleNumber);

    FOffset[0] = 0;
    ROffset[0] = 0;
    TOffset[0] = 0;

    for (int f=1; f < FrequencyNumber; f++)
    {
        FOffset[f] = FOffset[f-1] + std::complex<double>(distribution(generator),distribution(generator));
    }
    for (int r = 1; r < RotationAngleNumber; r++)
    {
        ROffset[r] = ROffset[r-1] + std::complex<double>(distribution(generator),distribution(generator));
    }
    for (int t = 1; t < TiltAngleNumber; t++)
    {
        TOffset[t] = TOffset[t-1] + std::complex<double>(distribution(generator),distribution(generator));
    }

    F.Resize(FrequencyNumber,RotationAngleNumber,TiltAngleNumber);

    for (int t = 0; t < TiltAngleNumber; t++)
    {
        for (int r = 0; r < RotationAngleNumber; r++)
        {
            for (int f=0; f < FrequencyNumber; f++)
            {
                //double Real = t*r*f;
                //double Imag = 0;
                std::complex<double> ValueAtPoint = FOffset[f] + ROffset[r] + TOffset[t];
                F.WriteTo(f,r,t,ValueAtPoint);

                //qDebug() << "Cycle: double= " <<  Real << ", F= " <<  F.ReadFrom(f,r,t).real();
            }
        }
    }

    F.FStart = FrequencyStart;
    F.FStop = FrequencyStop;
    F.FNum =  FrequencyNumber;

    F.RStart = RotationAngleStart;
    F.RStop = RotationAngleStop;
    F.RNum =  RotationAngleNumber;

    F.TStart = TiltAngleStart;
    F.TStop = TiltAngleStop;
    F.TNum =  TiltAngleNumber;

    emit MeasurementFinished(F);


}


void ProcessImitation::MeasureContinuously(bool ContinuousModeIsOn)
{
    /*
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
    */
}


void ProcessImitation::SetFrequencyRange(double FreqStart, double FreqStop, double FreqNum)
{
    FrequencyStart = FreqStart;
    FrequencyStop = FreqStop;
    FrequencyNumber = FreqNum;
}


void ProcessImitation::SetAngleRanges(double RotStart, double RotStop, double RotNum, double TiltStart, double TiltStop, double TiltNum)
{
    RotationAngleStart = RotStart;
    RotationAngleStop = RotStop;
    RotationAngleNumber = RotNum;

    TiltAngleStart = TiltStart;
    TiltAngleStop = TiltStop;
    TiltAngleNumber = TiltNum;
}




void ProcessImitation::PerformNextMeasurement()
{
    /*
    for (int i=0; i< NumberOfPoints-1; ++i)
    {
        f[i] = f[i+1];
    }
    f[NumberOfPoints-1] = f[NumberOfPoints-2]+ std::complex<double> (distribution(generator),distribution(generator));

    emit MeasurementPerformed(f);
    */
}




ProcessImitation::~ProcessImitation()
{

}




/* // Старая функция измерений
    f = QVector <std::complex<double>> (NumberOfPoints);

    f[0] = std::complex<double>(0,0);

    for (int i=1; i<NumberOfPoints; ++i)
    {
        f[i] = f[i-1] + std::complex<double> (distribution(generator),distribution(generator)) ;
    }

    emit MeasurementPerformed(f);
*/

