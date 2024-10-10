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
//#include <random>
#include <QFile>
#include <QDataStream>
//#include <cmath>
//#include <complex>
#include <selectionrectclass.h>

class PlotClass : public QCustomPlot
{
    Q_OBJECT
public:
    PlotClass(QWidget *parent = nullptr);
    ~PlotClass();

    QCPItemTracer * MouseMoveMarker;
    QCPItemText * MouseMoveLabel;
    bool markeraddbuttonactive = false;
    bool markerdeletebuttonactive = false;
    int iter = 0;
    QColor MarkerColour = Qt::red;
    int MarkerStyle = 1;
    std::list <QCPItemTracer*> AddedMarkersList;        //Переименовать
    std::list <QCPItemText*> AddedMarkerLabelsList;     //Переименовать

    int SelectedGraph = 0;

 //   double FreqStart = 1.0;
 //   double FreqStop = 2.0;
 //   int NumberOfPoints = 1601;

    //QVector <double> XVector, YVector;
    //QVector <std::complex<double>> f; // Убрать вообще

    bool ContinuousMeasurementMode = false;

    SelectionRectClass * SelectionRectangle;

    QTimer * Timer;

    QCPItemText * PlotLabel;


public slots:
    //void UpdateMeasuredData  (QVector <std::complex<double>> MeasuredData);
    //void UpdateBackgroundPlot(QVector <std::complex<double>> BackgroundData);

    void ResetPlot();

    void DeleteAllMarkers();
    void CopyPlot();
    void SaveData(); // Устар
    double SubstractMarkers(QCPItemTracer * Marker1, QCPItemTracer * Marker2);
    //void ImportData();
    //void FourierTransform(); //Перенести в MainWindow?
    //QVector <std::complex<double>> FourierTransformVector(QVector <std::complex<double>> f);
    //void InverseFourierTransform();
    void AddNewMarker(double Key, int Style, QColor Colour, int GraphNumber = 0); // Возможно стоит добавить value, если маркер откреплён

    void ContinuousMeasurementsModeChanged(bool ModeStatus);

    void ChangeSelectedGraph(int GraphId);

    void saveDat(QString filePath);
    void saveCsv(QString filePath);
    void loadDat(QString filePath);
    void loadCsv(QString filePath);

    void SaveAs();
    void OpenFile();


    void ToNextMax(); // Переместить маркер на следующий максимум справа от текущего положения
    void ToPrevMax();



protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public:
signals:
    void ErrorOccured(QString ErrorText);
    void MarkerAddedSignal(QCPItemTracer* MarkerPtr);
    void AllMarkersDeletedSignal();
    void MarkerDeletedSignal(int Index);
    void MarkerSelectedSignal(int Index);
    void MarkerUnSelectedSignal(int Index);
};

#endif // PLOTCLASS_H
