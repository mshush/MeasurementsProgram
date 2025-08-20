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
#include <widgetforcustomplot.h>
#include <legendwidget.h>

class TabWidgetForTools : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForTools();
    ~TabWidgetForTools();

    // Вкладки
    WidgetForCustomPlot * PatternTab; // Дублирует Pattern
    QTreeWidget * MessagesTab; // Сообщения
    LegendWidget * LegendTab; // Легенда
    QWidget * ScriptTab; // Скрипт
    TreeWidgetForFiles * File_ManagerTab; // Файловый менеджер
    QTreeWidget * DebugMessagesTab; // Сообщения для разработчика

    // Функции из конструктора
    void SetUpGeneralStyle();
    void SetUpPatternTab();
    void FillMessagesTab();
    void SetUpLegendTab();
    void SetUpFilesManagerTab();
    void FillDebugMessagesTab();

    void UpdateText();




    //void setContentsMarginsToZero(QWidget *widget);

signals:


public slots:


};

#endif // TABWIDGETFORTOOLS_H




















// Устаревшее
//void DisplayError(QString ErrorText);

//void ContinuousMeasurementsButtonClickedSignal(bool CheckedStatus);
//void ErrorOccured(QString ErrorText);
//void SendContinuousMeasurementsButtonClickedSignal();
//QPushButton * StartMeasurementsButton;
//QPushButton * StopMeasurementsButton;
//QPushButton * ContinuousMeasurementsButton;

//QPushButton * SaveDataButton;
//QPushButton * ImportDataButton;

//QPushButton * FourierTransformButton;
//QPushButton * InverseFourierTransformButton;

//QPushButton * SaveThreeDimensionalVectorButton;
//QPushButton * GetPlotDataButton;
