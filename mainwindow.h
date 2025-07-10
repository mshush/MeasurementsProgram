#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QObject>
#include <tabwidgetforparameters.h>
#include <tabwidgetfortools.h>
#include <treewidgetforfiles.h>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <tabwidgetforcharts.h>
#include <widgetforcustomplot.h>
#include <plotclass.h>
#include <processimitation.h>
#include <QDataStream>
#include <QThread>
#include <QProgressBar>
#include <QTranslator>
#include "measurmentscontrol.h"
#include "testVNA.h"
#include "ui_mainwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //TestVNA * VNATest;
    QTranslator translator;

    MeasDataClass MeasData;
    MeasurmentsControl *MeasControl;

    TabWidgetForParameters * TabOfParameters;
    TabWidgetForTools * TabOfTools;
    TabWidgetForCharts * ChartTab;
    WidgetForCustomPlot * CustomPlotWidget;
    ProcessImitation * Process;

    QComplexVector FullPatternArray;
    void FillPatternArrayFromMeasData();



    QAction * SaveFileAction;
    QAction * OpenFileAction;
    QAction * StartMeasureAction;
    QAction * StopMeasureAction;
    QAction * MeasureBackground;
    QAction * MeasureCalibration;
    QTimer * Timer;


    void SetThreeDimensionalVector(ThreeDimensionalVector F);
    void ChangeAngleOfDemonstration();
    void SaveThreeDimensionalVector();
    void SetBackground();
    void SubstractBackground();
    void SetCalibration ();

    bool BackgroundAddedToMainPlot = false;

    void ShowErrorMessage(QString Description, QString Advice);


    void ConnectPlot();
    void ConnectMenu();
    void ConnectSetup();
    void ConnectProcessing();
    void ConnectTabs();

    void UpdatePlotData();

    void UploadFile();

    int azim=0;
    int elev=0;


    int CurrentPlotIndex=0;
    bool ResetPlotNeeded;


    QAction* MeasureAction;
    QAction* MeasureBackgroundAction;
    QAction* MeasureTargetAction;


    QAction* MeasureAzTargetAction;
    QAction* MeasureResponseAtSingleAnglAction;
    QAction* MeasureBckgndAtSingleAnglAction;
    QAction* MeasureCurrentAspectAction;
    QAction* AbortAction;
    QAction* PaintPlotsAction;

    QMenu * MenuFile;
    QMenu * MenuFileWrite;
    QMenu * MenuFileRead;
    QMenu * MenuMeasure;
    QMenu * MenuProcess;
    QMenu * MenuPost_Process;
    QMenu * MenuOptions;
    QMenu * MenuCreatePylComp;
    QMenu * MenuLanguage;


    QAction * SetRussianLanguageAction;
    QAction * SetEnglishLanguageAction;


    QVector<double> X1601;

    void FillMenu();

    void SetConnectionMainWinWithMeasCntrl();

    void changeEvent(QEvent *event) override;

    QVector <MeasDataClass::MeasDataType> DataTypeVector =
        {
            MeasDataClass::MeasDataType::CalibrationArr,
            MeasDataClass::MeasDataType::CurrentAspect,
            MeasDataClass::MeasDataType::CurrentGatedProfRange,
            MeasDataClass::MeasDataType::CurrentProfRange,
            MeasDataClass::MeasDataType::PatternArr,
            MeasDataClass::MeasDataType::ProcessedBcknd,
            MeasDataClass::MeasDataType::RawBcknd,
            MeasDataClass::MeasDataType::RawRsp,
            MeasDataClass::MeasDataType::RawTarget
        };

public slots:
    void SetAllVNAParamsFromInterface();
    void SetAllOPUParamsFromInterface();
    void GetPlotFromDat();


    void OnMeasureAzTargetActionPressed(); // Переименовать в clicked
    void OnMeasureResponseAtSingleAnglActionPressed();
    void OnMeasureBckgndAtSingleAnglActionPressed();
    void OnMeasureCurrentAspectActionPressed();
    void OnAbortActionPressed();
    void OnSaveAsActionPressed();

    void UpdateAzimuthPlot(int iaz, int iel);

    void ChangeLanguageToRussian();
    void ChangeLanguageToEnglish();

    void PaintAllPlots();



    void PaintSomePlot(int TabID, LegendWidget::DataFromLegendRow LegendData);

    //void SendDataToLegend();


    void UpdatePlots();


    void addRandomError(QVector<double>& data, double mean, double stddev);

    void ConnectLegendAndChartTabs();
    // Связанные с легендой слоты: возможно лучше перенести.
    void OnReadDataSignalReceived();
    void OnWriteDataSignalReceived();
    void OnAddLineSignalReceived();
    void OnDeleteLineSignalReceived();
    void OnClearAllSignalReceived();
    void OnUpLineSignalReceived();
    void OnDownLineSignalReceived();
    void CopyToMemoryLineSignalReceived();
    void RefreshSignalReceived();



signals:
    void ErrorOccured(QString ErrorText);
    //void SendDataToLegend(QVector <double> Freq, QVector <double> Az, QVector <double> El);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

