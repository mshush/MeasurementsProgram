 #include "processimitation.h"



ProcessImitation::ProcessImitation(QObject * parent) : QObject(parent)
{
    RefreshTimer = new QTimer;
    generator = std::default_random_engine (time(0));
    distribution = std::normal_distribution<double> (0.0, 1.0);
}


void ProcessImitation::Measure()
{

    F.Resize(FrequencyNumber,AzimuthNumber,ElevationNumber);

    F.VNAParameters.StartFreq = FrequencyStart;
    F.VNAParameters.StopFreq = FrequencyStop;
    F.VNAParameters.NumOfPoi =  FrequencyNumber;

    F.OPUParameters.startAzAngl = AzimuthStart;
    F.OPUParameters.stopAzAngl = AzimuthStop;
    F.OPUParameters.AzTrigPoints =  AzimuthNumber;

    F.OPUParameters.startElAngl = ElevationStart;
    F.OPUParameters.stopElAngl = ElevationStop;
    F.OPUParameters.ElTrigPoints =  ElevationNumber;


    int TotalNumberOfIterations = ElevationNumber * AzimuthNumber * FrequencyNumber;

    emit ProgressSignal(0);

    for (int e = 0; e < ElevationNumber; e++)
    {
        for (int a = 0; a < AzimuthNumber; a++)
        {
            for (int f=0; f < FrequencyNumber; f++)
            {
                std::complex<double>  PerfectValue = std::complex <double> (std::round(pow(sin(2 * f * M_PI / F.VNAParameters.NumOfPoi),5)) + 0.01*a + e, 0);
                std::complex<double>  Noise = 0.01 * std::complex<double>(distribution(generator),distribution(generator));
                std::complex<double> MeasuredValue =  PerfectValue + Noise; //  + FOffset[f] + ROffset[r] + TOffset[t];

                if (MeasurementMode == Response)
                {
                    MeasuredValue += std::complex <double> (0, pow(cos(2 * f * M_PI / F.VNAParameters.NumOfPoi),10));
                }

                if (MeasurementMode == Calibration) // убрать калибровку -- она не здесь
                {
                    MeasuredValue += std::complex <double> (1, 1); ;
                }

                F.WriteToObjectResult(f,a,e, MeasuredValue);


                int iter = e * (F.OPUParameters.AzTrigPoints * F.VNAParameters.NumOfPoi)  + a * F.VNAParameters.NumOfPoi + f;
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


void ProcessImitation::MeasureContinuously(bool ContinuousModeIsOn) //Поочерёдно действительная/мнимая части или два массива?
{
    if (ContinuousModeIsOn)
    {
        int TotalNumberOfIterations = ElevationNumber * AzimuthNumber * FrequencyNumber;

        QVector <double> VectorForSending(BufferSize, 0.0);

        emit ProgressSignal(0);

        int VectorIndex = 0;

        for (int e = 0; e < ElevationNumber; e++)
        {
            for (int a = 0; a < AzimuthNumber; a++)
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
                        int iter = e * (AzimuthNumber * FrequencyNumber)  + a * FrequencyNumber + f;
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


void ProcessImitation::SetAngleRanges(double AzStart, double AzStop, double AzNum, double ElStart, double ElStop, double ElNum)
{
    AzimuthStart = AzStart;
    AzimuthStop = AzStop;
    AzimuthNumber = AzNum;

    ElevationStart = ElStart;
    ElevationStop = ElStop;
    ElevationNumber = ElNum;
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
    Stopped = true; // Неправильно работает // Нужно ли вообще убрать?
}



ProcessImitation::~ProcessImitation()
{}






/* // Старая функция измерений
    f = QVector <std::complex<double>> (NumberOfPoints);

    f[0] = std::complex<double>(0,0);

    for (int i=1; i<NumberOfPoints; ++i)
    {
        f[i] = f[i-1] + std::complex<double> (distribution(generator),distribution(generator)) ;
    }

    emit MeasurementPerformed(f);
*/
