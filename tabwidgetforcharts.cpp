#include "tabwidgetforcharts.h"

TabWidgetForCharts::TabWidgetForCharts()

{


    this->setFixedHeight(560);

    for (int i=0;i<9;i++)
    {
        WidgetForCustomPlot * TempTab = new WidgetForCustomPlot(this);
        TempTab->customPlot->xAxis->setLabel("N");
        addTab(TempTab,"Tab" + QString::number(i));
        PlotTabs.push_back(TempTab);
        TempTab->customPlot->addGraph();
        TempTab->customPlot->addGraph();
        TempTab->customPlot->addGraph();
    }

    this->setTabText(0, "CASweep");
    this->setTabText(1, "RTSweep");
    this->setTabText(2, "RBSweep");
    this->setTabText(3, "RRSweep");
    this->setTabText(4, "ClbrSweep");
    this->setTabText(5, "PttrnSweep");
    this->setTabText(6, "CurrentAspect");
    this->setTabText(7, "Current(Gated)ProfRangeVector");
    this->setTabText(8, "От угла");

    PrintPreviewTab = new PrintPreview(this);
    addTab(PrintPreviewTab,"Print Preview");


    connect(this, &TabWidgetForCharts::currentChanged, this, &TabWidgetForCharts::SendImagesIfPrintPreview);

    //connect(PrintPreviewTab->PatternBox, &QCheckBox::toggled, PlotTabs[0], PlotClass::SendPlotImageForPreview);




    /*
    SweepTab = new WidgetForCustomPlot(this);
    SweepTab->customPlot->xAxis->setLabel("Frequency (GHz)");
    SweepTab->XRangeUnitsLabel->setText("GHz");
    addTab(SweepTab,"Sweep");
    PlotTabs.push_back(SweepTab);
    SweepTab->customPlot->addGraph();


    ProfRangeTab = new WidgetForCustomPlot(this);
    ProfRangeTab->customPlot->xAxis->setLabel("Delay (m)");
    ProfRangeTab->XRangeUnitsLabel->setText("m");
    addTab(ProfRangeTab,"Prof Range");
    PlotTabs.push_back(ProfRangeTab);
    ProfRangeTab->customPlot->addGraph();
    ProfRangeTab->customPlot->addGraph();

    GatedProfileTab = new WidgetForCustomPlot(this);
    GatedProfileTab->customPlot->xAxis->setLabel("Delay (m)");
    GatedProfileTab->XRangeUnitsLabel->setText("m");
    addTab(GatedProfileTab,"Gated Profile");
    PlotTabs.push_back(GatedProfileTab);



    PatternTab = new WidgetForCustomPlot(this);
    PatternTab->customPlot->xAxis->setLabel("Az (deg)");
    PatternTab->XRangeUnitsLabel->setText("deg");
    addTab(PatternTab,"Pattern");
    PlotTabs.push_back(PatternTab);
    */
    //PrintPreviewTab = new PrintPreview(this);
    //addTab(PrintPreviewTab, "Print Preview");

    //connect(PrintPreviewTab->PreviewButton, &QPushButton::clicked, this, &TabWidgetForCharts::ShowPrintPreview);



    /*
    MeasurementPlotTabFrequency = new WidgetForCustomPlot(this);
    addTab(MeasurementPlotTabFrequency,"Preview");
    PlotTabs.push_back(MeasurementPlotTabFrequency);


    MeasurementPlotTabAngle = new WidgetForCustomPlot(this);
    MeasurementPlotTabAngle->customPlot->xAxis->setLabel("Угол поворота, градусы");
    MeasurementPlotTabAngle->XRangeUnitsLabel->setText("град");
    addTab(MeasurementPlotTabAngle,"Pattern");
    PlotTabs.push_back(MeasurementPlotTabAngle);


    TimeOfFlightPlotTab = new WidgetForCustomPlot(this);
    TimeOfFlightPlotTab->customPlot->xAxis->setLabel("Расстояние, м");
    TimeOfFlightPlotTab->XRangeUnitsLabel->setText("м");
    addTab(TimeOfFlightPlotTab,"Down-range");
    PlotTabs.push_back(TimeOfFlightPlotTab);



    CrossRangeTab = new WidgetForCustomPlot(this);
    addTab(CrossRangeTab,"Cross-range");
    PlotTabs.push_back(CrossRangeTab);


    ColorMapTab = new WidgetForCustomPlot(this);
    addTab(ColorMapTab,"Color map");
    PlotTabs.push_back(ColorMapTab);


    StatisticaTab = new WidgetForCustomPlot(this);
    addTab(StatisticaTab,"Statistica");
    PlotTabs.push_back(StatisticaTab);


    FrequencyTab = new WidgetForCustomPlot(this);
    addTab(FrequencyTab,"Frequency");
    PlotTabs.push_back(FrequencyTab);


    ScriptEditorTab = new WidgetForCustomPlot(this);
    addTab(ScriptEditorTab,"Script Editor");
    PlotTabs.push_back(ScriptEditorTab);


    PrintPreviewTab = new WidgetForCustomPlot(this);
    addTab(PrintPreviewTab,"Print Preview");
    PlotTabs.push_back(PrintPreviewTab);
    */





    //this->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    // Добавить окно с предпросмотром сохраняемого изображения.
    //qDebug()<<"PlotWindowSize = " << this->size();

    //setTabsClosable(true); Можно было так.
    //this->setTabsMovable(true);

    //this->setTabToolTip(0, "Вкладка по умолчанию, на которую влияют кнопки запуска и непрерывного измерения");


    SendImagesIfPrintPreview(PlotTabs.size());
}



void TabWidgetForCharts::SendImagesIfPrintPreview(int TabIndex)
{


    if (TabIndex == PlotTabs.size())
    {
        QVector <QImage> VectorOfPlotImages;

        for (int i=0;i<PlotTabs.size();i++)
        {
            PlotClass * customPlot = PlotTabs[i]->customPlot;
            QPixmap PlotPixmap = customPlot->toPixmap();
            QImage PlotImage = PlotPixmap.toImage();
            VectorOfPlotImages.append(PlotImage);
        }
        PrintPreviewTab->VectorOfPlotImages = VectorOfPlotImages;
        qDebug()<<"Sent";
    }

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

    /*
    ////connect(TempCloseButton, &QPushButton::clicked, this, [TempTabPtr,this]()
            {
                removeTab(indexOf(TempTabPtr));
            }
            );
    */
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

/*
void TabWidgetForCharts::ShowPrintPreview()
{
    QPainter Painter(this->PrintPreviewTab->Printer);
    PlotTabs[0]->customPlot->render(&Painter);
    PrintPreviewTab->PrintPreviewWidget->setVisible(true);
}
*/
