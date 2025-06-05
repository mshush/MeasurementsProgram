#include "tabwidgetforparameters.h"

TabWidgetForParameters::TabWidgetForParameters(QWidget *parent) : QTabWidget(parent)
{
    //this->setMaximumWidth(300);
    //this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->setMaximumWidth(300);
    MeasurementTab = new CustomMeasurementTreeWidget();
    ProcessingTab  = new CustomProcessingTreeWidget();
    //FileTreeTab = new TreeWidgetForFiles();

    addTab(MeasurementTab, "Setup");
    addTab(ProcessingTab, "Processing");
    //addTab(FileTreeTab, "Навигация");
}



TabWidgetForParameters::~TabWidgetForParameters()
{
    /*
    delete Tab1;
    //delete Tab2;
    delete Tab3;
    */
}
