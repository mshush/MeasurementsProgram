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
    QVector <WidgetForCustomPlot*> PlotTabs; // Сделать листом?

    WidgetForCustomPlot * MeasurementPlotTab;
    WidgetForCustomPlot * TimeOfFlightPlotTab;


public slots:
    //void CreateNewTabFromImportedData();
    //void SendMeasureSignalToFirstTab(); // Теперь процесс имитируется в ProcessImitation
    //void SendMeasureContinuouslySignalToFirstTab();
    //void SetFrequencyParameters(double FreqStart, double FreqStop, int NumberOfPoints);
    //void UpdateMeasurementPlot(QVector <std::complex<double>> f);
    //void UpdateBackgroundPlot (QVector <std::complex<double>> bf);
    //void SaveData();
    void InitiateCloseTabButton();
    void ContinuousMeasurementModeChanged();
    //void PerformFourierTransformOfCurrentPlot();
    //void PerformInverseFourierTransformOfCurrentPlot();
    //void ChangeDemonstratedAngles();

};






#endif // TABWIDGETFORCHARTS_H
