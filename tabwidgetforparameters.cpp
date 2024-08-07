#include "tabwidgetforparameters.h"

TabWidgetForParameters::TabWidgetForParameters(QWidget *parent) : QTabWidget(parent)
{
    Tab1 = new MeasurementsParametersWidget();
    //Tab2 = new ProcessingParametersWidget();
    Tab3 = new TreeWidgetForFiles();

    addTab(Tab1, "Измерение");
    //addTab(Tab2, "Обработка");
    addTab(Tab3, "Открыть");

    resize(200,500);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}




TabWidgetForParameters::~TabWidgetForParameters()
{
    delete Tab1;
    //delete Tab2;
    delete Tab3;
    delete StartFrequencyLineEdit;
    delete StopFrequencyLineEdit;
}
