#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QChartView>
#include <QObject>
#include <QWidget>

class CustomChartView : public QChartView
{
    Q_OBJECT
public:
    CustomChartView(QChart *chart, QWidget *parent=nullptr);
    bool MovementEnabled = false;
    bool RubberBandEnabled = false;
    QPoint CurrentChartPosition = QPoint(0,0);

    double ScaleFactorX;
    double ScaleFactorY;


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



private:
    QPoint LastMousePosition;
    QPoint FirstMousePosition;
    QPoint EndMousePosition;
};








































#endif // CUSTOMCHARTVIEW_H












































/*
class ChartView : public QtCharts::QChartView
{
public:


protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            m_lastMousePos = event->pos();
            setCursor(Qt::ClosedHandCursor);
        }
        QtCharts::QChartView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (event->buttons() & Qt::LeftButton)
        {
            QPoint delta = event->pos() - m_lastMousePos;
            chart()->scroll(-delta.x(), delta.y());
            m_lastMousePos = event->pos();
        }
        QtCharts::QChartView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {
            setCursor(Qt::ArrowCursor);
        }
        QtCharts::QChartView::mouseReleaseEvent(event);
    }

private:
    QPoint m_lastMousePos;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a QLineSeries with some data points
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    series->append(0, 1);
    series->append(1, 3);
    series->append(2, 2);
    series->append(3, 4);
    series->append(4, 3);

    // Create a QChart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Chart with Panning");

    // Create a ChartView (custom QChartView) and set the chart
    ChartView *chartView = new ChartView(chart);

    // Create a main window to display the chart view
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
*/
