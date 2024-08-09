#ifndef TABWIDGETFORCHARTS_H
#define TABWIDGETFORCHARTS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QTabBar>
//#include<widgetforchart.h>
#include <widgetforcustomplot.h>
//#include <QMdiArea> Можно попробовать наследовать отсюда

class TabWidgetForCharts : public QTabWidget
{
    Q_OBJECT
public:

    //WidgetForChart * ChartTab;
    //WidgetForCustomPlot * PlotTab;
    TabWidgetForCharts();
    ~TabWidgetForCharts();
    QVector <WidgetForCustomPlot*> PlotTabs; // Сделать листом

public slots:
    void CreateNewTabFromImportedData();
    //void SendMeasureSignalToFirstTab();
    //void SendMeasureContinuouslySignalToFirstTab();
    void SetMeasurementParameters(double FreqStart, double FreqStop, int NumberOfPoints);
    void UpdateMeasurementPlot(QVector <std::complex<double>> f);
    void SaveData();
    void InitiateCloseTabButton();
    void ContinuousMeasurementModeChanged();
    void PerformFourierTransformOfCurrentPlot();
    void PerformInverseFourierTransformOfCurrentPlot();
};






#endif // TABWIDGETFORCHARTS_H
