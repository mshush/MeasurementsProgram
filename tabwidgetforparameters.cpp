#include "tabwidgetforparameters.h"

TabWidgetForParameters::TabWidgetForParameters(QWidget *parent) : QTabWidget(parent)
{
    this->setMaximumWidth(300);
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    MeasurementTab = new MeasurementsParametersWidget();
    ResultTab = new ResultParametersWidget();
    FileTreeTab = new TreeWidgetForFiles();

    addTab(MeasurementTab, "Измерение");
    addTab(ResultTab, "Результат");
    addTab(FileTreeTab, "Открыть");

}




TabWidgetForParameters::~TabWidgetForParameters()
{
    /*
    delete Tab1;
    //delete Tab2;
    delete Tab3;
    */
}
