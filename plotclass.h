#ifndef PLOTCLASS_H
#define PLOTCLASS_H

#include <qcustomplot.h>
#include <QObject>
#include <QWidget>
#include <QList>
#include <list>
#include <QClipboard>
#include <QImage>
#include <random>

class PlotClass : public QCustomPlot
{
    Q_OBJECT
public:
    PlotClass(QWidget *parent = nullptr);

    QCPItemTracer * MouseMoveMarker;
    QCPItemText * MouseMoveLabel;
    bool markeraddbuttonactive = false;
    bool markerdeletebuttonactive = false;
    int iter = 0;
    QColor MarkerColour = Qt::black;
    int MarkerStyle = 1;
    std::list <QCPItemTracer*> AddedMarkersList;
    std::list <QCPItemText*> AddedMarkerLabelsList;
    QRubberBand * RubberBand;

    //QList<QCPItemTracer*> MarkerList;

    void ResetPlot();
    void SavePlot();
    void DeleteAllMarkers();
    void CopyPlot();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // PLOTCLASS_H
