#ifndef PLOTCLASS_H
#define PLOTCLASS_H

#include <qcustomplot.h>
#include <QObject>
#include <QWidget>
#include <QList>

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


    //QList<QCPItemTracer*> MarkerList;

    void ResetPlot();
    void SavePlot();
    void DeleteAllMarkers();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // PLOTCLASS_H
