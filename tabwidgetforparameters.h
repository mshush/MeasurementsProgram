#ifndef TABWIDGETFORPARAMETERS_H
#define TABWIDGETFORPARAMETERS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <measurementsparameterswidget.h>
#include <QLineEdit>
#include <treewidgetforfiles.h>
#include <resultparameterswidget.h>

class TabWidgetForParameters : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForParameters(QWidget *parent = nullptr);
    ~TabWidgetForParameters();

    MeasurementsParametersWidget * MeasurementTab;
    ResultParametersWidget * ResultTab;
    TreeWidgetForFiles * FileTreeTab;
};

#endif // TABWIDGETFORPARAMETERS_H
