#ifndef TABWIDGETFORPARAMETERS_H
#define TABWIDGETFORPARAMETERS_H

#include <QObject>
#include <QTabWidget>
#include <QWidget>
#include <measurementsparameterswidget.h>
//#include <processingparameterswidget.h> // Пока не используется
#include <QLineEdit>
#include <treewidgetforfiles.h>


class TabWidgetForParameters : public QTabWidget
{
    Q_OBJECT
public:
    TabWidgetForParameters(QWidget *parent = nullptr);
    ~TabWidgetForParameters();

    MeasurementsParametersWidget * ParametersTab;
    //ProcessingParametersWidget * Tab2;
    TreeWidgetForFiles * FileTreeTab;
};

#endif // TABWIDGETFORPARAMETERS_H
