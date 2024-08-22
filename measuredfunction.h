#ifndef MEASUREDFUNCTION_H
#define MEASUREDFUNCTION_H



#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>


class MeasuredFunction
{
public:
    MeasuredFunction();

    ~MeasuredFunction();

    int FNum; //Число точек по частотам
    int RNum; //Число точек по углам поворота
    int TNum; //Число точек по углам наклона

    double FStart; //Начальная частота
    double RStart; //Начальный угол поворота
    double TStart; //Начальный угол наклона

    double FStop; //Конечная частота
    double RStop; //Конечный угол поворота
    double TStop; //Конечный угол наклона



    QVector <std::complex<double>> Function; // Сам массив


    void Resize(int FNum, int RNum, int TNum); // Смена размера
    void WriteTo(int f, int r, int t, std::complex<double> NewValue); // Запись по индексам
    std::complex<double> ReadFrom(int f, int r, int t); // Чтение по индексам
    QVector <std::complex<double>> GetFrequencyVectorAt(int r, int t); // Чтение строчки

    int FindRotationIndex(double RotationValue); // Индекс угла поворота по значению
    int FindTiltIndex(double TiltValue); // Индекс угла наклона по значению


    QVector <double> FreqVector (); // Получает вектор частот из MeasuredFunction
    QVector <double> AmplVectorAtAngles (int r, int t); // Получает вектор амплитуд из MeasuredFunction при углах с индексами r и t

    QVector <double> DistVector (); // Получает вектор расстояний из MeasuredFunction
    QVector <double> FourierAmplVectorAtAngles (int r, int t); // Получает вектор амплитуд фурье образов из MeasuredFunction при углах с индексами r и t


    bool CheckBackgroundForSuitability (MeasuredFunction BG); //Проверка размерностей перед вычитанием
    void SubstractBackground (MeasuredFunction BG); // Вычитание фона
    void Calibrate (MeasuredFunction Calibration, int SampleType); // Калибровка
    void ClearFunction(); // Очистка функции


    // Для удобного сохранения через QDataStream
    friend QDataStream &operator<<(QDataStream &out, const MeasuredFunction &MyMF);


    // Для удобного чтения через QDataStream
    friend QDataStream &operator>>(QDataStream &in, MeasuredFunction &MyMeasuredFunction);


};





#endif // MEASUREDFUNCTION_H
