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
#include <random>
#include <QFile>
#include <QDataStream>
#include <cmath>
#include <complex>
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
    QColor MarkerColour = Qt::black;
    int MarkerStyle = 1;
    std::list <QCPItemTracer*> AddedMarkersList;
    std::list <QCPItemText*> AddedMarkerLabelsList;

 //   double FreqStart = 1.0;
 //   double FreqStop = 2.0;
 //   int NumberOfPoints = 1601;

    //QVector <double> x, y;
    //QVector <std::complex<double>> f; // Убрать вообще

    bool ContinuousMeasurementMode = false;

    SelectionRectClass * SelectionRectangle;


public slots:
    //void UpdateMeasuredData  (QVector <std::complex<double>> MeasuredData);
    //void UpdateBackgroundPlot(QVector <std::complex<double>> BackgroundData);

    void ResetPlot();
    void SavePlot();
    void DeleteAllMarkers();
    void CopyPlot();
    void SaveData();
    //void ImportData();
    //void FourierTransform(); //Перенести в MainWindow?
    //QVector <std::complex<double>> FourierTransformVector(QVector <std::complex<double>> f);
    //void InverseFourierTransform();
    void AddNewMarker(int Key, int Style, QColor Colour);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // PLOTCLASS_H
