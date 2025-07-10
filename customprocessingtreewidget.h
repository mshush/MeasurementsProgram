#ifndef CUSTOMPROCESSINGTREEWIDGET_H
#define CUSTOMPROCESSINGTREEWIDGET_H

#include <QTreeWidget>
#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QtWidgets>

class CustomProcessingTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    CustomProcessingTreeWidget();

    // Окошки для параметров (12 разделов)
    //Таблицы
    QTableWidget * AzimuthScale;
    QTableWidget * AzimuthOffset;
    QTableWidget * ZOffset;

    QTableWidget * FrequencyProcessingSubrange;
    QTableWidget * AngularProcessingSubrange;
    QTableWidget * StatisticaSubrange;

    QTableWidget * WindowDR;
    QTableWidget * WindowCR;
    QTableWidget * Gate;

    QTableWidget * ImageSubrange;
    QTableWidget * ISARParameters;
    QTableWidget * Sketch;


    //items
    QTreeWidgetItem * AzimuthScaleItem;
    QTreeWidgetItem * AzimuthOffsetItem;
    QTreeWidgetItem * ZOffsetItem;

    QTreeWidgetItem * FrequencyProcessingSubrangeItem;
    QTreeWidgetItem * AngularProcessingSubrangeItem;
    QTreeWidgetItem * StatisticaSubrangeItem;

    QTreeWidgetItem * WindowDRItem;
    QTreeWidgetItem * WindowCRItem;
    QTreeWidgetItem * GateItem;

    QTreeWidgetItem * ImageSubrangeItem;
    QTreeWidgetItem * ISARParametersItem;
    QTreeWidgetItem * SketchItem;


    // Функции заполнения таблиц
    void FillAzimuthScale();
    void FillAzimuthOffset();
    void FillZOffset();

    void FillFrequencyProcessingSubrange();
    void FillAngularProcessingSubrange();
    void FillStatisticaSubrange();

    void FillWindowDR();
    void FillWindowCR();
    void FillGate();

    void FillImageSubrange();
    void FillISARParameters();
    void FillSketch();




    // Вводимые параметры



























};

#endif // CUSTOMPROCESSINGTREEWIDGET_H
