#ifndef SELECTIONRECTCLASS_H
#define SELECTIONRECTCLASS_H

#include <qcustomplot.h>
#include <QObject>
#include <QtGui/QPainter>

class SelectionRectClass : public QCPSelectionRect
{
    Q_OBJECT
public:
    SelectionRectClass(QCustomPlot *parent);

    bool XAxisLocked = false;
    bool YAxisLocked = false;

protected:
    void draw(QCPPainter *painter) override;
};

#endif // SELECTIONRECTCLASS_H
