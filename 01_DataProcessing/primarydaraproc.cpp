#include "primarydaraproc.h"
#include "qcoreapplication.h"

/*
void PrimaryDataProc::SetDefaultParameters()
{
    /*
    NumOfPoin = 1601;

    sampleData = new double[NumOfPoin*2];
    sampleFData = new double[NumOfPoin*2];
    ResponseArr = new double[NumOfPoin*2];
    BckndArr = new double[NumOfPoin*2];
    double h = (StopFreq - StartFreq)/NumOfPoin;
    f = new double[NumOfPoin*2];
    for (int i = 0 ; i < NumOfPoin; i++)
    {
        f[2*i] = StartFreq + h*i;
        f[2*i+1] = StartFreq + h*i;
    }
/*
    for(int i =0; i<NumOfPoin*2; i++)
    {
        ResponseArr[i] = 1;
        BckndArr[i] = 0;
    }

}*/

void PrimaryDataProc::DivVect(ComplexVector &Divisible, ComplexVector Divident)
{

}

void PrimaryDataProc::DivVect(ComplexVector &Divisible, DoubleVector Divident)
{

}

void PrimaryDataProc::Div(ComplexVector &Dividend, double Number)
{

}

void PrimaryDataProc::SubtractVect(ComplexVector &Init, ComplexVector SubtrTerm)
{

}

void PrimaryDataProc::SubtractVect(ComplexVector Init, ComplexVector SubtrTerm, ComplexVector &Result)
{

}

void PrimaryDataProc::SubtractVect(DoubleVector &Init, DoubleVector SubtrTerm)
{

}

DoubleVector PrimaryDataProc::AmplArrVect(ComplexVector ComplexVec)
{
    int N = ComplexVec.size();
    DoubleVector AmplVec(N);
    std::complex<double> c;
    double temp;
    for (int i = 0 ; i < N; i++)
    {
        c = ComplexVec[i];
        temp = (c.real() *c.real() + c.imag()*c.imag());
        if (fabs(temp) < 10e-20) temp = 10e-20;
        AmplVec[i] = log10(temp)*10;
    }
    return AmplVec;

}



PrimaryDataProc::PrimaryDataProc()
{

}

void PrimaryDataProc::ProcessBckndRawData(ComplexVector RawData, MeasDataClass &MeasData)
{
    MeasData.SetRawBcknd(RawData);
    UpdateSweepGraphSignal(AmplArrVect( RawData ) );
   ComplexVector FilteredData(RawData.size());
    FilterClass.FilterSignalKaiser(RawData, FilteredData);
    FilterClass.FFT(FilteredData);
    UpdateGatedProfileRangeSignal(AmplArrVect( FilteredData) );
    FilterClass.FFT(RawData);
    UpdateProfRangeSignal(AmplArrVect( RawData ));
    RedrawAllGraphsSignal();
}

void PrimaryDataProc::ProcessResponseRawData(ComplexVector RawData, MeasDataClass &MeasData)
{
    MeasData.SetRawResponse(RawData);
    UpdateSweepGraphSignal(AmplArrVect( RawData ) );

    SubtractVect(RawData, MeasData.GetBcknd());

   ComplexVector FilteredData(RawData.size());
    FilterClass.FilterSignalKaiser(RawData, FilteredData);

    FilterClass.FFT(FilteredData);
    UpdateGatedProfileRangeSignal(AmplArrVect( FilteredData) );

    DoubleVector RefRCS;
    //DivVect(FilteredData, *vector of cylinder rcs*);  !!! must be added
    MeasData.SetProcessedResponse(FilteredData);
    FilterClass.FFT(RawData);
    UpdateProfRangeSignal(AmplArrVect( RawData ));

    RedrawAllGraphsSignal();

}



void PrimaryDataProc::ProcessAnglSweepRawData(ComplexVector RawData, MeasDataClass &MeasData)
{
    //MeasData.AppendSweepToTargetRawDataArr(RawData);

    UpdateSweepGraphSignal(AmplArrVect( RawData ) );

    SubtractVect(RawData, MeasData.GetBcknd());

   ComplexVector FilteredData(RawData.size());
    FilterClass.FilterSignalKaiser(RawData, FilteredData);

    FilterClass.FFT(FilteredData);
    UpdateGatedProfileRangeSignal(AmplArrVect( FilteredData) );

    DivVect(FilteredData, MeasData.GetCalibrArray());
    MeasData.AppendSingleAngleSweepToDiag(FilteredData);
    int f = MeasData.getPatternViewFreq();
    // FIX UPDATE OF RCS POINT ADD !!
    UpdateProfRangeSignal(AmplArrVect( FilteredData ));

    FilterClass.FFT(RawData);
    UpdateProfRangeSignal(AmplArrVect( RawData ));

    RedrawAllGraphsSignal();

}




















/*
void PrimaryDataProc::SetFileName(QString name)
{

}

void PrimaryDataProc::SaveBckndToFile()
{

}

void PrimaryDataProc::SaveResponseToFile()
{

}

void PrimaryDataProc::LoadBckndFromFile()
{

}

void PrimaryDataProc::LoadResponseFromFile()
{

}
*/
