#ifndef WIDGETFORCUSTOMPLOT_H
#define WIDGETFORCUSTOMPLOT_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <QFileDialog>
#include <plotclass.h>


class WidgetForCustomPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForCustomPlot(QWidget *parent = nullptr);

    PlotClass * customPlot;
    QWidget * ControlsWidget;
    QHBoxLayout * HorizontalPlotLayout;
    QVBoxLayout * VerticalControlsLayout;

    //Кнопки для сохранения
    void InitiateSaveLayout();
    QVBoxLayout * VerticalSaveLayout;
    QPushButton * SaveButton;
    QPushButton * CopyButton;




    //GroupBox для движения/приближения
    void InitiateMovementGroupBox();
    QGroupBox * MovementGroupBox;
    QVBoxLayout * MovementGroupBoxLayout;
    QHBoxLayout * LockAxesLayout;
    QPushButton * ResetButton;
    QPushButton * RubberBandButton;
    QPushButton * LockXAxisButton;
    QPushButton * LockYAxisButton;


    //GroupBox для манипуляций с маркерами
    void InitiateMarkerGroupBox();
    QGroupBox * MarkerGroupBox;
    QVBoxLayout * MarkerGroupBoxLayout;
    QHBoxLayout * MarkerStyleLayout;
    QHBoxLayout * MarkerAddDeleteLayout;
    QPushButton * MarkerAddButton;
    QPushButton * MarkerDeleteButton;
    QPushButton * DeleteAllMarkersButton;
    QPushButton * MarkerSettingsButton;
    QColor MarkerColourChoise = Qt::black;
    int MarkerStyleChoise = 0;
    QComboBox * MarkerStyleComboBox;
    QPushButton * MarkerColourButton;
    QColorDialog * ColourDialogue;
    void InitiateMarkerPreviewPlot();
    QCustomPlot * MarkerPreviewPlot;
    QCPItemTracer * PreviewMarker;

    //Окно с настройкой внешнего вида маркера
    //QDialog * MarkerSettingsDialogue;
    //QDialogButtonBox * MarkerSettingsDialogueButtonBox;

    //QVBoxLayout * MarkerSettingsDialogueLayout;
    //int MarkerStyleChoice;



public slots:
    void OpenMarkerColourDialogue();
    void ChangeMarkerStyle( int ComboIndex);
    //void DialogueResultAccepted();
    void ActivateRubberBand();
    void LockXAxis();
    void LockYAxis();
};

#endif // WIDGETFORCUSTOMPLOT_H
