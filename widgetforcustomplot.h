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
    QColor MarkerColour = Qt::black;
    //Окно с настройкой внешнего вида маркера
    QDialog * MarkerSettingsDialogue;
    QDialogButtonBox * MarkerSettingsDialogueButtonBox;
    QComboBox * MarkerTypeComboBox;
    QPushButton * MarkerColourButton;

    QVBoxLayout * MarkerSettingsDialogueLayout;

public slots:
    void OpenMarkerSettings();
    void OpenMarkerColourDialogue();
    void ChangeMarkerType(int TypeIndex);
};

#endif // WIDGETFORCUSTOMPLOT_H
