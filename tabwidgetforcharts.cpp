#include "tabwidgetforcharts.h"

TabWidgetForCharts::TabWidgetForCharts()

{
    //ChartTabBar = new QTabBar(this);


    AddMeasuredTabs();
    /*
    WidgetForCustomPlot * PlotTab = new WidgetForCustomPlot;
    addTab(PlotTab,"График" +QString::number(this->count()+1));
    PlotTabs.push_back(PlotTab);
    */

    //ChartTab = new WidgetForChart;
    //addTab(ChartTab,"График 2");

    /*
    QWidget * Tab2 = new QWidget;
    addTab(Tab2,"График 2");
    QWidget * Tab3 = new QWidget;
    addTab(Tab3,"График 3");
    */

    /*
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
    */
}


void TabWidgetForCharts::CreateNewTabFromImportedData()
{

    QString FilePath = QFileDialog::getOpenFileName(this, "Select File to Load", QDir::homePath(), "Data Files (*.dat)");

    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Не получилось открыть файл для записи: " << File.errorString();
        return;
    }

    WidgetForCustomPlot * PlotTab = new WidgetForCustomPlot;

    QFileInfo FileInfo(FilePath);
    addTab(PlotTab, FileInfo.baseName());

    this->setTabToolTip(this->count()-1, FilePath);

    PlotTabs.push_back(PlotTab);
    PlotClass * TempPlotPtr = PlotTab->customPlot;


    QVector <double> MarkerKeys;
    QVector <int> MarkerStyles;
    QVector <QColor> MarkerColours;

    QVector <double> f_real(1601);
    QVector <double> f_imag(1601);


    QDataStream in(&File);
    in >> TempPlotPtr->x >> TempPlotPtr->y >> f_real >> f_imag >> MarkerKeys >> MarkerStyles >> MarkerColours;
    File.close();

    for (int i=0;i<1601;i++)
    {
        TempPlotPtr->f[i] = std::complex<double>(f_real[i],f_imag[i]);
    }

    for (int m=0; m<MarkerKeys.size(); m++)
    {
        TempPlotPtr->AddNewMarker(MarkerKeys[m], MarkerStyles[m], MarkerColours[m]);
    }

    TempPlotPtr->graph(0)->setData(TempPlotPtr->x, TempPlotPtr->y);

    TempPlotPtr->rescaleAxes();
    TempPlotPtr->replot();

    InitiateCloseTabButton();
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


void TabWidgetForCharts::SaveData()
{
    //QString SaveDirectory = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());


    QString Path = QDir::homePath() + "/" + QString(tabToolTip(currentIndex())) + ".dat";
    qDebug()<< "Путь = " + Path + ", Индекс = " + QString::number(currentIndex());
    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", Path, "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly)) {
        qWarning() << "Не получилось открыть файл для чтения:" << File.errorString();
        return;
    }

    PlotClass * CurrentPlot = PlotTabs[currentIndex()]->customPlot;

    QVector <double> f_real(1601);
    QVector <double> f_imag(1601);

    for (int i=0;i<1601;i++)
    {
        f_real[i] = CurrentPlot->f[i].real();
        f_imag[i] = CurrentPlot->f[i].imag();
    }


    QVector <double> MarkerKeys;
    QVector <int> MarkerStyles;
    QVector <QColor> MarkerColours;


    for (QCPItemTracer * Marker : CurrentPlot->AddedMarkersList)
    {
        MarkerKeys.push_back(Marker->graphKey());
        MarkerStyles.push_back(Marker->style());
        MarkerColours.push_back(Marker->pen().color());
    }

    QDataStream out(&File);
    out << CurrentPlot->x << CurrentPlot->y << f_real << f_imag << MarkerKeys << MarkerStyles <<MarkerColours;
    File.close();

}




void TabWidgetForCharts::AddMeasuredTabs()
{

    QString DateString = QDate::currentDate().toString("yyyy-MM-dd");
    QString TimeString = QTime::currentTime().toString("HH-mm");


    WidgetForCustomPlot * NewPlotTab = new WidgetForCustomPlot;
    addTab(NewPlotTab, "Результат измерений");
    PlotTabs.push_back(NewPlotTab);

    this->setTabToolTip(count()-1, "Результат_измерений_" + DateString + "_" + TimeString);

    InitiateCloseTabButton();

    WidgetForCustomPlot * NewPlotTabF = new WidgetForCustomPlot;
    NewPlotTabF->customPlot->f = NewPlotTab->customPlot->f;
    NewPlotTabF->customPlot->FourierTransform();
    addTab(NewPlotTabF,"Дальностный портрет");
    PlotTabs.push_back(NewPlotTabF);

    this->setTabToolTip(count()-1, "Дальностный_портрет_" + DateString + "_" + TimeString);

    InitiateCloseTabButton();
}


void TabWidgetForCharts::InitiateCloseTabButton()
{

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


TabWidgetForCharts::~TabWidgetForCharts()
{
    qDeleteAll(PlotTabs);
    PlotTabs.clear();
}




