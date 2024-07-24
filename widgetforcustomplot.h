#ifndef WIDGETFORCUSTOMPLOT_H
#define WIDGETFORCUSTOMPLOT_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <QFileDialog>

class WidgetForCustomPlot : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetForCustomPlot(QWidget *parent = nullptr);

    QCustomPlot * customPlot;
    QWidget * ControlsWidget;
    QHBoxLayout * HorizontalPlotLayout;
    QVBoxLayout * VerticalControlsLayout;
    QPushButton * ResetButton;
    QPushButton * SaveButton;
public slots:
    void SavePlot();
};

#endif // WIDGETFORCUSTOMPLOT_H
