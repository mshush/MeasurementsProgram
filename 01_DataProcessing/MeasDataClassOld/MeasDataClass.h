#ifndef MeasDataClass_H
#define MeasDataClass_H



#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>
#include "referencercs.h"

#define CCW 0
#define CW 1

struct VNAParams
{
    QString ip = "192.168.0.84";
    int port = 5025;

    int Pow = 0;
    double StartFreq = 1;
    double StopFreq = 20;
    int NumOfPoi = 1601;
    int NumOfSweeps  = 1;
    int IF = 10000;
    QString Datatype = "double";
    double type;
    QString MeasParameter = "S21";
    bool ExternalTriggerOn = false;
};


struct OPUParams
{
    double startAzAngl = 0;
    double stopAzAngl = 360;
    double startElAngl = 0;
    double stopElAngl = 0;
    int Speed = 1;
    int AzTrigPoints = 3600;
    int ElTrigPoints = 1;
    int MoveMode = CCW;
};



class MeasDataClass
{
private:
    ReferenceRCS RefCylinder;
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
    QVector <std::complex<double>> TargetMeasArray;     //  Результат измерений на объекте. Трёхмерный массив комплексных чисел (Изначально был только один массив -- Function)
    QVector <std::complex<double>> BackgroundMeasArray; //  Результат измерения фона. Одномерный массив
    QVector <std::complex<double>> ResponseMeasArray;   //  Результат измерения образца (отклик) для калибровки
    // изменила названия переменных
    void Resize(int FreqNum, int AzNum, int ElNum);

    // Чтение из массива и запись в массив TargetMeasArray
    // поменяла названия на более четкие, изменила названия переменных
    std::complex<double> ReadFromTargetMeasArray (int FreqIndex, int TargetMeasArray, int ElIndex);  // Чтение по индексам частоты и углов   из массива результата измерения объекта
    void WriteValueToTargetArray  (int FreqIndex, int TargetMeasArray, int ElIndex, std::complex<double> NewValue); // Запись по индексам
    void WriteSweepToTargetArray (int TargetMeasArray, int ElIndex, QVector <std::complex<double>> SingleSweep); // Запись строки функции от частот по индексам углов


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


    // изменила название MateItScarce -> DonwSample
    QVector<std::complex<double>> DownSample(QVector<std::complex<double>> MyVector); // Прореживание    // QVector<std::complex<double>> MakeItScarcer(QVector<std::complex<double>> MyVector); // Прореживание

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

    void SetBackgroundVector(QVector<std::complex<double>> MeasuredBackground);
    void SetResponseVector  (QVector<std::complex<double>> MeasuredResponse);

    // добавила перезгрузку функций

    void SetBackgroundVector(double* ReBcknd, double* ImBcknd);
    void SetResponseVector(double* ReBcknd, double* ImBcknd);

    void SetBackgroundVector(double* Bcknd);
    void SetResponseVector(double* Rsp);

    // Для удобного сохранения через QDataStream
    friend QDataStream &operator<<(QDataStream &out, const MeasDataClass &MyMF);
    // Для удобного чтения через QDataStream
    friend QDataStream &operator>>(QDataStream &in, MeasDataClass &MyMeasDataClass);

};





#endif // MeasDataClass_H
