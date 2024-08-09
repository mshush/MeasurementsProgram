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
    int NumberOfPoints = 1601;
    QVector <double> x, y; // Или лучше QCPVector2D?
    QVector <std::complex<double>> f; //Перенести в имитацию процесса?
    bool ContinuousMeasurementMode = false;

    //Перенести в имитацию процесса-------------------------
    //std::default_random_engine generator;
    //std::normal_distribution<double> distribution;
    //std::gamma_distribution<double> distribution;
    //std::cauchy_distribution<double> distribution;
    //QTimer * RefreshTimer;
    //-------------------------------------------------------

public slots:
    void UpdateMeasuredData(QVector <std::complex<double>> MeasuredData);
    void ResetPlot();
    void SavePlot();
    void DeleteAllMarkers();
    void CopyPlot();
    //void Measure();
    //void MeasureContinuously();
    //void RefreshPlot();
    void SaveData();
    //void ImportData();
    void FourierTransform();
    void InverseFourierTransform();
    void AddNewMarker(int Key, int Style, QColor Colour);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // PLOTCLASS_H
