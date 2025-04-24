#ifndef CUSTOMMEASUREMENTTREEWIDGET_H
#define CUSTOMMEASUREMENTTREEWIDGET_H


#include <QObject>
#include <QTreeWidget>
#include <QWidget>
#include <QTableWidget>

#include "qcheckbox.h"
#include "qcombobox.h"
#include "qheaderview.h"
#include "qlineedit.h"
#include "qpushbutton.h"


class CustomMeasurementTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    CustomMeasurementTreeWidget(QWidget *parent = nullptr);

    // Окошки для параметров (9 разделов)

    QTableWidget * Navigator;
    QTableWidget * Summary;
    QTableWidget * Configs;

    QTableWidget * Files;
    QTableWidget * FrequencyRange;
    QTableWidget * AzimuthRange;

    QTableWidget * Pre_ProcessingGate;
    QTableWidget * CalibrationTarget;
    QTableWidget * PNA;


    QTreeWidgetItem * NavigatorItem;
    QTreeWidgetItem * SummaryItem;
    QTreeWidgetItem * ConfigsItem;

    QTreeWidgetItem * FilesItem;
    QTreeWidgetItem * FrequencyRangeItem;
    QTreeWidgetItem * AzimuthRangeItem;

    QTreeWidgetItem * Pre_ProcessingGateItem;
    QTreeWidgetItem * CalibrationTargetItem;
    QTreeWidgetItem * PNAItem;


    void FillNavigator();
    void FillSummary();
    void FillConfigs();

    void FillFiles();
    void FillFrequencyRange();
    void FillAzimuthRange();

    void FillPre_ProcessingGate();
    void FillCalibrationTarget();
    void FillPNA();



    // Вводимые параметры


    const std::pair<double, double> FrequencyRanges[6] =  {
                                                          {3.25,  1.35},   //S
                                                          {4.9,  1.9},     //C
                                                          {7.0,  2.4},     //C2
                                                          {10.3,  4.2},    //X
                                                          {15.2, 5.6},     //Ku
                                                          {15.2, 5.6}      //Ka Почему такое же, как Ku??? Почему можно менять???
                                                          };


    const int IFValues[6] = {
                                10,
                                100,
                                1000,
                                3000,
                                10000,
                                35000
                            };

    double FrequencyStart = 1;
    double FrequencyStop = 2;
    int FrequencyNumber = 1601;

    double AzimuthStart = 0;
    double AzimuthStop = 359;
    int AzimuthNumber = 360;

    double ElevationStart = 0;
    double ElevationStop = 9;
    int ElevationNumber = 10;



    // Используемые виджеты:


    QComboBox * ConfigsRangeComboBox;

    QLineEdit * FrequencyRangeCenterEdit;
    QLineEdit * FrequencyRangeSpanEdit;
    QLineEdit * FrequencyRangeNEdit;

    QLineEdit * AzimuthRangeCenterEdit;
    QLineEdit * AzimuthRangeSpanEdit;
    QLineEdit * AzimuthRangeNEdit;
    QCheckBox * AzimuthRangeDefaultNCheckBox;

    QLineEdit * ElevationRangeCenterEdit;
    QLineEdit * ElevationRangeSpanEdit;
    QLineEdit * ElevationRangeNEdit;
    QCheckBox * ElevationRangeDefaultNCheckBox;

    QLineEdit * PNAGeneratorEdit;
    QComboBox * PNAIFBox;

    QLineEdit * Pre_ProcessingGateStartEdit;
    QLineEdit * Pre_ProcessingGateStopEdit;
    QComboBox * Pre_ProcessingGateShapeBox;



    // Слоты:
    public slots:

    void FrequencyRangeChanged(int index);






















};

#endif // CUSTOMMEASUREMENTTREEWIDGET_H
