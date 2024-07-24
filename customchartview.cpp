#include "customchartview.h"



CustomChartView::CustomChartView(QChart *chart, QWidget *parent): QChartView(chart, parent)
{
    //setRubberBand(QChartView::RectangleRubberBand);
    setRenderHint(QPainter::Antialiasing);
}



void CustomChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && MovementEnabled)
    {
        FirstMousePosition = event->pos();
        LastMousePosition = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton && MovementEnabled) // Здесь нужно двигать относительно графика, а не относительно окна?
    {
        QPoint delta = event->pos() - LastMousePosition;
        chart()->scroll(-delta.x(), delta.y());
        CurrentChartPosition+=delta;
        LastMousePosition = event->pos();
        //qDebug()<<chart()->plotArea().size();
        //viewport()->update();
    }
    if (event->buttons() & Qt::LeftButton && RubberBandEnabled)
    {

    }

// qDebug()<<this->frameSize(); ====>> 347 192


    //qDebug()<<event->pos();

    QChartView::mouseMoveEvent(event);
}

void CustomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && MovementEnabled)
    {
        setCursor(Qt::ArrowCursor);
    }

    if (event->button() == Qt::LeftButton &&  RubberBandEnabled)
    {
        //EndMousePosition = event->pos() - FirstMousePosition;
        //ScaleFactorX = EndMousePosition.x()/chart()->size().width();
        //ScaleFactorY = EndMousePosition.y()/chart()->size().height();
        //qDebug()<<ScaleFactorX<<ScaleFactorY;
    }
    QChartView::mouseReleaseEvent(event);
}
