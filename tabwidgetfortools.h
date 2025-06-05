#ifndef TABWIDGETFORTOOLS_H
#define TABWIDGETFORTOOLS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>
#include <QIcon>
#include <QProgressBar>
#include <treewidgetforfiles.h>
#include <widgetforcustomplot.h>>

class TabWidgetForTools : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForTools();
    ~TabWidgetForTools();

    WidgetForCustomPlot * PatternTab;
    QTreeWidget * MessagesTab;
    QTableWidget * LegendTab;
    QWidget * ScriptTab;
    TreeWidgetForFiles * File_ManagerTab;
    QTreeWidget * DebugMessagesTab;


    QPushButton * StartMeasurementsButton;
    QPushButton * StopMeasurementsButton;
    QPushButton * ContinuousMeasurementsButton;

    //QPushButton * SaveDataButton;
    //QPushButton * ImportDataButton;

    //QPushButton * FourierTransformButton;
    //QPushButton * InverseFourierTransformButton;

    QPushButton * SaveThreeDimensionalVectorButton;
    QPushButton * GetPlotDataButton;

    void FillDebugMessagesTab();

    void setContentsMarginsToZero(QWidget *widget);


signals:
    void ContinuousMeasurementsButtonClickedSignal(bool CheckedStatus);
    void ErrorOccured(QString ErrorText);

public slots:
    void SendContinuousMeasurementsButtonClickedSignal();
    void DisplayError(QString ErrorText);

};

#endif // TABWIDGETFORTOOLS_H
