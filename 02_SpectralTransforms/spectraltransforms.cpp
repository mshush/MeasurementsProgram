#include "spectraltransforms.h"

SpectralTransformsClass::SpectralTransformsClass(QObject *parent)
    : QObject{parent}
{

}

void SpectralTransformsClass::convertToLibComplexArr(const double *realPart, const double *imagPart, int size, complex_1d_array &complexArray)
{

}

void SpectralTransformsClass::convertFromLibComplexArr(complex_1d_array &complexArray, QVector<std::complex<double> > &dest)
{

}

void SpectralTransformsClass::convertFromLibComplexArr(const complex_1d_array &complexArray, double *realPart, double *imagPart, int size)
{

}

void SpectralTransformsClass::FFT(double *reSource, double *imSource, double *reDest, double *imDest, int NumOfPoin)
{

}

void SpectralTransformsClass::FFT(QVector<std::complex<double> > Source, QVector<std::complex<double> > &Dest)
{

}

void SpectralTransformsClass::FFT(QVector<std::complex<double> > &Source)
{

}

void SpectralTransformsClass::FFT(double *reSource, double *imSource, int NumOfPoin)
{

}

void SpectralTransformsClass::IFFT(QVector<std::complex<double> > Source, QVector<std::complex<double> > &Dest)
{

}

void SpectralTransformsClass::IFFT(QVector<std::complex<double> > &Source)
{

}

void SpectralTransformsClass::IFFT(double *reSource, double *imSource, int NumOfPoin)
{

}

void SpectralTransformsClass::IFFT(double *reSource, double *imSource, double *reDest, double *imDest, int NumOfPoin)
{

}

int SpectralTransformsClass::ConvolveLinear(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest)
{

}

int SpectralTransformsClass::ConvolveLinear(QVector<std::complex<double> > Source1, QVector<std::complex<double> > Source2, QVector<std::complex<double> > &Dest)
{

}

int SpectralTransformsClass::ConvolveCirc(double *reSignal1, double *imSignal1, int L1, double *reSignal2, double *imSignal2, int L2, double *reDest, double *imDest)
{

}

int SpectralTransformsClass::ConvolveCirc(QVector<std::complex<double> > Source1, QVector<std::complex<double> > Source2, QVector<std::complex<double> > &Dest)
{

}

int SpectralTransformsClass::ConvolveNoLib(QVector<std::complex<double> > Source1, QVector<std::complex<double> > Source2, QVector<std::complex<double> > &Dest)
{

}

void SpectralTransformsClass::ConvolveNoLib(double *a, double *aim, double *b, double *bim, double *res, double *resim, int aLen, int bLen)
{

}

std::vector<double> SpectralTransformsClass::KaiserWin(int N, double beta)
{

}

void SpectralTransformsClass::FilterSignalKaiser(double *reSignal, double *imSignal)
{

}

void SpectralTransformsClass::FilterSignalKaiser(double *reSignal, double *imSignal, int N_FilterTaps, double betaKaiser)
{

}

void SpectralTransformsClass::FilterSignalKaiser(QVector<std::complex<double> > Source, QVector<std::complex<double> > &Dest, int N_FilterTaps, double betaKaiser)
{

}

void SpectralTransformsClass::FilterSignalKaiser(QVector<std::complex<double> > Source, QVector<std::complex<double> > &Dest)
{

}

void SpectralTransformsClass::FilterSignalKaiser(QVector<std::complex<double> > Source)
{

}

