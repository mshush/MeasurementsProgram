#ifndef TABWIDGETFORCHARTS_H
#define TABWIDGETFORCHARTS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QTabBar>
//#include<widgetforchart.h>
#include <widgetforcustomplot.h>

class TabWidgetForCharts : public QTabWidget
{
    Q_OBJECT
public:

    //WidgetForChart * ChartTab;
    //WidgetForCustomPlot * PlotTab;
    TabWidgetForCharts();

    QVector <WidgetForCustomPlot*> PlotTabs;

public slots:
    void CreateNewTabFromImportedData();
    //void SendMeasureSignalToFirstTab();
    //void SendMeasureContinuouslySignalToFirstTab();

    void SetStartStopFrequencies(double StartFreq, double StopFreq);
};






#endif // TABWIDGETFORCHARTS_H
