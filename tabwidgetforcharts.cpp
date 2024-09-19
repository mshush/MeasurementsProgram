#include "tabwidgetforcharts.h"

TabWidgetForCharts::TabWidgetForCharts()

{
    //ChartTabBar = new QTabBar(this);
    //AddMeasuredTabs();

    MeasurementPlotTab = new WidgetForCustomPlot(this);
    addTab(MeasurementPlotTab,"Текущее измерение");
    PlotTabs.push_back(MeasurementPlotTab);

    TimeOfFlightPlotTab = new WidgetForCustomPlot(this);
    addTab(TimeOfFlightPlotTab,"Дальностный портрет");
    PlotTabs.push_back(TimeOfFlightPlotTab);

    //setTabsClosable(true); Можно было так.
    //this->setTabsMovable(true);

    this->setTabToolTip(0, "Вкладка по умолчанию, на которую влияют кнопки запуска и непрерывного измерения");


}

/*
void TabWidgetForCharts::CreateNewTabFromImportedData()
{

    QString FilePath = QFileDialog::getOpenFileName(this, "Select File to Load", QDir::homePath(), "Data Files (*.dat)");

    QFile File(FilePath);
    if (!File.open(QIODevice::ReadOnly)) {
        qWarning() << "Не получилось открыть файл для записи: " << File.errorString();
        return;
    }

    WidgetForCustomPlot * PlotTab = new WidgetForCustomPlot(this);

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
*/






/*
void TabWidgetForCharts::SetFrequencyParameters(double StartFreq, double StopFreq, int NumberOfPoints)
{
    QVector <double> xTemp(NumberOfPoints);
    for (int i=0; i<NumberOfPoints; i++)
    {
        xTemp[i] = StartFreq + i * (StopFreq-StartFreq)/(NumberOfPoints-1);
    }
    this->PlotTabs[0]->customPlot->x = xTemp;
}
*/

/*
void TabWidgetForCharts::SaveData() // Добавить формат CSV. // Перенесено в PlotClass
{
    QString DateString = QDate::currentDate().toString("yyyy-MM-dd");
    QString TimeString = QTime::currentTime().toString("HH-mm");

    QString NameOfSavedFile = "Измерение_" + DateString + "_" + TimeString;

    //QString SaveDirectory = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
    QString Path = QDir::homePath() + "/" + NameOfSavedFile + ".dat";
    //qDebug()<< "Путь = " + Path + ", Индекс = " + QString::number(currentIndex());
    QString FilePath = QFileDialog::getSaveFileName(this, "Save File", Path, "Data Files (*.dat);;All Files (*)");

    QFile File(FilePath);
    if (!File.open(QIODevice::WriteOnly)) {
        qWarning() << "Не получилось открыть файл для записи:" << File.errorString();
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
*/


/*
void TabWidgetForCharts::UpdateMeasurementPlot(QVector <std::complex<double>> f)
{
    PlotTabs[0]->customPlot->UpdateMeasuredData(f);
    PlotTabs[1]->customPlot->UpdateMeasuredData(PlotTabs[1]->customPlot->FourierTransformVector(f));

    //------------ Устаревшая часть
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
    //----------------
}
*/



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


void TabWidgetForCharts::ContinuousMeasurementModeChanged()
{
    PlotTabs[0]->customPlot->ContinuousMeasurementMode = dynamic_cast<QPushButton*>(sender())->isChecked();
}







TabWidgetForCharts::~TabWidgetForCharts()
{
    /*
    qDeleteAll(PlotTabs);
    PlotTabs.clear();
    */
}

/*
void TabWidgetForCharts::PerformFourierTransformOfCurrentPlot()
{
    PlotClass * CurrentPlot = PlotTabs[currentIndex()]->customPlot;
    QVector <std::complex<double>> F = CurrentPlot->f;
    QVector <std::complex<double>> Transform(F.size());
    QString TabName = tabText(currentIndex());
    int N = F.size();

    for (int i=0;i<N;i++)
    {
        Transform[i] = 0;
        for (int j=0;j<N;j++)
        {
            Transform[i] += F[j] * exp( - std::complex<double>(0, 2 * M_PI * j * i / N));
        }
        Transform[i]/=N;
    }

    WidgetForCustomPlot * NewTab = new WidgetForCustomPlot(this);
    PlotTabs.append(NewTab);
    addTab(NewTab, "F(" + TabName + ")");
    InitiateCloseTabButton();

    NewTab->customPlot->UpdateMeasuredData(Transform);
    NewTab->customPlot->rescaleAxes();
    NewTab->customPlot->replot();
}
*/


/*
void TabWidgetForCharts::PerformInverseFourierTransformOfCurrentPlot()
{
    PlotClass * CurrentPlot = PlotTabs[currentIndex()]->customPlot;
    QVector <std::complex<double>> Transform = CurrentPlot->f;
    QVector <std::complex<double>> F(Transform.size());
    QString TabName = tabText(currentIndex());
    int N = F.size();

    for (int i=0;i<N;i++)
    {
        F[i] = 0;
        for (int j=0;j<N;j++)
        {
            F[i] += Transform[j] * exp( std::complex<double>(0, 2 * M_PI * j * i / N));
        }
    }

    WidgetForCustomPlot * NewTab = new WidgetForCustomPlot(this);
    PlotTabs.append(NewTab);
    addTab(NewTab, "InvF(" + TabName + ")");
    InitiateCloseTabButton();

    NewTab->customPlot->UpdateMeasuredData(F);
    NewTab->customPlot->rescaleAxes();
    NewTab->customPlot->replot();
}
*/



/*
void TabWidgetForCharts::ChangeDemonstratedAngles() // В MainWindow
{

}
*/



