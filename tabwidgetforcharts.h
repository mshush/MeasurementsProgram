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

    QStringList TabTitleList =
        {
            tr("Measuring"), // Текущий свип (По умолчанию от частоты)
            tr("Profile Range"), // Текущий дальностный портрет (на этом угле)
            tr("Unprocessed"), // Необработанные данные
            tr("Pattern")  // Обработанный Pattern
            //tr("ClbrSweep"),
            //tr("PttrnSweep"),
            //tr("CurrentAspect"),
            //tr("Current(Gated)ProfRangeVector"),
            //tr("Azimuth"),
        };


    // Вектор вкладок с графиками
    QVector <WidgetForCustomPlot*> PlotTabs; // Сделать вектором из QWidget, чтобы разные классы-наследники вносить (Скорее всего так понадобится сделать после добавления радиоизображения, так как для него понадобится другая панель управления)

    // Вкладка с предпросмотром
    PrintPreview        * PrintPreviewTab;

    // Функция обновления текста
    void UpdateText();
    void UpdateTabTitles();
    void UpdatePrintPreviewCheckBoxes();


signals:
    void SendCurrentPlotIndexToLegendSignal(int TabIndex);
    void SendPixmapToPreview(QPixmap pixmap);

public slots:
    void InitiateCloseTabButton();
    void OnTabChanged(int TabIndex);
    void SendPixmapToPrintPreview(int Tabindex, int width, int height, double scale = 1.0);
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


/*
    // Виджеты вкладок с графиками
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
    */
