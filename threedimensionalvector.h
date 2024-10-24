#ifndef THREEDIMENSIONALVECTOR_H
#define THREEDIMENSIONALVECTOR_H



#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>


class ThreeDimensionalVector
{
public:
    ThreeDimensionalVector();

    ~ThreeDimensionalVector();

    ThreeDimensionalVector(QVector <double> ReceivedVector);


    int FNum; //Число точек по частотам
    int ANum; //Число точек по углам поворота ANum от Azimuth
    int ENum; //Число точек по углам наклона  ENum от Elevation

    double FStart; //Начальная частота
    double AStart; //Начальный угол поворота
    double EStart; //Начальный угол наклона

    double FStop; //Конечная частота
    double AStop; //Конечный угол поворота
    double EStop; //Конечный угол наклона



    int CurrentIndex = 0;


    QVector <std::complex<double>> Function; // Сам массив


    void Resize(int FNum, int ANum, int ENum); // Смена размера
    void WriteTo(int f, int r, int t, std::complex<double> NewValue); // Запись по индексам
    std::complex<double> ReadFrom(int f, int r, int t); // Чтение по индексам
    QVector <std::complex<double>> GetFrequencyVectorAt(int r, int t); // Чтение строчки

    int FindAzimuthIndex(double AzimuthValue); // Индекс угла поворота по значению
    int FindElevationIndex(double ElevationValue); // Индекс угла наклона по значению

    double FindAzimuthValue(int r);
    double FindElevationValue    (int t);

    void WriteToRow(int r, int t, QVector <std::complex<double>> FreqVect); // Запись строки функции от частот по индексам углов

    void SetRanges(double FreqStart, double FreqStop, double FreqNumber, double AzimuthStart, double AzimuthStop, double AzimuthNumber, double ElevationStart, double ElevationStop, double ElevationNumber);

    QVector <double> FreqVector (); // Получает вектор частот         из ThreeDimensionalVector
    QVector <double> AzimuthVector ();  // Получает вектор углов вращения из ThreeDimensionalVector
    QVector <double> ElevationVector (); // Получает вектор углов наклона  из ThreeDimensionalVector

    QVector <double> AmplitudeVectorAtAngles (int r, int t); // Получает вектор амплитуд из ThreeDimensionalVector при углах с индексами r и t
    QVector <double> AmplitudeVectorAtFrequencyElevation(int f, int t); // Получает вектор амплитуд из ThreeDimensionalVector на частоте f

    QVector <double> DistVector (); // Получает вектор расстояний из ThreeDimensionalVector
    QVector <double> FourierAmplVectorAtAngles (int r, int t); // Получает вектор амплитуд фурье образов из ThreeDimensionalVector при углах с индексами r и t


    bool CheckBackgroundForSuitability (ThreeDimensionalVector BG); //Проверка размерностей перед вычитанием
    void SubstractBackground (ThreeDimensionalVector BG); // Вычитание фона
    void Calibrate (ThreeDimensionalVector Calibration, int SampleType); // Калибровка
    void ClearFunction(); // Очистка функции


    void AddMeasuredValues(QVector <double> vector);


    // Для удобного сохранения через QDataStream
    friend QDataStream &operator<<(QDataStream &out, const ThreeDimensionalVector &MyMF);


    // Для удобного чтения через QDataStream
    friend QDataStream &operator>>(QDataStream &in, ThreeDimensionalVector &MyThreeDimensionalVector);

    void FillComplexVectorWithDoubleValues(QVector<double> ReceivedVector);







};





#endif // THREEDIMENSIONALVECTOR_H
