#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
#include <QtWidgets>
//#include <QtCharts>
#include <QObject>
#include <tabwidgetforparameters.h>
#include <tabwidgetfortools.h>
//#include <widgetforchart.h>
#include <treewidgetforfiles.h>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <tabwidgetforcharts.h>
#include <widgetforcustomplot.h>
#include <plotclass.h>
#include <processimitation.h>
#include <QDataStream>
//#include <QLocale>
#include <QThread>
#include <QProgressBar>


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

    QThread * Thread;

    //enum ModeOfMeasurement {Response, Background, Calibration};


    // Индикатор выполнения
    //QProgressBar * ProgressBar;


    QAction * SaveFileAction;
    QAction * OpenFileAction;
    QAction * StartMeasureAction;
    QAction * StopMeasureAction;
    QAction * MeasureBackground;
    QAction * MeasureCalibration;


    void SetThreeDimensionalVector(ThreeDimensionalVector F);
    void ChangeAngleOfDemonstration();
    void SaveThreeDimensionalVector();
    void SetBackground();
    void SubstractBackground();
    void SetCalibration ();

    bool BackgroundAddedToMainPlot = false;

    void ShowErrorMessage(QString Description, QString Advice);

    void ConnectObjects();

    void UploadFile();

    // Индикатор выполнения
    //QProgressBar * ProgressBar;


    int azim=0;
    int elev=0;


    int CurrentPlotIndex=0;

/*
protected:
    void showEvent(QShowEvent *event) override;
    //void CalculateDistancePortrait();
*/

public slots:
    //void TellPlotTabsToChangeAngle(QVector <std::complex<double>> NeededRowFromThreeDimensionalVector); //

    void HandleReceivedMeasuredFreqVector( QVector <double> ReceivedVector);

    void GetPlotFromDat();

signals:
    void ErrorOccured(QString ErrorText);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

