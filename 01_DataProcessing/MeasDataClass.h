#ifndef MeasDataClass_H
#define MeasDataClass_H



#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>
#include "referencetarget.h"
#include "common.h"

class MeasDataClass
{
private:
    ReferenceTarget RefCylinder;
    VNAParams VNAParameters;
    OPUParams OPUParameters;

    int CurrentIndex = 0;
    int CurrentAzimuthIndex = 0;
    int CurrentElevationIndex = 0;

public:
    MeasDataClass();

    ~MeasDataClass();

    MeasDataClass(QVector <double> ReceivedVector);

    void SetOPUParameters(OPUParams OPUPars);
    void SetOPUParameters(double AzimuthStart, double AzimuthStop, double AzimuthNumber, double ElevationStart, double ElevationStop, double ElevationNumber, int Speed, int MoveMode);
    void SetVNAParameters(int Po, double StartFreq, double StopFreq, int NumOfPoi, int NumOfSweeps, int IF, QString Datatype, QString MeasParameter, bool ExternalTriggerOn);
    void SetVNAParameters(VNAParams VNAPars);
    void SetReferenceCylinderPars(double height, double radius);
    void CopyVNAParams(VNAParams dest);
    void CopyOPUParams(OPUParams dest);


    // поменяла названия на более четкие
    QVector <std::complex<double>> MeasArray;     //  Результат измерений на объекте. Трёхмерный массив комплексных чисел (Изначально был только один массив -- Function)
    //QVector <std::complex<double>> BackgroundMeasArray; //  Результат измерения фона. Одномерный массив
    //QVector <std::complex<double>> ResponseMeasArray;   //  Результат измерения образца (отклик) для калибровки
    // изменила названия переменных
    void Resize(int FreqNum, int AzNum, int ElNum);

    // Чтение из массива и запись в массив MeasArray
    // поменяла названия на более четкие, изменила названия переменных
    std::complex<double> ReadFromMeasArray (int FreqIndex, int MeasArray, int ElIndex);  // Чтение по индексам частоты и углов   из массива результата измерения объекта
    void WriteValueToArray  (int FreqIndex, int MeasArray, int ElIndex, std::complex<double> NewValue); // Запись по индексам
    void WriteSweepToArray (int MeasArray, int ElIndex, QVector <std::complex<double>> SingleSweep); // Запись строки функции от частот по индексам углов


    // Чтение строки частот для фиксированных углов поворота
    // поменяла названия на более четкие, изменила названия переменных
    int FindAzimuthIndex(double AzimuthValue); // Вычисляет индекс угла поворота по значению
    int FindElevationIndex(double ElevationValue); // Вычисляет индекс угла наклона по значению
    double FindAzimuthValue (int AzIndex);   //Находит значение азимута по индексу
    double FindElevationValue (int ElIndex);   //Находит значение угла подъёма по индексу


    // поменяла название на более четкое
    QVector <double> GetFreqVector ();         // Вектор частот
    QVector <double> GetAzimuthVector ();      // Вектор углов вращения
    QVector <double> GetElevationVector ();    // Вектор углов наклона
    // поменяла название на более четкое, изменила названия переменных
    QVector <std::complex<double>> GetSweepAt(int AzIndex, int ElIndex); // Чтение строчки частот по заданным углам

    void GetSweepAt(int AzIndex, int ElIndex, QVector <std::complex<double>> );
    void GetSweepAt(int AzIndex, int ElIndex, double *re, double *im );



    // изменила название MateItScarce -> DonwSample
    QVector<std::complex<double>> DownSample(QVector<std::complex<double>> MyVector); // Прореживание    // QVector<std::complex<double>> MakeItScarcer(QVector<std::complex<double>> MyVector); // Прореживание
    void DownSample(int NResultSamples);
    // Калибровка = Вычесть bcknd из Response и поделить на опорное ЭПР, поэтому в названии не нужно еще SubtractBcknd
    // Ничего не принимает и не возвращает, так как операция проводится с уже записанными в объект массивами
    void Calibrate();

    // Заполнения векторов:

    // поменяла название на более четкое, изменила названия переменных

    void SetSweep(QVector <std::complex<double>> SingleSweep, int AzIndex, int ElIndex = 0); //

    // добавила перезгрузку функций
    void SetSweep(double* ReSweep, double* ImSweep, int AzIndex, int ElIndex = 0); //
    void SetSweep(double* Sweep, int AzIndex, int ElIndex = 0); //

    // поменяла название на более четкое, изменила названия переменных

    //void SetBackgroundVector(QVector<std::complex<double>> MeasuredBackground);
    //void SetResponseVector  (QVector<std::complex<double>> MeasuredResponse);

    // добавила перезгрузку функций

    //void SetBackgroundVector(double* ReBcknd, double* ImBcknd);
    //void SetResponseVector(double* ReRsp, double* ImRsp);

    //void SetBackgroundVector(double* Bcknd);
    //void SetResponseVector(double* Rsp);

    // Для удобного сохранения через QDataStream
    friend QDataStream &operator<<(QDataStream &out, const MeasDataClass &MyMF);
    // Для удобного чтения через QDataStream
    friend QDataStream &operator>>(QDataStream &in, MeasDataClass &MyMeasDataClass);

};





#endif // MeasDataClass_H
