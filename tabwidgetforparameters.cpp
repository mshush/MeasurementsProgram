#include "tabwidgetforparameters.h"

TabWidgetForParameters::TabWidgetForParameters(QWidget *parent) : QTabWidget(parent)
{
    MeasurementTab = new MeasurementsParametersWidget();
    ResultTab = new ResultParametersWidget();
    FileTreeTab = new TreeWidgetForFiles();

    addTab(MeasurementTab, "Измерение");
    addTab(ResultTab, "Результат");
    addTab(FileTreeTab, "Открыть");

    setFixedWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}




TabWidgetForParameters::~TabWidgetForParameters()
{
    /*
    delete Tab1;
    //delete Tab2;
    delete Tab3;
    */
}
