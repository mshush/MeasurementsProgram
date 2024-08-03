#include "tabwidgetforcharts.h"

TabWidgetForCharts::TabWidgetForCharts()

{
    //ChartTabBar = new QTabBar(this);


    WidgetForCustomPlot * PlotTab = new WidgetForCustomPlot;
    addTab(PlotTab,"График" +QString::number(this->count()+1));
    PlotTabs.push_back(PlotTab);

    //ChartTab = new WidgetForChart;
    //addTab(ChartTab,"График 2");

    /*
    QWidget * Tab2 = new QWidget;
    addTab(Tab2,"График 2");
    QWidget * Tab3 = new QWidget;
    addTab(Tab3,"График 3");
    */


    QPushButton* TempCloseButton = new QPushButton("X");

    TempCloseButton->setStyleSheet("QPushButton {"
                                   "background-color: #FF6F61;"
                                   "color: white;"
                                   "border-radius: 0px;" // Adjust the value to make it more circular
                                   "width: 15px;"
                                   "height: 15px;"
                                   "}");
    TempCloseButton->setFixedSize(15,15);

    tabBar()->setTabButton(0, QTabBar::RightSide, TempCloseButton);

    QWidget * TempTabPtr = this->widget(0);

    connect(TempCloseButton, &QPushButton::clicked, this, [TempTabPtr,this]()
            {
                removeTab(indexOf(TempTabPtr));
            }
            );

    this->setTabToolTip(0, "Вкладка по умолчанию, на которую влияют кнопки запуска и непрерывного измерения");

}


void TabWidgetForCharts::CreateNewTabFromImportedData()
{

    QString FilePath = QFileDialog::getOpenFileName(this, "Select File to Load", QDir::homePath(), "Data Files (*.dat)");

    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << File.errorString();
    }

    WidgetForCustomPlot * PlotTab = new WidgetForCustomPlot;

    QFileInfo FileInfo(FilePath);
    addTab(PlotTab, FileInfo.fileName());

    this->setTabToolTip(this->count()-1, FilePath);

    PlotTabs.push_back(PlotTab);
    PlotClass * TempPlotPtr = PlotTab->customPlot;


    QDataStream in(&File);
    in >> TempPlotPtr->x >> TempPlotPtr->y;
    File.close();

    TempPlotPtr->graph(0)->setData(TempPlotPtr->x, TempPlotPtr->y);
    TempPlotPtr->rescaleAxes();
    TempPlotPtr->replot();




    QPushButton* TempCloseButton = new QPushButton("X");

    TempCloseButton->setStyleSheet("QPushButton {"
                                   "background-color: #FF6F61;"
                                   "color: white;"
                                   "border-radius: 0px;" // Adjust the value to make it more circular
                                   "width: 15px;"
                                   "height: 15px;"
                                   "}");
    TempCloseButton->setFixedSize(15,15);

    tabBar()->setTabButton(this->count()-1, QTabBar::RightSide, TempCloseButton);

    QWidget * TempTabPtr = this->widget(this->count()-1);

    connect(TempCloseButton, &QPushButton::clicked, this, [TempTabPtr,this]()
            {
                removeTab(indexOf(TempTabPtr));
            }
            );
}








void TabWidgetForCharts::SetStartStopFrequencies(double StartFreq, double StopFreq)
{

    QVector <double> xTemp(1601);
    for (int i=0; i<1601; i++)
    {
        xTemp[i] = StartFreq + i * (StopFreq-StartFreq)/1600;
    }
    this->PlotTabs[0]->customPlot->x = xTemp;

}










