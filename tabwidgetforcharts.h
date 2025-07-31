#ifndef TABWIDGETFORCHARTS_H
#define TABWIDGETFORCHARTS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QTabBar>
//#include<widgetforchart.h>
#include <widgetforcustomplot.h>
//#include <QMdiArea> Можно попробовать наследовать отсюда
#include <printpreview.h>

class TabWidgetForCharts : public QTabWidget
{
    Q_OBJECT
public:

    TabWidgetForCharts();
    ~TabWidgetForCharts();
    QVector <WidgetForCustomPlot*> PlotTabs; // Сделать вектором из QWidget, чтобы разные классы-наследники вносить (Скорее всего так понадобится сделать после добавления радиоизображения, так как для него понадобится другая панель управления)


    WidgetForCustomPlot * MeasurementPlotTabFrequency;
    WidgetForCustomPlot * TimeOfFlightPlotTab;
    WidgetForCustomPlot * MeasurementPlotTabAngle;
    WidgetForCustomPlot * CrossRangeTab;
    WidgetForCustomPlot * ColorMapTab;
    WidgetForCustomPlot * StatisticaTab;
    WidgetForCustomPlot * FrequencyTab;
    WidgetForCustomPlot * ScriptEditorTab;


    WidgetForCustomPlot * SweepTab;
    WidgetForCustomPlot * ProfRangeTab;
    WidgetForCustomPlot * GatedProfileTab;
    WidgetForCustomPlot * PatternTab;
    PrintPreview        * PrintPreviewTab;

signals:
    void SendCurrentPlotIndexToLegendSignal(int TabIndex);

public slots:
    void InitiateCloseTabButton();
    void SendImagesIfPrintPreview(int TabIndex);
};






#endif // TABWIDGETFORCHARTS_H


//void PerformFourierTransformOfCurrentPlot();
//void PerformInverseFourierTransformOfCurrentPlot();
//void ChangeDemonstratedAngles();
//void ShowPrintPreview();
//void ContinuousMeasurementModeChanged();
//void CreateNewTabFromImportedData();
//void SendMeasureSignalToFirstTab(); // Теперь процесс имитируется в ProcessImitation
//void SendMeasureContinuouslySignalToFirstTab();
//void SetFrequencyParameters(double FreqStart, double FreqStop, int NumberOfPoints);
//void UpdateMeasurementPlot(QVector <std::complex<double>> f);
//void UpdateBackgroundPlot (QVector <std::complex<double>> bf);
//void SaveData();
