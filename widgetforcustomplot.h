#ifndef WIDGETFORCUSTOMPLOT_H
#define WIDGETFORCUSTOMPLOT_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <QFileDialog>
#include <plotclass.h>
#include <map>

class WidgetForCustomPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForCustomPlot(QWidget *parent = nullptr);

    PlotClass * customPlot;
    QWidget * ControlsWidget;
    QVBoxLayout * VerticalPlotLayout;
    QHBoxLayout * HorizontalControlsLayout;
    QPushButton * ResetButton;
    QPushButton * SaveButton;

    //GroupBox для манипуляций с маркерами
    QGroupBox * MarkerManipulationGroupBox;
    QVBoxLayout * MarkerManipulationLayout;
    QHBoxLayout * MarkerStyleLayout;
    QHBoxLayout * MarkerAddDeleteLayout;
    QPushButton * MarkerAddButton;
    QPushButton * MarkerDeleteButton;
    QPushButton * DeleteAllMarkersButton;
    QPushButton * MarkerSettingsButton;
    QColor MarkerColourChoise = Qt::black;
    int MarkerStyleChoise = 3;

    //Окно с настройкой внешнего вида маркера
    QDialog * MarkerSettingsDialogue;
    QDialogButtonBox * MarkerSettingsDialogueButtonBox;
    QComboBox * MarkerStyleComboBox;
    QPushButton * MarkerColourButton;
    QVBoxLayout * MarkerSettingsDialogueLayout;
/*
    std::map<int, QCPItemTracer::TracerStyle> IndexToMarkerStyle =
        {
        {0, QCPItemTracer::TracerStyle::tsSquare},
        {1, QCPItemTracer::TracerStyle::tsCrosshair},
        {2, QCPItemTracer::TracerStyle::tsPlus},
        {3, QCPItemTracer::TracerStyle::tsCircle}
        };
*/

public slots:
    void OpenMarkerSettings();
    void OpenMarkerColourDialogue();
    void ChangeMarkerStyle();
};

#endif // WIDGETFORCUSTOMPLOT_H
