#ifndef SPECTRALTRANSFORMSCLASS_H
#define SPECTRALTRANSFORMSCLASS_H


#include "include_/fasttransforms.h"
//#include "fftw3.h"
#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
#include <QVector>
//

#define LightVel 299792458
//#define REAL 0
//#define IMAG 1
//using QComplexVector = QVector<std::complex<double>>;
//using QDoubleVector = QVector<double>;
using QComplexVector = QVector<std::complex<double>>;
using QDoubleVector = QVector<double>;
//using QComplexVector = std::vector<std::complex<double>>;
//using QDoubleVector = std::vector<double>;

using namespace alglib;

class SpectralTransformsClass
{
private:
    void convertToLibComplexArr(const double* realPart, const double* imagPart, int size, complex_1d_array& complexArray);
    void convertFromLibComplexArr(const complex_1d_array& complexArray, double* realPart, double* imagPart, int size);
    void convertToLibComplexArr(QComplexVector origin, complex_1d_array& complexArray);
    void convertFromLibComplexArr(complex_1d_array& complexArray, QComplexVector &dest);

    void convertFromRealLibArr(complex_1d_array& complexArray, QVector <double> &dest);

public:

    explicit SpectralTransformsClass();



    QComplexVector QDoubleArrToComplexArr(QDoubleVector Doublearr);
    QComplexVector DivVect(QComplexVector Divisible,QComplexVector Divident);
    QComplexVector DivVect(QComplexVector Divisible, QDoubleVector Divident);
    QComplexVector Div(QComplexVector Divisible, double Number);
    QComplexVector Div(QComplexVector Divisible, std::complex<double> Number);
    QComplexVector SubtractVect(QComplexVector Init,QComplexVector SubtrTerm);
    QComplexVector SubtractVect(QComplexVector Init,QDoubleVector SubtrTerm);
    QComplexVector SubtractVect(QDoubleVector Init, QDoubleVector SubtrTerm);


    QComplexVector FFT(QComplexVector Source, int Nfft);
    void FFT(QComplexVector& Source);
    //void FFT(   QComplexVector Source,    QComplexVector& Dest, int Nfft);
    QComplexVector IFFT(   QComplexVector Source,    int Nfft);
    void IFFT(QComplexVector &Source);
    //void IFFT(   QComplexVector Source,    QComplexVector &Dest, int Nfft);
    void FFTNorm(QComplexVector &V, double x0_orig, double x1_orig, int Norig, bool inverseFFT = false);
    void FFTNorm(QComplexVector &V, double sampling_step_orig, bool inverseFFT = false);
    void FFTShift(QComplexVector &list);
    void FFTPhaseCorrection(QComplexVector &Source, double x0_orig, double x1_orig, int Num_points_original, bool inverseFFT = false);
    //void IFFTPhaseCorrection(QComplexVector &Source, double t0, double t1, int Num_points);
    QComplexVector FFTWithPhsCorrectionAndNorm(QComplexVector V, double x0_orig, double x1_orig, int FFTNum = 2048, bool inverseFFT = false);

    //int ConvolveLinear(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest);
    QComplexVector ConvolveLinear( QComplexVector Source1,  QComplexVector Source2);
    //int ConvolveCirc(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest);
    QComplexVector ConvolveCirc( QComplexVector Source1,  QComplexVector Source2);
    QComplexVector ConvolveLinear(QDoubleVector Source1, QComplexVector Source2);
    QComplexVector ConvolveNoLib( QComplexVector Source1,  QComplexVector Source2);
    //void ConvolveNoLib(double *a, double *aim, double *b,double *bim, double *res, double *resim, int aLen, int bLen);
    //void IFFTNorm(QComplexVector &V, double sampling_step);

    QDoubleVector GetAmplVectordB(QComplexVector ComplexVector);
    QDoubleVector GetSqrNormVector(QComplexVector ComplexVector);
    double GetAmpl(std::complex<double> ComplexDouble);
    double GetAmpldB(std::complex<double> ComplexDouble);
    QDoubleVector GetPhaseVector(QComplexVector ComplexVector);

    void AppendZeros(QComplexVector& V, int FinalNumofPoin);
    double integrateArray(QDoubleVector V);


};


class FilterClass : public SpectralTransformsClass
{

private:
    double IdealFilterImpulseResp(int k, double nu_cutoff);
    double IdealFilterBPImpulseResp1(int k, double nu_cutoff1, double nu_cutoff2);

    std::complex<double> IdealFilterBPImpulseResp(int k, double nu_cutoff1, double nu_cutoff2);
public:
    QComplexVector FirWin(int num_taps, double L1,  double L2, double Lhalf, QString Type, double betaKaiser = 1);
    // QDoubleVector FirWin(int num_taps, double f_cutoff, double f_sampling, QString Type, double betaKaiser = 1);
    QComplexVector FilterSignalFIR(QComplexVector Filter_Coeffs, QComplexVector signal);
    QComplexVector FilterSignalFIR(QComplexVector Filter_Coeffs, QComplexVector signal, int Nsignal_convolve);
    QComplexVector FilterSignalFIR(QComplexVector signal, int num_taps, double L_cutoff1, double L_cutoff2, int L_sampling, QString Type, double betaKaiser = 1);

    //void KaiserWin(int num_taps, double beta);
    //void RectWin(int num_taps)

    FilterClass();

};

#endif // SPECTRALTRANSFORMS_H
