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

    // Переводчик
    QTranslator translator;

    // Измерения и таймер
    MeasDataClass MeasData;
    MeasurmentsControl * MeasControl;
    QTimer * Timer;

    QComplexVector FullPatternArray; // Нужно ли так заморачиваться?
    void FillPatternArrayFromMeasData();



    // Видимые виджеты
    TabWidgetForParameters * TabOfParameters;
    TabWidgetForTools * TabOfTools;
    TabWidgetForCharts * ChartTab;


    // Функции соединения
    void ConnectMenu();
    void ConnectMessages();
    void ConnectDebugMessages();
    void ConnectLegendAndChartTabs();

    // Функции из конструктора
    void FillMainWindow();
    void FillMenu();
    void SetUpMeasControlAndTimer();
    void SetUpGeneralStyle();
    void SetUpConnections();


    // Пункты Меню
    QMenu * MenuFile;
    QMenu * MenuFileWrite;
    QMenu * MenuFileRead;
    QMenu * MenuMeasure;
    QMenu * MenuProcess;
    QMenu * MenuPost_Process;
    QMenu * MenuOptions;
    QMenu * MenuCreatePylComp;
    QMenu * MenuLanguage;

    // Всплывающие действия в строке меню
    QAction * SaveFileAction;
    QAction * OpenFileAction;
    QAction * StartMeasureAction;
    QAction * StopMeasureAction;
    QAction * MeasureBackground;
    QAction * MeasureCalibration;

    QAction* MeasureAction;
    QAction* MeasureBackgroundAction;
    QAction* MeasureTargetAction;

    QAction* MeasureAzTargetAction;
    QAction* MeasureResponseAtSingleAnglAction;
    QAction* MeasureBckgndAtSingleAnglAction;
    QAction* MeasureCurrentAspectAction;
    QAction* AbortAction;
    QAction* PaintPlotsAction;

    QAction * SetRussianLanguageAction;
    QAction * SetEnglishLanguageAction;

    // Переделываю функцию изменения для смены языка
    void changeEvent(QEvent *event) override;


    // Вектор типов данных (для простоты)
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

    bool ResetPlotNeeded; // Индикатор, нужно ли обновить график -- как-то избавиться

public slots:
    // Слоты установки параметров приборов из интерфейса
    void SetAllVNAParamsFromInterface();
    void SetAllOPUParamsFromInterface();

    // Вызываются при нажатии на действия из меню
    void OnMeasureAzTargetActionTriggered();
    void OnMeasureResponseAtSingleAnglActionTriggered();
    void OnMeasureBckgndAtSingleAnglActionTriggered();
    void OnMeasureCurrentAspectActionTriggered();
    void OnAbortActionTriggered();
    void OnSaveAsActionTriggered();


    //Слоты смены языка
    void ChangeLanguageToRussian();
    void ChangeLanguageToEnglish();

    // Рисование графиков
    void UpdateAzimuthPlot(int iaz, int iel); // Обновляет график от угла
    void PaintAllPlots();  // Слот перерисовки всех графиков
    void PaintSomePlot(int TabID, LegendWidget::DataFromLegendRow LegendData);// Функция отрисовки одного графика в соответствии с легендой
    void UpdatePlots(); // Обновить графики



    // Связанные с легендой слоты
    void OnReadDataSignalReceived();
    void OnWriteDataSignalReceived();
    void OnAddLineSignalReceived();
    void OnDeleteLineSignalReceived();
    void OnClearAllSignalReceived();
    void OnUpLineSignalReceived();
    void OnDownLineSignalReceived();
    void CopyToMemoryLineSignalReceived();
    void RefreshSignalReceived();

    // Вывод сообщения об ошибке
    void ShowErrorMessage(QString Description, QString Advice);

signals:
    void ErrorOccured(QString ErrorText);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H



















//  Не используемые, устаревшие куски
/*
    void SetThreeDimensionalVector(ThreeDimensionalVector F);
    void ChangeAngleOfDemonstration();
    void SaveThreeDimensionalVector();
    void SetBackground();
    void SubstractBackground();
    void SetCalibration ();
    bool BackgroundAddedToMainPlot = false;
    //void ConnectSetup();
    //void ConnectProcessing();
    //void ConnectTabs();
    //void ConnectPlot();

    void SetConnectionMainWinWithMeasCntrl();
    void UploadFile();


    void UpdatePlotData();


    int azim=0;
    int elev=0;

    int CurrentPlotIndex=0;

    //void GetPlotFromDat();

    //void addRandomError(QVector<double>& data, double mean, double stddev);

*/


