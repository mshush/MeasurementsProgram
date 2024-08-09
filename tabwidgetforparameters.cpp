#include "tabwidgetforparameters.h"

TabWidgetForParameters::TabWidgetForParameters(QWidget *parent) : QTabWidget(parent)
{
    ParametersTab = new MeasurementsParametersWidget();
    //Tab2 = new ProcessingParametersWidget();
    FileTreeTab = new TreeWidgetForFiles();

    addTab(ParametersTab, "Измерение");
    //addTab(Tab2, "Обработка");
    addTab(FileTreeTab, "Открыть");

    resize(200,500);
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
