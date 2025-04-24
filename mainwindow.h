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

QT_BEGIN_NAMESPACE
namespace Ui {
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
    QTranslator * translator;

    MeasDataClass MeasData;
    MeasurmentsControl *MeasControl;

    //QMenuBar * MenuBar;
    TabWidgetForParameters * TabOfParameters;
    TabWidgetForTools * TabOfTools;
    //WidgetForChart * ChartWidget;
    TabWidgetForCharts * ChartTab;
    //TreeWidgetForFiles * FileTreeWidget;
    WidgetForCustomPlot * CustomPlotWidget;
    ProcessImitation * Process;
    //void addItems(const QDir &directory, QTreeWidgetItem *parent); // Перенести в отдельный класс для дерева

    ThreeDimensionalVector StoredFunction; // Хранить в WidgetForCustomPlot чтобы открывать старое?
    ThreeDimensionalVector CalibrationFunction;
    ThreeDimensionalVector BackgroundFunction;

    //QThread * Thread;



    //enum ModeOfMeasurement {Response, Background, Calibration};


    // Индикатор выполнения
    //QProgressBar * ProgressBar;


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

    // Индикатор выполнения
    //QProgressBar * ProgressBar;


    int azim=0;
    int elev=0;


    int CurrentPlotIndex=0;
    bool ResetPlotNeeded;


    QAction* MeasureAction;
    QAction* MeasureBackgroundAction;
    QAction* MeasureTargetAction;


    QAction* MeasureAzTargetAction;
    QAction* MeasureResponseAtSignleAnglAction;
    QAction* MeasureBckgndAtSingleAnglAction;
    QAction* MeasureCurrentAspectAction;
    QAction* AbortAction;
    QAction* PaintPlotsAction;


    QAction * SetRussianLanguageAction;
    QAction * SetEnglishLanguageAction;


    QVector<double> X1601;
    //QThread * MeasThread;

/*
protected:
    void showEvent(QShowEvent *event) override;
    //void CalculateDistancePortrait();
*/

    void FillMenu();

    void SetConnectionMainWinWithMeasCntrl();


public slots:
    //void TellPlotTabsToChangeAngle(QVector <std::complex<double>> NeededRowFromThreeDimensionalVector); //

    //void HandleReceivedMeasuredFreqVector( QVector <double> ReceivedVector);

    void SetAllVNAParamsFromInterface();
    void SetAllOPUParamsFromInterface();

    void GetPlotFromDat();


    void OnMeasureAzTargetActionPressed();
    void OnMeasureResponseAtSignleAnglActionPressed();
    void OnMeasureBckgndAtSingleAnglActionPressed();
    void OnMeasureCurrentAspectActionPressed();
    void OnAbortActionPressed();


    void UpdateAzimuthPlot(int iaz, int iel);

    //void OnMeasurePressed();
    //void OnMeasureBackgroundPressed();
    //void OnMeasureTargetPressed();


//    void UpdateSweepGraphSlot(QDoubleVector SweepArrayAmpl);
//    void UpdateProfRangeSlot(QDoubleVector ProfRangeArrayAmpl);
//    void UpdateGatedProfileRangeSlot(QDoubleVector SweepArrayAmpl);
//    void UpdatePatternSlot(QDoubleVector DiagAnglArrayAmpl);


    void ChangeLanguageToRussian();
    void ChangeLanguageToEnglish();

    void PaintAllPlots(); // разбить
    void UpdatePlots();


    void addRandomError(QVector<double>& data, double mean, double stddev);

signals:
    void ErrorOccured(QString ErrorText);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

