#ifndef PLOTCLASS_H
#define PLOTCLASS_H

#include <qcustomplot.h>
#include <QObject>
#include <QWidget>
#include <QList>
#include <list>
#include <QClipboard>
#include <QImage>
#include <QTimer>
#include <QFile>
#include <QDataStream>
#include <selectionrectclass.h>
#include <QVector>


class PlotClass : public QCustomPlot
{
    Q_OBJECT
public:
    PlotClass(QWidget *parent = nullptr);
    ~PlotClass();

    //Функции из конструктора:
    void SetUpGeneralStyle();
    void SetUpItems();
    void SetUpCursorPositionText();
    void SetUpConnections();

    // Функции из функций из конструктора
    void SetUpMouseMoveMarker();
    void SetUpPolarAxes();
    void SetUpDescartesAxes();





    enum class ComplexInfo // Перечисление видов отображения комплексных чисел (по оси Y)
    {
        Amplitude,
        Phase,
        Real_Part,
        Imaginary_Part
    };

    ComplexInfo ComplexDisplayMode = ComplexInfo::Amplitude; //Режим отображения комплексных чисел

    bool PolarFormatInUse = false; // Булевая переменная для обозначения, используется ли полярный формат

    SelectionRectClass * SelectionRectangle; // Прямоугольник выбора


    QCPItemTracer * MouseMoveMarker; // Маркер прицела
    QCPItemText * MouseMoveLabel; // Подпись к маркеру прицела

    // Для полярного графика:
    class CustomRadialAxis : public QCPPolarAxisRadial
    {
    public:
        CustomRadialAxis(QCPPolarAxisAngular *parent);
    protected:
        void draw(QCPPainter *painter) override;
    };



    // Оси полярного графика
    QCPPolarAxisAngular * AngularAxis;
    //QCPPolarAxisRadial * RadialAxis;
    CustomRadialAxis * RadialAxis;
    // Возможно понадобится массив графиков

    QCPAxisRect * AxisRectangle; // Прямоугольник с осями сохраняю сюда пока работа идёт с полярным графиком

    QVector <double> KeyVector;


    bool markeraddbuttonactive = false;
    bool markerdeletebuttonactive = false;
    int iter = 0;
    QColor MarkerColour = Qt::red;
    int MarkerStyle = 1;
    std::list <QCPItemTracer*> AddedMarkersList;        //Переименовать
    std::list <QCPItemText*> AddedMarkerLabelsList;     //Переименовать

    int SelectedGraph = 0;


    QCPItemText * PlotLabel;

    int CurrentMarkerIndex = 0;

    QColor GenerateColor(int n) // Чтобы графики были разных цветов, но не слишком тёмными.
    {
        int R = 100 + (n * 222) % 156;
        int G = 100 + (n * 553) % 156;
        int B = 100 + (n * 819) % 156;
        return QColor(R,G,B);
    }

    QVector <QCPGraph *> GraphVector;

    void AddEmptyGraphToPlot();

    QString XAxisLabel = tr("X-Axis, x-units");
    QString YAxisLabel = tr("Y-Axis, y-units");




public slots:
    //void UpdateMeasuredData  (QVector <std::complex<double>> MeasuredData);
    //void UpdateBackgroundPlot(QVector <std::complex<double>> BackgroundData);

    void ResetPlot();

    QPixmap PixmapForPreview(int widthparam, int heightparam, double scaleparam);

    void DeleteAllMarkers();
    void CopyPlot();
    void SaveData(); // Устар
    double SubstractMarkers(QCPItemTracer * Marker1, QCPItemTracer * Marker2);

    void AddNewMarker(double Key, int Style, QColor Colour, int GraphNumber = 0); // Возможно стоит добавить value, если маркер откреплён


    void ChangeSelectedGraph(int GraphId);

    void saveDat(QString filePath);
    void saveCsv(QString filePath);
    void loadDat(QString filePath);
    void loadCsv(QString filePath);

    void SaveAs();
    void OpenFile();


    void ToNextMax(); // Переместить маркер на следующий максимум справа от текущего положения
    void ToPrevMax();


    void ChangeYAxisMax (QString  MaxValue);
    void ChangeYAxisSpan(QString SpanValue);


    void ChangeToPolarFormat();     // Переводит график в полярный формат
    void ChangeToDescartesFormat(); // Переводит график в декартовый формат


protected:
    void mouseMoveEvent     (QMouseEvent *event) override;
    void mousePressEvent    (QMouseEvent *event) override;
    void mouseReleaseEvent  (QMouseEvent *event) override;
public:
signals:
    void ErrorOccured(QString ErrorText);
    void MarkerAddedSignal(QCPItemTracer* MarkerPtr);
    void AllMarkersDeletedSignal();
    void MarkerDeletedSignal(int Index);
    void MarkerSelectedSignal(int Index);
    void MarkerUnSelectedSignal(int Index);
    void GraphClickedSignal(int Index);


};

#endif // PLOTCLASS_H















//void ContinuousMeasurementsModeChanged(bool ModeStatus);
//void ImportData();
//void FourierTransform(); //Перенести в MainWindow?
//QVector <std::complex<double>> FourierTransformVector(QVector <std::complex<double>> f);
//void InverseFourierTransform();
//void OnSelectionChangedSlot(bool selected, QCPItemText * NewMarkerLabel, QCPItemTracer * NewMarker);
//void selectionChangedByUser() override; Так не работает
//bool ContinuousMeasurementMode = false;

