#ifndef THREEDIMENSIONALVECTOR_H
#define THREEDIMENSIONALVECTOR_H



#include <complex>
#include <QVector>
#include <QDataStream>
#include <QDebug>



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
    QString MoveMode = "CCW"; // Поменял здесь тип int->QString. (Возможно не так понял)
};



class ThreeDimensionalVector
{
public:
    ThreeDimensionalVector();

    ~ThreeDimensionalVector();

    ThreeDimensionalVector(QVector <double> ReceivedVector);

    VNAParams VNAParameters;
    OPUParams OPUParameters;


    int CurrentIndex = 0;


    QVector <std::complex<double>> ObjectMeasurementResult;     //  Результат измерений на объекте. Трёхмерный массив комплексных чисел (Изначально был только один массив -- Function)
    QVector <std::complex<double>> BackgroundMeasurementResult; //  Результат измерения фона. Одномерный массив
    QVector <std::complex<double>> ResponseMeasurementResult;   //  Результат измерения образца (отклик) для калибровки



    void Resize(int FNum, int ANum, int ENum); // Смена размера массивов -- теперь меняются три массива, а не один

    // Чтение из массива и запись в массив ObjectMeasurementResult
    std::complex<double> ReadFromObjectResult       (int f, int a, int e);  // Чтение по индексам частоты и углов   из массива результата измерения объекта
    void                 WriteToObjectResult        (int f, int a, int e, std::complex<double> NewValue); // Запись по индексам


    // Чтение строки частот для фиксированных углов поворота
    QVector <std::complex<double>> GetFrequencyVectorAt(int a, int e); // Чтение строчки частот по заданным углам


    int FindAzimuthIndex(double AzimuthValue); // Вычисляет индекс угла поворота по значению
    int FindElevationIndex(double ElevationValue); // Вычисляет индекс угла наклона по значению

    double FindAzimuthValue      (int a);   //Находит значение азимута по индексу
    double FindElevationValue    (int e);   //Находит значение угла подъёма по индексу

    void WriteToRowOfObjectResult(int a, int e, QVector <std::complex<double>> FreqVect); // Запись строки функции от частот по индексам углов

    void SetRanges(double FreqStart, double FreqStop, double FreqNumber, double AzimuthStart, double AzimuthStop, double AzimuthNumber, double ElevationStart, double ElevationStop, double ElevationNumber);

    QVector <double> FreqVector ();         // Вектор частот
    QVector <double> AzimuthVector ();      // Вектор углов вращения
    QVector <double> ElevationVector ();    // Вектор углов наклона



    QVector<std::complex<double>> MakeItScarcer(QVector<std::complex<double>> MyVector); // Прореживание


    QVector <double> SubstractBackgroundAndCalibrate(); // Выдаёт массив действительных чисел

    void ClearFunction();

    // Заполнения векторов:
    void AddMeasuredRow(QVector <std::complex<double>> FrequencyRow);
    void ReceiveBackgroundVector(QVector<std::complex<double>> MeasuredBackground);
    void ReceiveResponseVector  (QVector<std::complex<double>> MeasuredResponse);

    // Для удобного сохранения через QDataStream
    friend QDataStream &operator<<(QDataStream &out, const ThreeDimensionalVector &MyMF);
    // Для удобного чтения через QDataStream
    friend QDataStream &operator>>(QDataStream &in, ThreeDimensionalVector &MyThreeDimensionalVector);

    void FillComplexVectorWithDoubleValues(QVector<double> ReceivedVector);


    //Для построчного заполнения
    int CurrentAzimuthIndex = 0;
    int CurrentElevationIndex = 0;

    // Вернул
    QVector <double> AmplitudeVectorAtAngles            (int a, int e); // Получает вектор амплитуд из ObjectMeasurementVector при углах с индексами a и e



    //QVector <double> FourierAmplVectorAtAngles (int a, int e); // Получает вектор амплитуд фурье образов из ThreeDimensionalVector при углах с индексами a и e (Не быстрое преобразование Фурье)

    //void AddMeasuredObjectValues(QVector <double> vector); -- устаревшее заполнение
    // Заменил Всё на функцию на SubstractBackgroundAndCalibrate
    //  QVector <double> AmplitudeVectorAtFrequencyElevation(int f, int e); // Получает вектор амплитуд из ObjectMeasurementVector на частоте f и угле e
    //  bool CheckBackgroundForSuitability (ThreeDimensionalVector BG);
    //  void SubstractBackground (ThreeDimensionalVector BG);
    //  void Calibrate (ThreeDimensionalVector Calibration, int SampleType);
    //


    //int FNum; // Заменено на NumOfPoi из VNAParams     // Число точек по частотам
    //int ANum; // Заменено на AzTrigPoints из OPUParams // Число точек по углам поворота ANum от Azimuth
    //int ENum; // Заменено на ElTrigPoints из OPUParams // Число точек по углам наклона  ENum от Elevation

    // double FStart; // Заменено на StartFreq из VNAParams   // Начальная частота
    // double AStart; // Заменено на startAzAngl из OPUParams // Начальный угол поворота
    // double EStart; // Заменено на startElAngl из OPUParams // Начальный угол наклона

    // double FStop; // Заменено на StopFreq из VNAParams    //Конечная частота
    // double AStop; // Заменено на stopAzAngl из OPUParams  //Конечный угол поворота
    // double EStop; // Заменено на stopElAngl из OPUParams  //Конечный угол наклона



};





#endif // THREEDIMENSIONALVECTOR_H
