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

                if (MeasurementMode == Response)
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

        QVector <double> VectorForSending(BufferSize, 0.0);

        emit ProgressSignal(0);

        int VectorIndex = 0;

        for (int t = 0; t < TiltAngleNumber; t++)
        {
            for (int r = 0; r < RotationAngleNumber; r++)
            {
                for (int f=0; f < FrequencyNumber; f++)
                {

                    //if (Stopped==true) {return;}

                    if (f%20==0){QThread::msleep(1);}

                    std::complex<double>  PerfectValue = std::complex <double> (std::round(pow(sin(2 * f * M_PI / FrequencyNumber),5)), 0);
                    std::complex<double>  Noise = 0.01 * std::complex<double>(distribution(generator),distribution(generator));
                    std::complex<double> MeasuredValue =  PerfectValue + Noise; //  + FOffset[f] + ROffset[r] + TOffset[t];

                    //this->thread()->wait(50);


                    if (MeasurementMode == Response)
                    {
                        MeasuredValue += std::complex <double> (0, pow(cos(2 * f * M_PI / FrequencyNumber),10));
                    }

                    if (MeasurementMode == Calibration)
                    {
                        MeasuredValue += std::complex <double> (1, 1); ;
                    }


                    VectorForSending[VectorIndex] = MeasuredValue.real();
                    VectorIndex++;
                    if (VectorIndex == BufferSize)
                    {
                        VectorIndex = 0;
                        emit IterationOfMeasurementFinished(VectorForSending);
                        VectorForSending = QVector <double> (BufferSize, 0.0);
                    }




                    VectorForSending[VectorIndex] = MeasuredValue.imag();
                    VectorIndex++;
                    if (VectorIndex == BufferSize)
                    {
                        VectorIndex = 0;
                        emit IterationOfMeasurementFinished(VectorForSending);
                        VectorForSending = QVector <double> (BufferSize, 0.0);

                    }


                    if (f%15==0)
                    {
                        int iter = t * (RotationAngleNumber * FrequencyNumber)  + r * FrequencyNumber + f;
                        int percentage = (iter * 100) / TotalNumberOfIterations;
                        //float perflo = double((iter)) / TotalNumberOfIterations;
                        //qDebug()<< iter << perflo;
                        emit ProgressSignal(percentage);
                    }

                    /*
                    if (iter % (int(TotalNumberOfIterations/100)) == 0)
                    {
                        qDebug()<<iter<< "--->" <<iter % (int(TotalNumberOfIterations/100));
                        int percentage = (iter  * 100) / TotalNumberOfIterations;
                        emit ProgressSignal(percentage);
                    }
                    */
                }    
            }
        }

        if (VectorIndex!=0)
        {
            emit IterationOfMeasurementFinished(VectorForSending.mid(0,VectorIndex-1));
        }
        emit ProgressSignal(100);

    }
    else
    {

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
    //qDebug()<<"!!!";

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



void ProcessImitation::StopEverything()
{
    Stopped = true;
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
