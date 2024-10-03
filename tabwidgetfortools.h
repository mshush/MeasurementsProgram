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

class TabWidgetForTools : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForTools();
    ~TabWidgetForTools();

    QWidget * PatternTab;
    QWidget * MessagesTab;
    QWidget * LegendTab;
    TreeWidgetForFiles * File_ManagerTab;
    QTableWidget * Debug_MessagesTab;


    QPushButton * StartMeasurementsButton;
    QPushButton * StopMeasurementsButton;
    QPushButton * ContinuousMeasurementsButton;

    //QPushButton * SaveDataButton;
    //QPushButton * ImportDataButton;

    //QPushButton * FourierTransformButton;
    //QPushButton * InverseFourierTransformButton;

    QPushButton * SaveMeasuredFunctionButton;
    QPushButton * GetPlotDataButton;




signals:
    void ContinuousMeasurementsButtonClickedSignal(bool CheckedStatus);
    void ErrorOccured(QString ErrorText);

public slots:
    void SendContinuousMeasurementsButtonClickedSignal();
    void DisplayError(QString ErrorText);

};

#endif // TABWIDGETFORTOOLS_H
