#ifndef SPECTRALTRANSFORMSCLASS_H
#define SPECTRALTRANSFORMSCLASS_H

#include <QObject>
#include "fasttransforms.h"
#include "fftw3.h"
#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
#include "common.h"

#define LightVel 299792458
#define REAL 0
#define IMAG 1

using namespace alglib;

class SpectralTransformsClass : public QObject
{
    Q_OBJECT
private:
    void convertToLibComplexArr(const double* realPart, const double* imagPart, int size, complex_1d_array& complexArray);
    void convertFromLibComplexArr(const complex_1d_array& complexArray, double* realPart, double* imagPart, int size);

    void convertToLibComplexArr(QVector <std::complex<double>> origin, complex_1d_array& complexArray);
    void convertFromLibComplexArr(complex_1d_array& complexArray, QVector <std::complex<double>>& dest);

    void convertFromRealLibArr(complex_1d_array& complexArray, QVector <double> &dest);

public:
    explicit SpectralTransformsClass(QObject *parent = nullptr);


    void FFT(double *reSource, double *imSource, double *reDest, double *imDest, int NumOfPoin);
    void FFT(   ComplexVector Source,    ComplexVector& Dest);
    void FFT(   ComplexVector& Source);
    void FFT(double *reSource, double *imSource, int NumOfPoin);

    void IFFT(   ComplexVector Source,    ComplexVector &Dest);
    void IFFT(   ComplexVector &Source);
    void IFFT(double *reSource, double *imSource, int NumOfPoin);
    void IFFT(double *reSource, double *imSource,  double *reDest, double *imDest, int NumOfPoin);

    int ConvolveLinear(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest);
    int ConvolveLinear( ComplexVector Source1,  ComplexVector Source2,  ComplexVector & Dest);
    int ConvolveCirc(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest);
    int ConvolveCirc( ComplexVector Source1,  ComplexVector Source2,  ComplexVector & Dest);
    int ConvolveNoLib( ComplexVector Source1,  ComplexVector Source2,  ComplexVector & Dest);
    void ConvolveNoLib(double *a, double *aim, double *b,double *bim, double *res, double *resim, int aLen, int bLen);

    std::vector<double> KaiserWin(int N, double beta);
    void FilterSignalKaiser(double *reSignal, double *imSignal);
    void FilterSignalKaiser(double *reSignal, double *imSignal, int N_FilterTaps, double betaKaiser);

    void FilterSignalKaiser(QVector<std::complex<double>> Source ,    ComplexVector & Dest , int N_FilterTaps, double betaKaiser  );
    void FilterSignalKaiser(QVector<std::complex<double>> Source ,    ComplexVector & Dest   );
    void FilterSignalKaiser(QVector<std::complex<double>> Source);

signals:

};

#endif // SPECTRALTRANSFORMS_H
