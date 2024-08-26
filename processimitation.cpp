#include "processimitation.h"



ProcessImitation::ProcessImitation(QObject * parent) : QObject(parent)
{
    RefreshTimer = new QTimer;
    generator = std::default_random_engine (time(0));
    distribution = std::normal_distribution<double> (0.0, 1.0);
}


void ProcessImitation::Measure()
{

    F.Resize(FrequencyNumber,RotationAngleNumber,TiltAngleNumber);

    F.FStart = FrequencyStart;
    F.FStop = FrequencyStop;
    F.FNum =  FrequencyNumber;

    F.RStart = RotationAngleStart;
    F.RStop = RotationAngleStop;
    F.RNum =  RotationAngleNumber;

    F.TStart = TiltAngleStart;
    F.TStop = TiltAngleStop;
    F.TNum =  TiltAngleNumber;

    int TotalNumberOfIterations = TiltAngleNumber * RotationAngleNumber * FrequencyNumber;

    emit ProgressSignal(0);

    for (int t = 0; t < TiltAngleNumber; t++)
    {
        for (int r = 0; r < RotationAngleNumber; r++)
        {
            for (int f=0; f < FrequencyNumber; f++)
            {
                std::complex<double>  PerfectValue = std::complex <double> (std::round(pow(sin(2 * f * M_PI / F.FNum),5)) + r + t, 0);
                std::complex<double>  Noise = 0.01 * std::complex<double>(distribution(generator),distribution(generator));
                std::complex<double> MeasuredValue =  PerfectValue + Noise; //  + FOffset[f] + ROffset[r] + TOffset[t];

                if (MeasurementMode == Object)
                {
                    MeasuredValue += std::complex <double> (0, pow(cos(2 * f * M_PI / F.FNum),10));
                }

                if (MeasurementMode == Calibration)
                {
                    MeasuredValue += std::complex <double> (1, 1); ;
                }

                F.WriteTo(f,r,t, MeasuredValue);


                int iter = t * (F.RNum * F.FNum)  + r * F.FNum + f;
                if (iter % (TotalNumberOfIterations/100) == 0)
                {
                    int percentage = (iter  * 100) / TotalNumberOfIterations;
                    emit ProgressSignal(percentage);

                }
            }
        }
    }

    emit ProgressSignal(100);
    emit MeasurementFinished(F);

}


void ProcessImitation::MeasureContinuously(bool ContinuousModeIsOn)
{

    if (ContinuousModeIsOn)
    {

        int TotalNumberOfIterations = TiltAngleNumber * RotationAngleNumber * FrequencyNumber;

        QVector <std::complex<double>> FreqVect(FrequencyNumber);

        emit ProgressSignal(0);

        for (int t = 0; t < TiltAngleNumber; t++)
        {
            for (int r = 0; r < RotationAngleNumber; r++)
            {
                for (int f=0; f < FrequencyNumber; f++)
                {
                    std::complex<double>  PerfectValue = std::complex <double> (std::round(pow(sin(2 * f * M_PI / F.FNum),5)) + r + t, 0);
                    std::complex<double>  Noise = 0.01 * std::complex<double>(distribution(generator),distribution(generator));
                    std::complex<double> MeasuredValue =  PerfectValue + Noise; //  + FOffset[f] + ROffset[r] + TOffset[t];

                    //qDebug()<<PerfectValue.real();

                    if (MeasurementMode == Object)
                    {
                        MeasuredValue += std::complex <double> (0, pow(cos(2 * f * M_PI / F.FNum),10));
                    }

                    if (MeasurementMode == Calibration)
                    {
                        MeasuredValue += std::complex <double> (1, 1); ;
                    }

                    FreqVect[f] = MeasuredValue;

                    //qDebug()<<"complexValues = " << FreqVect[f].real() << "," << FreqVect[f].imag() ;

                    int iter = t * (F.RNum * F.FNum)  + r * F.FNum + f;
                    if (iter % (TotalNumberOfIterations/100) == 0)
                    {
                        int percentage = (iter  * 100) / TotalNumberOfIterations;
                        emit ProgressSignal(percentage);

                    }

                    emit IterationOfMeasurementFinished(r, t, FreqVect);

                }
            }
        }

        emit ProgressSignal(100);
        //emit MeasurementFinished(F);

    }
    else
    {
        //disconnect(RefreshTimer, &QTimer::timeout, this, &ProcessImitation::PerformNextMeasurement);
    }

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
    qDebug()<<"!!!";

    //emit ProgressSignal();
    //Measure();
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
