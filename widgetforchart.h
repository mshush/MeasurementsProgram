#ifndef WIDGETFORCHART_H
#define WIDGETFORCHART_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QGraphicsView>
#include <customchartview.h>

class WidgetForChart : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForChart(QWidget *parent = nullptr);

    QHBoxLayout * HorizontalChartLayout;
    QLineSeries * ChartSeries;
    QChart * Chart;
    int freq1;
    int freq2;
    CustomChartView *ChartView;
    QSlider * Freq1Slider;
    QSlider * Freq2Slider;

    QValueAxis * axisY;
    void ScaleToZoom(QRectF rect, QPointF fromScenePoint, QPointF toScenePoint);


    //QGroupBox * ChartManipulationGroupBox;
    //QVBoxLayout * ChartManipulationMainLayout;
    //QGridLayout * ChartManipulationGridLayout;

public slots:
void RedrawChart();
};

#endif // WIDGETFORCHART_H
