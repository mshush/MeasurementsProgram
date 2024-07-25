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
    QPushButton * MarkerAddButton;
    QPushButton * MarkerDeleteButton;
    QPushButton * DeleteAllMarkersButton;


};

#endif // WIDGETFORCUSTOMPLOT_H
